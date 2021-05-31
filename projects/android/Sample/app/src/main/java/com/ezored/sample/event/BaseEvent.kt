package com.ezored.sample.event

open class BaseEvent {

    var tag: String? = null

    fun tagIsEqual(tagToCompare: String): Boolean {
        return if (tag == null) {
            false
        } else tag == tagToCompare
    }
}
