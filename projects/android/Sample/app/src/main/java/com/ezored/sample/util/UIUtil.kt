package com.ezored.sample.util

import android.app.Activity
import android.app.Dialog
import android.content.Context
import android.content.DialogInterface
import android.content.Intent
import android.content.res.ColorStateList
import android.content.res.Resources
import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.PorterDuff
import android.graphics.drawable.BitmapDrawable
import android.graphics.drawable.Drawable
import android.graphics.drawable.GradientDrawable
import android.os.Build
import android.os.Looper
import android.text.SpannableString
import android.text.TextUtils
import android.text.style.ForegroundColorSpan
import android.util.TypedValue
import android.view.View
import android.view.WindowManager
import android.view.animation.AnimationUtils
import android.view.inputmethod.InputMethodManager
import android.widget.EditText
import android.widget.TextView
import androidx.annotation.ColorInt
import androidx.annotation.ColorRes
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import androidx.core.content.ContextCompat
import com.ezored.sample.R
import com.ezored.util.Logger

object UIUtil {

    fun startServiceOrForegroundService(context: Context, intent: Intent) {
        try {
            ContextCompat.startForegroundService(context, intent)
        } catch (e: Exception) {
            Logger.e("[Application : startServiceOrForegroundService] Failed to start foreground service")
            e.printStackTrace()
        }
    }

    fun showAlert(context: Context, title: String, message: String) {
        val alertDialog = AlertDialog.Builder(context).create()
        alertDialog.setTitle(title)
        alertDialog.setMessage(message)

        alertDialog.setButton(
            AlertDialog.BUTTON_NEUTRAL, context.getString(R.string.dialog_button_ok)
        ) { dialog, which -> dialog.dismiss() }

        alertDialog.show()
    }

    fun showViewById(activity: Activity?, viewId: Int) {
        if (activity == null) {
            return
        }

        val view = activity.findViewById<View>(viewId)

        if (view != null) {
            view.visibility = View.VISIBLE
        }
    }

    fun showViewById(container: View?, viewId: Int) {
        if (container == null) {
            return
        }

        val view = container.findViewById<View>(viewId)

        if (view != null) {
            view.visibility = View.VISIBLE
        }
    }

    fun hideViewById(container: View?, viewId: Int) {
        if (container == null) {
            return
        }

        val view = container.findViewById<View>(viewId)

        if (view != null) {
            view.visibility = View.GONE
        }
    }

    fun hideViewById(activity: Activity?, viewId: Int) {
        if (activity == null) {
            return
        }

        val view = activity.findViewById<View>(viewId)

        if (view != null) {
            view.visibility = View.GONE
        }
    }

    fun convertDpToPixel(dp: Float): Float {
        val metrics = Resources.getSystem().displayMetrics
        val px = dp * (metrics.densityDpi / 160f)
        return Math.round(px).toFloat()
    }

