import Foundation
import UIKit

extension String {
    
    func sizeOfString(constrainedToHeight height: CGFloat, withFontSize fontSize: CGFloat) -> CGSize {
        return NSString(string: self).boundingRect(
            with: CGSize(width: CGFloat(Double.greatestFiniteMagnitude), height: height),
            options: NSStringDrawingOptions.usesLineFragmentOrigin,
            attributes: [NSAttributedString.Key.font: UIFont.systemFont(ofSize: fontSize)],
            context: nil
            ).size
    }
    
    func encodeUrl() -> String? {
        return self.addingPercentEncoding(withAllowedCharacters: .urlHostAllowed)
    }
    
    func decodeUrl() -> String? {
        return self.removingPercentEncoding
    }
    
    var isValidURL: Bool {
        let detector = try! NSDataDetector(types: NSTextCheckingResult.CheckingType.link.rawValue)
        
        if let match = detector.firstMatch(in: self, options: [], range: NSRange(location: 0, length: self.endIndex.utf16Offset(in: self))) {
            return match.range.length == self.endIndex.utf16Offset(in: self)
        } else {
            return false
        }
    }
}
