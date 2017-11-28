package com.example.sunbaiwan9527.myapplication;

import android.os.Environment;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    /*static {;
        System.loadLibrary("cmvs");
        System.loadLibrary("genOption");
        System.loadLibrary("pmvs2");
    }
    private native void cmvs(String pmvs_path,String max_image,String CPU_number);
    private native void genOption(String pmvs_path);
    private native void pmvs(String pmvs_path,String name);*/
    private String TAG ="sunbaiwan9527";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Handler mhandler = new Handler();
        String path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES).toString()+ File.separator+"DAKA/photo";
        mhandler.postDelayed(new WorkThread(path), 1000);
    }
    public class WorkThread implements Runnable {
        private boolean isRunning = false;
        private String dir = null;

        public WorkThread(String dir) {
            //Util.scanDir(dir, "jpg", dir + "/list_tmp.txt");
            this.dir = dir;
        }

        @Override
        public void run() {
            Reconstraction.getInstance(dir).getvolume();
            /*try {
                if(!isRunning) {
                    isRunning = true;

                    // CMVS-PMVS - Cluster-Patch Multiview Stereo

	                        Log.d(TAG, "pmvs-cmvs start");
	                        cmvs(dir + "/pmvs/", "100", "8");
	                        genOption(dir + "/pmvs/");
	                        for (int i = 0; i < 1; i++) {
	                            String name = String.format("option-%04d", i);
	                            String path = dir + "/pmvs/" + name;
	                            pmvs(dir + "/pmvs/", name);

	                        Log.d(TAG, "pmvs-cmvs end");
	                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }*/
        }
    }
}
