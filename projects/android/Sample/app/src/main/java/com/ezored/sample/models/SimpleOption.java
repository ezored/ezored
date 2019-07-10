package com.ezored.sample.models;

import android.content.Context;
import com.ezored.sample.R;
import com.ezored.sample.enums.SimpleOptionTypeEnum;

public class SimpleOption {

    private SimpleOptionTypeEnum type;

    public SimpleOption(SimpleOptionTypeEnum type) {
        this.type = type;
    }

    public String getDescription(Context context) {
        if (type == SimpleOptionTypeEnum.SHARED_DATA) {
            return context.getString(R.string.option_shared_data);
        } else if (type == SimpleOptionTypeEnum.HTTP_REQUEST) {
            return context.getString(R.string.option_http_request);
        } else if (type == SimpleOptionTypeEnum.HTTPS_REQUEST) {
            return context.getString(R.string.option_https_request);
        } else if (type == SimpleOptionTypeEnum.SECRET_KEY) {
            return context.getString(R.string.option_secret_key);
        } else if (type == SimpleOptionTypeEnum.APP_VERSION) {
            return context.getString(R.string.option_app_version);
        } else if (type == SimpleOptionTypeEnum.TODO) {
            return context.getString(R.string.option_todo);
        } else if (type == SimpleOptionTypeEnum.FILE_HELPER) {
            return context.getString(R.string.option_file_helper);
        }

        return "";
    }

    public int getImage(Context context) {
        return R.drawable.ic_simple_option;
    }

    public SimpleOptionTypeEnum getType() {
        return type;
    }

}
