package com.ezored.sample.ui.fragment;


import android.graphics.drawable.ColorDrawable;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.content.ContextCompat;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;

import com.ezored.sample.R;
import com.ezored.sample.adapter.MainViewPagerAdapter;
import com.ezored.sample.ui.fragment.base.BaseFragment;
import com.ezored.sample.ui.viewpager.CustomViewPager;

public class MainFragment extends BaseFragment implements BottomNavigationView.OnNavigationItemSelectedListener {

    private CustomViewPager viewPager;
    private MainViewPagerAdapter adapter;

    private HomeFragment homeFragment;
    private SettingsFragment settingsFragment;

    private BottomNavigationView navigation;

    public static MainFragment newInstance() {
        return new MainFragment();
    }

    @Override
    protected void createAll(View view) {
        super.createAll(view);

        // view pager
        adapter = new MainViewPagerAdapter(getChildFragmentManager());

        homeFragment = HomeFragment.newInstance();
        adapter.addFragment(homeFragment);

        settingsFragment = SettingsFragment.newInstance();
        adapter.addFragment(settingsFragment);

        viewPager = view.findViewById(R.id.main_view_pager);

        if (viewPager != null) {
            viewPager.disableScroll(true);
            viewPager.setOffscreenPageLimit(adapter.getCount());
            viewPager.setAdapter(adapter);
            viewPager.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    return true;
                }
            });
        }

        // bottom navigation
        navigation = view.findViewById(R.id.navigation);
        navigation.setBackground(new ColorDrawable(ContextCompat.getColor(getContext(), R.color.white)));
        navigation.setOnNavigationItemSelectedListener(this);
    }

    @Override
    protected int getFragmentLayout() {
        return R.layout.fragment_main;
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()) {
            case R.id.navigation_home:
                viewPager.setCurrentItem(0);
                return true;
            case R.id.navigation_settings:
                viewPager.setCurrentItem(1);
                return true;
        }

        return false;
    }

}
