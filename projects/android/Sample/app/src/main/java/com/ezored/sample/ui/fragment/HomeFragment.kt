package com.ezored.sample.ui.fragment

import android.view.View
import androidx.recyclerview.widget.RecyclerView
import com.ezored.core.ApplicationCore
import com.ezored.dataservices.TodoDataService
import com.ezored.domain.Todo
import com.ezored.helpers.EnvironmentHelper
import com.ezored.helpers.SharedDataHelper
import com.ezored.io.FileHelper
import com.ezored.net.http.*
import com.ezored.sample.R
import com.ezored.sample.adapter.SimpleOptionAdapter
import com.ezored.sample.enums.LoadStateEnum
import com.ezored.sample.enums.SimpleOptionTypeEnum
import com.ezored.sample.models.SimpleOption
import com.ezored.sample.ui.activity.TodoListActivity
import com.ezored.sample.ui.fragment.base.BaseListFragment
import com.ezored.sample.utils.UIUtil
import java.util.*

class HomeFragment : BaseListFragment<SimpleOption>(), SimpleOptionAdapter.SimpleOptionAdapterListener {

    override var adapter: RecyclerView.Adapter<*>
        get() {
            val adapter = SimpleOptionAdapter(context, listData)
            adapter.setListener(this)

            return adapter
        }
        set(value) {
            super.adapter = value
        }

    override val screenNameForAnalytics: String?
        get() = "Home"

    override fun createAll(view: View) {
        super.createAll(view)

        // toolbar
        setupToolbar(R.string.title_home)

        validateLoadData()
    }

    override fun onLoadNewData() {
        super.onLoadNewData()

        listData = ArrayList()
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.SECRET_KEY))
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.SHARED_DATA))
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.HTTP_REQUEST))
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.HTTPS_REQUEST))
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.FILE_HELPER))
        listData!!.add(SimpleOption(SimpleOptionTypeEnum.TODO))

        // list
        updateAdapter()

        remoteDataLoadState = LoadStateEnum.LOADED
    }

    override fun needLoadNewData(): Boolean {
        return isAdded
    }

    override fun onSimpleOptionItemClick(view: View, position: Int) {
        val option = listData!![position]

        if (option.type == SimpleOptionTypeEnum.SHARED_DATA) {
            doActionSharedData()
        } else if (option.type == SimpleOptionTypeEnum.HTTP_REQUEST) {
            doActionHttpRequest()
        } else if (option.type == SimpleOptionTypeEnum.HTTPS_REQUEST) {
            doActionHttpsRequest()
        } else if (option.type == SimpleOptionTypeEnum.SECRET_KEY) {
            doActionSecretKey()
        } else if (option.type == SimpleOptionTypeEnum.TODO) {
            doActionTodo()
        } else if (option.type == SimpleOptionTypeEnum.FILE_HELPER) {
            doActionFileHelper()
        }
    }

    private fun doActionSecretKey() {
        UIUtil.showAlert(
            context,
            getString(R.string.dialog_title),
            String.format(Locale.getDefault(), "KEY IS:\n%s", EnvironmentHelper.getSecretKey())
        )
    }

    private fun doActionHttpsRequest() {
        showLoadingView()

        UIUtil.runOnNewThread {
            val headers = ArrayList<HttpHeader>()
            headers.add(HttpHeader("Content-Type", "application/x-www-form-urlencoded"))

            val params = ArrayList<HttpRequestParam>()
            params.add(HttpRequestParam("username", "demo"))
            params.add(HttpRequestParam("password", "demo"))

            val request = HttpRequest("https://httpbin.org/post", HttpMethod.METHOD_POST, params, headers, "")
            val response = HttpClient.shared().doRequest(request)

            UIUtil.runOnMainThread {
                UIUtil.showAlert(context, getString(R.string.dialog_title), response.body)
                showMainView()
            }
        }
    }

    private fun doActionHttpRequest() {
        showLoadingView()

        UIUtil.runOnNewThread {
            val headers = ArrayList<HttpHeader>()
            headers.add(HttpHeader("Content-Type", "application/x-www-form-urlencoded"))

            val params = ArrayList<HttpRequestParam>()
            params.add(HttpRequestParam("username", "demo"))
            params.add(HttpRequestParam("password", "demo"))

            val request = HttpRequest("https://httpbin.org/post", HttpMethod.METHOD_POST, params, headers, "")
            val response = HttpClient.shared().doRequest(request)

            UIUtil.runOnMainThread {
                UIUtil.showAlert(context, getString(R.string.dialog_title), response.body)
                showMainView()
            }
        }
    }

    private fun doActionSharedData() {
        SharedDataHelper.setDemoFlag(!SharedDataHelper.getDemoFlag())

        if (rvList.adapter != null) {
            rvList.adapter!!.notifyDataSetChanged()
        }
    }

    private fun doActionFileHelper() {
        val size = FileHelper.getFileSize(
            FileHelper.join(
                ApplicationCore.shared().initializationData.basePath,
                "database.db3"
            )
        )
        val message = String.format(Locale.getDefault(), "%d bytes / %.5f mbytes", size, size.toDouble() / 1048576)

        UIUtil.showAlert(context, getString(R.string.dialog_title), message)
    }

    private fun doActionTodo() {
        showLoadingView()

        UIUtil.runOnNewThread {
            // add some rows
            TodoDataService.truncate()

            for (i in 1..100) {
                val todo = Todo(
                    0,
                    String.format(Locale.getDefault(), "Title %d", i),
                    String.format(
                        Locale.getDefault(),
                        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. %d",
                        i
                    ),
                    HashMap(),
                    false,
                    Date(),
                    Date()
                )

                TodoDataService.add(todo)
            }

            // show list activity
            UIUtil.runOnMainThread {
                showMainView()

                val intent = TodoListActivity.newIntent(context)
                startActivity(intent)
            }
        }
    }

    companion object {
        fun newInstance(): HomeFragment {
            return HomeFragment()
        }
    }

}
