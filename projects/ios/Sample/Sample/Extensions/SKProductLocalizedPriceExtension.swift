import Foundation
import StoreKit

extension SKProduct {
    
    var localizedPrice: String {
        let formatter = NumberFormatter()
        formatter.numberStyle = .currency
        formatter.locale = self.priceLocale
        return formatter.string(from: self.price) ?? "\(price)"
    }
    
}
