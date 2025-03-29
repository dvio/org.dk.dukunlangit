#pragma once

#include <jni.h>
#include <string>

namespace GlobalVars {
    extern jobject LangitContext;
    extern jobject GameResources;
    extern std::string GameVersion;
    extern int GameType;
    extern std::string ServerHostname;
    extern std::string ConfigDir;

    extern float GlobalScale;
    extern std::string ActiveStyle;
} // GlobalVars