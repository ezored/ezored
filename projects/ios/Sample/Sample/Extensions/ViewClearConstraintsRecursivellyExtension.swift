import UIKit

extension UIView {
    
    func clearConstraintsRecursivelly() {
        for subview in self.subviews {
            subview.clearConstraintsRecursivelly()
        }
        
        self.removeConstraints(self.constraints)
    }
    
}
