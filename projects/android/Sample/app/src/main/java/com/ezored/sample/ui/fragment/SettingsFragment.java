package com.ezored.sample.ui.fragment;

import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import com.ezored.sample.R;
import com.ezored.sample.adapter.SimpleOptionAdapter;
import com.ezored.sample.enums.LoadStateEnum;
import com.ezored.sample.enums.SimpleOptionTypeEnum;
import com.ezored.sample.models.SimpleOption;
import com.ezored.sample.ui.fragment.base.BaseListFragment;
import com.ezored.sample.utils.UIUtil;

import java.util.ArrayList;
import java.util.Locale;

public class SettingsFragment extends BaseListFragment<SimpleOption> implements SimpleOptionAdapter.SimpleOptionAdapterListener {

    public static SettingsFragment newInstance() {
        return new SettingsFragment();
    }

    @Override
    protected void createAll(View view) {
        super.createAll(view);

        // toolbar
        setupToolbar(R.string.title_settings);
    }

    @Override
    protected void onLoadNewData() {
        super.onLoadNewData();

        listData = new ArrayList<>();
        listData.add(new SimpleOption(SimpleOptionTypeEnum.APP_VERSION));

        // list
        updateAdapter();

        remoteDataLoadState = LoadStateEnum.LOADED;
    }

    @Override
    protected boolean needLoadNewData() {
        return true;
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

        if (option.getType().equals(SimpleOptionTypeEnum.APP_VERSION)) {
            doActionAppVersion();
        }
    }

    private void doActionAppVersion() {
        try {
            PackageManager manager = getContext().getPackageManager();
            PackageInfo info = manager.getPackageInfo(getContext().getPackageName(), PackageManager.GET_ACTIVITIES);
            String version = String.format(Locale.getDefault(), "Version: %s\nBuild: %d", info.versionName, info.versionCode);

            UIUtil.showAlert(getContext(), getString(R.string.dialog_title), version);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    protected String getScreenNameForAnalytics() {
        return "Settings";
    }

}
