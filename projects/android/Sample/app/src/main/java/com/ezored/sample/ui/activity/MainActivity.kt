package com.ezored.sample.ui.activity

import android.content.Intent
import com.ezored.sample.ui.activity.base.BaseActivity
import com.ezored.sample.ui.fragment.MainFragment
import com.ezored.sample.ui.fragment.base.BaseFragment

class MainActivity : BaseActivity() {

    private var fragment: MainFragment? = null

    override val fragmentInstance: BaseFragment?
        get() {
            fragment = MainFragment.newInstance()
            return fragment
        }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        fragment?.onActivityResult(requestCode, resultCode, data)
    }
}
