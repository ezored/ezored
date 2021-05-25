package com.ezored.sample.ui.activity

import android.app.SearchManager
import android.content.Context
import android.content.Intent
import android.graphics.PorterDuff
import android.os.Bundle
import android.view.Menu
import android.view.View
import androidx.appcompat.widget.SearchView
import androidx.appcompat.widget.Toolbar
import com.ezored.sample.R
import com.ezored.sample.ui.activity.base.BaseActivity
import com.ezored.sample.ui.fragment.TodoListFragment
import com.ezored.sample.ui.fragment.base.BaseFragment

class TodoListActivity : BaseActivity() {

    private var fragment: TodoListFragment? = null

    override val fragmentInstance: BaseFragment?
        get() {
            fragment = TodoListFragment.newInstance()
            return fragment
        }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        fragment?.onActivityResult(requestCode, resultCode, data)
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        val inflater = menuInflater
        inflater.inflate(R.menu.todo_list_menu, menu)

        val searchManager = getSystemService(Context.SEARCH_SERVICE) as SearchManager
        val searchView = menu.findItem(R.id.menu_search).actionView as SearchView
        searchView.setSearchableInfo(searchManager.getSearchableInfo(componentName))
        searchView.setIconifiedByDefault(false)

        val closeButton = searchView.findViewById<View>(androidx.appcompat.R.id.search_close_btn)
        closeButton.setOnClickListener {
            val toolbar = findViewById<Toolbar>(R.id.toolbar)
            toolbar.collapseActionView()

            fragment?.search("")
        }

        for (i in 0 until menu.size()) {
            val drawable = menu.getItem(i).icon

            if (drawable != null) {
                drawable.mutate()
                drawable.setColorFilter(resources.getColor(R.color.white), PorterDuff.Mode.SRC_ATOP)
            }
        }

        return true
    }

    public override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        handleIntent(intent)
    }

    override fun onNewIntent(intent: Intent) {
        super.onNewIntent(intent)
        handleIntent(intent)
    }

    private fun handleIntent(intent: Intent) {
        if (Intent.ACTION_SEARCH == intent.action) {
            val query = intent.getStringExtra(SearchManager.QUERY)
            fragment?.search(query ?: "")
        }
    }

    companion object {
        fun newIntent(context: Context): Intent {
            return Intent(context, TodoListActivity::class.java)
        }
    }
}
