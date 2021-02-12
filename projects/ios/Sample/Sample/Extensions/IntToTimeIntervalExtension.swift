import Foundation

extension Int {
    var seconds: Int {
        return self
    }

    var minutes: Int {
        return seconds * 60
    }

    var hours: Int {
        return minutes * 60
    }

    var days: Int {
        return hours * 24
    }

    var weeks: Int {
        return days * 7
    }

    var months: Int {
        return weeks * 4
    }

    var years: Int {
        return months * 12
    }
}
