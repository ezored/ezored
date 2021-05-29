package com.ezored.sample.event

class EventNetworkStateChanged : BaseEvent {

    var isConnected = true
    var type: Int = 0

    constructor(isConnected: Boolean, type: Int) : super() {
        this.isConnected = isConnected
        this.type = type
    }
}
