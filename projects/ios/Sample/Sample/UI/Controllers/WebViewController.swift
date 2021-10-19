import Foundation
import UIKit
import WebKit

class WebViewController: BaseViewController, WKNavigationDelegate {
    var webView: WKWebView!

    func reload() {
        var url = EZRHttpServer.shared()?.getSocketAddress() ?? ""
        url = url.replacingOccurrences(of: "0.0.0.0", with: "localhost")

        var request = URLRequest(url: URL(string: url)!)
        request.httpMethod = "GET"
        request.cachePolicy = .reloadIgnoringLocalAndRemoteCacheData

        webView.load(request)
    }

    override func createAll() {
        super.createAll()

        navigationItem.title = "TitleWebView".localized

        // left button
        let leftButton = UIBarButtonItem(image: UIImage(named: "BtClose")?.imageWithColor(color: UIColor(hexString: "#ffffff")!), style: .plain, target: self, action: #selector(onLeftButtonAction))
        navigationItem.leftBarButtonItem = leftButton

        // right button
        let rightButton = UIBarButtonItem(image: UIImage(named: "BtHome")?.imageWithColor(color: UIColor(hexString: "#ffffff")!), style: .plain, target: self, action: #selector(onRightButtonAction))
        navigationItem.rightBarButtonItem = rightButton

        // web view
        webView = WKWebView()
        webView.scrollView.showsVerticalScrollIndicator = false
        webView.scrollView.showsHorizontalScrollIndicator = false
        webView.backgroundColor = UIColor.clear
        webView.translatesAutoresizingMaskIntoConstraints = false
        webView.navigationDelegate = self
        getMainContainerView().addSubview(webView)

        // init
        reload()
    }

    override func layoutAll() {
        super.layoutAll()

        // web view
        view.addConstraint(NSLayoutConstraint(item: webView!, attribute: .centerX, relatedBy: .equal, toItem: view, attribute: .centerX, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: webView!, attribute: .centerY, relatedBy: .equal, toItem: view, attribute: .centerY, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: webView!, attribute: .width, relatedBy: .equal, toItem: view, attribute: .width, multiplier: 1.0, constant: 0.0))
        view.addConstraint(NSLayoutConstraint(item: webView!, attribute: .height, relatedBy: .equal, toItem: view, attribute: .height, multiplier: 1.0, constant: 0.0))
    }

    @objc func onLeftButtonAction(button _: UIBarButtonItem) {
        dismiss(animated: true, completion: nil)
    }

    @objc func onRightButtonAction(button _: UIBarButtonItem) {
        reload()
    }
}
