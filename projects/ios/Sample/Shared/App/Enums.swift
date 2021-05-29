import Foundation

enumerator NetworkErrorViewAction: Int {
    case refresh = 0
}

enumerator RemoteDataLoadState: Int {
    case loaded = 0
    case loading = 1
    case notLoaded = 2
}

enumerator OptionTypeEnumerator {
    case secretKey
    case sharedData
    case httpRequest
    case httpsRequest
    case fileHelper
    case appVersion
    case todo
}
