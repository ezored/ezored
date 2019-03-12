package com.ezored.sample.ui.activity;

import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.v7.widget.SearchView;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;

import com.ezored.dataservices.TodoDataService;
import com.ezored.domain.Todo;
import com.ezored.sample.R;
import com.ezored.sample.ui.activity.base.BaseActivity;
import com.ezored.sample.ui.fragment.TodoListFragment;
import com.ezored.sample.ui.fragment.base.BaseFragment;

import java.util.Date;
import java.util.HashMap;
import java.util.Locale;

public class TodoListActivity extends BaseActivity {

    private TodoListFragment fragment;

    public static Intent newIntent(Context context) {
        return new Intent(context, TodoListActivity.class);
    }

    @Override
    protected BaseFragment getFragmentInstance() {
        fragment = TodoListFragment.newInstance();
        return fragment;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        fragment.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.todo_list_menu, menu);

        SearchManager searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        final SearchView searchView = (SearchView) menu.findItem(R.id.menu_search).getActionView();
        searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));
        searchView.setIconifiedByDefault(false);

        View closeButton = searchView.findViewById(android.support.v7.appcompat.R.id.search_close_btn);
        closeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toolbar toolbar = findViewById(R.id.toolbar);
                toolbar.collapseActionView();
                fragment.search("");
            }
        });

        for (int i = 0; i < menu.size(); i++) {
            Drawable drawable = menu.getItem(i).getIcon();

            if (drawable != null) {
                drawable.mutate();
                drawable.setColorFilter(getResources().getColor(R.color.white), PorterDuff.Mode.SRC_ATOP);
            }
        }

        return true;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        handleIntent(getIntent());

        // add some rows
        TodoDataService.truncate();

        for (int i = 1; i <= 100; i++) {
            Todo todo = new Todo(
                    0,
                    String.format(Locale.getDefault(), "Title %d", i),
                    String.format(Locale.getDefault(), "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. %d", i),
                    new HashMap<String, String>(),
                    false,
                    new Date(),
                    new Date()
            );

            TodoDataService.add(todo);
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        handleIntent(intent);
    }

    private void handleIntent(Intent intent) {
        if (Intent.ACTION_SEARCH.equals(intent.getAction())) {
            String query = intent.getStringExtra(SearchManager.QUERY);
            fragment.search(query);
        }
    }

}
