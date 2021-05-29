import Foundation
import UIKit

extension UIDevice {
    var iPhone: Bool {
        return UIDevice().userInterfaceIdiom == .phone
    }

    enum ScreenType: String {
        case iPhone4
        case iPhone5
        case iPhone6
        case iPhone6Plus
        case Unknown
    }

    var screenType: ScreenType? {
        guard iPhone else { return nil }
        switch UIScreen.main.nativeBounds.height {
        case 960:
            return .iPhone4
        case 1136:
            return .iPhone5
        case 1334:
            return .iPhone6
        case 2208:
            return .iPhone6Plus
        default:
            return nil
        }
    }

    static func isScreen35inch() -> Bool {
        return UIDevice().screenType == .iPhone4
    }

    func isScreen4inch() -> Bool {
        return UIDevice().screenType == .iPhone5
    }

    func isScreen47inch() -> Bool {
        return UIDevice().screenType == .iPhone6
    }

    func isScreen55inch() -> Bool {
        return UIDevice().screenType == .iPhone6Plus
    }
}
