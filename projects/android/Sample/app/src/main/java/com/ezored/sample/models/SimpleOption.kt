package com.ezored.sample.models

import android.content.Context
import com.ezored.sample.R
import com.ezored.sample.enums.SimpleOptionTypeEnum

class SimpleOption(val type: SimpleOptionTypeEnum) {

    fun getDescription(context: Context): String {
        return when {
            type === SimpleOptionTypeEnum.SHARED_DATA -> context.getString(R.string.option_shared_data)
            type === SimpleOptionTypeEnum.HTTP_REQUEST -> context.getString(R.string.option_http_request)
            type === SimpleOptionTypeEnum.HTTPS_REQUEST -> context.getString(R.string.option_https_request)
            type === SimpleOptionTypeEnum.SECRET_KEY -> context.getString(R.string.option_secret_key)
            type === SimpleOptionTypeEnum.APP_VERSION -> context.getString(R.string.option_app_version)
            type === SimpleOptionTypeEnum.TODO -> context.getString(R.string.option_todo)
            type === SimpleOptionTypeEnum.FILE_HELPER -> context.getString(R.string.option_file_helper)
            else -> ""
        }
    }

    fun getImage(context: Context): Int {
        return R.drawable.ic_simple_option
    }

}
