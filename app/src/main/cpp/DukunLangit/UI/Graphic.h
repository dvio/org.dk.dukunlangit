#pragma once

#include "imgui.h"
#include <string>
#include <unordered_map>

#include <GlobalVars.h>

extern ImTextureID ImageLogo;
extern ImTextureID MainMenuBtnBG;
extern ImTextureID CBTrue;
extern ImTextureID CBFalse;

//Icons

extern ImTextureID icAutoCR;
extern ImTextureID icEdenRun;
extern ImTextureID icMain;
extern ImTextureID icExtra;
extern ImTextureID icFarming;
extern ImTextureID icAutoMusic;
extern ImTextureID icSettings;
extern ImTextureID icSettings2;
extern ImTextureID icTeleport;

extern ImTextureID icEssentials;
extern ImTextureID icWitchcraft;
extern ImTextureID icMapHack;
extern ImTextureID icFakery;
extern ImTextureID icGameSpeed;

extern ImTextureID icAmbience;
extern ImTextureID icAvatar;
extern ImTextureID icCamera;
extern ImTextureID icMiscellaneous;
extern ImTextureID icWorldTP;
extern ImTextureID icBlink;

extern ImTextureID icSpirits;
extern ImTextureID icSpiritShop;
extern ImTextureID icAbout;

extern void InitImages();

namespace Graphic {
    extern std::unordered_map<std::string, ImTextureID> MenuTextures;

    ImTextureID GetMenuIcon(std::string iconName);

    float NormalizeScale(float value);
    int NormalizeScale(int value);
    ImVec2 NormalizeScale(const ImVec2& value);
    ImVec4 NormalizeScale(const ImVec4& value);

}