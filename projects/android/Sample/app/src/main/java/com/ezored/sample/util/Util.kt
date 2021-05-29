package com.ezored.sample.util

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.net.NetworkCapabilities
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.text.TextUtils
import android.view.accessibility.AccessibilityManager
import com.ezored.sample.app.Application
import java.util.Random

@Suppress("Deprecation", "Unused")
object Util {

    val isNetworkAvailable: Boolean
        get() {
            val cm =
                Application.instance.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
            return cm.activeNetworkInfo != null && (cm.activeNetworkInfo?.isConnected ?: false)
        }

    private val isNetworkWifi: Boolean
        get() {
            val cm =
                Application.instance.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

            return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                cm.getNetworkCapabilities(cm.activeNetwork)
                    ?.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)
                    ?: false
            } else {
                cm.activeNetworkInfo?.type == ConnectivityManager.TYPE_WIFI
            }
        }

    fun convertMapToBundle(map: Map<String, String>?): Bundle {
        val bundle = Bundle(map?.size ?: 0)

        if (map != null) {
            for ((key, value) in map) {
                bundle.putString(key, value)
            }
        }

        return bundle
    }

    fun randomInt(min: Int, max: Int): Int {
        val r = Random()
        return r.nextInt(max - min + 1) + min
    }

    fun toClockTimestampInSecondsFormat(ms: Long): String {
        // converts to seconds first
        val newMS = ms / 1000

        // convert others
        val h = newMS / 3600
        val m = newMS % 3600 / 60
        val s = newMS % 60

        var str = String.format("%02d:", m) + String.format("%02d", s)

        if (h > 0) {
            // only show hour digits if they are nonzero.
            str = String.format("%02d:", h) + str
        }

        return str
    }

    fun isAccessibilityEnabled(context: Context): Boolean {
        val am = context.getSystemService(Context.ACCESSIBILITY_SERVICE) as AccessibilityManager
        return am.isEnabled
    }

    fun openExternalURL(context: Context?, url: String) {
        if (context == null) {
            return
        }

        if (TextUtils.isEmpty(url)) {
            return
        }

        val browserIntent = Intent(Intent.ACTION_VIEW, Uri.parse(url))
        context.startActivity(browserIntent)
    }

    fun randomString(size: Int): String {
        val generator = Random()
        val randomStringBuilder = StringBuilder()
        var tempChar: Char

        for (i in 0 until size) {
            tempChar = (generator.nextInt(96) + 32).toChar()
            randomStringBuilder.append(tempChar)
        }

        return randomStringBuilder.toString()
    }
}
