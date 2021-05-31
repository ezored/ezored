package com.ezored.util;

import android.util.Log;

public class LoggerPlatformServiceImpl extends LoggerPlatformService {

    private String group;

    public LoggerPlatformServiceImpl(String group) {
        this.group = group;
    }

    @Override
    public void v(String message) {
        Log.v(group, message);
    }

    @Override
    public void d(String message) {
        Log.d(group, message);
    }

    @Override
    public void i(String message) {
        Log.i(group, message);
    }

    @Override
    public void w(String message) {
        Log.w(group, message);
    }

    @Override
    public void e(String message) {
        Log.e(group, message);
    }

    @Override
    public void setGroup(String group) {
        this.group = group;
    }

}