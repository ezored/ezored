package com.ezored.sample.ui.fragment.base;

import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.ActionBar;
import android.support.v7.widget.Toolbar;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.ezored.sample.R;
import com.ezored.sample.enums.LoadStateEnum;
import com.ezored.sample.ui.activity.base.BaseActivity;
import com.ezored.sample.utils.DateTimeUtils;
import com.ezored.sample.utils.UIUtil;
import com.ezored.util.Logger;

import org.greenrobot.eventbus.EventBus;

public class BaseFragment extends Fragment {

    protected LoadStateEnum remoteDataLoadState = LoadStateEnum.NOT_LOADED;
    protected long lastCacheUpdate = 0;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Bundle arguments = getArguments();

        if (arguments != null) {
            onGetArguments(arguments);
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(getFragmentLayout(), container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        createAll(view);
        layoutAll(view);

        showMainView();
    }

    @Override
    public void setUserVisibleHint(boolean isVisibleToUser) {
        super.setUserVisibleHint(isVisibleToUser);

        if (isVisibleToUser) {
            onFragmentVisible();
        } else {
            onFragmentNotVisible();
        }
    }

    @Override
    public void onStart() {
        super.onStart();

        if (registerForEventBus()) {
            EventBus.getDefault().register(this);
        }
    }

    @Override
    public void onStop() {
        super.onStop();

        if (registerForEventBus()) {
            EventBus.getDefault().unregister(this);
        }
    }

    protected void hideAllViews() {
        UIUtil.hideViewById(getView(), R.id.main_view);
        UIUtil.hideViewById(getView(), R.id.network_error_view);
        UIUtil.hideViewById(getView(), R.id.error_view);
        UIUtil.hideViewById(getView(), R.id.loading_view);
    }

    protected void showMainView() {
        hideAllViews();

        if (getView() != null && getView().findViewById(R.id.main_view) != null) {
            getView().findViewById(R.id.main_view).setBackgroundColor(ContextCompat.getColor(getContext(), getViewBackgroundColor()));
            UIUtil.showViewById(getView(), R.id.main_view);
        }
    }

    protected void showLoadingView() {
        hideAllViews();

        if (getView() != null && getView().findViewById(R.id.loading_view) != null) {
            getView().findViewById(R.id.loading_view).setBackgroundColor(ContextCompat.getColor(getContext(), getViewBackgroundColor()));

            ProgressBar progressBar = (ProgressBar) getView().findViewById(R.id.pbLoadingView);
            progressBar.getIndeterminateDrawable().setColorFilter(ContextCompat.getColor(getContext(), getLoadingViewProgressBarColor()), PorterDuff.Mode.MULTIPLY);

            UIUtil.showViewById(getView(), R.id.loading_view);
        }
    }

    protected void showNetworkView(String message) {
        hideAllViews();

        if (getView() != null && getView().findViewById(R.id.network_error_view) != null) {
            getView().findViewById(R.id.network_error_view).setBackgroundColor(ContextCompat.getColor(getContext(), getViewBackgroundColor()));

            TextView tvMessage = (TextView) getView().findViewById(R.id.tv_message);
            tvMessage.setText(message);

            Button btNetworkError = (Button) getView().findViewById(R.id.bt_network_error);

            btNetworkError.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    onBtNetworkErrorClick();
                }
            });

