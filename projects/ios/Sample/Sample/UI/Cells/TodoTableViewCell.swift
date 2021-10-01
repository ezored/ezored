import Foundation
import UIKit

class TodoTableViewCell: UITableViewCell {
    var lbId: UILabel!
    var lbTitle: UILabel!
    var lbBody: UILabel!
    var lbCreatedAt: UILabel!

    var ivIcon: UIImageView!
    var lineView: UIView!

    var containerView: UIView!
    var iconContainerView: UIView!
    var dataContainerView: UIView!

    var todo: EZRDomainTodo!

    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)

        createAll()
        layoutAll()
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }

    func bind(todo: EZRDomainTodo, hasSeparator: Bool) {
        self.todo = todo

        // data
        lbId.text = String(format: "ID: %d", todo.id)
        lbTitle.text = String(format: "Title: %@", todo.title)
        lbBody.text = String(format: "Body: %@", todo.body)
        lbCreatedAt.text = String(format: "Created at: %@", DateTimeHelper.formatAsMysql(date: todo.createdAt))

        // image
        var imageName = "IcoItemOff"

        if todo.done {
            imageName = "IcoItemOn"
        }

        ivIcon.image = UIImage(named: imageName)

        // separator
        lineView.isHidden = !hasSeparator
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

        // icon container
        iconContainerView = UIView()
        iconContainerView.translatesAutoresizingMaskIntoConstraints = false
        containerView.addSubview(iconContainerView)

        // data container
        dataContainerView = UIView()
        dataContainerView.translatesAutoresizingMaskIntoConstraints = false
        containerView.addSubview(dataContainerView)

        // id
        lbId = createLabel()
        dataContainerView.addSubview(lbId)

        // title
        lbTitle = createLabel()
        dataContainerView.addSubview(lbTitle)

        // body
        lbBody = createLabel()
        dataContainerView.addSubview(lbBody)

        // created at
        lbCreatedAt = createLabel()
        dataContainerView.addSubview(lbCreatedAt)

        // icon
        ivIcon = UIImageView()
        ivIcon.tintColor = UIColor(hexString: "#3d5afe")!
        ivIcon.translatesAutoresizingMaskIntoConstraints = false
        ivIcon.backgroundColor = UIColor.clear
        iconContainerView.addSubview(ivIcon)
    }

    func createLabel() -> UILabel {
        let label = UILabel()
        label.textAlignment = NSTextAlignment.left
        label.textColor = .black
        label.font = UIFont.systemFont(ofSize: 14)
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        label.backgroundColor = UIColor.clear
        label.lineBreakMode = .byWordWrapping
        return label
    }

    func layoutAll() {
        contentView.addConstraintsWithFormat(format: "H:|-[v0]-|", views: containerView)
        contentView.addConstraintsWithFormat(format: "H:|[v0]|", views: lineView)
        contentView.addConstraintsWithFormat(format: "V:|-[v0]-[v1(1)]|", views: containerView, lineView)

        containerView.addConstraintsWithFormat(format: "H:|-[v0]-[v1]-|", views: iconContainerView, dataContainerView)
        containerView.addConstraintsWithFormat(format: "V:|[v0]|", views: dataContainerView)

        iconContainerView.addConstraintsWithFormat(format: "H:|-[v0(26)]-|", views: ivIcon)
        iconContainerView.addConstraintsWithFormat(format: "V:|-[v0(26)]-|", views: ivIcon)

        dataContainerView.addConstraintsWithFormat(format: "H:|-[v0]-|", views: lbId)
        dataContainerView.addConstraintsWithFormat(format: "H:|-[v0]-|", views: lbTitle)
        dataContainerView.addConstraintsWithFormat(format: "H:|-[v0]-|", views: lbBody)
        dataContainerView.addConstraintsWithFormat(format: "H:|-[v0]-|", views: lbCreatedAt)
        dataContainerView.addConstraintsWithFormat(format: "V:|-[v0]-[v1]-[v2]-[v3]-|", views: lbId, lbTitle, lbBody, lbCreatedAt)
    }
}
