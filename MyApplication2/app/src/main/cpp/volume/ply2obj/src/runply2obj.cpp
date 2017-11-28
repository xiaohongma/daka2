//
// Created by sunbaiwan9527 on 16-10-9.
//

//#include "runply2obj.h"
#include <jni.h>
#include <android/log.h>
//#include <iostream>
//#include <vector>
//#include <list>
#include <stdlib.h>
#include <stdio.h>

#define  LOG_TAG    "ply2obj"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"{
#include "runply2obj.h"

void Java_com_example_sunbaiwan9527_myapplication_Reconstraction_ply2obj(JNIEnv* env, jobject thiz ,jstring in_ply,jstring out_obj)
{
    const char* infile1;
    const char* outfile;
    infile1 = env->GetStringUTFChars(in_ply, JNI_FALSE);
    outfile = env->GetStringUTFChars(out_obj, JNI_FALSE);
    char* infile1_2 = new char[strlen(infile1)+1];
    char* outfile2 =new char[strlen(outfile)+1];
    strcpy(infile1_2,infile1);
    strcpy(outfile2,outfile);
    int argc =3;
    char **argv = new char*[argc];
    argv[0] ="runply";
    argv[1] = infile1_2;
    argv[2] =outfile2;
    test(argc,argv);
}
}