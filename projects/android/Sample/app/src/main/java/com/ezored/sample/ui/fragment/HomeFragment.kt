package com.ezored.sample.ui.fragment

import android.view.View
import androidx.lifecycle.MutableLiveData
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
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import java.util.*

class HomeFragment : BaseListFragment<SimpleOption>(),
    SimpleOptionAdapter.SimpleOptionAdapterListener {

    override val screenNameForAnalytics: String?
        get() = "Home"

    override fun createAll(view: View) {
        super.createAll(view)

        setupToolbar(R.string.title_home)
        createLiveData()
        validateLoadData()
    }

    override fun onLoadNewData() {
        super.onLoadNewData()

        val list = ArrayList<SimpleOption>()
        list.add(SimpleOption(SimpleOptionTypeEnum.SECRET_KEY))
        list.add(SimpleOption(SimpleOptionTypeEnum.SHARED_DATA))
        list.add(SimpleOption(SimpleOptionTypeEnum.HTTPS_REQUEST))
        list.add(SimpleOption(SimpleOptionTypeEnum.FILE_HELPER))
        list.add(SimpleOption(SimpleOptionTypeEnum.TODO))

        listData?.value = list

        remoteDataLoadState = LoadStateEnum.LOADED
    }

    override fun onSimpleOptionItemClick(view: View, option: SimpleOption) {
        when {
            option.type == SimpleOptionTypeEnum.SHARED_DATA -> doActionSharedData()
            option.type == SimpleOptionTypeEnum.HTTPS_REQUEST -> doActionHttpsRequest()
            option.type == SimpleOptionTypeEnum.SECRET_KEY -> doActionSecretKey()
            option.type == SimpleOptionTypeEnum.TODO -> doActionTodo()
            option.type == SimpleOptionTypeEnum.FILE_HELPER -> doActionFileHelper()
        }
    }

    private fun createLiveData() {
        listData = MutableLiveData()

        (listData as MutableLiveData<ArrayList<SimpleOption>>).observe(
            this,
            androidx.lifecycle.Observer { list ->
                adapter = SimpleOptionAdapter(context!!, list)
                (adapter as SimpleOptionAdapter).setListener(this)

                updateAdapter()

                adapter.notifyDataSetChanged()
            })
    }

    override fun needLoadNewData(): Boolean {
        return isAdded
    }

    private fun doActionSecretKey() {
        context?.let { context ->
            UIUtil.showAlert(
                context,
                getString(R.string.dialog_title),
                String.format(
                    Locale.getDefault(),
                    "KEY IS:\n%s",
                    EnvironmentHelper.getSecretKey()
                )
            )
        }
    }

    private fun doActionHttpsRequest() {
        showLoadingView()

        launch(Dispatchers.IO) {
            val headers = ArrayList<HttpHeader>()
            headers.add(HttpHeader("Content-Type", "application/x-www-form-urlencoded"))

            val params = ArrayList<HttpRequestParam>()
            params.add(HttpRequestParam("username", "demo"))
            params.add(HttpRequestParam("password", "demo"))

            val request =
                HttpRequest("https://httpbin.org/post", HttpMethod.METHOD_POST, params, headers, "")
            val response = HttpClient.shared().doRequest(request)

            launch(Dispatchers.Main) {
                context?.let {
                    UIUtil.showAlert(it, getString(R.string.dialog_title), response.body)
                }

                showMainView()
            }
        }
    }

    private fun doActionSharedData() {
        SharedDataHelper.setDemoFlag(!SharedDataHelper.getDemoFlag())
        rvList.adapter?.notifyDataSetChanged()
    }

    private fun doActionFileHelper() {
        val size = FileHelper.getFileSize(
            FileHelper.join(
                ApplicationCore.shared().initializationData.basePath,
                "database.db3"
            )
        )

        val message = String.format(
            Locale.getDefault(),
            "%d bytes / %.5f mbytes",
            size,
            (size.toDouble() / 1048576)
        )

        context?.let {
            UIUtil.showAlert(it, getString(R.string.dialog_title), message)
        }
    }

    private fun doActionTodo() {
        showLoadingView()

        launch(Dispatchers.IO) {
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

            launch(Dispatchers.Main) {
                showMainView()

                context?.let {
                    val intent = TodoListActivity.newIntent(it)
                    startActivity(intent)
                }
            }
        }
    }

    companion object {
        fun newInstance(): HomeFragment {
            return HomeFragment()
        }
    }

}
