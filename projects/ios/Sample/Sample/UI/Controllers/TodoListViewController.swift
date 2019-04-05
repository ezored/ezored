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
    }
    
    override func onLoadNewData() {
        super.onLoadNewData()
        
        if searchText.isEmpty {
            listData = EZRDataServicesTodoDataService.findAllOrderByCreatedAtDesc()
        } else {
            listData = EZRDataServicesTodoDataService.find(byTitle: searchText)
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
            EZRDataServicesTodoDataService.setDoneById(todo.id, done: !todo.done)
            listData?[indexPath.row] = EZRDataServicesTodoDataService.find(byId: todo.id)
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
