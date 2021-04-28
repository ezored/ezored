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
            let demoFlag = EZRHelpersSharedDataHelper.getDemoFlag()
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
        }
    }

    func getImage() -> UIImage {
        return UIImage(named: "IcoSimpleOption")!.imageWithColor(color: UIColor(hexString: "#ff3860")!)!
    }
}
