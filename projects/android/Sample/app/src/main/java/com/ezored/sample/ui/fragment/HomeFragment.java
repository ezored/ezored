package com.ezored.sample.ui.fragment;

import android.content.Intent;
import android.support.v7.widget.RecyclerView;
import android.view.View;

import com.ezored.core.ApplicationCore;
import com.ezored.dataservices.TodoDataService;
import com.ezored.domain.Todo;
import com.ezored.helpers.EnvironmentHelper;
import com.ezored.helpers.SharedDataHelper;
import com.ezored.io.FileHelper;
import com.ezored.net.http.HttpClient;
import com.ezored.net.http.HttpHeader;
import com.ezored.net.http.HttpMethod;
import com.ezored.net.http.HttpRequest;
import com.ezored.net.http.HttpRequestParam;
import com.ezored.net.http.HttpResponse;
import com.ezored.sample.R;
import com.ezored.sample.adapter.SimpleOptionAdapter;
import com.ezored.sample.enums.LoadStateEnum;
import com.ezored.sample.enums.SimpleOptionTypeEnum;
import com.ezored.sample.interfaces.Closure;
import com.ezored.sample.models.SimpleOption;
import com.ezored.sample.ui.activity.TodoListActivity;
import com.ezored.sample.ui.fragment.base.BaseListFragment;
import com.ezored.sample.utils.UIUtil;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;

public class HomeFragment extends BaseListFragment<SimpleOption> implements SimpleOptionAdapter.SimpleOptionAdapterListener {

    public static HomeFragment newInstance() {
        return new HomeFragment();
    }

    @Override
    protected void createAll(View view) {
        super.createAll(view);

        // toolbar
        setupToolbar(R.string.title_home);

        validateLoadData();
    }

    @Override
    protected void onLoadNewData() {
        super.onLoadNewData();

        listData = new ArrayList<>();
        listData.add(new SimpleOption(SimpleOptionTypeEnum.SECRET_KEY));
        listData.add(new SimpleOption(SimpleOptionTypeEnum.SHARED_DATA));
        listData.add(new SimpleOption(SimpleOptionTypeEnum.HTTP_REQUEST));
        listData.add(new SimpleOption(SimpleOptionTypeEnum.HTTPS_REQUEST));
        listData.add(new SimpleOption(SimpleOptionTypeEnum.FILE_HELPER));
        listData.add(new SimpleOption(SimpleOptionTypeEnum.TODO));

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
        SimpleOptionAdapter adapter = new SimpleOptionAdapter(getContext(), listData);
        adapter.setListener(this);

        return adapter;
    }

    @Override
    public void onSimpleOptionItemClick(View view, int position) {
        SimpleOption option = listData.get(position);

        if (option.getType().equals(SimpleOptionTypeEnum.SHARED_DATA)) {
            doActionSharedData();
        } else if (option.getType().equals(SimpleOptionTypeEnum.HTTP_REQUEST)) {
            doActionHttpRequest();
        } else if (option.getType().equals(SimpleOptionTypeEnum.HTTPS_REQUEST)) {
            doActionHttpsRequest();
        } else if (option.getType().equals(SimpleOptionTypeEnum.SECRET_KEY)) {
            doActionSecretKey();
        } else if (option.getType().equals(SimpleOptionTypeEnum.TODO)) {
            doActionTodo();
        } else if (option.getType().equals(SimpleOptionTypeEnum.FILE_HELPER)) {
            doActionFileHelper();
        }
    }

    private void doActionSecretKey() {
        UIUtil.showAlert(getContext(), getString(R.string.dialog_title), String.format(Locale.getDefault(), "KEY IS:\n%s", EnvironmentHelper.getSecretKey()));
    }

    private void doActionHttpsRequest() {
        showLoadingView();

        UIUtil.runOnNewThread(new Closure() {
            @Override
            public void exec() {
                ArrayList<HttpHeader> headers = new ArrayList<>();
                headers.add(new HttpHeader("Content-Type", "application/x-www-form-urlencoded"));

                ArrayList<HttpRequestParam> params = new ArrayList<>();
                params.add(new HttpRequestParam("username", "demo"));
                params.add(new HttpRequestParam("password", "demo"));

                HttpRequest request = new HttpRequest("https://httpbin.org/post", HttpMethod.METHOD_POST, params, headers, "");
                final HttpResponse response = HttpClient.shared().doRequest(request);

                UIUtil.runOnMainThread(new Closure() {
                    @Override
                    public void exec() {
                        UIUtil.showAlert(getContext(), getString(R.string.dialog_title), response.getBody());
                        showMainView();
                    }
                });
            }
        });
    }

    private void doActionHttpRequest() {
        showLoadingView();

        UIUtil.runOnNewThread(new Closure() {
            @Override
            public void exec() {
                ArrayList<HttpHeader> headers = new ArrayList<>();
                headers.add(new HttpHeader("Content-Type", "application/x-www-form-urlencoded"));

                ArrayList<HttpRequestParam> params = new ArrayList<>();
                params.add(new HttpRequestParam("username", "demo"));
                params.add(new HttpRequestParam("password", "demo"));

                HttpRequest request = new HttpRequest("https://httpbin.org/post", HttpMethod.METHOD_POST, params, headers, "");
                final HttpResponse response = HttpClient.shared().doRequest(request);

                UIUtil.runOnMainThread(new Closure() {
                    @Override
                    public void exec() {
                        UIUtil.showAlert(getContext(), getString(R.string.dialog_title), response.getBody());
                        showMainView();
                    }
                });
            }
        });
    }

    private void doActionSharedData() {
        SharedDataHelper.setDemoFlag(!SharedDataHelper.getDemoFlag());

        if (rvList.getAdapter() != null) {
            rvList.getAdapter().notifyDataSetChanged();
        }
    }

    private void doActionFileHelper() {
        long size = FileHelper.getFileSize(FileHelper.join(ApplicationCore.shared().getInitializationData().getBasePath(), "database.db3"));
        String message = String.format(Locale.getDefault(), "%d bytes / %.5f mbytes", size, ((double) size) / 1048576);

        UIUtil.showAlert(getContext(), getString(R.string.dialog_title), message);
    }

    private void doActionTodo() {
        showLoadingView();

        UIUtil.runOnNewThread(new Closure() {
            @Override
            public void exec() {
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

                // show list activity
                UIUtil.runOnMainThread(new Closure() {
                    @Override
                    public void exec() {
                        showMainView();

                        Intent intent = TodoListActivity.newIntent(getContext());
                        startActivity(intent);
                    }
                });
            }
        });
    }

    @Override
    protected String getScreenNameForAnalytics() {
        return "Home";
    }

}
