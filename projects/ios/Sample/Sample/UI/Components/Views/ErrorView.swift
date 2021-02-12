import Foundation
import UIKit

class ErrorView: UIView {
    var lbMessage: UILabel!

    override init(frame: CGRect) {
        super.init(frame: frame)

        backgroundColor = getBackgroundColor()

        createAll()
        layoutAll()
    }

    func createAll() {
        // message
        lbMessage = UILabel()
        lbMessage.textAlignment = NSTextAlignment.center
        lbMessage.textColor = getTextColor()
        lbMessage.font = UIFont.boldSystemFont(ofSize: 16)
        lbMessage.numberOfLines = 0
        lbMessage.translatesAutoresizingMaskIntoConstraints = false
        addSubview(lbMessage)
    }

    func layoutAll() {
        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-30-[lbMessage]-30-|", options: [], metrics: nil, views: [
            "lbMessage": lbMessage!,
        ]))

        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|-[lbMessage]-|", options: [], metrics: nil, views: [
            "lbMessage": lbMessage!,
        ]))
    }

    func getBackgroundColor() -> UIColor {
        return .white
    }

    func getTextColor() -> UIColor {
        return .black
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}
