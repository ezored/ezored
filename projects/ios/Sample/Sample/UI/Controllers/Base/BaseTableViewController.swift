import Foundation
import UIKit

class BaseTableViewController: BaseViewController, UITableViewDelegate, UITableViewDataSource {
    
    var tableView: UITableView!
    
    override func createAll() {
        super.createAll()
        
        // table view
        tableView = UITableView()
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.backgroundColor = UIColor.clear
        tableView.dataSource = self
        tableView.delegate = self
        view.addSubview(tableView)
    }
    
    override func layoutAll() {
        super.layoutAll()
        
        // table view
        view.addConstraint(NSLayoutConstraint(item: tableView, attribute: .centerX, relatedBy: .equal, toItem: view, attribute: .centerX, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: tableView, attribute: .centerY, relatedBy: .equal, toItem: view, attribute: .centerY, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: tableView, attribute: .width, relatedBy: .equal, toItem: view, attribute: .width, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: tableView, attribute: .height, relatedBy: .equal, toItem: view, attribute: .height, multiplier: 1.0, constant: 0.0))
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return onTableViewGetNumberOfRows(tableView: tableView, section: section)
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        return onTableViewCreateCell(tableView: tableView, indexPath: indexPath)
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return UITableView.automaticDimension
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        onTableViewSelectedRow(tableView: tableView, indexPath: indexPath)        
    }
    
    func tableView(_ tableView: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
        if indexPath.row > 0 && indexPath.row == onTableViewGetNumberOfRows(tableView: tableView, section: 0) - 1 {
            onTableViewReachLastItem(tableView: tableView, indexPath: indexPath)
        }
    }
    
    override func networkErrorViewProtocolOnAction(action: NetworkErrorViewAction) {
        super.networkErrorViewProtocolOnAction(action: action)
        
        if action == .refresh {
            if remoteDataLoadState != .loading {
                remoteDataLoadState = .notLoaded
            }
            
            loadData()
        }
    }
    
    override func viewWillAppear(_ animated: Bool) {
        if let selectedRows = tableView.indexPathForSelectedRow {
            tableView.deselectRow(at: selectedRows, animated: true)
        }
        
        super.viewWillAppear(true)
    }
    
    override func getVCTitle() -> String {
        return "BaseTableView"
    }
    
    // MARK: EVENTS
    
    func onTableViewCreateCell(tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
        // Will be implemented on child
        return UITableViewCell()
    }
    
    func onTableViewGetNumberOfRows(tableView: UITableView, section: Int) -> Int {
        // Will be implemented on child
        return 0
    }
    
    func onTableViewSelectedRow(tableView: UITableView, indexPath: IndexPath) {
        // Will be implemented on child
    }
    
    func onTableViewReachLastItem(tableView: UITableView, indexPath: IndexPath) {
        // Will be implemented on child
    }
    
    // MARK: CACHE
    
    override func onCacheExpired() {
        super.onCacheExpired()
        
        if remoteDataLoadState != .loading {
            remoteDataLoadState = .notLoaded
        }
        
        loadData()
    }
    
}

