package com.ezored.sample.utils;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.support.annotation.ColorInt;
import android.support.annotation.ColorRes;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.SpannableString;
import android.text.TextUtils;
import android.text.style.ForegroundColorSpan;
import android.util.DisplayMetrics;
import android.util.TypedValue;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;

import com.ezored.sample.R;
import com.ezored.sample.interfaces.Closure;
import com.ezored.util.Logger;

import java.lang.reflect.Field;
import java.util.Random;

public class UIUtil {

    public static void showAlert(Context context, String title, String message) {
        AlertDialog alertDialog = new AlertDialog.Builder(context).create();
        alertDialog.setTitle(title);
        alertDialog.setMessage(message);
        alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, context.getString(R.string.dialog_button_ok),
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
        alertDialog.show();
    }

    public static void showViewById(Activity activity, int viewId) {
        if (activity == null) {
            return;
        }

        View view = activity.findViewById(viewId);

        if (view != null) {
            view.setVisibility(View.VISIBLE);
        }
    }

    public static void showViewById(View container, int viewId) {
        if (container == null) {
            return;
        }

        final View view = container.findViewById(viewId);

        if (view != null) {
            view.setVisibility(View.VISIBLE);
        }
    }

    public static void hideViewById(View container, int viewId) {
        if (container == null) {
            return;
        }

        View view = container.findViewById(viewId);

        if (view != null) {
            view.setVisibility(View.GONE);
        }
    }

    public static void hideViewById(Activity activity, int viewId) {
        if (activity == null) {
            return;
        }

        View view = activity.findViewById(viewId);

        if (view != null) {
            view.setVisibility(View.GONE);
        }
    }

    public static float convertDpToPixel(float dp) {
        DisplayMetrics metrics = Resources.getSystem().getDisplayMetrics();
        float px = dp * (metrics.densityDpi / 160f);
        return Math.round(px);
    }

