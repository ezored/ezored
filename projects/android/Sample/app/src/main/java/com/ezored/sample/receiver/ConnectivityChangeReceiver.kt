package com.ezored.sample.receiver

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import com.ezored.sample.event.EventNetworkStateChanged
import com.ezored.util.Logger
import org.greenrobot.eventbus.EventBus

class ConnectivityChangeReceiver : BroadcastReceiver() {

    @Suppress("Deprecation")
    override fun onReceive(context: Context, intent: Intent) {
        val cm = context.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val activeNetwork = cm.activeNetworkInfo

        if (activeNetwork != null) {
            val isConnected = activeNetwork.isConnected

            val eventNetworkStateChanged = EventNetworkStateChanged(isConnected, activeNetwork.type)
            EventBus.getDefault().post(eventNetworkStateChanged)

            Logger.d("[ConnectivityChangeReceiver : onReceive] Connected: " + (if (isConnected) "YES" else "NO") + " / Type: " + activeNetwork.typeName)
        } else {
            val eventNetworkStateChanged = EventNetworkStateChanged(false, 0)
            EventBus.getDefault().post(eventNetworkStateChanged)

            Logger.d("[ConnectivityChangeReceiver : onReceive] Connected: NO")
        }
    }
}
