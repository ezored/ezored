import Foundation
import UIKit

extension UIImage {
    func create(withText text: String, offset: CGPoint) -> UIImage? {
        let font = UIFont.boldSystemFont(ofSize: 11)
        let _text = (text as NSString)

        UIGraphicsBeginImageContextWithOptions(size, false, 0.0)

        // background
        draw(in: CGRect(x: 0, y: 0, width: size.width, height: size.height))

        // text
        let textSize = _text.size(withAttributes: [NSAttributedString.Key.font: font])

        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.lineBreakMode = .byWordWrapping
        paragraphStyle.alignment = .center

        let attributes = [NSAttributedString.Key.font: font,
                          NSAttributedString.Key.foregroundColor: UIColor.white,
                          NSAttributedString.Key.paragraphStyle: paragraphStyle]

        _text.draw(in: CGRect(x: 0 + offset.x, y: (size.width / 2) - (textSize.width / 2) + offset.y, width: size.width, height: size.height), withAttributes: attributes)

        // final image
        let imageWithText = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()

        return imageWithText
    }

    func cropToBounds(width: Double, height: Double) -> UIImage {
        let cgimage = cgImage!
        let contextImage = UIImage(cgImage: cgimage)
        let contextSize: CGSize = contextImage.size
        var posX: CGFloat = 0.0
        var posY: CGFloat = 0.0
        var cgwidth = CGFloat(width)
        var cgheight = CGFloat(height)

        if contextSize.width > contextSize.height {
            posX = ((contextSize.width - contextSize.height) / 2)
            posY = 0
            cgwidth = contextSize.height
            cgheight = contextSize.height
        } else {
            posX = 0
            posY = ((contextSize.height - contextSize.width) / 2)
            cgwidth = contextSize.width
            cgheight = contextSize.width
        }

        let rect = CGRect(x: posX, y: posY, width: cgwidth, height: cgheight)
        let imageRef: CGImage = cgimage.cropping(to: rect)!
        let image = UIImage(cgImage: imageRef, scale: scale, orientation: imageOrientation)

        return image
    }
}
