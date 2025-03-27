#include "Main.h"

#include "GlobalVars.h"
#include "Graphic.h"
#include "Menu.h"
#include "Styles.h"

namespace Core {
    void InitMain(){
        InitImages();
        Menu::InitMenus(9, GlobalVars::GameType);
        Styles::InitStyles();
        Styles::ApplyStyle("TransparentNeon");
    }
}
