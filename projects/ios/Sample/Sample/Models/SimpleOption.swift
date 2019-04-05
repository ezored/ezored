import Foundation
import UIKit

class SimpleOption {
    
    var type: OptionTypeEnum!
    var hasSeparator: Bool!
    
    init(type: OptionTypeEnum, hasSeparator: Bool) {
        self.type = type
        self.hasSeparator = hasSeparator
    }
    
    func getDescription() -> String {
        if type == .secretKey {
            return "OptionSecretKey".localized
        } else if type == .sharedData {
            let demoFlag = EZRHelpersSharedDataHelper.getDemoFlag()
            return String(format: "%@ %@", "OptionSharedData".localized, (demoFlag ? "ON" : "OFF"))
        } else if type == .httpRequest {
            return "OptionHttpRequest".localized
        } else if type == .httpsRequest {
            return "OptionHttpsRequest".localized
        } else if type == .fileHelper {
            return "OptionFileHelper".localized
        } else if type == .appVersion {
            return "OptionAppVersion".localized
        } else if type == .todo {
            return "OptionTodo".localized
        }
        
        return ""
    }
    
    func getImage() -> UIImage {
        return UIImage(named: "IcoSimpleOption")!.imageWithColor(color: UIColor(hexString: "#ff3860")!)!
    }
    
}
