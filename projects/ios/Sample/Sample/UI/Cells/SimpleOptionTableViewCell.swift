import Foundation
import UIKit

class SimpleOptionTableViewCell: UITableViewCell {
    var lbDescription: UILabel!
    var ivIcon: UIImageView!
    var lineView: UIView!
    var containerView: UIView!
    var option: SimpleOption!

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)

        createAll()
        layoutAll()
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }

    func bind(option: SimpleOption) {
        self.option = option

        lbDescription.text = option.getDescription()
        ivIcon.image = option.getImage()

        lineView.isHidden = !option.hasSeparator
    }

    func createAll() {
        // content
        contentView.backgroundColor = UIColor(hexString: "#FFFFFF")!

        // container
        containerView = UIView()
        containerView.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(containerView)

        // divider
        lineView = UIView()
        lineView.translatesAutoresizingMaskIntoConstraints = false
        lineView.backgroundColor = UIColor(hexString: "#E0E0E0")!
        contentView.addSubview(lineView)

        // description
        lbDescription = UILabel()
        lbDescription.textAlignment = NSTextAlignment.left
        lbDescription.textColor = .black
        lbDescription.font = UIFont.systemFont(ofSize: 14)
        lbDescription.numberOfLines = 0
        lbDescription.translatesAutoresizingMaskIntoConstraints = false
        lbDescription.backgroundColor = UIColor.clear
        lbDescription.lineBreakMode = .byWordWrapping
        containerView.addSubview(lbDescription)

        // icon
        ivIcon = UIImageView()
        ivIcon.tintColor = UIColor(hexString: "#D21601")!
        ivIcon.translatesAutoresizingMaskIntoConstraints = false
        ivIcon.backgroundColor = UIColor.clear
        containerView.addSubview(ivIcon)
    }

    func layoutAll() {
        contentView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-[containerView]-|", options: [], metrics: nil, views: [
            "containerView": containerView!,
        ]))

        contentView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|[lineView]|", options: [], metrics: nil, views: [
            "lineView": lineView!,
        ]))

        contentView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|-[containerView]-[lineView(1)]|", options: [], metrics: nil, views: [
            "containerView": containerView!,
            "lineView": lineView!,
        ]))

        containerView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|[ivIcon(26)]-[lbDescription]|", options: [], metrics: nil, views: [
            "ivIcon": ivIcon!,
            "lbDescription": lbDescription!,
        ]))

        containerView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|-6-[ivIcon(26)]-6-|", options: [], metrics: nil, views: [
            "ivIcon": ivIcon!,
        ]))

        containerView.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|-6-[lbDescription]-6-|", options: [], metrics: nil, views: [
            "lbDescription": lbDescription!,
        ]))
    }
}
