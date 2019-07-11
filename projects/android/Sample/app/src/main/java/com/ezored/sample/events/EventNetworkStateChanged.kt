package com.ezored.sample.events

class EventNetworkStateChanged : BaseEvent {

    var isConnected = true
    var type: Int = 0

    constructor(isConnected: Boolean, type: Int) : super() {
        this.isConnected = isConnected
        this.type = type
    }

}
