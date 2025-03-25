package org.dkproject.dukunlangit;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;

import com.tgc.sky.BuildConfig;
import com.tgc.sky.GameActivity;

import java.io.File;
import java.io.IOException;

public class LauncherActivity extends Activity {
    private SharedPreferences sharedPreferences;
    public static String ACTIVE_SKY_PACKAGE;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Retrieve the selected package name
        sharedPreferences = getSharedPreferences("DukunLangitConfig", MODE_PRIVATE);
        ACTIVE_SKY_PACKAGE = sharedPreferences.getString("active_sky_package", "com.tgc.sky.android");

        if (!ACTIVE_SKY_PACKAGE.isEmpty()) {
            // Placeholder for library loading logic
            Log.d("LauncherActivity", "Loading libraries for: " + ACTIVE_SKY_PACKAGE);

//            loadLibraries(ACTIVE_SKY_PACKAGE);
        } else {
            Log.e("LauncherActivity", "No package selected.");
        }

        int gameType = 0;
        if (ACTIVE_SKY_PACKAGE.equals("com.tgc.sky.android.test.gold")) {
            gameType = 1;
        } else if (ACTIVE_SKY_PACKAGE.equals("com.tgc.sky.android.huawei")) {
            gameType = 2;
        }

        loadGame(gameType);
    }

    private void loadGame(int gameType) {
        PackageManager pm = getPackageManager();
        try {
            PackageInfo pkgInfo;
            pkgInfo = pm.getPackageInfo(ACTIVE_SKY_PACKAGE, PackageManager.GET_SHARED_LIBRARY_FILES);
            Context langitContext = getApplicationContext();
            Resources gameResources = null;
            try {
                Context gameContext = getApplicationContext().createPackageContext(
                        ACTIVE_SKY_PACKAGE,
                        Context.CONTEXT_INCLUDE_CODE | Context.CONTEXT_IGNORE_SECURITY);
                gameResources = gameContext.getResources();
            } catch (PackageManager.NameNotFoundException e) {
                e.printStackTrace();
            }
            LangitApplication.init(pkgInfo.packageName, langitContext, gameResources);
            String gameVersion = pkgInfo.versionName;
            BuildConfig.SKY_VERSION = gameVersion.substring(0, gameVersion.indexOf(' ')).trim();
            BuildConfig.VERSION_CODE = pkgInfo.versionCode;
//            String nativeLibraryDir = pkgInfo.applicationInfo.nativeLibraryDir;
//            File modsDir = new File(getFilesDir(), "mods");
            File configDir = new File(getFilesDir(), "config");
            if (!configDir.isDirectory() && !configDir.mkdirs()) throw new IOException("Failed to create config directory");


            String nativeLibraryDir = pkgInfo.applicationInfo.nativeLibraryDir;
            Log.d("LauncherActivity", "Loading Bootloader\n" + nativeLibraryDir);

            boolean success = ELFLoader.loadLibrary(nativeLibraryDir, "libBootloader.so");

            if (success) {
                Log.d("LauncherActivity", "Bootloader loaded successfully");
                System.out.println("Library loaded successfully");
            } else {
                Log.d("LauncherActivity", "Failed to load Bootloader");
                System.err.println("Failed to load library");
            }

            Log.d("LauncherActivity", "Loading Native library");

            System.loadLibrary("DukunLangit");



            if (ACTIVE_SKY_PACKAGE.equals("com.tgc.sky.android.test.gold")) {
//                ACTIVE_SKY_PACKAGE = "com.tgc.sky.android.test.";
                BuildConfig.SKY_SERVER_HOSTNAME = "beta.radiance.thatgamecompany.com";
                BuildConfig.SKY_BRANCH_NAME = "Test";
                BuildConfig.SKY_STAGE_NAME = "Beta";
            }

            Log.d("LauncherActivity", "Initializing Native variables");
            initVars(gameVersion, gameType, BuildConfig.SKY_SERVER_HOSTNAME, configDir.getAbsolutePath(), langitContext, gameResources);
            BuildConfig.APPLICATION_ID = ACTIVE_SKY_PACKAGE;

            Log.d("LauncherActivity", "Starting Game");
            startActivity(new Intent(this, GameActivity.class));

        } catch (PackageManager.NameNotFoundException e) {
//            alertDialog(getString(R.string.sky_not_installed));
        } catch (Throwable e) {
//            alertDialog(e);
        }
    }

    private void loadLibraries(String packageName) {
        // TODO: Implement actual library loading logic
        Log.d("LauncherActivity", "Libraries for " + packageName + " would be loaded here.");
    }

    public static native void initVars(
            String gameVersion,
            int gameType,
            String hostName,
            String configDir,
            Context context,
            Resources resources
    );
    public static native void onKeyboardCompleteNative(String message);
}
