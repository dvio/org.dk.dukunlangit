package org.dkproject.dukunlangit;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        CardView cardAndroid = findViewById(R.id.cardAndroid);
        CardView cardBeta = findViewById(R.id.cardBeta);
        CardView cardHuawei = findViewById(R.id.cardHuawei);

        // Assign package names to each CardView
        cardAndroid.setOnClickListener(view -> checkAndSavePackage("com.tgc.sky.android"));
        cardBeta.setOnClickListener(view -> checkAndSavePackage("com.tgc.sky.android.test.gold"));
        cardHuawei.setOnClickListener(view -> checkAndSavePackage("com.tgc.sky.android.huawei"));
    }

    private void checkAndSavePackage(String packageName) {
        PackageManager pm = getPackageManager();
        try {
            pm.getPackageInfo(packageName, PackageManager.GET_ACTIVITIES);

            // Package exists, save it to SharedPreferences
            SharedPreferences sharedPreferences = getSharedPreferences("DukunLangitConfig", MODE_PRIVATE);
            SharedPreferences.Editor editor = sharedPreferences.edit();
            editor.putString("active_sky_package", packageName);
            editor.apply();

            // Start the LauncherActivity
            Intent intent = new Intent(this, LauncherActivity.class);
            startActivity(intent);
        } catch (PackageManager.NameNotFoundException e) {
            // Package doesn't exist, show a toast message
            Toast.makeText(this, "Package " + packageName + " does not exist", Toast.LENGTH_SHORT).show();
        }
    }
}
