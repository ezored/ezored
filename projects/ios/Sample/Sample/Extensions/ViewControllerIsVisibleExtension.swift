import Foundation
import UIKit

public extension UIViewController {
    func isVisible() -> Bool {
        if isViewLoaded, view.window != nil {
            return true
        }

        return false
    }
}
