package com.ezored.sample.adapter

import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter

class MainViewPagerAdapter(fm: FragmentManager) :
    FragmentPagerAdapter(fm, BEHAVIOR_RESUME_ONLY_CURRENT_FRAGMENT) {

    private var fragmentList: ArrayList<Fragment>? = null

    init {
        this.fragmentList = ArrayList()
    }

    override fun getItem(position: Int): Fragment {
        return fragmentList?.get(position) ?: Fragment()
    }

    override fun getCount(): Int {
        return fragmentList?.size ?: 0
    }

    fun addFragment(fragment: Fragment) {
        fragmentList?.add(fragment)
    }
}
