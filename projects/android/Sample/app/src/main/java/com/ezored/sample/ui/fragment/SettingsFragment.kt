package com.ezored.sample.ui.fragment

import android.view.View
import androidx.lifecycle.MutableLiveData
import com.ezored.sample.BuildConfig
import com.ezored.sample.R
import com.ezored.sample.adapter.SimpleOptionAdapter
import com.ezored.sample.enumerator.LoadStateEnum
import com.ezored.sample.enumerator.SimpleOptionTypeEnum
import com.ezored.sample.model.SimpleOption
import com.ezored.sample.ui.fragment.base.BaseListFragment
import com.ezored.sample.util.UIUtil
import java.util.Locale

class SettingsFragment :
    BaseListFragment<SimpleOption>(),
    SimpleOptionAdapter.SimpleOptionAdapterListener {

    override val screenNameForAnalytics: String
        get() = "Settings"

    override fun createAll(view: View) {
        super.createAll(view)

        setupToolbar(R.string.title_settings)
        createLiveData()
    }

    override fun onLoadNewData() {
        super.onLoadNewData()

        val list = ArrayList<SimpleOption>()
        list.add(SimpleOption(SimpleOptionTypeEnum.APP_VERSION))

        listData?.value = list

        remoteDataLoadState = LoadStateEnum.LOADED
    }

    private fun createLiveData() {
        listData = MutableLiveData()

        (listData as MutableLiveData<ArrayList<SimpleOption>>).observe(
            this,
            androidx.lifecycle.Observer { list ->
                adapter = SimpleOptionAdapter(requireContext(), list)
                (adapter as SimpleOptionAdapter).setListener(this)

                updateAdapter()

                adapter.notifyDataSetChanged()
            }
        )
    }

    override fun needLoadNewData(): Boolean {
        return true
    }

    override fun onSimpleOptionItemClick(view: View, option: SimpleOption) {
        when {
            option.type == SimpleOptionTypeEnum.APP_VERSION -> doActionAppVersion()
        }
    }

    private fun doActionAppVersion() {
        try {
            context?.let { context ->
                val version = String.format(
                    Locale.getDefault(),
                    "Version: %s\nBuild: %d",
                    BuildConfig.VERSION_NAME,
                    BuildConfig.VERSION_CODE
                )

                UIUtil.showAlert(context, getString(R.string.dialog_title), version)
            }
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
