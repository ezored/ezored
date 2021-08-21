import Foundation
import UIKit

struct SimpleOption: Hashable {
    let type: OptionTypeEnum
    let hasSeparator: Bool

    func getDescription() -> String {
        switch type {
        case .secretKey:
            return "OptionSecretKey".localized
        case .sharedData:
            let demoFlag = EZRHelperSharedDataHelper.getDemoFlag()
            return String(format: "%@ %@", "OptionSharedData".localized, demoFlag ? "ON" : "OFF")
        case .httpRequest:
            return "OptionHttpRequest".localized
        case .httpsRequest:
            return "OptionHttpsRequest".localized
        case .fileHelper:
            return "OptionFileHelper".localized
        case .appVersion:
            return "OptionAppVersion".localized
        case .todo:
            return "OptionTodo".localized
        case .webServer:
            let demoFlag = EZRHttpServer.shared()?.isRunning() ?? false
            return String(format: "%@ %@", "OptionWebServer".localized, demoFlag ? "ON" : "OFF")
        case .webView:
            return "OptionWebView".localized
        }
    }

    func getImage() -> UIImage {
        return UIImage(named: "IcoSimpleOption")!.imageWithColor(color: UIColor(hexString: "#D21601")!)!
    }
}
