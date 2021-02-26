package com.ezored.data;

import android.content.Context;
import android.content.SharedPreferences;

public class SharedDataPlatformServiceImpl extends SharedDataPlatformService {

    private final Context context;

    public SharedDataPlatformServiceImpl(Context context) {
        this.context = context;
    }

    @Override
    public void setString(String groupName, String key, String value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putString(key, value).apply();
        }
    }

    @Override
    public void setInteger(String groupName, String key, int value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putInt(key, value).apply();
        }
    }

    @Override
    public void setLong(String groupName, String key, long value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putLong(key, value).apply();
        }
    }

    @Override
    public void setBool(String groupName, String key, boolean value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putBoolean(key, value).apply();
        }
    }

    @Override
    public void setFloat(String groupName, String key, float value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putFloat(key, value).apply();
        }
    }

    @Override
    public void setDouble(String groupName, String key, double value) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.putFloat(key, (float) value).apply();
        }
    }

    @Override
    public String getString(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            String value = sharedPreferences.getString(key, null);

            if (value != null) {
                return value;
            }
        }

        return "";
    }

    @Override
    public int getInteger(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.getInt(key, 0);
        }

        return 0;
    }

    @Override
    public long getLong(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.getLong(key, 0);
        }

        return 0;
    }

    @Override
    public boolean getBool(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.getBoolean(key, false);
        }

        return false;
    }

    @Override
    public float getFloat(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.getFloat(key, 0);
        }

        return 0;
    }

    @Override
    public double getDouble(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.getFloat(key, 0);
        }

        return 0;
    }

    @Override
    public String getStringWithDefaultValue(String groupName, String key, String defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                String value = sharedPreferences.getString(key, null);

                if (value != null) {
                    return value;
                }
            }
        }

        if (defaultValue != null) {
            return defaultValue;
        } else {
            return "";
        }
    }

    @Override
    public int getIntegerWithDefaultValue(String groupName, String key, int defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                return sharedPreferences.getInt(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public long getLongWithDefaultValue(String groupName, String key, long defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                return sharedPreferences.getLong(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public boolean getBoolWithDefaultValue(String groupName, String key, boolean defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                return sharedPreferences.getBoolean(key, false);
            }
        }

        return defaultValue;
    }

    @Override
    public float getFloatWithDefaultValue(String groupName, String key, float defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                return sharedPreferences.getFloat(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public double getDoubleWithDefaultValue(String groupName, String key, double defaultValue) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            if (sharedPreferences.contains(key)) {
                return sharedPreferences.getFloat(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public boolean has(String groupName, String key) {
        SharedPreferences sharedPreferences = createSharedPreferences(groupName);

        if (sharedPreferences != null && key != null) {
            return sharedPreferences.contains(key);
        }

        return false;
    }

    @Override
    public void remove(String groupName, String key) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null && key != null) {
            editor.remove(key).apply();
        }
    }

    @Override
    public void clear(String groupName) {
        SharedPreferences.Editor editor = createEditor(groupName);

        if (editor != null) {
            editor.clear().apply();
        }
    }

    private SharedPreferences createSharedPreferences(String groupName) {
        return context.getSharedPreferences(groupName, Context.MODE_PRIVATE);
    }

    private SharedPreferences.Editor createEditor(String groupName) {
        SharedPreferences sharedPreferences = context.getSharedPreferences(groupName, Context.MODE_PRIVATE);
        return sharedPreferences.edit();
    }

}