    public static void setActivityAsTransparent(Activity activity) {
        if (activity == null) {
            return;
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            Window window = activity.getWindow();
            window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS | WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN | View.SYSTEM_UI_FLAG_LAYOUT_STABLE);
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
            window.setStatusBarColor(Color.TRANSPARENT);
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            Window window = activity.getWindow();
            window.addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
            window.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS, WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        }
    }

    public static void adjustToolbarPadding(Activity activity, View view) {
        if (view == null) {
            return;
        }

        int paddingTop;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            paddingTop = getStatusBarHeight(activity);
        } else {
            paddingTop = 0;
        }

        TypedValue typedValue = new TypedValue();
        activity.getTheme().resolveAttribute(android.support.v7.appcompat.R.attr.drawableSize, typedValue, true);
        paddingTop += TypedValue.complexToDimensionPixelOffset(typedValue.data, activity.getResources().getDisplayMetrics());
        activity.findViewById(R.id.toolbar).setPadding(0, paddingTop, 0, 0);
    }

    private static int getStatusBarHeight(Activity activity) {
        int result = 0;
        int resourceId = activity.getResources().getIdentifier("status_bar_height", "dimen", "android");
        if (resourceId > 0) {
            result = activity.getResources().getDimensionPixelSize(resourceId);
        }
        return result;
    }

    public static Drawable drawableColorChange(Context context, int icon, int color) {
        Drawable drawable;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            drawable = context.getDrawable(icon);
        } else {
            drawable = context.getResources().getDrawable(icon);
        }

        if (drawable != null) {
            drawable.setColorFilter(ContextCompat.getColor(context, color), PorterDuff.Mode.SRC_IN);
        }

        return drawable;
    }

    public static void runOnMainThread(final Closure closure) {
        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(new Runnable() {
            @Override
            public void run() {
                if (closure != null) {
                    closure.exec();
                }
            }
        });
    }

    public static void runOnMainThreadDelayed(final Closure closure, final long millis) {
        Handler handler = new Handler(Looper.getMainLooper());
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                if (closure != null) {
                    closure.exec();
                }
            }
        }, millis);
    }

    public static void runOnNewThread(final Closure closure) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                if (closure != null) {
                    closure.exec();
                }
            }
        }).start();
    }

    public static void runOnNewThreadDelayed(final Closure closure, final long millis) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(millis);
                } catch (Exception e) {
                    // ignore
                }

                if (closure != null) {
                    closure.exec();
                }
            }
        }).start();
    }

    public static void changeVisibility(View view, int visibility, boolean animate) {
        if (view == null || visibility == view.getVisibility()) {
            return;
        }

        view.clearAnimation();

        if (animate) {
            int animResourceId;

            if (visibility == View.VISIBLE) {
                animResourceId = android.R.anim.fade_in;
            } else {
                animResourceId = android.R.anim.fade_out;
            }

            Animation anim = AnimationUtils.loadAnimation(view.getContext(), animResourceId);
            view.setAnimation(anim);
        }

        view.setVisibility(visibility);
    }

    public static Bitmap drawableToBitmap(Drawable drawable) {
        Bitmap bitmap = null;

        if (drawable instanceof BitmapDrawable) {
            BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;

            if (bitmapDrawable.getBitmap() != null) {
                return bitmapDrawable.getBitmap();
            }
        }

        if (drawable.getIntrinsicWidth() <= 0 || drawable.getIntrinsicHeight() <= 0) {
            bitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888); // Single color bitmap will be created of 1x1 pixel
        } else {
            bitmap = Bitmap.createBitmap(drawable.getIntrinsicWidth(), drawable.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
        }

        Canvas canvas = new Canvas(bitmap);
        drawable.setBounds(0, 0, canvas.getWidth(), canvas.getHeight());
        drawable.draw(canvas);

        return bitmap;
    }

    public static boolean checkIfAlertDialogIsShowing(AlertDialog alertDialog) {
        if (alertDialog == null) {
            return false;
        }

        if (alertDialog.isShowing()) {
            return true;
        } else {
            return false;
        }
    }


    public static void dismissDialog(Dialog dialog) {
        if (dialog == null) {
            return;
        }

        try {
            dialog.dismiss();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void dismissDialogInterface(DialogInterface dialogInterface) {
        if (dialogInterface == null) {
            return;
        }

        try {
            dialogInterface.dismiss();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void showPlayerNoConnectionAlertDialog(AlertDialog alertDialog) {
        if (alertDialog == null) {
            return;
        }

        try {
            alertDialog.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void applyFadeAnimation(Context context) {
        if (context instanceof AppCompatActivity) {
            ((Activity) context).overridePendingTransition(0, R.anim.activity_fade_out);
        }
    }

    public static void setActivityAsFullScreen(Activity activity) {
        if (activity == null) {
            return;
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            final Window window = activity.getWindow();
            window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
    }

    public static float getScreenWidth() {
        return Resources.getSystem().getDisplayMetrics().widthPixels;
    }

    public static void hideKeyboard(Activity context) {
        if (context != null) {
            View view = context.getCurrentFocus();

            if (view != null) {
                IBinder token = view.getWindowToken();

                if (token != null) {
                    try {
                        InputMethodManager imm = (InputMethodManager) context.getSystemService(Context.INPUT_METHOD_SERVICE);
                        imm.hideSoftInputFromWindow(token, 0);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    public static void setCursorDrawableColor(EditText editText, @ColorInt int color) {
        try {
            // Get the cursor resource id
            Field field = TextView.class.getDeclaredField("mCursorDrawableRes");
            field.setAccessible(true);
            int drawableResId = field.getInt(editText);

            // Get the editor
            field = TextView.class.getDeclaredField("mEditor");
            field.setAccessible(true);
            Object editor = field.get(editText);

            // Get the drawable and set a color filter
            Drawable drawable = ContextCompat.getDrawable(editText.getContext(), drawableResId);
            drawable.setColorFilter(color, PorterDuff.Mode.SRC_IN);
            Drawable[] drawables = {drawable, drawable};

            // Set the drawables
            field = editor.getClass().getDeclaredField("mCursorDrawable");
            field.setAccessible(true);
            field.set(editor, drawables);
        } catch (Exception e) {
            // ignore
        }
    }

    public static String randomString(int size) {
        Random generator = new Random();
        StringBuilder randomStringBuilder = new StringBuilder();
        char tempChar;

        for (int i = 0; i < size; i++) {
            tempChar = (char) (generator.nextInt(96) + 32);
            randomStringBuilder.append(tempChar);
        }

        return randomStringBuilder.toString();
    }

    public static ColorStateList buildColorStateList(Context context, @ColorRes int pressedColorRes, @ColorRes int defaultColorRes) {
        int pressedColor = ContextCompat.getColor(context, pressedColorRes);
        int defaultColor = ContextCompat.getColor(context, defaultColorRes);

        return new ColorStateList(
                new int[][]{
                        new int[]{android.R.attr.state_selected, android.R.attr.state_checked},
                        new int[]{} // this should be empty to make default color as we want
                }, new int[]{
                pressedColor,
                defaultColor
        }
        );
    }

    private static boolean isOnMainThread() {
        if (Looper.getMainLooper().getThread() == Thread.currentThread()) {
            return true;
        }

        return false;
    }

    public static void checkThread(String prefix) {
        if (!TextUtils.isEmpty(prefix)) {
            prefix = prefix + " ";
        }

        if (isOnMainThread()) {
            Logger.i(prefix + "Main thread");
        } else {
            Logger.i(prefix + "New thread");
        }
    }

    public static void setGradientBackground(View view, @ColorInt int topColor, @ColorInt int bottomColor) {
        if (view == null) {
            return;
        }

        GradientDrawable drawable = new GradientDrawable(GradientDrawable.Orientation.TOP_BOTTOM, new int[]{
                topColor,
                bottomColor,
        });

        view.setBackground(drawable);
    }

    public static void setMenuTextColor(final Context context, final Toolbar toolbar, final int menuResId, final int colorRes) {
        if (context == null || toolbar == null) {
            return;
        }

        toolbar.post(new Runnable() {
            @Override
            public void run() {
                View settingsMenuItem = toolbar.findViewById(menuResId);

                if (settingsMenuItem instanceof TextView) {
                    TextView tv = (TextView) settingsMenuItem;
                    tv.setTextColor(ContextCompat.getColor(context, colorRes));
                } else {
                    Menu menu = toolbar.getMenu();

                    if (menu != null) {
                        MenuItem item = menu.findItem(menuResId);

                        if (item != null && item.getTitle() != null) {
                            SpannableString s = new SpannableString(item.getTitle());
                            s.setSpan(new ForegroundColorSpan(ContextCompat.getColor(context, colorRes)), 0, s.length(), 0);
                            item.setTitle(s);
                        }
                    }
                }
            }
        });
    }

    public void startServiceOrForegroundService(Context context, Intent intent) {
        try {
            ContextCompat.startForegroundService(context, intent);
        } catch (Exception e) {
            Logger.e("[Application : startServiceOrForegroundService] Failed to start foreground service");
            e.printStackTrace();
        }
    }

}
