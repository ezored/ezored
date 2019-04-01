package com.ezored.sample.ui.activity;

import android.content.Intent;

import com.ezored.sample.ui.activity.base.BaseActivity;
import com.ezored.sample.ui.fragment.MainFragment;
import com.ezored.sample.ui.fragment.base.BaseFragment;

public class MainActivity extends BaseActivity {

    private MainFragment fragment;

    @Override
    protected BaseFragment getFragmentInstance() {
        fragment = MainFragment.newInstance();
        return fragment;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        fragment.onActivityResult(requestCode, resultCode, data);
    }

}
