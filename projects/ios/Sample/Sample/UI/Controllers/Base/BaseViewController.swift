import UIKit

class BaseViewController: UIViewController, NetworkErrorViewProtocol {
    var errorView: ErrorView!
    var loadingView: LoadingView!
    var networkErrorView: NetworkErrorView!

    var lastCacheUpdate: TimeInterval?

    var remoteDataLoadState: RemoteDataLoadState = .notLoaded

    var created = false

    override func viewDidLoad() {
        super.viewDidLoad()

        title = getVCTitle()

        createAll()
        layoutAll()
        loadData()

        created = true
    }

    func createAll() {
        // controller
        navigationItem.title = getVCTitle()
        setupNavigationBar()
        setupTabBar()

        // view
        createMainContainerView()

        // error view
        errorView = createErrorView()
        getMainContainerView().addSubview(errorView)
        showErrorView(show: false, message: "")

        // loading view
        loadingView = createLoadingView()
        getMainContainerView().addSubview(loadingView)
        showLoadingView(show: false)

        // network error view
        networkErrorView = createNetworkErrorView()
        getMainContainerView().addSubview(networkErrorView)
        showNetworkErrorView(show: false, message: "")
    }

    func layoutAll() {
        addMainContraints()
    }

    func createErrorView() -> ErrorView {
        let errorView = ErrorView()
        errorView.translatesAutoresizingMaskIntoConstraints = false
        return errorView
    }

    func createLoadingView() -> LoadingView {
        let loadingView = LoadingView()
        loadingView.translatesAutoresizingMaskIntoConstraints = false
        return loadingView
    }

    func createNetworkErrorView() -> NetworkErrorView {
        let networkErrorView = NetworkErrorView()
        networkErrorView.translatesAutoresizingMaskIntoConstraints = false
        networkErrorView.delegate = self
        return networkErrorView
    }

