package com.ezored.sample.ui.fragment.base

import android.graphics.PorterDuff
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.ProgressBar
import android.widget.TextView
import androidx.appcompat.app.ActionBar
import androidx.appcompat.widget.Toolbar
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import com.ezored.sample.R
import com.ezored.sample.enumerator.LoadStateEnum
import com.ezored.sample.ui.activity.base.BaseActivity
import com.ezored.sample.util.DateTimeUtil
import com.ezored.sample.util.UIUtil
import com.ezored.util.Logger
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import org.greenrobot.eventbus.EventBus

open class BaseFragment : Fragment(), CoroutineScope {

    override val coroutineContext = Dispatchers.Main

    protected var remoteDataLoadState = LoadStateEnum.NOT_LOADED

    protected var lastCacheUpdate: Long = 0

    protected val viewBackgroundColor: Int
        get() = R.color.white

    protected val loadingViewProgressBarColor: Int
        get() = R.color.color_accent

    protected open val fragmentLayout: Int
        get() = 0

    protected open val screenNameForAnalytics: String?
        get() = null

    protected val isLoading: Boolean
        get() = remoteDataLoadState == LoadStateEnum.LOADING

    private val paintToolbarLogo: Boolean
        get() = true

    protected val toolbar: Toolbar?
        get() = view?.findViewById(R.id.toolbar) as Toolbar

    protected val toolbarLogo: Int
        get() = R.drawable.ic_toolbar_logo

    protected val toolbarIconColor: Int
        get() = R.color.white

    protected val toolbarBackgroundColor: Int
        get() = R.color.color_primary

    protected val toolbarTextColor: Int
        get() = R.color.white

    protected val supportActionBar: ActionBar?
        get() = (activity as BaseActivity).supportActionBar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val arguments = arguments

