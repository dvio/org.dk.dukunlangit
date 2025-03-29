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

    void InitPages();

    void DrawUI();


    void DrawMainPage();
    void DrawTestPage();

    //Style
    void DrawStyleSelector(std::string label);

    bool BeginScrollingChild(const char* str_id, const ImVec2& size, ImGuiChildFlags childFlags = 0, ImGuiWindowFlags flags = 0);
    void EndScrollingChild();

}

namespace TestPage {
    void InitPages();
    void DrawContent();
}
