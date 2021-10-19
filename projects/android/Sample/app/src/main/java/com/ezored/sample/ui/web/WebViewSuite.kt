package com.ezored.sample.ui.web

import android.content.Context
import android.content.Intent
import android.graphics.Bitmap
import android.net.Uri
import android.os.Handler
import android.util.AttributeSet
import android.view.ViewStub
import android.webkit.GeolocationPermissions
import android.webkit.WebChromeClient
import android.webkit.WebResourceError
import android.webkit.WebResourceRequest
import android.webkit.WebResourceResponse
import android.webkit.WebView
import android.webkit.WebViewClient
import android.widget.ProgressBar
import android.widget.RelativeLayout
import androidx.annotation.NonNull
import androidx.annotation.Nullable
import com.ezored.sample.R

/**
 * A combination of WebView and Progressbar.
 * The main aim of this library is to delay the inflation of WebView,
 * So that it does not slow down Activity creation, which happens since Android 5.0.
 * You can have a look at this StackOverflow post:
 * https://stackoverflow.com/questions/46928113/inflating-webview-is-slow-since-lollipop/
 */
class WebViewSuite : RelativeLayout {

    // attributes
    private var progressBarStyle = PROGRESS_BAR_STYLE_LINEAR
    private var inflationDelay = 100
    private var enableJavaScript = false
    private var overrideTelLink = true
    private var overrideEmailLink = true
    private var overridePdfLink = true
    private var showZoomControl = false
    private var enableVerticalScrollBar = false
    private var enableHorizontalScrollBar = false
    private var url: String? = null

    // loading static data
    private var htmlData: String? = null
    private var mimeType: String? = null
    private var encoding: String? = null

    // view elements
    var webView: WebView? = null
        private set

    private var webViewStub: ViewStub? = null
    private var linearProgressBar: ProgressBar? = null
    private var circularProgressBar: ProgressBar? = null
    private var customProgressBar: ProgressBar? = null
    private var webViewInflated = false
    private var callback: WebViewSuiteCallback? = null
    private var interference: WebViewSetupInterference? = null
    private var openPDFCallback: WebViewOpenPDFCallback? = null

    constructor(@NonNull context: Context) : super(context) {
        init(context)
    }

    constructor(@NonNull context: Context, @Nullable attrs: AttributeSet?) : super(context, attrs) {
        val a = context.theme.obtainStyledAttributes(attrs, R.styleable.WebViewSuite, 0, 0)

        try {
            progressBarStyle = a.getInt(
                R.styleable.WebViewSuite_webViewProgressBarStyle,
                PROGRESS_BAR_STYLE_LINEAR
            )
            inflationDelay = a.getInt(R.styleable.WebViewSuite_inflationDelay, 100)
            enableJavaScript = a.getBoolean(R.styleable.WebViewSuite_enableJavaScript, false)
            overrideTelLink = a.getBoolean(R.styleable.WebViewSuite_overrideTelLink, true)
            overrideEmailLink = a.getBoolean(R.styleable.WebViewSuite_overrideEmailLink, true)
            overridePdfLink = a.getBoolean(R.styleable.WebViewSuite_overridePdfLink, true)
            showZoomControl = a.getBoolean(R.styleable.WebViewSuite_showZoomControl, false)
            enableVerticalScrollBar =
                a.getBoolean(R.styleable.WebViewSuite_enableVerticalScrollBar, false)
            enableHorizontalScrollBar =
                a.getBoolean(R.styleable.WebViewSuite_enableHorizontalScrollBar, false)
            url = a.getString(R.styleable.WebViewSuite_url)
        } finally {
            a.recycle()
        }

        init(context)
    }

    constructor(
        @NonNull context: Context,
        @Nullable attrs: AttributeSet?,
        defStyleAttr: Int
    ) : super(context, attrs, defStyleAttr) {
        init(context)
    }

