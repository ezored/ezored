import Foundation

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
        return addingPercentEncoding(withAllowedCharacters: .urlHostAllowed)
    }

    func decodeUrl() -> String? {
        return removingPercentEncoding
    }

    var isValidURL: Bool {
        let detector = try! NSDataDetector(types: NSTextCheckingResult.CheckingType.link.rawValue)

        if let match = detector.firstMatch(in: self, options: [], range: NSRange(location: 0, length: endIndex.utf16Offset(in: self))) {
            return match.range.length == endIndex.utf16Offset(in: self)
        } else {
            return false
        }
    }
}
