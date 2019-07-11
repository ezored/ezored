package com.ezored.sample.ui.fragment

import android.content.pm.PackageManager
import android.view.View
import androidx.recyclerview.widget.RecyclerView
import com.ezored.sample.R
import com.ezored.sample.adapter.SimpleOptionAdapter
import com.ezored.sample.enums.LoadStateEnum
import com.ezored.sample.enums.SimpleOptionTypeEnum
import com.ezored.sample.models.SimpleOption
import com.ezored.sample.ui.fragment.base.BaseListFragment
import com.ezored.sample.utils.UIUtil
import java.util.*

class SettingsFragment : BaseListFragment<SimpleOption>(), SimpleOptionAdapter.SimpleOptionAdapterListener {

    override var adapter: RecyclerView.Adapter<*>
        get() {
            val adapter = SimpleOptionAdapter(context!!, listData)
            adapter.setListener(this)

            return adapter
        }
        set(value) {
            super.adapter = value
        }

    override val screenNameForAnalytics: String?
        get() = "Settings"

    override fun createAll(view: View) {
        super.createAll(view)

        // toolbar
        setupToolbar(R.string.title_settings)
    }

    override fun onLoadNewData() {
        super.onLoadNewData()

        listData = ArrayList()
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.APP_VERSION))

        updateAdapter()

        remoteDataLoadState = LoadStateEnum.LOADED
    }

    override fun needLoadNewData(): Boolean {
        return true
    }

    override fun onSimpleOptionItemClick(view: View, position: Int) {
        val option = listData!![position]

        if (option.type == SimpleOptionTypeEnum.APP_VERSION) {
            doActionAppVersion()
        }
    }

    private fun doActionAppVersion() {
        try {
            val manager = context!!.packageManager
            val info = manager.getPackageInfo(context!!.packageName, PackageManager.GET_ACTIVITIES)
            val version =
                String.format(Locale.getDefault(), "Version: %s\nBuild: %d", info.versionName, info.versionCode)

            UIUtil.showAlert(context, getString(R.string.dialog_title), version)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    companion object {
        fun newInstance(): SettingsFragment {
            return SettingsFragment()
        }
    }

}
