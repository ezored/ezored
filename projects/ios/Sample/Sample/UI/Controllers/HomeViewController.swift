import UIKit

class HomeViewController: BaseTableViewController {
    var listData: [SimpleOption]?
    let cellIdentifier = "HomeOptionTableViewCell"

    override func createAll() {
        super.createAll()

        // register cell types
        tableView.register(SimpleOptionTableViewCell.self, forCellReuseIdentifier: cellIdentifier)
        tableView.estimatedRowHeight = 50
        tableView.separatorStyle = .none
    }

    override func onLoadNewData() {
        super.onLoadNewData()

        listData = []
        listData?.append(SimpleOption(type: .secretKey, hasSeparator: true))
        listData?.append(SimpleOption(type: .sharedData, hasSeparator: true))
        listData?.append(SimpleOption(type: .httpRequest, hasSeparator: true))
        listData?.append(SimpleOption(type: .httpsRequest, hasSeparator: true))
        listData?.append(SimpleOption(type: .fileHelper, hasSeparator: true))
        listData?.append(SimpleOption(type: .todo, hasSeparator: true))
        listData?.append(SimpleOption(type: .webServer, hasSeparator: true))
        listData?.append(SimpleOption(type: .webView, hasSeparator: false))
    }

    override func needLoadNewData() -> Bool {
        return true
    }

    override func onTableViewSelectedRow(tableView: UITableView, indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)

        if let option = listData?[indexPath.row] {
            if option.type == .sharedData {
                doActionSharedData()
            } else if option.type == .httpRequest {
                doActionHttpRequest()
            } else if option.type == .httpsRequest {
                doActionHttpsRequest()
            } else if option.type == .secretKey {
                doActionSecretKey()
            } else if option.type == .fileHelper {
                doActionFileHelper()
            } else if option.type == .todo {
                doActionTodo()
            } else if option.type == .webServer {
                doActionWebServer()
            } else if option.type == .webView {
                doActionWebView()
            }
        }
    }

    override func onTableViewCreateCell(tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier, for: indexPath) as! SimpleOptionTableViewCell

        if let option = listData?[indexPath.row] {
            cell.bind(option: option)
            return cell
        }

        return UITableViewCell()
    }

    override func onTableViewGetNumberOfRows(tableView _: UITableView, section _: Int) -> Int {
        if let listData = listData {
            return listData.count
        }

        return 0
    }

    override func getVCTitle() -> String {
        return "TitleHome".localized
    }

    override func getTitleForAnalytics() -> String {
        return "Home"
    }

    // MARK: Actions

    func doActionSharedData() {
        EZRHelperSharedDataHelper.setDemoFlag(!EZRHelperSharedDataHelper.getDemoFlag())
        tableView.reloadData()
    }

    func doActionFileHelper() {
        guard let core = EZRCoreApplicationCore.shared() else { return }

        let size = EZRFileHelper.getFileSize(EZRFileHelper.join(core.getInitializationData().basePath, second: "database.db3"))

        let message = String(format: "DialogDatabaseSizeMessage".localized, size, Double(size) / 1_048_576)
        UIUtil.showAlert(parent: self, title: "DialogTitle".localized, message: message, onClose: nil)
    }

    func doActionHttpRequest() {
        showLoadingView(show: true)

        DispatchQueue.global(qos: .background).async {
            var headers = [EZRHttpHeader]()
            headers.append(EZRHttpHeader(name: "Content-Type", value: "application/x-www-form-urlencoded"))

            var params = [EZRHttpRequestParam]()
            params.append(EZRHttpRequestParam(name: "username", value: "demo"))
            params.append(EZRHttpRequestParam(name: "password", value: "demo"))

            let request = EZRHttpRequest(url: "http://httpbin.org/post", method: .methodPost, params: params, headers: headers, body: "")
            let response = EZRHttpClient.shared()?.do(request)

            DispatchQueue.main.async {
                UIUtil.showAlert(parent: self, title: "DialogTitle".localized, message: String(format: "DialogHttpMessage".localized, request.url, response?.body ?? ""), onClose: nil)
                self.showMainView()
            }
        }
    }

    func doActionHttpsRequest() {
        showLoadingView(show: true)

        DispatchQueue.global(qos: .background).async {
            var headers = [EZRHttpHeader]()
            headers.append(EZRHttpHeader(name: "Content-Type", value: "application/x-www-form-urlencoded"))

            var params = [EZRHttpRequestParam]()
            params.append(EZRHttpRequestParam(name: "username", value: "demo"))
            params.append(EZRHttpRequestParam(name: "password", value: "demo"))

            let request = EZRHttpRequest(url: "https://httpbin.org/post", method: .methodPost, params: params, headers: headers, body: "")
            let response = EZRHttpClient.shared()?.do(request)

            DispatchQueue.main.async {
                UIUtil.showAlert(parent: self, title: "DialogTitle".localized, message: String(format: "DialogHttpMessage".localized, request.url, response?.body ?? ""), onClose: nil)
                self.showMainView()
            }
        }
    }

    func doActionSecretKey() {
        let secretKey = EZRHelperEnvironmentHelper.getSecretKey()
        let message = String(format: "DialogSecretKeyMessage".localized, secretKey)

        UIUtil.showAlert(parent: self, title: "DialogTitle".localized, message: message, onClose: nil)
    }

    func doActionTodo() {
        showLoadingView(show: true)

        DispatchQueue.global(qos: .background).async {
            let count = EZRRepositoryTodoRepository.count()

            if count == 0 {
                // add some rows
                EZRRepositoryTodoRepository.truncate()

                for i in 1 ... 100 {
                    let todo = EZRDomainTodo(
                        id: 0,
                        title: String(format: "Title %i", i),
                        body: String(format: "New TODO item description: %i", i),
                        data: [:],
                        done: false,
                        createdAt: Date(),
                        updatedAt: Date()
                    )

                    EZRRepositoryTodoRepository.add(todo)
                }
            }

            // show list view controller
            DispatchQueue.main.async {
                self.showMainView()
                self.navigationController?.pushViewController(TodoListViewController(), animated: true)
            }
        }
    }

    func doActionWebServer() {
        guard let server = EZRHttpServer.shared() else { return }

        DispatchQueue.main.async {
            if server.isRunning() {
                server.stop()
            } else {
                server.start()
            }

            self.tableView.reloadRows(at: [IndexPath(row: 6, section: 0)], with: UITableView.RowAnimation.automatic)
        }
    }

    func doActionWebView() {
        let controller = WebViewController()
        let nc = UINavigationController(rootViewController: controller)
        nc.modalPresentationStyle = .fullScreen

        navigationController?.present(nc, animated: true, completion: nil)
    }
}
