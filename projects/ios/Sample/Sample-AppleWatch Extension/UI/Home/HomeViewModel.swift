
import Foundation

class HomeViewModel: NSObject, ObservableObject {
    @Published private(set) var listData: [SimpleOption] = []
    @Published var alertMessage: ViewModelState<String, Never> = .notLoaded
    @Published var showTodoList: ActionState? = .inactive
        
    
    func loadData() {
        var data: [SimpleOption] = []
        data.append(SimpleOption(type: .secretKey, hasSeparator: true))
        data.append(SimpleOption(type: .sharedData, hasSeparator: true))
        data.append(SimpleOption(type: .httpRequest, hasSeparator: true))
        data.append(SimpleOption(type: .httpsRequest, hasSeparator: true))
        data.append(SimpleOption(type: .fileHelper, hasSeparator: true))
        data.append(SimpleOption(type: .todo, hasSeparator: true))
        data.append(SimpleOption(type: .appVersion, hasSeparator: true))
        data.append(SimpleOption(type: .webServer, hasSeparator: false))
        
        listData = data
        showTodoList = .inactive
        alertMessage = .notLoaded
        
        NSLog("Changing listData")
    }
    
    func tapAlertMessage() {
        alertMessage = .notLoaded
    }

    func selectItem(_ item: SimpleOption) {
        switch item.type {
        case .secretKey:
            doActionSecretKey()
        case .sharedData:
            doActionSharedData()
        case .httpRequest:
            doActionHttpRequest()
        case .httpsRequest:
            doActionHttpsRequest()
        case .fileHelper:
            doActionFileHelper()
        case .todo:
            doActionTodo()
        case .appVersion:
            doAppVersion()
        case .webServer:
            doActionWebServer()
        case .webView:
            doActionWebView()
        }
    }


    // MARK: Actions

    private func doActionSharedData() {
        EZRHelperSharedDataHelper.setDemoFlag(!EZRHelperSharedDataHelper.getDemoFlag())
        loadData()
    }

    private func doActionFileHelper() {
        guard let core = EZRCoreApplicationCore.shared() else { return }

        let size = EZRFileHelper.getFileSize(EZRFileHelper.join(core.getInitializationData().basePath, second: "database.db3"))

        let message = String(format: "DialogDatabaseSizeMessage".localized, size, Double(size) / 1_048_576)
        alertMessage = .loaded(data: message)
    }

    private func doActionHttpRequest() {
        alertMessage = .loading(data: nil)

        DispatchQueue.global(qos: .background).async {
            var headers = [EZRHttpHeader]()
            headers.append(EZRHttpHeader(name: "Content-Type", value: "application/x-www-form-urlencoded"))

            var params = [EZRHttpRequestParam]()
            params.append(EZRHttpRequestParam(name: "username", value: "demo"))
            params.append(EZRHttpRequestParam(name: "password", value: "demo"))

            let request = EZRHttpRequest(url: "http://httpbin.org/post", method: .methodPost, params: params, headers: headers, body: "")
            let response = EZRHttpClient.shared()?.do(request)
            let message = String(format: "DialogHttpMessage".localized, request.url, response?.body ?? "")
            DispatchQueue.main.async {
                self.alertMessage = .loaded(data: message)
            }
        }
    }

    private func doActionHttpsRequest() {
        alertMessage = .loading(data: nil)

        DispatchQueue.global(qos: .background).async {
            var headers = [EZRHttpHeader]()
            headers.append(EZRHttpHeader(name: "Content-Type", value: "application/x-www-form-urlencoded"))

            var params = [EZRHttpRequestParam]()
            params.append(EZRHttpRequestParam(name: "username", value: "demo"))
            params.append(EZRHttpRequestParam(name: "password", value: "demo"))

            let request = EZRHttpRequest(url: "https://httpbin.org/post", method: .methodPost, params: params, headers: headers, body: "")
            let response = EZRHttpClient.shared()?.do(request)
            let message = String(format: "DialogHttpMessage".localized, request.url, response?.body ?? "")

            DispatchQueue.main.async {
                self.alertMessage = .loaded(data: message)
            }
        }
    }

    private func doActionSecretKey() {
        let secretKey = EZRHelperEnvironmentHelper.getSecretKey()
        let message = String(format: "DialogSecretKeyMessage".localized, secretKey)

        alertMessage = .loaded(data: message)
    }

    private func doActionTodo() {
        self.showTodoList = .loading

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
                self.showTodoList = .active
            }
        }
    }

    private func doAppVersion() {
        guard let dictionary = Bundle.main.infoDictionary,
              let version = dictionary["CFBundleShortVersionString"] as? String,
              let build = dictionary["CFBundleVersion"] as? String else {
            return
        }
        
        let sdk = EZRCoreApplicationCore.shared()?.getVersion() ?? ""
        let message = "Version: \(version)\nBuild: \(build)\nSDK: \(sdk)"
        
        alertMessage = .loaded(data: message)
    }
    
    func doActionWebServer() {
        guard let server = EZRHttpServer.shared() else { return }
        
        DispatchQueue.main.async {
            if server.isRunning() {
                server.stop()
            } else {
                server.start()
            }
            
            self.loadData()
        }
    }
    
    func doActionWebView() {
        // TODO: implement
    }

}
