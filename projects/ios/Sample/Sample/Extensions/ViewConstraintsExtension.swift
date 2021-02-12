import Foundation
import UIKit

/*
 Example: addConstraintsWithFormat(format: "V:|[v0][v1(1)]|", views: collectionView, dividerLine)
 */

public extension UIView {
    func addConstraintsWithFormat(format: String, views: UIView...) {
        var viewsDictionary = [String: UIView]()

        for (index, view) in views.enumerated() {
            let key = "v\(index)"
            view.translatesAutoresizingMaskIntoConstraints = false
            viewsDictionary[key] = view
        }

        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: format, options: NSLayoutConstraint.FormatOptions(), metrics: nil, views: viewsDictionary))
    }

    func addWidthConstraint(view: UIView, width: CGFloat) {
        view.translatesAutoresizingMaskIntoConstraints = false
        addConstraint(NSLayoutConstraint(item: view, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: width))
    }

    func addHeightConstraint(view: UIView, width: CGFloat) {
        view.translatesAutoresizingMaskIntoConstraints = false
        addConstraint(NSLayoutConstraint(item: view, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: width))
    }

    func addSizeConstraint(view: UIView, size: CGFloat) {
        view.translatesAutoresizingMaskIntoConstraints = false
        addWidthConstraint(view: view, width: size)
        addHeightConstraint(view: view, width: size)
    }
}
