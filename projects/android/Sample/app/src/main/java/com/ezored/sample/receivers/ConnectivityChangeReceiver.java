package com.ezored.sample.receivers;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import com.ezored.sample.events.EventNetworkStateChanged;
import com.ezored.util.Logger;

import org.greenrobot.eventbus.EventBus;

public class ConnectivityChangeReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();

        if (activeNetwork != null) {
            boolean isConnected = activeNetwork.isConnected();

            EventNetworkStateChanged eventNetworkStateChanged = new EventNetworkStateChanged(isConnected, activeNetwork.getType());
            EventBus.getDefault().post(eventNetworkStateChanged);

            Logger.d("[ConnectivityChangeReceiver : onReceive] Connected: " + (isConnected ? "YES" : "NO") + " / Type: " + activeNetwork.getTypeName());
        } else {
            EventNetworkStateChanged eventNetworkStateChanged = new EventNetworkStateChanged(false, 0);
            EventBus.getDefault().post(eventNetworkStateChanged);

            Logger.d("[ConnectivityChangeReceiver : onReceive] Connected: NO");
        }
    }

}
