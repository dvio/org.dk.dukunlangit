package org.dkproject.dukunlangit;

import android.app.Application;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.res.Resources;
import android.content.Context;

public class LangitApp extends Application {
    private static LangitApp langitApplication;
    private static String gamePkg;

    private static  Context langitContext;
    private static Resources gameRes;

    public static void init(String pkgName, Context context, Resources resources){
        gamePkg = pkgName;
        langitContext = context;
        gameRes = resources;
    }

    public static Context getLangitContext(){
        if (langitContext == null){
            throw new IllegalStateException("LangitContext is not initialized");
        }
        return langitContext;
    }

    public static Resources getGameResources(){
        if (gameRes == null){
            throw new IllegalStateException("GameResources is not initialized");
        }
        return gameRes;
    }

    public static String getGamePackageName(){
        if (gamePkg.isEmpty()){
            throw new IllegalStateException("GamePackageName is not initialized");
        }
        return gamePkg;
    }

//    public static LangitApp deez() {
//        return langitApplication;
//    }
}
