import Foundation

extension Collection {
    func get(at i: Self.Index) -> Self.Iterator.Element? {
        return indices.contains(i) ? self[i] : nil
    }
}

extension Array where Element: NSObject {
    mutating func appendIfNotContains(_ element: Element) {
        if !contains(element) {
            append(element)
        }
    }
}

extension Optional where Wrapped: Collection {
    var isNullOrEmpty: Bool { return self == nil || self?.isEmpty == true }
}

/// Returns the first argument if it's not null and not empty, otherwise will return the second argument.
infix operator ?!: NilCoalescingPrecedence

@inlinable func ?! <T: Collection>(optional: T?, defaultValue: @autoclosure () throws -> T) rethrows -> T {
    if let value = optional,
       !value.isEmpty
    {
        return value
    } else {
        return try defaultValue()
    }
}
