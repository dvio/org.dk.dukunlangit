#ifndef USERLIB_MENU_H
#define USERLIB_MENU_H

#endif //USERLIB_MENU_H

#include "imgui.h"
#include <string>
#include <vector>

namespace UI {
    struct MenuButton {
        ImTextureID texture;
        std::string label;
        bool isSelected;
    };
//    extern void ShowFloatingMenuButton();
//    extern void DrawMainMenu();

    extern void DrawUI();


    extern void DrawMainPage();
    extern void DrawTestPage();

}
