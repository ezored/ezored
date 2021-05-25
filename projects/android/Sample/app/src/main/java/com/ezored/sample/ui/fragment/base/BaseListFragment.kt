package com.ezored.sample.ui.fragment.base

import android.view.View
import androidx.core.content.ContextCompat
import androidx.lifecycle.MutableLiveData
import androidx.recyclerview.widget.DefaultItemAnimator
import androidx.recyclerview.widget.DividerItemDecoration
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.recyclerview.widget.RecyclerView.Adapter
import com.ezored.sample.R

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
                val divider = DividerItemDecoration(context, DividerItemDecoration.VERTICAL)

                divider.setDrawable(
                    ContextCompat.getDrawable(
                        context,
                        R.drawable.list_item_separator
                    )!!
                )

                rvList.addItemDecoration(divider)
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
