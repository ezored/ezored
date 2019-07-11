package com.ezored.sample.utils;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import com.ezored.domain.DeviceData;
import com.ezored.domain.InitializationData;
import com.ezored.sample.BuildConfig;
import com.ezored.sample.app.Application;

import java.util.Locale;

import static android.provider.Settings.Secure;

public class EnvironmentUtil {

    public static String getAndroidId() {
        String id = Secure.getString(Application.getInstance().getContentResolver(), Secure.ANDROID_ID);

        if (TextUtils.isEmpty(id)) {
            return "";
        }

        return id;
    }

    public static String getFormattedSystemVersion() {
        return String.format("Android %s (API %s)", Build.VERSION.RELEASE, Build.VERSION.SDK_INT);
    }

    private static PackageInfo getPackageInfo() throws PackageManager.NameNotFoundException {
        Context context = Application.getInstance();
        PackageManager manager = context.getPackageManager();
        return manager.getPackageInfo(context.getPackageName(), 0);
    }

    public static String getAppVersionName() {
        try {
            return getPackageInfo().versionName;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return "";
    }

    public static int getAppVersionCode() {
        try {
            return getPackageInfo().versionCode;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }

        return 0;
    }

    public static int getScreenWidth() {
        return Application.getInstance().getResources().getDisplayMetrics().widthPixels;
    }

    public static int getScreenHeight() {
        return Application.getInstance().getResources().getDisplayMetrics().heightPixels;
    }

    public static float getScreenScale() {
        return Application.getInstance().getResources().getDisplayMetrics().density;
    }

    public static String getCurrentRegionCode() {
        try {
            // try get the region code using carrier informations
            TelephonyManager tm = (TelephonyManager) Application.getInstance().getSystemService(Context.TELEPHONY_SERVICE);

            if (tm != null) {
                String code = tm.getNetworkCountryIso();

                if (!TextUtils.isEmpty(code)) {
                    return code;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // if fail, get by the device locale
        return Locale.getDefault().getCountry();
    }

    public static String getAppName() {
        Context context = Application.getInstance();

        if (null != context) {
            return context.getApplicationInfo().loadLabel(context.getPackageManager()).toString();
        }

        return "";
    }

    public static DeviceData getDeviceData() {
        String deviceId = EnvironmentUtil.getAndroidId();
        String name = Build.MODEL;
        String systemName = "Android";
        String systemVersion = EnvironmentUtil.getFormattedSystemVersion();
        String model = Build.DEVICE;
        String localizedModel = Build.DEVICE;
        String appVersion = String.valueOf(EnvironmentUtil.getAppVersionCode());
        String appShortVersion = EnvironmentUtil.getAppVersionName();
        String appName = EnvironmentUtil.getAppName();
        float screenWidth = EnvironmentUtil.getScreenWidth();
        float screenHeight = EnvironmentUtil.getScreenHeight();
        float screenScale = EnvironmentUtil.getScreenScale();
        String systemOSName = "android";
        String systemLanguage = Locale.getDefault().getLanguage();
        String imei = "";
        String region = EnvironmentUtil.getCurrentRegionCode();

        if (TextUtils.isEmpty(deviceId)) {
            deviceId = "";
        }

        if (TextUtils.isEmpty(systemVersion)) {
            systemVersion = "";
        }

        if (TextUtils.isEmpty(appVersion)) {
            appVersion = "";
        }

        if (TextUtils.isEmpty(appShortVersion)) {
            appShortVersion = "";
        }

        if (TextUtils.isEmpty(appName)) {
            appName = "";
        }

        if (TextUtils.isEmpty(systemLanguage)) {
            systemLanguage = "";
        }

        if (TextUtils.isEmpty(imei)) {
            imei = "";
        }

        if (TextUtils.isEmpty(region)) {
            region = "";
        }

        return new DeviceData(deviceId, name, systemName, systemVersion, model, localizedModel, appVersion, appShortVersion, appName, screenWidth, screenHeight, screenScale, systemOSName, systemLanguage, imei, region);
    }

    public static InitializationData getInitializationData() {
        String basePath = Application.getInstance().getFilesDir().getAbsolutePath();

        if (TextUtils.isEmpty(basePath)) {
            basePath = "";
        }

        return new InitializationData(Application.getInstance().getPackageName(), BuildConfig.FLAVOR, basePath, 0, BuildConfig.DEBUG);
    }

}