        if (arguments != null) {
            onGetArguments(arguments)
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(fragmentLayout, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        createAll(view)
        layoutAll(view)

        showMainView()
    }

    override fun setUserVisibleHint(isVisibleToUser: Boolean) {
        super.setUserVisibleHint(isVisibleToUser)

        if (isVisibleToUser) {
            onFragmentVisible()
        } else {
            onFragmentNotVisible()
        }
    }

    override fun onStart() {
        super.onStart()

        if (registerForEventBus()) {
            EventBus.getDefault().register(this)
        }
    }

    override fun onStop() {
        super.onStop()

        if (registerForEventBus()) {
            EventBus.getDefault().unregister(this)
        }
    }

    protected fun hideAllViews() {
        UIUtil.hideViewById(view, R.id.main_view)
        UIUtil.hideViewById(view, R.id.network_error_view)
        UIUtil.hideViewById(view, R.id.error_view)
        UIUtil.hideViewById(view, R.id.loading_view)
    }

    protected fun showMainView() {
        hideAllViews()

        context?.let { context ->
            view?.let { view ->
                view.findViewById<View>(R.id.main_view)?.let { mainView ->
                    mainView.setBackgroundColor(
                        ContextCompat.getColor(
                            context,
                            viewBackgroundColor
                        )
                    )
                }

                UIUtil.showViewById(view, R.id.main_view)
            }
        }
    }

    protected fun showLoadingView() {
        hideAllViews()

        context?.let { context ->
            view?.let { view ->
                view.findViewById<View>(R.id.loading_view)?.let { loadingView ->
                    loadingView.setBackgroundColor(
                        ContextCompat.getColor(
                            context,
                            viewBackgroundColor
                        )
                    )
                }

                view.findViewById<ProgressBar>(R.id.pbLoadingView)?.let { pbLoadingView ->
                    pbLoadingView.indeterminateDrawable.setColorFilter(
                        ContextCompat.getColor(
                            context,
                            loadingViewProgressBarColor
                        ),
                        PorterDuff.Mode.MULTIPLY
                    )
                }

                UIUtil.showViewById(view, R.id.loading_view)
            }
        }
    }

    protected fun showNetworkView(message: String) {
        hideAllViews()

        context?.let { context ->
            view?.let { view ->
                view.findViewById<View>(R.id.network_error_view)?.let { networkErrorView ->
                    networkErrorView.setBackgroundColor(
                        ContextCompat.getColor(
                            context,
                            viewBackgroundColor
                        )
                    )

                    networkErrorView.findViewById<TextView>(R.id.tv_message)?.let { tvMessage ->
                        tvMessage.text = message
                    }

                    view.findViewById<Button>(R.id.bt_network_error)?.let { btNetworkError ->
                        btNetworkError.setOnClickListener { onBtNetworkErrorClick() }
                    }
                }

                UIUtil.showViewById(view, R.id.network_error_view)
            }
        }
    }

    protected fun showErrorView(message: String) {
        hideAllViews()

        context?.let { context ->
            view?.let { view ->
                view.findViewById<View>(R.id.error_view)?.let { errorView ->
                    errorView.setBackgroundColor(
                        ContextCompat.getColor(
                            context,
                            viewBackgroundColor
                        )
                    )

                    errorView.findViewById<TextView>(R.id.tv_message)?.let { tvMessage ->
                        tvMessage.text = message
                    }
                }

                UIUtil.showViewById(view, R.id.error_view)
            }
        }
    }

    protected fun onBtNetworkErrorClick() {
        // ignore
    }

    protected fun onFragmentNotVisible() {
        // ignore
    }

    protected fun onFragmentVisible() {
        activity?.let { activity ->
            // notify all analytics about it
            // AppEvents.onScreenChange(getScreenNameForAnalytics(), activity);
        }

        validateLoadData()
    }

    protected fun onGetArguments(arguments: Bundle) {
        // ignore
    }

    protected open fun createAll(view: View) {
        context?.let { context ->
            view.setBackgroundColor(ContextCompat.getColor(context, viewBackgroundColor))
        }
    }

    protected fun layoutAll(view: View) {
        // ignore
    }

    protected fun registerForEventBus(): Boolean {
        return false
    }

    // ///////////////////////////////////////////
    // REMOTE DATA
    // ///////////////////////////////////////////

    protected fun loadData() {
        if (!needLoadNewData()) {
            return
        }

        if (remoteDataLoadState != LoadStateEnum.NOT_LOADED) {
            return
        }

        remoteDataLoadState = LoadStateEnum.LOADING

        onLoadNewData()
    }

    protected fun validateLoadData() {
        validateCache()
        loadData()
    }

    protected open fun onLoadNewData() {
        // ignore
    }

    protected open fun needLoadNewData(): Boolean {
        return false
    }

    // ///////////////////////////////////////////
    // CACHE
    // ///////////////////////////////////////////

    protected fun onCacheExpired() {
        Logger.i("[BaseFragment : onCacheExpired] Cache expired now")
    }

    protected fun hasCache(): Boolean {
        return false
    }

    protected fun cacheExpireInterval(): Long {
        return 0
    }

    protected fun validateCache() {
        if (hasCache()) {
            lastCacheUpdate =
                if (lastCacheUpdate > 0) lastCacheUpdate else DateTimeUtil.currentTimestamp

            val currentTime = DateTimeUtil.currentTimestamp
            val expireTime = lastCacheUpdate + cacheExpireInterval()

            if (currentTime >= expireTime) {
                lastCacheUpdate = DateTimeUtil.currentTimestamp
                onCacheExpired()
            }
        }
    }

    // ///////////////////////////////////////////
    // TOOLBAR
    // ///////////////////////////////////////////

    fun setupToolbar(resId: Int) {
        setupToolbar(getString(resId))
    }

    fun setupToolbar(title: String?) {
        context?.let { context ->
            view?.let { view ->
                view.findViewById<Toolbar>(R.id.toolbar)?.let { toolbar ->
                    toolbar.title = ""
                    toolbar.setBackgroundColor(
                        ContextCompat.getColor(
                            context,
                            toolbarBackgroundColor
                        )
                    )
                    toolbar.setTitleTextColor(ContextCompat.getColor(context, toolbarTextColor))

                    (activity as BaseActivity).setSupportActionBar(toolbar)

                    supportActionBar?.let { supportActionBar ->
                        supportActionBar.elevation = UIUtil.convertDpToPixel(4f)

                        ContextCompat.getDrawable(context, R.drawable.ic_arrow_back)
                            ?.let { backArrowDrawable ->
                                backArrowDrawable.setColorFilter(
                                    ContextCompat.getColor(context, toolbarIconColor),
                                    PorterDuff.Mode.SRC_ATOP
                                )

                                supportActionBar.setHomeAsUpIndicator(backArrowDrawable)
                            }
                    }

                    if (hasToolbarLogo()) {
                        view.findViewById<ImageView>(R.id.iv_toolbar_logo)?.let { imToolbarLogo ->
                            onSetToolbarLogo(imToolbarLogo)
                        }
                    } else {
                        title?.let { title ->
                            view.findViewById<TextView>(R.id.tv_toolbar_title)
                                ?.let { tvToolbarTitle ->
                                    tvToolbarTitle.text = title
                                    tvToolbarTitle.setTextColor(
                                        ContextCompat.getColor(
                                            context,
                                            toolbarTextColor
                                        )
                                    )
                                }
                        }
                    }
                }
            }
        }
    }

    fun onSetToolbarLogo(logo: ImageView) {
        context?.let { context ->
            if (paintToolbarLogo) {
                logo.setImageDrawable(
                    UIUtil.drawableColorChange(
                        context,
                        toolbarLogo,
                        toolbarTextColor
                    )
                )
            } else {
                logo.setImageDrawable(ContextCompat.getDrawable(context, toolbarLogo))
            }
        }
    }

    protected fun showToolbarBackButton(show: Boolean) {
        supportActionBar?.setDisplayHomeAsUpEnabled(show)
        supportActionBar?.setDisplayShowHomeEnabled(show)
    }

    protected fun hasToolbarLogo(): Boolean {
        return false
    }
}
