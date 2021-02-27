import CoreTelephony
import Foundation
import UIKit

class EnvironmentUtil {
    static func getCurrentLanguageCode() -> String {
        if Locale.preferredLanguages.count > 0 {
            return Locale.preferredLanguages[0]
        }

        if Bundle.main.preferredLocalizations.count > 0 {
            return Bundle.main.preferredLocalizations[0]
        }

        return "en"
    }

    static func getCurrentRegionCode() -> String {
        #if !targetEnvironment(macCatalyst)
            let networkInfo = CTTelephonyNetworkInfo()

            if let carrier = networkInfo.subscriberCellularProvider {
                if let countryCode = carrier.isoCountryCode {
                    return countryCode
                }
            }
        #endif

        if let regionCode = Locale.current.regionCode {
            return regionCode
        }

        return ""
    }

    static func getAppVersion() -> String {
        if let value = Bundle.main.infoDictionary?["CFBundleVersion"] as? String {
            return value
        }

        return ""
    }

    static func getAppShortVersion() -> String {
        if let value = Bundle.main.infoDictionary?["CFBundleShortVersionString"] as? String {
            return value
        }

        return ""
    }

    static func getAppDisplayName() -> String {
        if let value = Bundle.main.infoDictionary?["CFBundleDisplayName"] as? String {
            return value
        }

        return ""
    }

    static func getAppName() -> String {
        if let value = Bundle.main.infoDictionary?[kCFBundleNameKey as String] as? String {
            return value
        }

        return ""
    }

    static func getDeviceId() -> String {
        if let value = UIDevice.current.identifierForVendor?.uuidString {
            return value
        }

        return ""
    }
}