    private fun init(context: Context) {
        val rootView = inflate(context, R.layout.web_view_suite, this)

        webViewStub = rootView.findViewById(R.id.web_view_stub)
        linearProgressBar = rootView.findViewById(R.id.web_view_linear_progressbar)
        circularProgressBar = rootView.findViewById(R.id.web_view_circular_progressbar)

        when (progressBarStyle) {
            PROGRESS_BAR_STYLE_CIRCULAR -> {
                linearProgressBar?.visibility = GONE
                circularProgressBar?.visibility = VISIBLE
            }
            PROGRESS_BAR_STYLE_NONE -> {
                linearProgressBar?.visibility = GONE
                circularProgressBar?.visibility = GONE
            }
            PROGRESS_BAR_STYLE_LINEAR -> {
                circularProgressBar?.visibility = GONE
                linearProgressBar?.visibility = VISIBLE
            }
            else -> {
                circularProgressBar?.visibility = GONE
                linearProgressBar?.visibility = VISIBLE
            }
        }

        val webViewInflationHandler = Handler()
        webViewInflationHandler.postDelayed(
            {
                webView = webViewStub?.inflate() as WebView
                webViewInflated = true
                postWebViewInflated()
            },
            inflationDelay.toLong()
        )
    }

    private fun postWebViewInflated() {
        if (!webViewInflated || webView == null) {
            return
        }

        setupWebView()

        if (url != null && url!!.isNotEmpty()) {
            webView?.loadUrl(url!!)
        } else if (htmlData != null && htmlData!!.isNotEmpty()) {
            webView?.loadData(htmlData!!, mimeType, encoding)
        }
    }

    /**
     * Submit your URL programmatically.
     * This will of course override the URL you set in XML (if any).
     * You can do this in onCreate() of your activity, because even if webView is null,
     * loading will be triggered again after webView is inflated.
     */
    fun startLoading(url: String?) {
        this.url = url

        if (!webViewInflated || webView == null) {
            return
        }

        webView?.loadUrl(url!!)
    }

    fun startLoadData(data: String?, mimeType: String?, encoding: String?) {
        htmlData = data

        this.mimeType = mimeType
        this.encoding = encoding

        if (!webViewInflated || webView == null) {
            return
        }

        webView?.loadData(htmlData!!, mimeType, encoding)
    }

    /**
     * A convenient method for you to override your onBackPressed.
     * return false if there is no more page to goBack / webView is not yet inflated.
     */
    fun goBackIfPossible(): Boolean {
        webView?.let {
            if (it.canGoBack()) {
                it.goBack()
                return true
            }
        }

        return false
    }

    /**
     * A convenient method for you to refresh.
     */
    fun refresh() {
        webView?.reload()
    }

    /**
     * If you don't like default progressbar, you can simply submit your own through this method.
     * It will automatically disappear and reappear according to page load.
     */
    fun setCustomProgressBar(progressBar: ProgressBar?) {
        customProgressBar = progressBar
    }

    fun toggleProgressbar(isVisible: Boolean) {
        val status = if (isVisible) VISIBLE else GONE

        when (progressBarStyle) {
            PROGRESS_BAR_STYLE_CIRCULAR -> circularProgressBar?.visibility = status
            PROGRESS_BAR_STYLE_NONE -> if (customProgressBar != null) customProgressBar?.visibility =
                status
            PROGRESS_BAR_STYLE_LINEAR -> linearProgressBar?.visibility = status
            else -> linearProgressBar?.visibility = status
        }
    }

    /**
     * If you want to customize the behavior of the webViewClient,
     * e.g. Override urls other than default telephone and email,
     * Use this method on WebViewSuite to submit the callbacks.
     * These callbacks will be executed after the codes in WebViewSuite are done.
     */
    fun customizeClient(callback: WebViewSuiteCallback?) {
        this.callback = callback
    }

    /**
     * If you want to customize the settings of the webViewClient,
     * You cannot do it directly in onCreate() of your activity by getting WebView from WebViewSuite.
     * Why? Because the main point of this library is to delay the inflation - WebView is null in onCreate()!
     *
     * Therefore, I provided a callback for you to submit your own settings.
     * Use this method on WebViewSuite (This time in onCreate()) and submit the callback.
     * This callback will be executed after the default settings in WebViewSuite are completed.
     * I can assure you that webView is not null during interfereWebViewSetup().
     */
    fun interfereWebViewSetup(interference: WebViewSetupInterference?) {
        this.interference = interference
    }

    fun setOpenPDFCallback(callback: WebViewOpenPDFCallback?) {
        openPDFCallback = callback
    }

