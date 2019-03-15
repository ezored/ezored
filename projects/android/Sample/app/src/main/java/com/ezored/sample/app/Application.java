package com.ezored.sample.app;

import android.arch.lifecycle.ProcessLifecycleOwner;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.multidex.MultiDexApplication;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatDelegate;
import android.util.Log;

import com.dropbox.djinni.JNILoader;
import com.ezored.core.ApplicationCore;
import com.ezored.data.SharedData;
import com.ezored.data.SharedDataPlatformServiceImpl;
import com.ezored.domain.DeviceData;
import com.ezored.domain.InitializationData;
import com.ezored.io.FileHelper;
import com.ezored.io.FileHelperPlatformServiceImpl;
import com.ezored.net.http.HttpClient;
import com.ezored.net.http.HttpClientPlatformServiceImpl;
import com.ezored.sample.BuildConfig;
import com.ezored.sample.data.AppData;
import com.ezored.sample.observers.AppLifecycleObserver;
import com.ezored.sample.receivers.ConnectivityChangeReceiver;
import com.ezored.sample.utils.EnvironmentUtil;
import com.ezored.sample.utils.Utils;
import com.ezored.util.Logger;
import com.ezored.util.LoggerLevel;
import com.ezored.util.LoggerPlatformServiceImpl;

import java.util.EnumSet;

public class Application extends MultiDexApplication {

    private static String LOG_GROUP = "SAMPLE";
    private static Application instance;
    private AppData appData;

    @Override
    public void onCreate() {
        super.onCreate();

        instance = this;

        appData = new AppData();

        AppCompatDelegate.setCompatVectorFromResourcesEnabled(true);

        loadNativeLibrary();

        ProcessLifecycleOwner.get().getLifecycle().addObserver(new AppLifecycleObserver());

        registerReceivers();

        if (BuildConfig.DEBUG) {
            Utils.showFacebookKeyHash(this);
        }
    }

    public AppData getAppData() {
        return appData;
    }

    private void registerReceivers() {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("android.net.conn.CONNECTIVITY_CHANGE");

        registerReceiver(new ConnectivityChangeReceiver(), intentFilter);
    }

    public static Application getInstance() {
        return instance;
    }

    public void startServiceOrForegroundService(Intent intent) {
        try {
            ContextCompat.startForegroundService(this, intent);
        } catch (Exception e) {
            Logger.e("[Application : startServiceOrForegroundService] Failed to start foreground service");
            e.printStackTrace();
        }
    }

    @Override
    public void onTerminate() {
        Logger.i("[Application : onTerminate] App terminated");
        super.onTerminate();
    }

    public void onMoveToForeground() {
        Logger.i("[Application : onMoveToForeground] App moved to foreground");
        getAppData().setAppInBackground(false);
    }

    public void onMoveToBackground() {
        Logger.i("[Application : onMoveToBackground] App moved to background");
        getAppData().setAppInBackground(true);
    }

    private void loadNativeLibrary() {
        try {
            System.loadLibrary("Core"); 

            JNILoader.load();

            initializeLogger();
            initializeHTTPClient();
            initializeSharedData();
            initializeFileHelper();
            initializeCore();
        } catch (UnsatisfiedLinkError e) {
            Log.e(LOG_GROUP, "Could not load native library");
            e.printStackTrace();
        }
    }

    private void initializeCore() {
        InitializationData initializationData = EnvironmentUtil.getInitializationData();
        DeviceData deviceData = EnvironmentUtil.getDeviceData();

        ApplicationCore.shared().initialize(initializationData, deviceData);
    }

    private void initializeLogger() {
        Logger.shared().setPlatformService(new LoggerPlatformServiceImpl(LOG_GROUP));

        if (BuildConfig.DEBUG) {
            Logger.shared().setLevel(LoggerLevel.VERBOSE);
        } else {
            Logger.shared().setLevel(LoggerLevel.ERROR);
        }
    }

    private void initializeHTTPClient() {
        HttpClient.shared().setPlatformService(new HttpClientPlatformServiceImpl());
    }

    private void initializeSharedData() {
        SharedData.shared().setPlatformService(new SharedDataPlatformServiceImpl(getApplicationContext()));
    }

    private void initializeFileHelper() {
        FileHelper.shared().setPlatformService(new FileHelperPlatformServiceImpl());
    }

}
