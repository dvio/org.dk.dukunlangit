package org.dkproject.dukunlangit;

import android.app.Application;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.res.Resources;
import android.content.Context;

public class LangitApp extends Application {
    private static LangitApp langitApplication;
    public static String gamePkg;
    public static Resources gameRes;
    public static Resources langitRes;
    public static LangitApp deez() {
        return langitApplication;
    }
}