    func addMainContraints() {
        // error view
        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-0-[errorView]-0-|", options: [], metrics: nil, views: [
            "errorView": errorView!,
        ]))

        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:[topLayoutGuide]-0-[errorView]-0-[bottomLayoutGuide]", options: [], metrics: nil, views: [
            "errorView": errorView!,
            "topLayoutGuide": topLayoutGuide,
            "bottomLayoutGuide": bottomLayoutGuide,
        ]))

        // loading view
        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-0-[loadingView]-0-|", options: [], metrics: nil, views: [
            "loadingView": loadingView!,
        ]))

        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:[topLayoutGuide]-0-[loadingView]-0-[bottomLayoutGuide]", options: [], metrics: nil, views: [
            "loadingView": loadingView!,
            "topLayoutGuide": topLayoutGuide,
            "bottomLayoutGuide": bottomLayoutGuide,
        ]))

        // network error view
        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-0-[networkErrorView]-0-|", options: [], metrics: nil, views: [
            "networkErrorView": networkErrorView!,
        ]))

        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:[topLayoutGuide]-0-[networkErrorView]-0-[bottomLayoutGuide]", options: [], metrics: nil, views: [
            "networkErrorView": networkErrorView!,
            "topLayoutGuide": topLayoutGuide,
            "bottomLayoutGuide": bottomLayoutGuide,
        ]))
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        setNeedsStatusBarAppearanceUpdate()
        title = getVCTitle()

        validateLoadData()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        // notify all analytics about it
        // AppEvents.onScreenChange(screenName: getTitleForAnalytics())
    }

    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        super.viewWillTransition(to: size, with: coordinator)
        onDeviceOrientationChanged()
    }

    func dismissKeyboard() {
        getMainContainerView().resignFirstResponder()
        getMainContainerView().endEditing(true)
    }

    override var preferredStatusBarStyle: UIStatusBarStyle {
        return getViewControllerPreferredStatusBarStyle()
    }

    func getViewControllerPreferredStatusBarStyle() -> UIStatusBarStyle {
        return .lightContent
    }

    // MARK: EVENTS

    func getTitleForAnalytics() -> String {
        return "Base"
    }

    func getVCTitle() -> String {
        return "Base"
    }

    func setupNavigationBar() {
        navigationController?.navigationBar.isTranslucent = false

        navigationController?.navigationBar.titleTextAttributes = [NSAttributedString.Key.foregroundColor: UIColor.white]
        navigationController?.navigationBar.tintColor = UIColor.white
        navigationController?.navigationBar.barTintColor = UIColor(hexString: "#D21601")!
        navigationController?.view.backgroundColor = UIColor(hexString: "#D21601")!
    }

    func setupTabBar() {
        tabBarController?.tabBar.backgroundColor = UIColor.white
        tabBarController?.tabBar.tintColor = UIColor(hexString: "#D21601")!
        tabBarController?.tabBar.clipsToBounds = true
        tabBarController?.tabBar.layer.borderWidth = 0.5
        tabBarController?.tabBar.layer.borderColor = UIColor(hexString: "#E0E0E0")!.cgColor
    }

    func validateLoadData() {
        validateCache()
        loadData()
    }

    func needLoadNewData() -> Bool {
        return false
    }

    func onLoadNewData() {
        // will be implemented on child
    }

    func loadData() {
        if !needLoadNewData() {
            return
        }

        if remoteDataLoadState != .notLoaded {
            return
        }

        remoteDataLoadState = .loading

        onLoadNewData()
    }

    func onDeviceOrientationChanged() {
        // will be implemented on child
    }

    // MARK: VIEWS

    func showErrorView(show: Bool, message: String) {
        if show {
            hideAllViews()
            errorView.lbMessage.text = message
            view.bringSubviewToFront(errorView)
            errorView.isHidden = false
            errorView.setNeedsLayout()
        } else {
            errorView.isHidden = true
        }
    }

    func showLoadingView(show: Bool) {
        if show {
            hideAllViews()
            view.bringSubviewToFront(loadingView)
            loadingView.visibilityChanged(visible: true)
            loadingView.isHidden = false
            loadingView.setNeedsLayout()
        } else {
            loadingView.isHidden = true
            loadingView.visibilityChanged(visible: false)
        }
    }

    func showNetworkErrorView(show: Bool, message: String) {
        if show {
            hideAllViews()
            networkErrorView.lbMessage.text = message
            view.bringSubviewToFront(networkErrorView)
            networkErrorView.isHidden = false
            networkErrorView.setNeedsLayout()
        } else {
            networkErrorView.isHidden = true
        }
    }

    func showMainView() {
        getMainContainerView().setNeedsLayout()
        hideAllViews()
    }

    func hideAllViews() {
        errorView.isHidden = true
        loadingView.isHidden = true
        networkErrorView.isHidden = true
    }

    func createMainContainerView() {
        view.backgroundColor = .white
    }

    func getMainContainerView() -> UIView {
        return view
    }

    func networkErrorViewProtocolOnAction(action _: NetworkErrorViewAction) {
        // will be implemented on child
    }

    // MARK: BACK BUTTON

    func createBackButton() {
        let image = UIImage(named: "BtBack")?.imageWithColor(color: .black)

        let button = UIButton(type: .system)
        button.frame = CGRect(x: -2, y: 0, width: 40, height: 40)
        button.setImage(image, for: .normal)
        button.contentHorizontalAlignment = .left
        button.addTarget(self, action: #selector(onBackButtonTouchUpInside), for: .touchUpInside)

        let container = UIView(frame: CGRect(x: 0, y: 0, width: 40, height: 40))
        container.addSubview(button)

        navigationItem.leftBarButtonItem = UIBarButtonItem(customView: container)
        navigationItem.hidesBackButton = true
    }

    @objc func onBackButtonTouchUpInside(button _: UIButton) {
        // A implementação ficará nas classes filhas
        if UIUtil.isPresentedViewController(viewController: self) {
            dismiss(animated: true, completion: nil)
        } else {
            navigationController?.popViewController(animated: true)
        }
    }

    // MARK: CACHE

    func hasCache() -> Bool {
        return false
    }

    func cacheExpireInterval() -> TimeInterval {
        return TimeInterval(0)
    }

    func validateCache() {
        if hasCache() {
            lastCacheUpdate = lastCacheUpdate ?? DateTimeHelper.getCurrentTimeStamp()

            let currentTime = DateTimeHelper.getCurrentTimeStamp()
            let expireTime = lastCacheUpdate! + cacheExpireInterval()

            if currentTime >= expireTime {
                lastCacheUpdate = DateTimeHelper.getCurrentTimeStamp()
                onCacheExpired()
            }
        }
    }

    func onCacheExpired() {
        // will be implemented on child
    }
}
