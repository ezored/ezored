import Foundation
import UIKit

class TodoListViewController: BaseTableViewController, SimpleSearchBarProtocol {
    
    var listData: [EZRDomainTodo]?
    let cellIdentifier = "TodoTableViewCell"
    
    var searchBar = SimpleSearchBar()
    var searchText = ""
    
    override func createAll() {
        super.createAll()
        
        // register cell types
        tableView.register(TodoTableViewCell.self, forCellReuseIdentifier: cellIdentifier)
        tableView.estimatedRowHeight = 100
        tableView.separatorStyle = .none
        
        // search bar
        searchBar.delegate = self
        searchBar.frame = CGRect(x: 0, y: 0, width: view.frame.width, height: 70)
        tableView.tableHeaderView = searchBar
        
        // add some rows
        EZRDataServiceTodoDataService.truncate()
        
        for i in 1...100 {
            let todo = EZRDomainTodo(
                id: 0,
                title: String(format: "Title %i", i),
                body: String(format: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. %i", i),
                data: [:],
                done: false,
                createdAt: Date(),
                updatedAt: Date()
            )
            
            EZRDataServiceTodoDataService.add(todo)
        }
    }
    
    override func onLoadNewData() {
        super.onLoadNewData()
        
        if searchText.isEmpty {
            listData = EZRDataServiceTodoDataService.findAllOrderByCreatedAtDesc()
        } else {
            listData = EZRDataServiceTodoDataService.find(byTitle: searchText)
        }
        
        tableView.reloadData()
        
        remoteDataLoadState = .loaded
    }
    
    override func needLoadNewData() -> Bool {
        return true
    }
    
    override func onTableViewSelectedRow(tableView: UITableView, indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        if let todo = listData?[indexPath.row] {
            EZRDataServiceTodoDataService.setDoneById(todo.id, done: !todo.done)
            listData?[indexPath.row] = EZRDataServiceTodoDataService.find(byId: todo.id)
            tableView.reloadRows(at: [indexPath], with: .automatic)
        }
    }
    
    override func onTableViewCreateCell(tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier, for: indexPath) as! TodoTableViewCell
        
        if let todo = listData?[indexPath.row] {
            cell.bind(todo: todo, hasSeparator: (indexPath.row + 1 < listData?.count ?? 0))
            return cell
        }
        
        return UITableViewCell()
    }
    
    override func onTableViewGetNumberOfRows(tableView: UITableView, section: Int) -> Int {
        if let listData = listData {
            return listData.count
        }
        
        return 0
    }
    
    func simpleSearchBarBtResetClicked() {
        if remoteDataLoadState != .loading {
            remoteDataLoadState = .notLoaded
            searchText = ""
            validateLoadData()
        }
    }
    
    func simpleSearchBarSearch(typedText: String) {
        if remoteDataLoadState != .loading {
            remoteDataLoadState = .notLoaded
            searchText = typedText
            validateLoadData()
        }
    }
    
    override func getVCTitle() -> String {
        return "TitleListTodo".localized
    }
    
    override func getTitleForAnalytics() -> String {
        return "Todo List"
    }
    
}
