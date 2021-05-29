package com.ezored.sample.models

import android.content.Context
import com.ezored.sample.R
import com.ezored.sample.enumerator.SimpleOptionTypeEnumerator

class SimpleOption(val type: SimpleOptionTypeEnumerator) {

    fun getDescription(context: Context): String {
        return when {
            type === SimpleOptionTypeEnumerator.SHARED_DATA -> context.getString(R.string.option_shared_data)
            type === SimpleOptionTypeEnumerator.HTTPS_REQUEST -> context.getString(R.string.option_https_request)
            type === SimpleOptionTypeEnumerator.SECRET_KEY -> context.getString(R.string.option_secret_key)
            type === SimpleOptionTypeEnumerator.APP_VERSION -> context.getString(R.string.option_app_version)
            type === SimpleOptionTypeEnumerator.TODO -> context.getString(R.string.option_todo)
            type === SimpleOptionTypeEnumerator.FILE_HELPER -> context.getString(R.string.option_file_helper)
            else -> ""
        }
    }

    fun getImage(): Int {
        return R.drawable.ic_simple_option
    }
}
