package com.ezored.sample.ui.fragment.base

import android.view.View
import androidx.core.content.ContextCompat
import androidx.lifecycle.MutableLiveData
import androidx.recyclerview.widget.DefaultItemAnimator
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.Adapter
import com.ezored.sample.R
import com.yqritc.recyclerviewflexibledivider.HorizontalDividerItemDecoration
import java.util.*

open class BaseListFragment<T> : BaseFragment() {

    protected var listData: MutableLiveData<ArrayList<T>>? = null
    protected lateinit var rvList: RecyclerView
    protected lateinit var layoutManager: LinearLayoutManager
    protected open lateinit var adapter: Adapter<*>

    override val fragmentLayout: Int
        get() = R.layout.fragment_base_list

    override val screenNameForAnalytics: String?
        get() = "Base list"

    override fun createAll(view: View) {
        super.createAll(view)

        layoutManager = getLayoutManagerForList()

        rvList = view.findViewById(R.id.rv_list)

        rvList.let { rvList ->
            rvList.layoutManager = layoutManager
            rvList.itemAnimator = DefaultItemAnimator()
            rvList.isNestedScrollingEnabled = false
            rvList.setHasFixedSize(true)

            context?.let { context ->
                rvList.addItemDecoration(
                    HorizontalDividerItemDecoration.Builder(context).color(
                        ContextCompat.getColor(context, R.color.grey_200)
                    ).build()
                )
            }
        }
    }

    protected fun getLayoutManagerForList(): LinearLayoutManager {
        val layoutManager = LinearLayoutManager(context)
        layoutManager.orientation = RecyclerView.VERTICAL
        return layoutManager
    }

    protected fun updateAdapter() {
        rvList.adapter = adapter
    }

}
