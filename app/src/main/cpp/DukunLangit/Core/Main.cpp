#include "Main.h"

#include "GlobalVars.h"
#include "Graphic.h"
#include "Menu.h"
#include "Styles.h"
#include "UI.h"

namespace Core {
    void InitMain(){
        InitImages();
        Menu::InitMenus(9, GlobalVars::GameType);
        Styles::InitStyles();
        GlobalVars::ActiveStyle = "RedNeon";

//        Styles::ApplyStyle("DarkMode");
        UI::InitPages();
    }
}
