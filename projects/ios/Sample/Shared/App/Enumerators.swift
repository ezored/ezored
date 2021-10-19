import Foundation

enum NetworkErrorViewAction: Int {
    case refresh = 0
}

enum RemoteDataLoadState: Int {
    case loaded = 0
    case loading = 1
    case notLoaded = 2
}

enum OptionTypeEnum {
    case secretKey
    case sharedData
    case httpRequest
    case httpsRequest
    case fileHelper
    case appVersion
    case todo
    case webServer
    case webView
}
