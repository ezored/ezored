import Foundation
import UIKit

protocol SimpleSearchBarProtocol {
    func simpleSearchBarBtResetClicked()
    func simpleSearchBarSearch(typedText: String)
}

class SimpleSearchBar: UIView, UISearchBarDelegate {
    // MARK: - Views

    private lazy var containerView: UIView = {
        let view = UIView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.backgroundColor = .clear
        return view
    }()

    private lazy var searchBar: UISearchBar = {
        let search = UISearchBar()
        search.delegate = self
        search.placeholder = "SimpleSearchBarHintText".localized
        search.sizeToFit()
        search.searchBarStyle = .minimal
        search.autocapitalizationType = .none
        return search
    }()

    private lazy var btReset: UIButton = {
        let button = UIButton(type: .system)
        button.backgroundColor = .clear
        button.isHidden = false
        button.alpha = 1
        button.setTitle("SimpleSearchBarBtReset".localized, for: .normal)
        button.setTitleColor(UIColor(hexString: "#000000"), for: .normal)
        button.tintColor = UIColor(hexString: "#000000")
        button.titleLabel?.font = UIFont.systemFont(ofSize: 13)
        button.addTarget(self, action: #selector(onBtResetTouchUpInside), for: .touchUpInside)
        button.translatesAutoresizingMaskIntoConstraints = false
        return button
    }()

    private lazy var btCancel: UIButton = {
        let button = UIButton(type: .system)
        button.backgroundColor = .clear
        button.isHidden = true
        button.alpha = 0
        button.setTitle("SimpleSearchBarBtCancel".localized, for: .normal)
        button.setTitleColor(UIColor(hexString: "#000000"), for: .normal)
        button.tintColor = UIColor(hexString: "#000000")
        button.titleLabel?.font = UIFont.systemFont(ofSize: 13)
        button.addTarget(self, action: #selector(onBtCancelTouchUpInside), for: .touchUpInside)
        button.translatesAutoresizingMaskIntoConstraints = false
        return button
    }()

    private lazy var stackview: UIStackView = {
        let stackview = UIStackView(arrangedSubviews: [searchBar, btReset, btCancel])
        stackview.axis = .horizontal
        stackview.spacing = 4
        stackview.alignment = .fill
        stackview.translatesAutoresizingMaskIntoConstraints = false
        return stackview
    }()

    var delegate: SimpleSearchBarProtocol?

    override init(frame: CGRect) {
        super.init(frame: frame)

        createAll()
        layoutAll()

        let textAttributes: [NSAttributedString.Key: Any] = [
            NSAttributedString.Key.font: UIFont.systemFont(ofSize: 13),
            NSAttributedString.Key.foregroundColor: UIColor(hexString: "#000000")!,
        ]

        UITextField.appearance(whenContainedInInstancesOf: [SimpleSearchBar.self]).defaultTextAttributes = textAttributes
    }

    @available(*, unavailable)
    required init?(coder _: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - UI Events

    func createAll() {
        containerView.addSubview(stackview)
        addSubview(containerView)
    }

    func layoutAll() {
        // container view
        addConstraint(NSLayoutConstraint(item: containerView, attribute: .centerX, relatedBy: .equal, toItem: self, attribute: .centerX, multiplier: 1.0, constant: 0.0))
        addConstraint(NSLayoutConstraint(item: containerView, attribute: .centerY, relatedBy: .equal, toItem: self, attribute: .centerY, multiplier: 1.0, constant: 0.0))
        addConstraint(NSLayoutConstraint(item: containerView, attribute: .width, relatedBy: .equal, toItem: self, attribute: .width, multiplier: 1.0, constant: 0.0))
        addConstraint(NSLayoutConstraint(item: containerView, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 50.0))

        // stackview
        containerView.addConstraint(NSLayoutConstraint(item: stackview, attribute: .leading, relatedBy: .equal, toItem: containerView, attribute: .leading, multiplier: 1.0, constant: 8.0))
        containerView.addConstraint(NSLayoutConstraint(item: stackview, attribute: .trailing, relatedBy: .equal, toItem: containerView, attribute: .trailing, multiplier: 1.0, constant: -16.0))
        containerView.addConstraint(NSLayoutConstraint(item: stackview, attribute: .bottom, relatedBy: .equal, toItem: containerView, attribute: .bottom, multiplier: 1.0, constant: 0.0))
        containerView.addConstraint(NSLayoutConstraint(item: stackview, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 34.0))

        // bt filter
        stackview.addConstraint(NSLayoutConstraint(item: btReset, attribute: .height, relatedBy: .equal, toItem: searchBar, attribute: .height, multiplier: 1.0, constant: 0.0))

        // bt cancel
        stackview.addConstraint(NSLayoutConstraint(item: btCancel, attribute: .height, relatedBy: .equal, toItem: searchBar, attribute: .height, multiplier: 1.0, constant: 0.0))
        stackview.addConstraint(NSLayoutConstraint(item: btCancel, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 55.0))
    }

    // MARK: Search bar delegate

    func searchBarShouldBeginEditing(_: UISearchBar) -> Bool {
        showCancelButton()
        return true
    }

    func searchBarCancelButtonClicked(_: UISearchBar) {
        updateSearch()
        showFilterButton()
    }

    func searchBarSearchButtonClicked(_: UISearchBar) {
        updateSearch()
    }

    // MARK: - Buttons actions

    @objc private func onBtResetTouchUpInside(sender _: UIButton) {
        delegate?.simpleSearchBarBtResetClicked()
    }

    @objc private func onBtCancelTouchUpInside(sender _: UIButton) {
        searchBar.endEditing(true)
        searchBar.text = ""

        showFilterButton()
        updateSearch()
    }

    // MARK: - Private methods

    private func updateSearch() {
        delegate?.simpleSearchBarSearch(typedText: searchBar.text ?? "")
    }

    private func showFilterButton() {
        UIView.animate(withDuration: 0.2, animations: {
            self.btCancel.isHidden = true
            self.btCancel.alpha = 0
            self.stackview.layoutIfNeeded()
        }, completion: { _ in
            UIView.animate(withDuration: 0.2, animations: {
                self.btReset.isHidden = false
                self.btReset.alpha = 1
                self.stackview.layoutIfNeeded()
            })
        })
    }

    private func showCancelButton() {
        UIView.animate(withDuration: 0.2, animations: {
            self.btReset.isHidden = true
            self.btReset.alpha = 0
            self.stackview.layoutIfNeeded()
        }, completion: { _ in
            UIView.animate(withDuration: 0.2, animations: {
                self.btCancel.isHidden = false
                self.btCancel.alpha = 1
                self.stackview.layoutIfNeeded()
            })
        })
    }
}
