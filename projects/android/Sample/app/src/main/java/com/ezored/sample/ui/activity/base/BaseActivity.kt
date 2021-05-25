package com.ezored.sample.ui.activity.base

import android.os.Bundle
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import com.ezored.sample.R
import com.ezored.sample.ui.fragment.base.BaseFragment
import org.greenrobot.eventbus.EventBus

open class BaseActivity : AppCompatActivity() {

    protected open val fragmentInstance: BaseFragment?
        get() = null

    protected val activityLayout: Int
        get() = R.layout.activity_base

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(activityLayout)
        setContentFragment()
        createAll()
    }

    protected fun createAll() {
        // ignore
    }

    protected fun setContentFragment() {
        val fm = supportFragmentManager
        val ft = fm.beginTransaction()

        fragmentInstance?.let {
            ft.replace(R.id.fragmentContent, it)
        }

        ft.commit()
    }

    protected fun onHomeButtonSelected() {
        finish()
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        if (item.itemId == android.R.id.home) {
            onHomeButtonSelected()
        }

        return super.onOptionsItemSelected(item)
    }

    protected fun registerForEventBus(): Boolean {
        return false
    }

    override fun onStart() {
        super.onStart()

        if (registerForEventBus()) {
            EventBus.getDefault().register(this)
        }
    }

    override fun onStop() {
        super.onStop()

        if (registerForEventBus()) {
            EventBus.getDefault().unregister(this)
        }
    }
}
