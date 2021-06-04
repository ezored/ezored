import UIKit

class SettingsViewController: BaseTableViewController {
    var listData: [SimpleOption]?
    let cellIdentifier = "SettingsOptionTableViewCell"

    override func createAll() {
        super.createAll()

        // register cell types
        tableView.register(SimpleOptionTableViewCell.self, forCellReuseIdentifier: cellIdentifier)
        tableView.estimatedRowHeight = 50
        tableView.separatorStyle = .none
    }

    override func onLoadNewData() {
        super.onLoadNewData()

        listData = []
        listData?.append(SimpleOption(type: .appVersion, hasSeparator: false))
    }

    override func needLoadNewData() -> Bool {
        return true
    }

    override func onTableViewSelectedRow(tableView: UITableView, indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)

        if let option = listData?[indexPath.row] {
            if option.type == .appVersion {
                doActionAppVersion()
            }
        }
    }

    override func onTableViewCreateCell(tableView: UITableView, indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier, for: indexPath) as! SimpleOptionTableViewCell

        if let option = listData?[indexPath.row] {
            cell.bind(option: option)
            return cell
        }

        return UITableViewCell()
    }

    override func onTableViewGetNumberOfRows(tableView _: UITableView, section _: Int) -> Int {
        if let listData = listData {
            return listData.count
        }

        return 0
    }

    override func getVCTitle() -> String {
        return "TitleSettings".localized
    }

    override func getTitleForAnalytics() -> String {
        return "Settings"
    }

    // MARK: Actions

    func doActionAppVersion() {
        let dictionary = Bundle.main.infoDictionary!
        let version = dictionary["CFBundleShortVersionString"] as! String
        let build = dictionary["CFBundleVersion"] as! String
        let sdk = EZRCoreApplicationCore.shared()?.getVersion() ?? ""
        let message = "Version: \(version)\nBuild: \(build)\nSDK: \(sdk)"

        UIUtil.showAlert(parent: self, title: "DialogTitle".localized, message: message, onClose: nil)
    }
}
