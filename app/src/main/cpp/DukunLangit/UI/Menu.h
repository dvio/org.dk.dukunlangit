#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "json.hpp"

using json = nlohmann::json;

namespace Menu {
    struct MenuItem {
        std::string id;
        bool enabled;
        bool hasUI;
        std::vector<int> tiers;
        std::vector<int> games;
        std::string icon;
        std::vector<MenuItem> submenus;
    };

    extern std::string ActiveMenu;  // Stores the currently active menu
    extern std::vector<MenuItem> Menus;  // Stores the parsed menus
    extern std::unordered_map<std::string, MenuItem*> MenuLookup;

    extern void InitMenus(int userTier, int userGame);  // Loads the menus from JSON
//    void RenderMenus();  // Calls ImGui to display the menu
}
