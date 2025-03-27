#include "Menu.h"
#include "imgui.h"
#include <iostream>

#include "Logger.h"

// Store menus

namespace Menu {
    std::string ActiveMenu = "";

    std::vector<Menu::MenuItem> Menus;
    std::unordered_map<std::string, MenuItem*> MenuLookup;

// Function to get JSON (Placeholder, replace with actual JSON retrieval)
    std::string getMenuJson() {
        return R"({
        "menus": [
            {
                "id": "Main",
                "enabled": true,
                "hasUI": false,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icMain",
                "submenus": [
                    {
                        "id": "Essentials",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icEssentials",
                        "submenus": []
                    },
                    {
                        "id": "Witchcraft",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icWitchcraft",
                        "submenus": []
                    },
                    {
                        "id": "Map Hack",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icMapHack",
                        "submenus": []
                    },
                    {
                        "id": "Fakery",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icFakery",
                        "submenus": []
                    }
                ]
            },
            {
                "id": "Extra",
                "enabled": true,
                "hasUI": false,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icExtra",
                "submenus": [
                    {
                        "id": "Miscellaneous",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icMiscellaneous",
                        "submenus": []
                    },
                    {
                        "id": "Avatar",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icAvatar",
                        "submenus": []
                    },
                    {
                        "id": "Ambience",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icAmbience",
                        "submenus": []
                    },
                    {
                        "id": "Camera",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icCamera",
                        "submenus": []
                    }
                ]
            },
            {
                "id": "Teleport",
                "enabled": true,
                "hasUI": false,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icTeleport",
                "submenus": [
                    {
                        "id": "World Teleport",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icWorldTP",
                        "submenus": []
                    },
                    {
                        "id": "Blink",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icBlink",
                        "submenus": []
                    }
                ]
            },
            {
                "id": "Farming",
                "enabled": true,
                "hasUI": false,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icFarming",
                "submenus": [
                    {
                        "id": "Auto Farm",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icFarming",
                        "submenus": []
                    },
                    {
                        "id": "Spirits",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icSpirits",
                        "submenus": []
                    },
                    {
                        "id": "Spirit Shop",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icSpiritShop",
                        "submenus": []
                    }
                ]
            },
            {
                "id": "Auto Music",
                "enabled": true,
                "hasUI": true,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icAutoMusic",
                "submenus": []
            },
            {
                "id": "Setting",
                "enabled": true,
                "hasUI": false,
                "tiers": [9, 0, 1, 2],
                "games": [0, 1, 2],
                "icon": "icSettings",
                "submenus": [
                    {
                        "id": "Settings",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icSettings2",
                        "submenus": []
                    },
                    {
                        "id": "About",
                        "enabled": true,
                        "hasUI": true,
                        "tiers": [9, 0, 1, 2],
                        "games": [0, 1, 2],
                        "icon": "icAbout",
                        "submenus": []
                    }]
            }
        ]
    })";
    }

    // Function to check if a menu is available for a user
    bool isMenuAvailable(const MenuItem& menu, int userTier, int userGame) {
        bool tierAllowed = std::find(menu.tiers.begin(), menu.tiers.end(), userTier) != menu.tiers.end();
        bool gameAllowed = std::find(menu.games.begin(), menu.games.end(), userGame) != menu.games.end();
        return menu.enabled && tierAllowed && gameAllowed;
    }

// Recursive function to parse a menu from JSON
    void parseMenu(const json &menuJson, int userTier, int userGame, std::vector<MenuItem> &menuList) {
        MenuItem menu;
        menu.id = menuJson.value("id", "");
        menu.enabled = menuJson.value("enabled", true);
        menu.hasUI = menuJson.value("hasUI", false);
        menu.tiers = menuJson.value("tiers", std::vector<int>{9});
        menu.games = menuJson.value("games", std::vector<int>{0, 1, 2});
        menu.icon = menuJson.value("icon", "default_icon");

        if (!isMenuAvailable(menu, userTier, userGame)) {
            return;  // Skip this menu
        }

        // Store the menu first
        menuList.push_back(menu);  // Do not use std::move
        MenuItem &storedMenu = menuList.back();  // Get reference AFTER adding

// Now parse submenus
        if (menuJson.contains("submenus")) {
            for (const auto &subJson : menuJson["submenus"]) {
                parseMenu(subJson, userTier, userGame, storedMenu.submenus);
            }
        }


        // Store in lookup map
        MenuLookup[storedMenu.id] = &storedMenu;
    }

    void InitMenus(int userTier, int userGame) {
        json menuData = json::parse(getMenuJson());
        Menus.clear();
        MenuLookup.clear();

        for (const auto &menuJson : menuData["menus"]) {
            parseMenu(menuJson, userTier, userGame, Menus);
        }

//        // Debugging
//        LOGI("Total Menus: %d", (int)Menus.size());
//        for (const auto &menu : Menus) {
//            LOGI("Menu ID: %s, Submenus: %d", menu.id.c_str(), (int)menu.submenus.size());
//        }
//        LOGI("Total Lookup Entries: %d", (int)MenuLookup.size());

    }

}
