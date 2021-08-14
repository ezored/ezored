import Foundation
import UIKit

class UIUtil {
    static func showAlert(parent: UIViewController, title: String?, message: String?, onClose _: (() -> Void)?) {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        alertController.addAction(UIAlertAction(title: "DialogButtonOK".localized, style: .default))
        parent.present(alertController, animated: true, completion: nil)
    }

    static func generateRandomColor() -> UIColor {
        let hue = CGFloat(arc4random() % 256) / 256 // use 256 to get full range from 0.0 to 1.0
        let saturation = CGFloat(arc4random() % 128) / 256 + 0.5 // from 0.5 to 1.0 to stay away from white
        let brightness = CGFloat(arc4random() % 128) / 256 + 0.5 // from 0.5 to 1.0 to stay away from black

        return UIColor(hue: hue, saturation: saturation, brightness: brightness, alpha: 1)
    }

    static func createAttributedString(_ content: String?, fontSize: Float?, textColor: String?, fontFamily: String?, textAlign: NSTextAlignment?, lineBreakMode: NSLineBreakMode?) -> NSMutableAttributedString {
        if let content = content {
            var text = content
            var styles = ""
            var useSystemFont = false

            if let fontFamily = fontFamily {
                styles = styles + String(format: "font-family: %@;", fontFamily)
            } else {
                if #available(iOS 10.0, *) {
                    styles = styles + String(format: "font-family: %@;", "-apple-system")
                } else {
                    useSystemFont = true
                }
            }

            if let fontSize = fontSize {
                if !useSystemFont {
                    styles = styles + String(format: "font-size: %fpx;", fontSize)
                }
            }

            text = String(format: "<span style='%@'>%@</span>", styles, content)

            let attrStr = try? NSMutableAttributedString(
                data: text.data(using: .unicode, allowLossyConversion: true)!,
                options: [NSAttributedString.DocumentReadingOptionKey.documentType: NSAttributedString.DocumentType.html],
                documentAttributes: nil
            )

            if let attrStr = attrStr {
                if let textColor = textColor {
                    attrStr.beginEditing()
                    attrStr.addAttribute(NSAttributedString.Key.foregroundColor, value: UIColor(hexString: textColor)!, range: NSMakeRange(0, attrStr.length))
                    attrStr.endEditing()
                }
            }

            if let attrStr = attrStr {
                if let textAlign = textAlign {
                    let paragraph = NSMutableParagraphStyle()
                    paragraph.alignment = textAlign

                    attrStr.beginEditing()
                    attrStr.addAttribute(NSAttributedString.Key.paragraphStyle, value: paragraph, range: NSMakeRange(0, attrStr.length))
                    attrStr.endEditing()
                }
            }

            if let attrStr = attrStr {
                if let lineBreakMode = lineBreakMode {
                    let paragraph = NSMutableParagraphStyle()
                    paragraph.lineBreakMode = lineBreakMode

                    attrStr.beginEditing()
                    attrStr.addAttribute(NSAttributedString.Key.paragraphStyle, value: paragraph, range: NSMakeRange(0, attrStr.length))
                    attrStr.endEditing()
                }
            }

            if useSystemFont {
                if let attrStr = attrStr {
                    if let fontSize = fontSize {
                        attrStr.beginEditing()
                        attrStr.addAttribute(NSAttributedString.Key.font, value: UIFont.systemFont(ofSize: CGFloat(fontSize)), range: NSMakeRange(0, attrStr.length))
                        attrStr.endEditing()
                    }
                }
            }

            return attrStr ?? NSMutableAttributedString()
        }

        return NSMutableAttributedString()
    }

    static func isPresentedViewController(viewController: UIViewController?) -> Bool {
        if let viewController = viewController {
            if let _ = viewController.presentingViewController {
                return true
            }

            if viewController.navigationController?.presentingViewController?.presentedViewController == viewController {
                return true
            }

            if viewController.tabBarController?.presentingViewController is UITabBarController {
                return true
            }
        }

        return false
    }

    static func vibrateForLongPressFeedback() {
        if #available(iOS 10.0, *) {
            let generator = UIImpactFeedbackGenerator(style: .light)
            generator.impactOccurred()
        } else {
            // para versões anteriores não temos o que usar
        }
    }

    static func formattedSeconds(totalSeconds: Int32) -> String {
        let seconds = totalSeconds % 60
        let minutes = (totalSeconds / 60) % 60
        let hours = totalSeconds / 3600

        if hours == 0 {
            if minutes == 0 {
                return String(format: "%02ds", seconds)
            }

            return String(format: "%02dm", minutes)
        }

        return String(format: "%02dh%02dm", hours, minutes)
    }

    static func appInBackground() -> Bool {
        let state = UIApplication.shared.applicationState

        if state == .background {
            return true
        }

        return false
    }

    static func isPortrait() -> Bool {
        var portraitOrientation = UIDevice.current.orientation == .portrait

        if UIDevice.current.orientation == .unknown || UIDevice.current.orientation == .faceUp {
            portraitOrientation = UIApplication.shared.statusBarOrientation == .portrait
        }

        if portraitOrientation {
            return true
        }

        return false
    }

    static func openExternalURL(with url: String) {
        if url.isEmpty { return }

        if #available(iOS 10.0, *) {
            UIApplication.shared.open(URL(string: url)!, options: [:], completionHandler: nil)
        } else {
            UIApplication.shared.openURL(URL(string: url)!)
        }
    }
}
