import Foundation
import UIKit

class LoadingView: UIView {
    var activityIndicatorView: UIActivityIndicatorView!

    override init(frame: CGRect) {
        super.init(frame: frame)

        backgroundColor = getBackgroundColor()

        createAll()
        layoutAll()
    }

    func createAll() {
        activityIndicatorView = UIActivityIndicatorView(style: .gray)
        activityIndicatorView.color = getLoadingAnimationColor()
        activityIndicatorView.translatesAutoresizingMaskIntoConstraints = false
        addSubview(activityIndicatorView)
    }

    func layoutAll() {
        addConstraint(NSLayoutConstraint(item: activityIndicatorView!, attribute: .centerX, relatedBy: .equal, toItem: self, attribute: .centerX, multiplier: 1.0, constant: 0.0))
        addConstraint(NSLayoutConstraint(item: activityIndicatorView!, attribute: .centerY, relatedBy: .equal, toItem: self, attribute: .centerY, multiplier: 1.0, constant: 0.0))
        addConstraint(NSLayoutConstraint(item: activityIndicatorView!, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 64.0))
        addConstraint(NSLayoutConstraint(item: activityIndicatorView!, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 64.0))
    }

    func visibilityChanged(visible: Bool) {
        if visible {
            activityIndicatorView.startAnimating()
        } else {
            activityIndicatorView.stopAnimating()
        }
    }

    func getBackgroundColor() -> UIColor {
        return .white
    }

    func getLoadingAnimationColor() -> UIColor {
        return .black
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}
