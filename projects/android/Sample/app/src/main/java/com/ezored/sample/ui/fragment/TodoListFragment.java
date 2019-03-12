package com.ezored.sample.ui.fragment;

import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.view.MenuItem;
import android.view.View;

import com.ezored.dataservices.TodoDataService;
import com.ezored.domain.Todo;
import com.ezored.sample.R;
import com.ezored.sample.adapter.TodoAdapter;
import com.ezored.sample.enums.LoadStateEnum;
import com.ezored.sample.ui.fragment.base.BaseListFragment;

public class TodoListFragment extends BaseListFragment<Todo> implements TodoAdapter.TodoAdapterListener {

    private String searchText;

    public static TodoListFragment newInstance() {
        return new TodoListFragment();
    }

    @Override
    protected void createAll(View view) {
        super.createAll(view);

        // toolbar
        setupToolbar(R.string.title_todo_list);
        showToolbarBackButton(true);

        validateLoadData();
    }

    @Override
    protected void onLoadNewData() {
        super.onLoadNewData();

        if (TextUtils.isEmpty(searchText)) {
            listData = TodoDataService.findAllOrderByCreatedAtDesc();
        } else {
            listData = TodoDataService.findByTitle(searchText);
        }

        // list
        updateAdapter();

        remoteDataLoadState = LoadStateEnum.LOADED;
    }

    @Override
    protected boolean needLoadNewData() {
        return isAdded();
    }

    @Override
    protected RecyclerView.Adapter getAdapter() {
        TodoAdapter adapter = new TodoAdapter(getContext(), listData);
        adapter.setListener(this);

        return adapter;
    }

    @Override
    public void onTodoItemClick(View view, int position) {
        Todo todo = listData.get(position);
        TodoDataService.setDoneById(todo.getId(), !todo.getDone());
        listData.set(position, TodoDataService.findById(todo.getId()));

        if (rvList.getAdapter() != null) {
            rvList.getAdapter().notifyDataSetChanged();
        }
    }

    public void search(String typedText) {
        if (remoteDataLoadState != LoadStateEnum.LOADING) {
            remoteDataLoadState = LoadStateEnum.NOT_LOADED;
            searchText = typedText;
            validateLoadData();
        }
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.menu_search:
                return true;

            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected int getFragmentLayout() {
        return R.layout.fragment_todo_list;
    }

    @Override
    protected String getScreenNameForAnalytics() {
        return "ToDo List";
    }

}
