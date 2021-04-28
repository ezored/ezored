import WatchKit

extension EnvironmentUtil {
    
    static func getCurrentRegionCode() -> String {
        if let regionCode = Locale.current.regionCode {
            return regionCode
        }

        return ""
    }
    
    static func getDeviceId() -> String {
        if let value = WKInterfaceDevice.current().identifierForVendor?.uuidString {
            return value
        }

        return ""
    }

}
