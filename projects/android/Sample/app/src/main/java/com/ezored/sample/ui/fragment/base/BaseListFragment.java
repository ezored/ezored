package com.ezored.sample.ui.fragment.base;

import android.support.v4.content.ContextCompat;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;

import com.ezored.sample.R;
import com.yqritc.recyclerviewflexibledivider.HorizontalDividerItemDecoration;

import java.util.ArrayList;

public class BaseListFragment<T> extends BaseFragment {

    protected ArrayList<T> listData;
    protected RecyclerView rvList;
    protected LinearLayoutManager layoutManager;

    @Override
    protected void createAll(View view) {
        super.createAll(view);

        layoutManager = getLayoutManager();

        rvList = view.findViewById(R.id.rv_list);
        rvList.setLayoutManager(layoutManager);
        rvList.setItemAnimator(new DefaultItemAnimator());
        rvList.setNestedScrollingEnabled(false);
        rvList.setHasFixedSize(true);
        rvList.addItemDecoration(new HorizontalDividerItemDecoration.Builder(getContext()).color(ContextCompat.getColor(getContext(), R.color.grey_200)).build());
    }

    protected LinearLayoutManager getLayoutManager() {
        LinearLayoutManager layoutManager = new LinearLayoutManager(getContext());
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);
        return layoutManager;
    }

    protected RecyclerView.Adapter getAdapter() {
        // need implement on child fragment
        return null;
    }

    protected void updateAdapter() {
        rvList.setAdapter(getAdapter());
    }

    @Override
    protected int getFragmentLayout() {
        return R.layout.fragment_base_list;
    }

    @Override
    protected String getScreenNameForAnalytics() {
        return "Base list";
    }

}
