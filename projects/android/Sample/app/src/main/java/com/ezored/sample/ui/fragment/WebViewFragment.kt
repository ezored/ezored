package com.ezored.sample.ui.fragment

import android.annotation.SuppressLint
import android.graphics.Bitmap
import android.os.Bundle
import android.view.View
import android.webkit.WebChromeClient
import android.webkit.WebResourceError
import android.webkit.WebResourceRequest
import android.webkit.WebResourceResponse
import android.webkit.WebView
import com.ezored.net.http.HttpServer
import com.ezored.sample.R
import com.ezored.sample.ui.fragment.base.BaseFragment
import com.ezored.sample.ui.web.WebViewSuite
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

class WebViewFragment : BaseFragment() {

    override val screenNameForAnalytics: String
        get() = "WebView"

    override val fragmentLayout: Int
        get() = R.layout.fragment_web_view

    private var webView: WebViewSuite? = null

    private var loadFirstPage = false

    override fun createAll(view: View) {
        super.createAll(view)

        setupToolbar(R.string.title_web_view)
        showToolbarBackButton(true)

        webView = view.findViewById(R.id.webView)
        webView?.interfereWebViewSetup(object : WebViewSuite.WebViewSetupInterference {
            @SuppressLint("SetJavaScriptEnabled")
            override fun interfereWebViewSetup(webView: WebView?) {
                val webSettings = webView?.settings

                webSettings?.javaScriptEnabled = true
                webSettings?.defaultTextEncodingName = "utf-8"
                webSettings?.javaScriptCanOpenWindowsAutomatically = true

                webView?.webChromeClient = object : WebChromeClient() {
                    // ignore
                }

                webView?.overScrollMode = View.OVER_SCROLL_NEVER
            }
        })

        webView?.customizeClient(object : WebViewSuite.WebViewSuiteCallback {
            override fun onPageStarted(view: WebView?, url: String?, favicon: Bitmap?) {
                // ignore
            }

            override fun onPageFinished(view: WebView?, url: String?) {
                if (!loadFirstPage) {
                    loadFirstPage = true

                    launch {
                        delay(1000)
                        showMainView()
                    }
                }
            }

            override fun shouldOverrideUrlLoading(view: WebView?, url: String?): Boolean {
                return false
            }

            override fun onReceivedError(
                view: WebView?,
                request: WebResourceRequest?,
                error: WebResourceError?
            ) {
                // ignore
            }

            override fun onReceivedHttpError(
                view: WebView?,
                request: WebResourceRequest?,
                errorResponse: WebResourceResponse?
            ) {
                // ignore
            }
        })

        reload()
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        showLoadingView()
    }

    private fun reload() {
        var url = HttpServer.shared().socketAddress
        url = url.replace("0.0.0.0", "localhost")

        webView?.startLoading(url)
    }

    companion object {
        fun newInstance(): WebViewFragment {
            return WebViewFragment()
        }
    }
}
