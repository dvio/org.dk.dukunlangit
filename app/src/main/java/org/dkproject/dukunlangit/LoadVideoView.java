package org.dkproject.dukunlangit;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.VideoView;
import android.view.View;
import android.widget.FrameLayout;

public class LoadVideoView extends VideoView {
    public LoadVideoView(Context context) {
        super(context);
    }

    public LoadVideoView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public LoadVideoView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int measuredWidth = MeasureSpec.getSize(widthMeasureSpec);
        int measuredHeight = MeasureSpec.getSize(heightMeasureSpec);

        int videoWidth = 1920;
        int videoHeight = 1080;

        int finalWidth = measuredWidth;
        int finalHeight = measuredHeight;

        if (videoWidth > 0 && videoHeight > 0) {
            float aspectRatio = (float) videoWidth / videoHeight;
            float viewRatio = (float) measuredWidth / measuredHeight;

            if (viewRatio > aspectRatio) {
                finalWidth = (int) (measuredHeight * aspectRatio);
            } else {
                finalHeight = (int) (measuredWidth / aspectRatio);
            }
        }

        setMeasuredDimension(finalWidth, finalHeight);

        // Ensure it's centered inside the FrameLayout
        final int widthToSet = finalWidth;
        final int heightToSet = finalHeight;
        post(() -> {
            View parent = (View) getParent();
            if (parent != null) {
                FrameLayout.LayoutParams params = (FrameLayout.LayoutParams) getLayoutParams();
                params.width = widthToSet;
                params.height = heightToSet;
                params.gravity = android.view.Gravity.CENTER;
                setLayoutParams(params);
            }
        });
    }


//    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
//
//        int width = getDefaultSize(0, widthMeasureSpec);
//        int height = getDefaultSize(0, heightMeasureSpec);
//        float aspectRatio = (float) 1920 / 1082;
//        float viewRatio = (float) width / height;
//        if (viewRatio > aspectRatio) {
//            width = (int) (height * aspectRatio);
//        } else {
//            height = (int) (width / aspectRatio);
//        }
//        setMeasuredDimension(width, height);
//    }

}