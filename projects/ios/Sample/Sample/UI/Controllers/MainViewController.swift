import Foundation
import UIKit

class MainViewController: UITabBarController, UITabBarControllerDelegate {
    override func viewDidLoad() {
        super.viewDidLoad()
        initialize()
        setNeedsStatusBarAppearanceUpdate()
    }

    func initialize() {
        let homeViewController = HomeViewController()
        homeViewController.tabBarItem = UITabBarItem(title: homeViewController.getVCTitle(), image: UIImage(named: "IcoHome"), tag: 0)
        let homeNC = UINavigationController(rootViewController: homeViewController)

        let settingsViewController = SettingsViewController()
        settingsViewController.tabBarItem = UITabBarItem(title: settingsViewController.getVCTitle(), image: UIImage(named: "IcoSettings"), tag: 1)
        let settingsNC = UINavigationController(rootViewController: settingsViewController)

        viewControllers = [homeNC, settingsNC]

        tabBar.barTintColor = UIColor(hexString: "#FFFFFF")
    }
}
