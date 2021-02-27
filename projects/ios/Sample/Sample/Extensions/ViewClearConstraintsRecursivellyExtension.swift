import UIKit

extension UIView {
    func clearConstraintsRecursivelly() {
        for subview in subviews {
            subview.clearConstraintsRecursivelly()
        }

        removeConstraints(constraints)
    }
}
