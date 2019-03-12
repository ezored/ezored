package com.ezored.data;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;

public class SharedDataPlatformServiceImpl extends SharedDataPlatformService {

    private SharedPreferences sharedPreferences;
    private SharedPreferences.Editor editor;
    private Context context;

    private String groupName;

    public SharedDataPlatformServiceImpl(Context context) {
        this.context = context;
    }

    @Override
    public void setString(String key, String value) {
        if (editor != null) {
            editor.putString(key, value);
        }
    }

    @Override
    public void setInteger(String key, int value) {
        if (editor != null) {
            editor.putInt(key, value);
        }
    }

    @Override
    public void setLong(String key, long value) {
        if (editor != null) {
            editor.putLong(key, value);
        }
    }

    @Override
    public void setBool(String key, boolean value) {
        if (editor != null) {
            editor.putBoolean(key, value);
        }
    }

    @Override
    public void setFloat(String key, float value) {
        if (editor != null) {
            editor.putFloat(key, value);
        }
    }

    @Override
    public void setDouble(String key, double value) {
        if (editor != null) {
            editor.putFloat(key, (float) value);
        }
    }

    @Override
    public String getString(String key) {
        if (sharedPreferences != null) {
            String value = sharedPreferences.getString(key, null);

            if (value != null) {
                return value;
            }
        }

        return "";
    }

    @Override
    public int getInteger(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.getInt(key, 0);
        }

        return 0;
    }

    @Override
    public long getLong(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.getLong(key, 0);
        }

        return 0;
    }

    @Override
    public boolean getBool(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.getBoolean(key, false);
        }

        return false;
    }

    @Override
    public float getFloat(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.getFloat(key, 0);
        }

        return 0;
    }

    @Override
    public double getDouble(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.getFloat(key, 0);
        }

        return 0;
    }

    @Override
    public void save(boolean async, boolean autoFinish) {
        if (editor != null) {
            if (async) {
                editor.apply();
            } else {
                editor.commit();
            }
        }

        if (autoFinish) {
            finish();
        }
    }

    @SuppressLint("CommitPrefEdits")
    @Override
    public void start(String groupName) {
        if (context != null) {
            this.groupName = groupName;

            sharedPreferences = context.getSharedPreferences(groupName, Context.MODE_PRIVATE);
            editor = sharedPreferences.edit();
        }
    }

    @Override
    public void finish() {
        sharedPreferences = null;
        editor = null;
    }

    @Override
    public void saveAsync() {
        save(true, true);
    }

    @Override
    public void saveSync() {
        save(false, true);
    }

    @Override
    public String getStringWithDefaultValue(String key, String defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                String value = sharedPreferences.getString(key, null);

                if (value != null) {
                    return value;
                }
            }
        }

        return defaultValue;
    }

    @Override
    public int getIntegerWithDefaultValue(String key, int defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                return sharedPreferences.getInt(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public long getLongWithDefaultValue(String key, long defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                return sharedPreferences.getLong(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public boolean getBoolWithDefaultValue(String key, boolean defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                return sharedPreferences.getBoolean(key, false);
            }
        }

        return defaultValue;
    }

    @Override
    public float getFloatWithDefaultValue(String key, float defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                return sharedPreferences.getFloat(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public double getDoubleWithDefaultValue(String key, double defaultValue) {
        if (sharedPreferences != null) {
            if (has(key)) {
                return sharedPreferences.getFloat(key, 0);
            }
        }

        return defaultValue;
    }

    @Override
    public boolean has(String key) {
        if (sharedPreferences != null) {
            return sharedPreferences.contains(key);
        }

        return false;
    }

    @Override
    public void remove(String key) {
        if (editor != null) {
            editor.remove(key);
        }
    }

    @Override
    public void clear() {
        if (editor != null) {
            editor.clear();
        }
    }

}