import Foundation

enum ViewModelState<TSuccess, TError> {
    case notLoaded
    case loading(data: TSuccess?) /// Sometimes the page is loading but there is already a valid data, such as refreshing/updating requests that runs after a successful load.
    case loaded(data: TSuccess) /// Page is fully loaded
    case loadedWithError(data: TSuccess, error: TError) /// Sometimes the page has valid data loaded, but some error is thrown anyway.
    case failure(error: TError) /// Page completely failed to load

    var data: TSuccess? {
        switch self {
        case let .loaded(data): return data
        case let .loading(data): return data
        case let .loadedWithError(data, _): return data
        default: return nil
        }
    }

    var error: TError? {
        if case let .failure(error) = self {
            return error
        } else if case let .loadedWithError(_, error) = self {
            return error
        } else {
            return nil
        }
    }

    var isLoading: Bool {
        if case .loading = self {
            return true
        } else {
            return false
        }
    }
    
    var isNotLoaded: Bool {
        if case .notLoaded = self {
            return true
        } else {
            return false
        }
    }
}
