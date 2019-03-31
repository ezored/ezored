package com.ezored.sample.events;

public class EventNetworkStateChanged extends BaseEvent {

    private int type;

    private boolean connected = true;

    public EventNetworkStateChanged(boolean connected, int type) {
        this.type = type;
        this.connected = connected;
    }

    public int getType() {
        return type;
    }

    public boolean isConnected() {
        return connected;
    }

}
