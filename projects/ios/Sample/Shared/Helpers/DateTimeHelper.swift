import Foundation

class DateTimeHelper {
    static func getCurrentTimeStamp() -> TimeInterval {
        return Date().timeIntervalSince1970
    }

    static func formatAsMysql(date: Date) -> String {
        let formatter = DateFormatter()
        formatter.timeZone = TimeZone(secondsFromGMT: 0)
        formatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        return formatter.string(from: date)
    }

    static func formatAsDeviceSettings(date: Date) -> String {
        let formatter = DateFormatter()
        formatter.timeZone = TimeZone.current
        formatter.dateStyle = .medium
        formatter.timeStyle = .medium
        return formatter.string(from: date)
    }

    static func formatAsUnixEpoch(date: Date) -> String {
        return "\(date.timeIntervalSince1970)"
    }

    static func formatShortAsDeviceSettings(date: Date) -> String {
        let formatter = DateFormatter()
        formatter.timeZone = TimeZone.current
        formatter.dateStyle = .short
        formatter.timeStyle = .none
        return formatter.string(from: date)
    }

    static func daysBy(date: Date) -> Int {
        let components = Calendar.current.dateComponents([.day], from: Date(), to: date)

        if let days = components.day {
            return days
        }
        return 0
    }
}