            UIUtil.showViewById(getView(), R.id.network_error_view);
        }
    }

    protected void showErrorView(String message) {
        hideAllViews();

        if (getView() != null && getView().findViewById(R.id.error_view) != null) {
            getView().findViewById(R.id.error_view).setBackgroundColor(ContextCompat.getColor(getContext(), getViewBackgroundColor()));

            TextView tvMessage = (TextView) getView().findViewById(R.id.tv_message);
            tvMessage.setText(message);

            UIUtil.showViewById(getView(), R.id.error_view);
        }
    }

    protected int getViewBackgroundColor() {
        return R.color.white;
    }

    protected int getLoadingViewProgressBarColor() {
        return R.color.color_accent;
    }

    protected void onBtErrorClick() {
        // ignore
    }

    protected void onBtNetworkErrorClick() {
        // ignore
    }

    protected void onFragmentNotVisible() {
        // ignore
    }

    protected void onFragmentVisible() {
        if (getActivity() != null) {
            // notify all analytics about it
            // AppEvents.onScreenChange(getScreenNameForAnalytics(), getActivity());
        }

        validateLoadData();
    }

    protected int getFragmentLayout() {
        return 0;
    }

    protected void onGetArguments(Bundle arguments) {

    }

    protected void createAll(View view) {
        view.setBackgroundColor(ContextCompat.getColor(getContext(), getViewBackgroundColor()));
    }

    protected void layoutAll(View view) {
        // ignore
    }

    protected boolean registerForEventBus() {
        return false;
    }

    protected String getScreenNameForAnalytics() {
        return null;
    }

    /////////////////////////////////////////////
    // REMOTE DATA
    /////////////////////////////////////////////

    protected void loadData() {
        if (!needLoadNewData()) {
            return;
        }

        if (remoteDataLoadState != LoadStateEnum.NOT_LOADED) {
            return;
        }

        remoteDataLoadState = LoadStateEnum.LOADING;

        onLoadNewData();
    }

    protected void validateLoadData() {
        validateCache();
        loadData();
    }

    protected void onLoadNewData() {
        // ignore
    }

    protected boolean needLoadNewData() {
        return false;
    }

    protected boolean isLoading() {
        return remoteDataLoadState == LoadStateEnum.LOADING;
    }

    /////////////////////////////////////////////
    // CACHE
    /////////////////////////////////////////////

    protected void onCacheExpired() {
        Logger.i("[BaseFragment : onCacheExpired] Cache expired now");
    }

    protected boolean hasCache() {
        return false;
    }

    protected long cacheExpireInterval() {
        return 0;
    }

    protected void validateCache() {
        if (hasCache()) {
            lastCacheUpdate = lastCacheUpdate > 0 ? lastCacheUpdate : DateTimeUtils.getCurrentTimestamp();

            long currentTime = DateTimeUtils.getCurrentTimestamp();
            long expireTime = lastCacheUpdate + cacheExpireInterval();

            if (currentTime >= expireTime) {
                lastCacheUpdate = DateTimeUtils.getCurrentTimestamp();
                onCacheExpired();
            }
        }
    }

    /////////////////////////////////////////////
    // TOOLBAR
    /////////////////////////////////////////////

    public void setupToolbar(int resId) {
        setupToolbar(getString(resId));
    }

    public void setupToolbar(String title) {
        View view = getView();

        if (view != null) {
            Toolbar toolbar = (Toolbar) view.findViewById(R.id.toolbar);

            if (toolbar != null) {
                toolbar.setTitle("");
                toolbar.setBackgroundColor(ContextCompat.getColor(getContext(), getToolbarBackgroundColor()));
                toolbar.setTitleTextColor(ContextCompat.getColor(getContext(), getToolbarTextColor()));

                ((BaseActivity) getActivity()).setSupportActionBar(toolbar);
                getSupportActionBar().setElevation(UIUtil.convertDpToPixel(4));

                final Drawable upArrow = ContextCompat.getDrawable(getContext(), R.drawable.ic_arrow_back);
                upArrow.setColorFilter(ContextCompat.getColor(getContext(), getToolbarIconColor()), PorterDuff.Mode.SRC_ATOP);
                getSupportActionBar().setHomeAsUpIndicator(upArrow);

                if (hasToolbarLogo()) {
                    ImageView imToolbarLogo = (ImageView) view.findViewById(R.id.iv_toolbar_logo);

                    if (imToolbarLogo != null) {
                        onSetToolbarLogo(imToolbarLogo);
                    }
                } else {
                    if (title != null) {
                        TextView tvToolbarTitle = (TextView) view.findViewById(R.id.tv_toolbar_title);

                        if (tvToolbarTitle != null) {
                            tvToolbarTitle.setText(title);
                            tvToolbarTitle.setTextColor(ContextCompat.getColor(getContext(), getToolbarTextColor()));
                        }
                    }
                }
            }
        }
    }

    public void onSetToolbarLogo(ImageView logo) {
        if (getContext() != null) {
            if (getPaintToolbarLogo()) {
                logo.setImageDrawable(UIUtil.drawableColorChange(getContext(), getToolbarLogo(), getToolbarTextColor()));
            } else {
                logo.setImageDrawable(ContextCompat.getDrawable(getContext(), getToolbarLogo()));
            }
        }
    }

    private boolean getPaintToolbarLogo() {
        return true;
    }

    protected Toolbar getToolbar() {
        View view = getView();

        if (view != null) {
            return (Toolbar) view.findViewById(R.id.toolbar);
        }

        return null;
    }

    protected int getToolbarLogo() {
        return R.drawable.ic_toolbar_logo;
    }

    protected int getToolbarIconColor() {
        return R.color.white;
    }

    protected int getToolbarBackgroundColor() {
        return R.color.color_primary;
    }

    protected int getToolbarTextColor() {
        return R.color.white;
    }

    protected void showToolbarBackButton(boolean show) {
        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayHomeAsUpEnabled(show);
            getSupportActionBar().setDisplayShowHomeEnabled(show);
        }
    }

    protected boolean hasToolbarLogo() {
        return false;
    }

    public ActionBar getSupportActionBar() {
        if (getActivity() != null) {
            return ((BaseActivity) getActivity()).getSupportActionBar();
        }

        return null;
    }

}
