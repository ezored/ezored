package com.ezored.sample.ui.activity

import android.content.Context
import android.content.Intent
import com.ezored.sample.ui.activity.base.BaseActivity
import com.ezored.sample.ui.fragment.WebViewFragment
import com.ezored.sample.ui.fragment.base.BaseFragment

class WebViewActivity : BaseActivity() {

    private var fragment: WebViewFragment? = null

    override val fragmentInstance: BaseFragment?
        get() {
            fragment = WebViewFragment.newInstance()
            return fragment
        }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        fragment?.onActivityResult(requestCode, resultCode, data)
    }

    companion object {
        fun newIntent(context: Context): Intent {
            return Intent(context, WebViewActivity::class.java)
        }
    }
}
