import UIKit

/// Represents parts of time
struct TimeParts: CustomStringConvertible {
    var seconds: Int32 = 0
    var minutes: Int32 = 0
    /// The string representation of the time parts (ex: 07:37)
    var description: String {
        return NSString(format: "%02d:%02d", minutes, seconds) as String
    }
}

/// Represents unset or empty time parts
let EmptyTimeParts = Int32(0).toTimeParts()

extension Int32 {
    /// The time parts for this integer represented from total seconds in time.
    /// -- returns: A TimeParts struct that describes the parts of time
    func toTimeParts() -> TimeParts {
        let seconds = self

        var mins: Int32 = 0
        var secs: Int32 = seconds

        if seconds >= 60 {
            mins = Int32(seconds / 60)
            secs = seconds - (mins * 60)
        }

        return TimeParts(seconds: secs, minutes: mins)
    }

    /// The string representation of the time parts (ex: 07:37)
    func asTimeString() -> String {
        return toTimeParts().description
    }
}
