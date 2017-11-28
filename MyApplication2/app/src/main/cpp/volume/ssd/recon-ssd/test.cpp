//
// Created by sunbaiwan9527 on 16-10-9.
//

#include <jni.h>
#include <android/log.h>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#define  LOG_TAG    "sdd_recon"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"{

void Java_com_example_sunbaiwan9527_myapplication_Reconstraction_ssd(JNIEnv *env, jobject thiz , jstring in_ply, jstring out_ply)
{
    const char* infile1;
    const char* outfile;
  // infile1 =  (env)->GetStringUTFChars(env, in_ply, 0);
    infile1 = env->GetStringUTFChars(in_ply, JNI_FALSE);
    outfile = env->GetStringUTFChars(out_ply, JNI_FALSE);
    char* infile1_2 = new char[strlen(infile1)+1];
    char* outfile2 =new char[strlen(outfile)+1];
    strcpy(infile1_2,infile1);
    strcpy(outfile2,outfile);
    int argc =3;
    char **argv = new char* [argc];
    argv[0] = "sdd_recon";
    argv[1] = infile1_2;
    argv[2] =outfile2;
    ssd(argc,argv);
}
}