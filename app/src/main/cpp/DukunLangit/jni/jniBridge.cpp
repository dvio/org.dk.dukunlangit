#include <jni.h>
#include <string>

static jobject g_langitContext = nullptr;
static jobject g_gameResources = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_org_dkproject_dukunlangit_LauncherActivity_initEssentials(
        JNIEnv *env,
        jclass clazz,
        jint gameVersion,
        jint gameType,
        jstring hostName,
        jstring configDir,
        jobject context,
        jobject resources) {
    if (!g_langitContext) g_langitContext = env->NewGlobalRef(context);
    if (!g_gameResources) g_gameResources = env->NewGlobalRef(resources);
}

// Getter function for C++ when needed
jobject getLangitContext(JNIEnv *env) {
    return g_langitContext;
}

jobject getGameResources(JNIEnv *env) {
    return g_gameResources;
}