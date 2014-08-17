package %TopDomainName:l%.%CompanyName:l%.%ProjectName:l%;

import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.util.DisplayMetrics;
import android.widget.Toast;

import java.io.File;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

import %TopDomainName:l%.%CompanyName:l%.%ProjectName:l%.R;

public class %ProjectName:c% extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static final String TAG = "%ProjectName:c%";
    private static %ProjectName:c% m_instance;
    public static long qtObject = 0;
    public static String initialData = "";
    public static String initialDataType = "";

    public %ProjectName:c%()
    {
        m_instance = this;
    }

    @Override
    protected void onStart()
    {
        super.onStart();
        m_instance = this;

        Intent intent = getIntent();

        String action = intent.getAction();

        if (action != null && action.equals(Intent.ACTION_VIEW)) {
            Uri data = intent.getData();
            if (data != null) {
                // Log.d(TAG, "DATA:" + data.toString()
                initialData = data.toString();
                initialDataType = intent.getType();
            }
        }
    }

    @Override
    protected void onNewIntent(Intent intent)
    {
        super.onNewIntent(intent);
        // Log.d(TAG, "onNewIntent: " + intent.toString());

        String action = intent.getAction();

        if (action != null && action.equals(Intent.ACTION_VIEW)) {
            Uri data = intent.getData();
            if (data != null) {
                // Handle new intent here
            }
        }
    }

    public static void setQtObject(long data) {
        qtObject = data;
    }

    public static void toast(final String message)
    {
        m_instance.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(m_instance.getApplicationContext(), message, Toast.LENGTH_SHORT).show();
            }
        });
    }

    public static void shareUrl(String name, String url)
    {
        Intent share = new Intent(android.content.Intent.ACTION_SEND);
        share.setType("text/plain");
        share.addFlags(Intent.FLAG_ACTIVITY_CLEAR_WHEN_TASK_RESET);
        share.putExtra(Intent.EXTRA_SUBJECT, name);
        if (!name.isEmpty()) {
            share.putExtra(Intent.EXTRA_TEXT, name + " - " + url + " via %ProjectName:c%");
            m_instance.startActivity(Intent.createChooser(share, "Share " + name));
        } else {
            share.putExtra(Intent.EXTRA_TEXT, url + " via %ProjectName:c%");
            m_instance.startActivity(Intent.createChooser(share, "Share this"));
        }
    }

    public static void shareFile(String filename)
    {
        Intent share = new Intent(android.content.Intent.ACTION_SEND);
        share.setType("image/*");
        File imageFileToShare = new File(filename);
        Uri uri = Uri.fromFile(imageFileToShare);
        share.putExtra(Intent.EXTRA_STREAM, uri);

        m_instance.startActivity(Intent.createChooser(share, "Share image"));
    }

    public static int getDPI()
    {
        DisplayMetrics dm = m_instance.getResources().getDisplayMetrics();
        return dm.densityDpi;
    }

    public static boolean isTablet()
    {
        return m_instance.getResources().getBoolean(R.bool.isTablet);
    }

    public static byte[] getImageData(String url) 
    {
        byte[] imageBuffer = new byte[0];

        try {
            Uri data = Uri.parse(url);
            InputStream contentData = m_instance.getApplicationContext().getContentResolver().openInputStream(data);

            int size = contentData.available();
            imageBuffer = new byte[size];
            contentData.read(imageBuffer, 0, size);

        } catch (Exception e) {
            e.printStackTrace();
            Log.e(TAG, "e " + e.getMessage());
        }

        return imageBuffer;
    }
}

