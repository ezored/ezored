package com.ezored.sample.ui.fragment

import android.graphics.drawable.ColorDrawable
import android.view.MenuItem
import android.view.View
import androidx.core.content.ContextCompat
import com.ezored.sample.R
import com.ezored.sample.adapter.MainViewPagerAdapter
import com.ezored.sample.ui.fragment.base.BaseFragment
import com.ezored.sample.ui.viewpager.CustomViewPager
import com.google.android.material.bottomnavigation.BottomNavigationView

class MainFragment : BaseFragment(), BottomNavigationView.OnNavigationItemSelectedListener {

    private var viewPager: CustomViewPager? = null
    private var adapter: MainViewPagerAdapter? = null

    private var homeFragment: HomeFragment? = null
    private var settingsFragment: SettingsFragment? = null

    private var navigation: BottomNavigationView? = null

    override val fragmentLayout: Int
        get() = R.layout.fragment_main

    override fun createAll(view: View) {
        super.createAll(view)

        // view pager
        adapter = MainViewPagerAdapter(childFragmentManager)

        homeFragment = HomeFragment.newInstance()
        adapter?.addFragment(homeFragment!!)

        settingsFragment = SettingsFragment.newInstance()
        adapter?.addFragment(settingsFragment!!)

        // view pager
        viewPager = view.findViewById(R.id.main_view_pager)

        viewPager?.let { viewPager ->
            viewPager.disableScroll(true)
            viewPager.offscreenPageLimit = adapter!!.count
            viewPager.adapter = adapter
            viewPager.setOnTouchListener { _, _ -> true }
        }

        // bottom navigation
        context?.let { context ->
            navigation = view.findViewById(R.id.navigation)

            navigation?.let { navigation ->
                navigation.background =
                    ColorDrawable(ContextCompat.getColor(context, R.color.white))

                navigation.setOnNavigationItemSelectedListener(this)
            }
        }
    }

    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        homeFragment?.userVisibleHint = false
        settingsFragment?.userVisibleHint = false

        when (item.itemId) {
            R.id.navigation_home -> {
                viewPager?.currentItem = 0
                homeFragment?.userVisibleHint = true
                return true
            }

            R.id.navigation_settings -> {
                viewPager?.currentItem = 1
                settingsFragment?.userVisibleHint = true
                return true
            }
        }

        return false
    }

    companion object {
        fun newInstance(): MainFragment {
            return MainFragment()
        }
    }
}