    fun setActivityAsTransparent(activity: Activity?) {
        if (activity == null) {
            return
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            val window = activity.window
            window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS or WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION)
            window.decorView.systemUiVisibility =
                View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN or View.SYSTEM_UI_FLAG_LAYOUT_STABLE
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS)
            window.statusBarColor = Color.TRANSPARENT
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            val window = activity.window
            window.addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS)
            window.setFlags(
                WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS,
                WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS
            )
        }
    }

    fun adjustToolbarPadding(activity: Activity, view: View?) {
        if (view == null) {
            return
        }

        var paddingTop: Int

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            paddingTop = getStatusBarHeight(activity)
        } else {
            paddingTop = 0
        }

        val typedValue = TypedValue()
        activity.theme.resolveAttribute(
            androidx.appcompat.R.attr.drawableSize,
            typedValue,
            true
        )
        paddingTop += TypedValue.complexToDimensionPixelOffset(
            typedValue.data,
            activity.resources.displayMetrics
        )
        activity.findViewById<View>(R.id.toolbar).setPadding(0, paddingTop, 0, 0)
    }

    fun getStatusBarHeight(activity: Activity): Int {
        var result = 0
        val resourceId =
            activity.resources.getIdentifier("status_bar_height", "dimen", "android")

        if (resourceId > 0) {
            result = activity.resources.getDimensionPixelSize(resourceId)
        }

        return result
    }

    fun drawableColorChange(context: Context, icon: Int, color: Int): Drawable? {
        val drawable: Drawable? = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            context.getDrawable(icon)
        } else {
            context.resources.getDrawable(icon)
        }

        drawable?.setColorFilter(ContextCompat.getColor(context, color), PorterDuff.Mode.SRC_IN)

        return drawable
    }

    fun changeVisibility(view: View?, visibility: Int, animate: Boolean) {
        if (view == null || visibility == view.visibility) {
            return
        }

        view.clearAnimation()

        if (animate) {
            val animResourceId: Int

            if (visibility == View.VISIBLE) {
                animResourceId = android.R.anim.fade_in
            } else {
                animResourceId = android.R.anim.fade_out
            }

            val anim = AnimationUtils.loadAnimation(view.context, animResourceId)
            view.animation = anim
        }

        view.visibility = visibility
    }

    fun drawableToBitmap(drawable: Drawable): Bitmap {
        var bitmap: Bitmap? = null

        if (drawable is BitmapDrawable) {
            if (drawable.bitmap != null) {
                return drawable.bitmap
            }
        }

        if (drawable.intrinsicWidth <= 0 || drawable.intrinsicHeight <= 0) {
            bitmap = Bitmap.createBitmap(
                1,
                1,
                Bitmap.Config.ARGB_8888
            ) // Single color bitmap will be created of 1x1 pixel
        } else {
            bitmap = Bitmap.createBitmap(
                drawable.intrinsicWidth,
                drawable.intrinsicHeight,
                Bitmap.Config.ARGB_8888
            )
        }

        val canvas = Canvas(bitmap!!)
        drawable.setBounds(0, 0, canvas.width, canvas.height)
        drawable.draw(canvas)

        return bitmap
    }

    fun checkIfAlertDialogIsShowing(alertDialog: AlertDialog?): Boolean {
        if (alertDialog == null) {
            return false
        }

        return alertDialog.isShowing
    }

    fun dismissDialog(dialog: Dialog?) {
        if (dialog == null) {
            return
        }

        try {
            dialog.dismiss()
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun dismissDialogInterface(dialogInterface: DialogInterface?) {
        if (dialogInterface == null) {
            return
        }

        try {
            dialogInterface.dismiss()
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun showPlayerNoConnectionAlertDialog(alertDialog: AlertDialog?) {
        if (alertDialog == null) {
            return
        }

        try {
            alertDialog.show()
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    fun applyFadeAnimation(context: Context) {
        if (context is AppCompatActivity) {
            (context as Activity).overridePendingTransition(0, R.anim.activity_fade_out)
        }
    }

    fun setActivityAsFullScreen(activity: Activity?) {
        if (activity == null) {
            return
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            val window = activity.window
            window.setFlags(
                WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
            )
        }
    }

    val screenWidth: Float
        get() = Resources.getSystem().displayMetrics.widthPixels.toFloat()

    fun hideKeyboard(context: Activity?) {
        if (context != null) {
            val view = context.currentFocus

            if (view != null) {
                val token = view.windowToken

                if (token != null) {
                    try {
                        val imm =
                            context.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
                        imm.hideSoftInputFromWindow(token, 0)
                    } catch (e: Exception) {
                        e.printStackTrace()
                    }
                }
            }
        }
    }

    fun setCursorDrawableColor(editText: EditText, @ColorInt color: Int) {
        try {
            // get the cursor resource id
            var field = TextView::class.java.getDeclaredField("mCursorDrawableRes")
            field.isAccessible = true
            val drawableResId = field.getInt(editText)

            // get the editor
            field = TextView::class.java.getDeclaredField("mEditor")
            field.isAccessible = true
            val editor = field.get(editText)

            // get the drawable and set a color filter
            val drawable = ContextCompat.getDrawable(editText.context, drawableResId)
            drawable!!.setColorFilter(color, PorterDuff.Mode.SRC_IN)
            val drawables = arrayOf(drawable, drawable)

            // set the drawables
            field = editor.javaClass.getDeclaredField("mCursorDrawable")
            field.isAccessible = true
            field.set(editor, drawables)
        } catch (e: Exception) {
            // ignore
        }
    }

    fun buildColorStateList(
        context: Context,
        @ColorRes pressedColorRes: Int,
        @ColorRes defaultColorRes: Int
    ): ColorStateList {
        val pressedColor = ContextCompat.getColor(context, pressedColorRes)
        val defaultColor = ContextCompat.getColor(context, defaultColorRes)

        return ColorStateList(
            arrayOf(
                intArrayOf(android.R.attr.state_selected, android.R.attr.state_checked),
                intArrayOf() // this should be empty to make default color as we want
            ),
            intArrayOf(pressedColor, defaultColor)
        )
    }

    private val isOnMainThread: Boolean
        get() = Looper.getMainLooper().thread === Thread.currentThread()

    fun checkThread(prefix: String) {
        var newPrefix = prefix

        if (!TextUtils.isEmpty(prefix)) {
            newPrefix = "$prefix "
        }

        if (isOnMainThread) {
            Logger.i(newPrefix + "Main thread")
        } else {
            Logger.i(newPrefix + "New thread")
        }
    }

    fun setGradientBackground(view: View?, @ColorInt topColor: Int, @ColorInt bottomColor: Int) {
        if (view == null) {
            return
        }

        val drawable = GradientDrawable(
            GradientDrawable.Orientation.TOP_BOTTOM,
            intArrayOf(topColor, bottomColor)
        )

        view.background = drawable
    }

    fun setMenuTextColor(context: Context?, toolbar: Toolbar?, menuResId: Int, colorRes: Int) {
        if (context == null || toolbar == null) {
            return
        }

        toolbar.post {
            val settingsMenuItem = toolbar.findViewById<View>(menuResId)

            if (settingsMenuItem is TextView) {
                settingsMenuItem.setTextColor(ContextCompat.getColor(context, colorRes))
            } else {
                val menu = toolbar.menu

                if (menu != null) {
                    val item = menu.findItem(menuResId)

                    if (item != null && item.title != null) {
                        val s = SpannableString(item.title)
                        s.setSpan(
                            ForegroundColorSpan(
                                ContextCompat.getColor(
                                    context,
                                    colorRes
                                )
                            ),
                            0, s.length, 0
                        )
                        item.title = s
                    }
                }
            }
        }
    }
}
