package com.ezored.sample.ui.activity.base;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;

import com.ezored.sample.R;
import com.ezored.sample.ui.fragment.base.BaseFragment;

import org.greenrobot.eventbus.EventBus;

public class BaseActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(getActivityLayout());
        setContentFragment();
        createAll();
    }

    protected void createAll() {
        // ignore
    }

    protected void setContentFragment() {
        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ft = fm.beginTransaction();
        ft.replace(R.id.fragmentContent, getFragmentInstance());
        ft.commit();
    }

    protected BaseFragment getFragmentInstance() {
        return null;
    }

    protected int getActivityLayout() {
        return R.layout.activity_base;
    }

    protected void onHomeButtonSelected() {
        finish();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem menuItem) {
        if (menuItem.getItemId() == android.R.id.home) {
            onHomeButtonSelected();
        }

        return super.onOptionsItemSelected(menuItem);
    }

    protected boolean registerForEventBus() {
        return false;
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

}
