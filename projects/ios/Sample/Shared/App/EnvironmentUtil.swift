import Foundation

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

}
