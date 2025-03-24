package org.dkproject.dukunlangit;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;

import com.tgc.sky.BuildConfig;
//import com.tgc.sky.GameActivity;

import java.io.File;
import java.io.IOException;
import java.util.Optional;

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
            loadLibraries(ACTIVE_SKY_PACKAGE);
        } else {
            Log.e("LauncherActivity", "No package selected.");
        }

        // Close the activity once done
        loadGame();
    }

    private void loadGame() {
        PackageManager pm = getPackageManager();
        try {
            PackageInfo pkgInfo;
            pkgInfo = pm.getPackageInfo(ACTIVE_SKY_PACKAGE, PackageManager.GET_SHARED_LIBRARY_FILES);
            Context langitContext = getApplicationContext();
            Resources gameResources = null;
            try {
                Context gameContext = getApplicationContext().createPackageContext(
                        "com.game.package",
                        Context.CONTEXT_INCLUDE_CODE | Context.CONTEXT_IGNORE_SECURITY);
                gameResources = gameContext.getResources();
            } catch (PackageManager.NameNotFoundException e) {
                e.printStackTrace();
            }
            LangitApp.init(pkgInfo.packageName, langitContext, gameResources);
            String gameVersion = pkgInfo.versionName;
            BuildConfig.SKY_VERSION = gameVersion.substring(0, gameVersion.indexOf(' ')).trim();
            BuildConfig.VERSION_CODE = pkgInfo.versionCode;
            String nativeLibraryDir = pkgInfo.applicationInfo.nativeLibraryDir;
//            File modsDir = new File(getFilesDir(), "mods");
            File configDir = new File(getFilesDir(), "config");
            if (!configDir.isDirectory() && !configDir.mkdirs()) throw new IOException("Failed to create config directory");

            String libBootloaderPath = nativeLibraryDir + ":/system/lib64/libBootloader.so";
            int result = ELFLoader.loadSharedLibrary(libBootloaderPath);
            if (result == 0) {
                System.out.println("Library loaded successfully");
            } else {
                System.err.println("Failed to load library");
            }
            System.loadLibrary("DukunLangit");
//            System.loadLibrary("Langit");

//            setDeviceInfoNative(
//                    deviceInfo.xdpi,
//                    deviceInfo.ydpi,
//                    deviceInfo.density,
//                    Optional.ofNullable(deviceInfo.deviceName).orElse(""),
//                    Optional.ofNullable(deviceInfo.deviceManufacturer).orElse(""),
//                    Optional.ofNullable(deviceInfo.deviceModel).orElse("")
//            );

//            IconLoader.findIcons();
//            BuildConfig.VERSION_CODE = sharedPreferences.getBoolean("skip_updates", false) ? 0x99999 : info.versionCode;
//            Integer gameType = skyPackages.getOrDefault(SKY_PACKAGE_NAME, 0);
//            MainActivity.settle(
//                    info.versionCode,
//                    gameType == null ? 0 : gameType,
//                    BuildConfig.SKY_SERVER_HOSTNAME,
//                    configDir.getAbsolutePath(),
//                    SkyMod.skyRes.getAssets()
//            );
//
//            if (SKY_PACKAGE_NAME.equals("com.tgc.sky.android.test.gold")) {
//                SKY_PACKAGE_NAME = "com.tgc.sky.android.test.";
//                BuildConfig.SKY_SERVER_HOSTNAME = "beta.radiance.thatgamecompany.com";
//                BuildConfig.SKY_BRANCH_NAME = "Test";
//                BuildConfig.SKY_STAGE_NAME = "Test";
//            }
//
//            if(sharedPreferences.getBoolean("custom_server", false)){
//
//                BuildConfig.SKY_SERVER_HOSTNAME = sharedPreferences.getString("server_host", BuildConfig.SKY_SERVER_HOSTNAME);
//                MainActivity.customServer(BuildConfig.SKY_SERVER_HOSTNAME);
//            }
//
//            new ElfRefcountLoader(nativeLibraryDir + ":/system/lib64", modsDir).load();
//            BuildConfig.APPLICATION_ID = SKY_PACKAGE_NAME;
//            startActivity(new Intent(this, GameActivity.class));
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

    public static native void initEssentials(
            int gameVersion,
            int gameType,
            String hostName,
            String configDir,
            Context context,
            Resources resources
    );
}
