#ifndef USERLIB_MENU_H
#define USERLIB_MENU_H

#endif //USERLIB_MENU_H

#include "imgui.h"
#include <string>

struct MenuButton {
    ImTextureID texture;
    std::string label;
    bool isSelected;
};

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
extern ImTextureID icFakery;
extern ImTextureID icMapHack;
extern ImTextureID icWitchcraft;

extern ImTextureID icAmbience;
extern ImTextureID icAvatar;
extern ImTextureID icCamera;
extern ImTextureID icMiscellaneous;
extern ImTextureID icWorldTP;
extern ImTextureID icBlink;

extern ImTextureID icSpirits;
extern ImTextureID icSpiritShop;

extern void InitImages();

namespace UI {
    extern std::vector<MenuButton> MainMenu;
    extern std::vector<std::vector<MenuButton>> SubMenu;
    extern void ShowFloatingMenuButton();
    extern void ShowMainMenu();
}
