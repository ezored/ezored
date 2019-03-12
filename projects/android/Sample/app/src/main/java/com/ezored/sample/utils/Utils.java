package com.ezored.sample.utils;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.view.accessibility.AccessibilityManager;
import com.ezored.sample.app.Application;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Map;
import java.util.Random;

public class Utils {

    public static boolean isNetworkAvailable() {
        final ConnectivityManager connectivityManager = ((ConnectivityManager) Application.getInstance().getSystemService(Application.getInstance().CONNECTIVITY_SERVICE));

        if (connectivityManager.getActiveNetworkInfo() != null && connectivityManager.getActiveNetworkInfo().isConnected()) {
            return true;
        }

        return false;
    }

    private static boolean isNetworkWifi() {
        final ConnectivityManager connectivityManager = ((ConnectivityManager) Application.getInstance().getSystemService(Application.getInstance().CONNECTIVITY_SERVICE));
        NetworkInfo activeNetwork = connectivityManager.getActiveNetworkInfo();

        if (activeNetwork != null && activeNetwork.getType() == ConnectivityManager.TYPE_WIFI) {
            return true;
        }

        return false;
    }

    public static Bundle convertMapToBundle(Map<String, String> map) {
        Bundle bundle = new Bundle(map != null ? map.size() : 0);

        if (map != null) {
            for (Map.Entry<String, String> entry : map.entrySet()) {
                bundle.putString(entry.getKey(), entry.getValue());
            }
        }

        return bundle;
    }

    public static int randomInt(int min, int max) {
        Random r = new Random();
        return r.nextInt(max - min + 1) + min;
    }

    public static String toClockTimestampInSecondsFormat(long ms) {
        ms = ms / 1000; // Converts to seconds first.
        long h = ms / 3600;
        long m = ms % 3600 / 60;
        long s = ms % 60;

        String str = String.format("%02d:", m) + String.format("%02d", s);
        if (h > 0) { // Only show hour digits if they are nonzero.
            str = String.format("%02d:", h) + str;
        }
        return str;
    }

    public static boolean isAccessibilityEnabled(Context context) {
        AccessibilityManager am = (AccessibilityManager) context.getSystemService(Context.ACCESSIBILITY_SERVICE);

        if (am != null) {
            return am.isEnabled();
        } else {
            return false;
        }
    }

    public static void openExternalURL(Context context, String url) {
        if (context == null) {
            return;
        }

        if (TextUtils.isEmpty(url)) {
            return;
        }

        Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        context.startActivity(browserIntent);
    }

    public static void showFacebookKeyHash(Context context) {
        try {
            PackageInfo info = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);

            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                Log.d("KeyHash:", Base64.encodeToString(md.digest(), Base64.DEFAULT));
            }
        } catch (PackageManager.NameNotFoundException e) {
            // ignore
        } catch (NoSuchAlgorithmException e) {
            // ignore
        }
    }

}
