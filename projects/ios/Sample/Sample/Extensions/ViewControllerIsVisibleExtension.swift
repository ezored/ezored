import Foundation
import UIKit

public extension UIViewController {
    
    func isVisible() -> Bool {
        if self.isViewLoaded && (self.view.window != nil) {
            return true
        }
        
        return false
    }
    
}
