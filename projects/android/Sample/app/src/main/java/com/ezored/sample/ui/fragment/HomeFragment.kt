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
import kotlinx.coroutines.withContext
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
                getString(R.string.dialog_secret_key_message, EnvironmentHelper.getSecretKey())
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

            withContext(Dispatchers.Main) {
                context?.let {
                    UIUtil.showAlert(
                        it,
                        getString(R.string.dialog_title),
                        getString(R.string.dialog_http_message, request.url, response.body)
                    )
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

        val message =
            getString(R.string.dialog_database_size_message, size, (size.toDouble() / 1048576))

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
                        "New TODO item description: %d",
                        i
                    ),
                    HashMap(),
                    false,
                    Date(),
                    Date()
                )

                TodoDataService.add(todo)
            }

            withContext(Dispatchers.Main) {
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
