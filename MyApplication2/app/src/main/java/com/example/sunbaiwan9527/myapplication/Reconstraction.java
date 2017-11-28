package com.example.sunbaiwan9527.myapplication;

import android.util.Log;

/**
 * Created by sunbaiwan9527 on 16-10-5.
 */
public class Reconstraction {
    static {;
        System.loadLibrary("cmvs");
        System.loadLibrary("genOption");
        System.loadLibrary("pmvs2");
        System.loadLibrary("ssd_recon");
        System.loadLibrary("ply2obj");
    }
    private native void cmvs(String pmvs_path,String max_image,String CPU_number);
    private native void genOption(String pmvs_path);
    private native void pmvs(String pmvs_path,String name);
    private native void ssd(String input_ply,String output_ply);
    private native void ply2obj(String input_ply,String output_obj);

    private static String dir;
    private static String TAG ="sunbaiwan9527";

    private static Reconstraction ourInstance ;

    public static Reconstraction getInstance(String dir) {
        if(ourInstance==null){
            ourInstance = new Reconstraction(dir);
        }
        return ourInstance;
    }

    private Reconstraction(String dir) {
        this.dir = dir;
    }
    public  void runpmvscmvs(){
        try {

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
    } catch (Exception e) {
        e.printStackTrace();
    }
    }
    public void getvolume(){
        Log.d(TAG, "ssd start");
      //  ssd(dir+"/pmvs/models/option-0000.ply",dir+"/pmvs/models/option_ssd.ply");
        Log.d(TAG, "ssd end");
        Log.d(TAG, "ply2obj start");
      //  ply2obj(dir+"/pmvs/models/option_ssd.ply",dir+"/pmvs/models/option_ssd.obj");
        Log.d(TAG, "ply2obj end");
        ObjectVolume.caculateVolume(dir+"/pmvs/models/option_ssd.obj");


    }
}
