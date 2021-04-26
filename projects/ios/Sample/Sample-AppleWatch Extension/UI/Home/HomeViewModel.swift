//
//  HomeViewModel.swift
//  Sample-AppleWatch Extension
//
//  Created by ubook on 26/04/21.
//  Copyright © 2021 PRSoluções. All rights reserved.
//

import Foundation

class HomeViewModel: NSObject, ObservableObject {
    @Published var listData: [SimpleOption] = []
    @Published var alertMessage: ViewModelState<String, Never> = .notLoaded
    @Published var showTodoList: Bool = false

    
    override init() {
        NSLog("INITIALIZING VIEW MODEL")
    }
    
    func loadData() {
        var data: [SimpleOption] = []
        data.append(SimpleOption(type: .secretKey, hasSeparator: true))
        data.append(SimpleOption(type: .sharedData, hasSeparator: true))
        data.append(SimpleOption(type: .httpRequest, hasSeparator: true))
        data.append(SimpleOption(type: .httpsRequest, hasSeparator: true))
        data.append(SimpleOption(type: .fileHelper, hasSeparator: true))
        data.append(SimpleOption(type: .todo, hasSeparator: false))
        data.append(SimpleOption(type: .appVersion, hasSeparator: false))
        
        listData = data
        NSLog("Changing listData")
    }

    func selectItem(at index: Int) {
        guard let option = listData.get(at: index)?.type else { return }
        switch option {
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
        }
    }


    // MARK: Actions

    private func doActionSharedData() {
        EZRHelpersSharedDataHelper.setDemoFlag(!EZRHelpersSharedDataHelper.getDemoFlag())
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
        let secretKey = EZRHelpersEnvironmentHelper.getSecretKey()
        let message = String(format: "DialogSecretKeyMessage".localized, secretKey)

        alertMessage = .loaded(data: message)
    }

    private func doActionTodo() {
        alertMessage = .loading(data: nil)

        DispatchQueue.global(qos: .background).async {
            // add some rows
            EZRDataServicesTodoDataService.truncate()

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

                EZRDataServicesTodoDataService.add(todo)
            }

            // show list view controller
            DispatchQueue.main.async {
                self.showTodoList = true
            }
        }
    }

    private func doAppVersion() {
        
    }
}
