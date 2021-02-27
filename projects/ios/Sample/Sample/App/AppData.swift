import Foundation

class AppData {
    private init() {}
    static let shared = AppData()

    var debug: Bool = false
}
