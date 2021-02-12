import Foundation
import UIKit
import WebKit

extension WKWebView {
    func evaluate(script: String, completionHandler: ((Any?, Error?) -> Swift.Void)? = nil) {
        var finished = false

        evaluateJavaScript(script) { result, error in
            completionHandler?(result, error)
            finished = true
        }

        while !finished {
            RunLoop.current.run(mode: .default, before: Date.distantFuture)
        }
    }
}
