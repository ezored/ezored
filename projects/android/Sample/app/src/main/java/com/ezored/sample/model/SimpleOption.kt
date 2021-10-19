package com.ezored.sample.model

import android.content.Context
import com.ezored.sample.R
import com.ezored.sample.enumerator.SimpleOptionTypeEnum

class SimpleOption(val type: SimpleOptionTypeEnum) {

    fun getDescription(context: Context): String {
        return when {
            type === SimpleOptionTypeEnum.SHARED_DATA -> context.getString(R.string.option_shared_data)
            type === SimpleOptionTypeEnum.HTTPS_REQUEST -> context.getString(R.string.option_https_request)
            type === SimpleOptionTypeEnum.SECRET_KEY -> context.getString(R.string.option_secret_key)
            type === SimpleOptionTypeEnum.APP_VERSION -> context.getString(R.string.option_app_version)
            type === SimpleOptionTypeEnum.TODO -> context.getString(R.string.option_todo)
            type === SimpleOptionTypeEnum.FILE_HELPER -> context.getString(R.string.option_file_helper)
            type === SimpleOptionTypeEnum.WEB_SERVER -> context.getString(R.string.option_web_server)
            type === SimpleOptionTypeEnum.WEB_VIEW -> context.getString(R.string.option_web_view)
            else -> ""
        }
    }

    fun getImage(): Int {
        return R.drawable.ic_simple_option
    }
}
