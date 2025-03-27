#include <jni.h>
#include <string>

#include "GlobalVars.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_dkproject_dukunlangit_LauncherActivity_initVars(
        JNIEnv *env,
        jclass clazz,
        jstring gameVersion,
        jint gameType,
        jstring hostName,
        jstring configDir,
        jobject context,
        jobject resources) {
    if (!GlobalVars::LangitContext) GlobalVars::LangitContext = env->NewGlobalRef(context);
    if (!GlobalVars::GameResources) GlobalVars::GameResources = env->NewGlobalRef(resources);
    GlobalVars::GameVersion = env->GetStringUTFChars(gameVersion, nullptr);
    GlobalVars::GameType = gameType;
    GlobalVars::ServerHostname = env->GetStringUTFChars(hostName, nullptr);
    GlobalVars::ConfigDir = env->GetStringUTFChars(configDir, nullptr);
}

// Getter function for C++ when needed
jobject getLangitContext(JNIEnv *env) {
    return GlobalVars::LangitContext;
}

jobject getGameResources(JNIEnv *env) {
    return GlobalVars::GameResources;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_dkproject_dukunlangit_LauncherActivity_onKeyboardCompleteNative(
        JNIEnv *env,
        jclass clazz,
        jstring message
) {
    //Fix This
//    std::string msg = env->GetStringUTFChars(message, nullptr);
//    for (auto& listener : Canvas::onKeyboardCompleteListeners) {
//        listener(msg);
//    }
}