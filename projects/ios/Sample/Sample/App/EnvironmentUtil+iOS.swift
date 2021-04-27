import CoreTelephony
import Foundation
import UIKit

extension EnvironmentUtil {
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

    static func getDeviceId() -> String {
        if let value = UIDevice.current.identifierForVendor?.uuidString {
            return value
        }

        return ""
    }
}