    fun getProgressBar(progressBarStyle: Int): ProgressBar? {
        return if (progressBarStyle == PROGRESS_BAR_STYLE_LINEAR) linearProgressBar else circularProgressBar
    }

    private fun setupWebView() {
        webView?.webViewClient = object : WebViewClient() {
            override fun onPageStarted(view: WebView?, url: String?, favicon: Bitmap?) {
                super.onPageStarted(view, url, favicon)

                toggleProgressbar(true)
                callback?.onPageStarted(view, url, favicon)
            }

            override fun onPageFinished(view: WebView, url: String) {
                super.onPageFinished(view, url)

                toggleProgressbar(false)
                callback?.onPageFinished(view, url)
            }

            override fun onReceivedHttpError(
                view: WebView?,
                request: WebResourceRequest?,
                errorResponse: WebResourceResponse?
            ) {
                super.onReceivedHttpError(view, request, errorResponse)

                toggleProgressbar(false)
                callback?.onReceivedHttpError(view, request, errorResponse)
            }

            override fun onReceivedError(
                view: WebView?,
                request: WebResourceRequest?,
                error: WebResourceError?
            ) {
                super.onReceivedError(view, request, error)

                toggleProgressbar(false)
                callback?.onReceivedError(view, request, error)
            }

            override fun shouldOverrideUrlLoading(view: WebView, url: String): Boolean {
                return if (url.startsWith("tel:") && overrideTelLink) {
                    try {
                        val telIntent = Intent(Intent.ACTION_DIAL, Uri.parse(url))
                        context?.startActivity(telIntent)
                        true
                    } catch (e: Exception) {
                        false
                    }
                } else if (url.startsWith("mailto:") && overrideEmailLink) {
                    try {
                        // only email apps should handle this
                        val emailIntent = Intent(Intent.ACTION_SENDTO)
                        emailIntent.data = Uri.parse("mailto:")
                        emailIntent.putExtra(Intent.EXTRA_EMAIL, arrayOf(url.substring(7)))

                        if (emailIntent.resolveActivity(context!!.packageManager) != null) {
                            context?.startActivity(emailIntent)
                        }

                        true
                    } catch (e: Exception) {
                        false
                    }
                } else if (url.endsWith("pdf") && overridePdfLink) {
                    context?.startActivity(Intent(Intent.ACTION_VIEW, Uri.parse(url)))

                    if (openPDFCallback != null) {
                        openPDFCallback?.onOpenPDF()
                    }

                    true
                } else {
                    if (callback != null) {
                        callback?.shouldOverrideUrlLoading(webView, url) ?: false
                    } else {
                        super.shouldOverrideUrlLoading(view, url)
                    }
                }
            }
        }

        webView?.webChromeClient = object : WebChromeClient() {
            override fun onGeolocationPermissionsShowPrompt(
                origin: String,
                callback: GeolocationPermissions.Callback
            ) {
                callback.invoke(origin, true, false)
                super.onGeolocationPermissionsShowPrompt(origin, callback)
            }
        }

        val webSettings = webView?.settings
        webSettings?.javaScriptEnabled = enableJavaScript
        webSettings?.builtInZoomControls = showZoomControl

        webView?.isVerticalScrollBarEnabled = enableVerticalScrollBar
        webView?.isHorizontalScrollBarEnabled = enableHorizontalScrollBar

        if (interference != null) {
            interference?.interfereWebViewSetup(webView)
        }
    }

    interface WebViewSuiteCallback {
        fun onPageStarted(view: WebView?, url: String?, favicon: Bitmap?)
        fun onPageFinished(view: WebView?, url: String?)
        fun shouldOverrideUrlLoading(view: WebView?, url: String?): Boolean
        fun onReceivedError(view: WebView?, request: WebResourceRequest?, error: WebResourceError?)
        fun onReceivedHttpError(
            view: WebView?,
            request: WebResourceRequest?,
            errorResponse: WebResourceResponse?
        )
    }

    interface WebViewSetupInterference {
        fun interfereWebViewSetup(webView: WebView?)
    }

    interface WebViewOpenPDFCallback {
        fun onOpenPDF()
    }

    companion object {
        const val PROGRESS_BAR_STYLE_NONE = 0
        const val PROGRESS_BAR_STYLE_LINEAR = 1
        const val PROGRESS_BAR_STYLE_CIRCULAR = 2
    }
}
