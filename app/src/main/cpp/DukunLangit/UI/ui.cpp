#define _USE_MATH_DEFINES

#include <string>
#include "ui.h"
#include <cmath>
//#include "imgui/imgui_internal.h"
#include "StbImage/create_texture.h"

ImTextureID ImageLogo;
ImTextureID MainMenuBtnBG;
ImTextureID CBTrue;
ImTextureID CBFalse;

ImTextureID icAutoCR;
ImTextureID icEdenRun;
ImTextureID icMain;
ImTextureID icSettings;
ImTextureID icSettings2;
ImTextureID icTeleport;
ImTextureID icExtra;
ImTextureID icFarming;
ImTextureID icAutoMusic;

ImTextureID icEssentials;
ImTextureID icFakery;
ImTextureID icMapHack;
ImTextureID icWitchcraft;

ImTextureID icAmbience;
ImTextureID icAvatar;
ImTextureID icCamera;
ImTextureID icMiscellaneous;
ImTextureID icWorldTP;
ImTextureID icBlink;
ImTextureID icSpirits;
ImTextureID icSpiritShop;

bool imagesInitialized = false;

void InitImages(){
    if (imagesInitialized)
        return;
    imagesInitialized = true;
    INCLUDE_IMG(logo_png);
    INCLUDE_IMG(icAutoCR_png);
    INCLUDE_IMG(icEdenRun_png);
    INCLUDE_IMG(icMain_png);
    INCLUDE_IMG(icSettings_png);
    INCLUDE_IMG(icSettings2_png);
    INCLUDE_IMG(icTeleport_png);
    INCLUDE_IMG(icExtra_png);
    INCLUDE_IMG(icFarming_png);
    INCLUDE_IMG(icAutoMusic_png);

    INCLUDE_IMG(icEssentials_png);
    INCLUDE_IMG(icFakery_png);
    INCLUDE_IMG(icMapHack_png);
    INCLUDE_IMG(icWitchcraft_png);

    INCLUDE_IMG(icAmbience_png);
    INCLUDE_IMG(icAvatar_png);
    INCLUDE_IMG(icCamera_png);
    INCLUDE_IMG(icMiscellaneous_png);
    INCLUDE_IMG(icWorldTP_png);
    INCLUDE_IMG(icBlink_png);
    INCLUDE_IMG(icSpirits_png)
    INCLUDE_IMG(icSpiritShop_png)

    ImageLogo = getTextureID(&logo_png);
    icAutoCR = getTextureID(&icAutoCR_png);
    icEdenRun = getTextureID(&icEdenRun_png);
    icMain = getTextureID(&icMain_png);
    icSettings = getTextureID(&icSettings_png);
    icSettings2 = getTextureID(&icSettings2_png);
    icTeleport = getTextureID(&icTeleport_png);
    icExtra = getTextureID(&icExtra_png);
    icFarming = getTextureID(&icFarming_png);
    icAutoMusic = getTextureID(&icAutoMusic_png);

    icEssentials = getTextureID(&icEssentials_png);
    icFakery = getTextureID(&icFakery_png);
    icMapHack = getTextureID(&icMapHack_png);
    icWitchcraft = getTextureID(&icWitchcraft_png);

    icAmbience = getTextureID(&icAmbience_png);
    icAvatar = getTextureID(&icAvatar_png);
    icCamera = getTextureID(&icCamera_png);
    icMiscellaneous = getTextureID(&icMiscellaneous_png);
    icWorldTP = getTextureID(&icWorldTP_png);
    icBlink = getTextureID(&icBlink_png);
    icSpirits  = getTextureID(&icSpirits_png);
    icSpiritShop  = getTextureID(&icSpiritShop_png);

    UI::MainMenu = {
            {icMain, "A", false},
            {icExtra, "B", false},
            {icTeleport, "C", false},
            {icFarming, "D", false},
            {icAutoMusic, "E", false},
            {icSettings, "F", false},
    };
    UI::SubMenu.push_back({
                                  {icEssentials, "A", false},
                                  {icWitchcraft, "B", false},
                                  {icMapHack, "C", false},
                                  {icFakery, "D", false},
                          });
    UI::SubMenu.push_back({
                                  {icMiscellaneous, "A", false},
                                  {icAvatar, "B", false},
                                  {icAmbience, "C", false},
                                  {icCamera, "D", false},
                          });
    UI::SubMenu.push_back({
                                  {icWorldTP, "A", false},
                                  {icBlink, "B", false},
                          });
    UI::SubMenu.push_back({
                                  {icFarming, "A", false},
                                  {icSpirits, "B", false},
                                  {icSpiritShop, "C", false},
                          });
    UI::SubMenu.push_back({

                          });
    UI::SubMenu.push_back({
                                  {icSettings2, "A", false},
                                  {icWitchcraft, "B", false},
                          });
}

namespace UI {
    int MainMenuSelected = -1;
    int SubMenuSelected = -1;
    std::vector<MenuButton> MainMenu;
    std::vector<std::vector<MenuButton>> SubMenu;
    bool isMenuOpen = false;
    bool isSubMenuOpen = false;

    enum MainButtonPos {
        Bottom = 0,
        Left = 1,
        Right = 2
    };

    MainButtonPos mainButtonPosition = Right; // Change this to Left or Right as needed

    void DrawButtonArc(ImDrawList* draw_list, ImVec2 center, float startAngle, float endAngle,
                       float innerRadius, float outerRadius, float gapSize, ImU32 color, ImU32 outlineColor, bool active) {
        int segments = 20; // More segments for smoother arcs
        std::vector<ImVec2> points;
        std::vector<ImVec2> outerPoints;

        float outRad = active ? outerRadius + 10.0f : outerRadius;

        float arcSpan = endAngle - startAngle;
        float radialOffset = arcSpan * (gapSize / 100.0f);

        float adjustedStart = startAngle + radialOffset / 2;
        float adjustedEnd = endAngle - radialOffset / 2;

        for (int i = 0; i <= segments; i++) {
            float t = (float)i / segments;
            float angle = adjustedStart + t * (adjustedEnd - adjustedStart);
            points.push_back(ImVec2(center.x + cosf(angle) * outRad,
                                    center.y + sinf(angle) * outRad));
        }
        outerPoints = points;

        for (int i = segments; i >= 0; i--) {
            float t = (float)i / segments;
            float angle = adjustedStart + t * (adjustedEnd - adjustedStart);
            points.push_back(ImVec2(center.x + cosf(angle) * innerRadius,
                                    center.y + sinf(angle) * innerRadius));
        }

        draw_list->AddConcavePolyFilled(points.data(), points.size(), active ? IM_COL32(130, 0, 0, 100) : color);
        draw_list->AddPolyline(points.data(), points.size(), outlineColor, true, 2.0f);
        if (active) {
            draw_list->AddPolyline(outerPoints.data(), outerPoints.size(),
                                   outlineColor, false, 8.0f);
        }
    }


    void ShowMainMenu() {
        int buttonCount = 6;
        ImVec2 buttonSize = ImVec2(100, 100);
        ImVec2 mainButtonSize = ImVec2(150, 150);

        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        ImVec2 center;
        float spacingRadius = 120.0f;
        float startAngle, endAngle;
        float btnPadding = 20.0f;

        if (mainButtonPosition == Bottom) {
            center = ImVec2(screenSize.x / 2, screenSize.y - mainButtonSize.y / 2);
            startAngle = -M_PI;
            endAngle = 0;
        } else if (mainButtonPosition == Left) {
            center = ImVec2(mainButtonSize.x / 2, screenSize.y / 2);
            startAngle = -M_PI / 2;
            endAngle = M_PI / 2;
        } else { // Right position
            center = ImVec2(screenSize.x - mainButtonSize.x / 2, screenSize.y / 2);
            startAngle = -M_PI / 2 + M_PI; // Adjusted by +180 degrees
            endAngle = M_PI / 2 + M_PI;
        }



        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;
        float maxButtonSize = fmax(buttonSize.x, buttonSize.y);

        float buttonArcRadius = spacingRadius + mainButtonSize.y / 2 + maxButtonSize / 2;
        float backgroundOuterRadius = buttonArcRadius + maxButtonSize / 2 + btnPadding;
        float backgroundInnerRadius = buttonArcRadius - maxButtonSize / 2 - btnPadding;
//        float backgroundInnerRadius = mainButtonSize.x / 2 + 100.0f;
        float gapSize = 5.0f;
        float subMenuInnerRadius = backgroundOuterRadius + btnPadding;
        float subMenuOuterRadius = subMenuInnerRadius + maxButtonSize + btnPadding * 2 + 5.0f; // + 5 to account for active state expansion


        float windowRadius = backgroundOuterRadius + maxButtonSize;

        if (!isMenuOpen) {
            windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
            windowRadius = mainButtonSize.x;
        } else {
            windowRadius = backgroundOuterRadius;
            if (isSubMenuOpen){
                windowRadius = subMenuOuterRadius;
            }
        }

        ImVec2 windowPos = ImVec2(center.x - windowRadius - 10, center.y - windowRadius - 10);
        ImVec2 windowSize = ImVec2(windowRadius * 2 + btnPadding, windowRadius * 2 + btnPadding);



        ImGui::SetNextWindowPos(windowPos);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("MainButtonWindow", nullptr, windowFlags);
        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));


        ImDrawList* drawList = ImGui::GetWindowDrawList();

        if (isMenuOpen) {
            float arcStep = (endAngle - startAngle) / (buttonCount - 1);

            for (int i = 0; i < buttonCount; i++) {
                int index;
                if (mainButtonPosition == Right) {
                    index = (buttonCount - 1) - i; // Reverse order for right side
                } else {
                    index = i;
                }

                float angle = startAngle + (index * arcStep);
                float btnArcRad = MainMenuSelected == i ? buttonArcRadius + 5 : buttonArcRadius;

                ImVec2 pos = ImVec2(center.x + cos(angle) * btnArcRad,
                                    center.y + sin(angle) * btnArcRad);

                float arcStart = angle - arcStep / 2;
                float arcEnd = angle + arcStep / 2;

                DrawButtonArc(drawList, center, arcStart, arcEnd,
                              backgroundInnerRadius, backgroundOuterRadius,
                              gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40), MainMenuSelected == i);

                ImGui::SetCursorScreenPos(ImVec2(pos.x - buttonSize.x / 2, pos.y - buttonSize.y / 2));
//                ImGui::PushID(("MainMenu" + std::to_string(i)).c_str());
                if (ImGui::ImageButton(("##MainMenu" + std::to_string(i)).c_str(),MainMenu[i].texture, buttonSize)) {
                    MainMenuSelected = (MainMenuSelected == i) ? -1 : i;
                    if (MainMenuSelected > -1 && SubMenu[MainMenuSelected].size() > 0) {
                        isSubMenuOpen = true;
                    } else {
                        isSubMenuOpen = false;
                    }
                }
//                ImGui::PopID();
            }

            if (MainMenuSelected > -1 && SubMenu[MainMenuSelected].size() > 0) {
                int subMenuCount = SubMenu[MainMenuSelected].size();
                float subMenuArcStep = M_PI / 8;

                // **Fix: Correct the submenu center angle mirroring**
                float subMenuCenterAngle = startAngle + (MainMenuSelected * arcStep);
                if (mainButtonPosition == Right) {
                    subMenuCenterAngle = endAngle - (subMenuCenterAngle - startAngle);
                }

                float subStartAngle = subMenuCenterAngle - (subMenuArcStep * (subMenuCount - 1) / 2);
                float subEndAngle = subMenuCenterAngle + (subMenuArcStep * (subMenuCount - 1) / 2);

                // Ensure submenu stays within bounds
                if (subStartAngle < startAngle) {
                    subStartAngle = startAngle;
                    subEndAngle = subStartAngle + (subMenuArcStep * (subMenuCount - 1));
                } else if (subEndAngle > endAngle) {
                    subEndAngle = endAngle;
                    subStartAngle = subEndAngle - (subMenuArcStep * (subMenuCount - 1));
                }

                float subArcStep = (subEndAngle - subStartAngle) / (subMenuCount - 1);

                for (int j = 0; j < subMenuCount; j++) {
                    int index = (mainButtonPosition == Right) ? (subMenuCount - 1 - j) : j;
                    float subAngle = subStartAngle + (index * subArcStep);
                    float subMenuRad = subMenuInnerRadius + maxButtonSize / 2 + btnPadding;
                    if (SubMenuSelected == j) {
                        subMenuRad += 5;
                    }
                    ImVec2 subPos = ImVec2(center.x + cos(subAngle) * subMenuRad,
                                           center.y + sin(subAngle) * subMenuRad);

                    DrawButtonArc(drawList, center, subAngle - subArcStep / 2, subAngle + subArcStep / 2,
                                  subMenuInnerRadius, subMenuOuterRadius,
                                  gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40), SubMenuSelected == j);

                    ImGui::SetCursorScreenPos(ImVec2(subPos.x - buttonSize.x / 2, subPos.y - buttonSize.y / 2));
//                    ImGui::PushID(("SubMenu" + std::to_string(j)).c_str());
                    if (ImGui::ImageButton(("SubMenu" + std::to_string(j)).c_str(),SubMenu[MainMenuSelected][j].texture, buttonSize)) {
                        SubMenuSelected = (SubMenuSelected == MainMenuSelected) ? -1 : j;
                        if (SubMenuSelected == 0) {
                            mainButtonPosition = Right;
                        } else if (SubMenuSelected == 1) {
                            mainButtonPosition = Bottom;
                        } else if (SubMenuSelected == 2) {
                            mainButtonPosition = Left;
                        }
                    }
//                    ImGui::PopID();
                }



            }

        }

        ImVec2 mainButtonPos = ImVec2(center.x - mainButtonSize.x / 2, center.y - mainButtonSize.y / 2);
        ImGui::SetCursorScreenPos(mainButtonPos);
        if (isMenuOpen){
            drawList->AddCircleFilled(center, backgroundInnerRadius - 20.0f,
                                      IM_COL32(0, 0, 0, 80));
            drawList->AddCircle(center, backgroundInnerRadius - 20.0f,
                                IM_COL32(255, 255, 255, 40), 0, 2.0f);
        } else {
            drawList->AddCircleFilled(center, fmax(mainButtonSize.x, mainButtonSize.y) / 2,
                                      IM_COL32(0, 0, 0, 80));
        }
        drawList->AddCircle(center, fmax(mainButtonSize.x, mainButtonSize.y) / 2,
                            IM_COL32(180, 0, 0, 180), 0, 2.0f);

        if (ImGui::ImageButton("##MainLogo",ImageLogo, mainButtonSize)) {
            isMenuOpen = !isMenuOpen;
        }

        ImGui::PopStyleVar();
        ImGui::End();
    }

//    if (SubMenuSelected == 0) {
//    mainButtonPosition = Right;
//} else if (SubMenuSelected == 1) {
//mainButtonPosition = Bottom;
//} else if (SubMenuSelected == 2) {
//mainButtonPosition = Left;
//}// Handle submenu click action here


//    void ShowMainMenu() {
//        int buttonCount = 6;
//        int subMenuCount = MainMenuSelected > -1 ? SubMenu[MainMenuSelected].size() : 0;
//        ImVec2 buttonSize = ImVec2(100, 100);
//        ImVec2 mainButtonSize = ImVec2(150, 150);
//
//        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
//        ImVec2 center;
//        float spacingRadius = 120.0f;
//        float startAngle, endAngle;
//
//        if (mainButtonPosition == Bottom) {
//            center = ImVec2(screenSize.x / 2, screenSize.y - mainButtonSize.y / 2);
//            startAngle = -M_PI;
//            endAngle = 0;
//        } else if (mainButtonPosition == Left) {
//            center = ImVec2(mainButtonSize.x / 2, screenSize.y / 2);
//            startAngle = -M_PI / 2;
//            endAngle = M_PI / 2;
//        } else {
//            center = ImVec2(screenSize.x - mainButtonSize.x / 2, screenSize.y / 2);
//            startAngle = M_PI / 2;
//            endAngle = -M_PI / 2;
//        }
//
//        float buttonArcRadius = spacingRadius + mainButtonSize.y / 2 + buttonSize.y / 2;
//        float backgroundOuterRadius = buttonArcRadius + buttonSize.y / 2 + 20.0f;
//        float backgroundInnerRadius = mainButtonSize.x / 2 + 100.0f;
//        float gapSize = 5.0f;
//
//        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;
//        float maxButtonSize = fmax(buttonSize.x, buttonSize.y);
//        float windowRadius = backgroundOuterRadius + maxButtonSize;
//        if (isMenuOpen && (SubMenuSelected > -1 && SubMenu[MainMenuSelected].size() > 0)) {
//            windowRadius = backgroundOuterRadius + maxButtonSize + 200.0f;
//        }
//
//        if (!isMenuOpen) {
//            windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
//            windowRadius = mainButtonSize.x;
//        }
//
//        ImVec2 windowPos = ImVec2(center.x - windowRadius, center.y - windowRadius);
//        ImVec2 windowSize = ImVec2(windowRadius * 2, windowRadius * 2);
//        ImGui::SetNextWindowPos(windowPos);
//        ImGui::SetNextWindowSize(windowSize);
//
//        ImGui::Begin("MainButtonWindow", nullptr, windowFlags);
//        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
//
//        ImDrawList* drawList = ImGui::GetWindowDrawList();
//
//        if (isMenuOpen) {
//            float arcStep = (endAngle - startAngle) / (buttonCount - 1);
//            float subMenuArcStep = M_PI / 8;
//
//            for (int i = 0; i < buttonCount; i++) {
//                float angle = startAngle + (i * arcStep);
//                float btnArcRad = MainMenuSelected == i ? buttonArcRadius + 5 : buttonArcRadius;
//
//                ImVec2 pos = ImVec2(center.x + cos(angle) * btnArcRad,
//                                    center.y + sin(angle) * btnArcRad);
//
//                float arcStart = angle - arcStep / 2;
//                float arcEnd = angle + arcStep / 2;
//
//                DrawButtonArc(drawList, center, arcStart, arcEnd,
//                              backgroundInnerRadius, backgroundOuterRadius,
//                              gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40), MainMenuSelected == i);
//
//                ImGui::SetCursorScreenPos(ImVec2(pos.x - buttonSize.x / 2, pos.y - buttonSize.y / 2));
//                ImGui::PushID(("MainMenu" + std::to_string(i)).c_str());
//                if (ImGui::ImageButton(MainMenu[i].texture, buttonSize)) {
//                    MainMenuSelected = (MainMenuSelected == i) ? -1 : i;
//                }
//                ImGui::PopID();
//
//                // If a button is selected, show its submenu
//                if (MainMenuSelected == i && SubMenu[MainMenuSelected].size() > 0) {
//                    float subMenuRadius = backgroundOuterRadius + maxButtonSize / 2 + 20; // Extend the arc
//
//                    // Ensure submenu doesn't go off screen
//                    float subStartAngle = angle - (subMenuArcStep * (subMenuCount - 1) / 2);
//                    float subEndAngle = angle + (subMenuArcStep * (subMenuCount - 1) / 2);
//
//                    // Adjust if out of screen bounds
//                    if (subStartAngle < startAngle) {
//                        subStartAngle = startAngle;
//                        subEndAngle = subStartAngle + (subMenuArcStep * (subMenuCount - 1));
//                    } else if (subEndAngle > endAngle) {
//                        subEndAngle = endAngle;
//                        subStartAngle = subEndAngle - (subMenuArcStep * (subMenuCount - 1));
//                    }
//
//                    float subArcStep = (subEndAngle - subStartAngle) / (subMenuCount - 1);
//
//                    for (int j = 0; j < subMenuCount; j++) {
//                        float subAngle = subStartAngle + (j * subArcStep);
//                        ImVec2 subPos = ImVec2(center.x + cos(subAngle) * subMenuRadius,
//                                               center.y + sin(subAngle) * subMenuRadius);
//
//                        DrawButtonArc(drawList, center, subAngle - subArcStep / 2, subAngle + subArcStep / 2,
//                                      backgroundOuterRadius + 20, backgroundOuterRadius + 120,
//                                      gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40), SubMenuSelected == j);
//
//                        ImGui::SetCursorScreenPos(ImVec2(subPos.x - buttonSize.x / 2, subPos.y - buttonSize.y / 2));
//                        ImGui::PushID(("SubMenu" + std::to_string(j)).c_str());
//                        if (ImGui::ImageButton(SubMenu[i][j].texture, buttonSize)) {
//                            SubMenuSelected = (SubMenuSelected == i) ? -1 : j;
//                            if (SubMenuSelected == 0) {
//                                mainButtonPosition = Right;
//                            } else if (SubMenuSelected == 1) {
//                                mainButtonPosition = Bottom;
//                            } else if (SubMenuSelected == 2) {
//                                mainButtonPosition = Left;
//                            }// Handle submenu click action here
//                        }
//                        ImGui::PopID();
//                    }
//                }
//            }
//        }
//
//        // Main button
//        ImVec2 mainButtonPos = ImVec2(center.x - mainButtonSize.x / 2, center.y - mainButtonSize.y / 2);
//        ImGui::SetCursorScreenPos(mainButtonPos);
//        if (ImGui::ImageButton(ImageLogo, mainButtonSize)) {
//            isMenuOpen = !isMenuOpen;
//        }
//
//        ImGui::PopStyleVar();
//        ImGui::End();
//    }


//    void ShowMainMenu() {
//        int buttonCount = 6;
//        ImVec2 buttonSize = ImVec2(100, 100);
//        ImVec2 mainButtonSize = ImVec2(150, 150);
//
//        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
//        ImVec2 center;
//        float spacingRadius = 120.0f;
//        float startAngle, endAngle;
//
//        if (mainButtonPosition == Bottom) {
//            center = ImVec2(screenSize.x / 2, screenSize.y - mainButtonSize.y / 2);
//            startAngle = -M_PI;
//            endAngle = 0;
//        } else if (mainButtonPosition == Left) {
//            center = ImVec2(mainButtonSize.x / 2, screenSize.y / 2);
//            startAngle = -M_PI / 2;
//            endAngle = M_PI / 2;
//        } else { // Right position
//            center = ImVec2(screenSize.x - mainButtonSize.x / 2, screenSize.y / 2);
//            startAngle = -M_PI / 2 + M_PI; // Adjusted by +180 degrees
//            endAngle = M_PI / 2 + M_PI;
//        }
//
//        float buttonArcRadius = spacingRadius + mainButtonSize.y / 2 + buttonSize.y / 2;
//        float backgroundOuterRadius = buttonArcRadius + buttonSize.y / 2 + 20.0f;
//        float backgroundInnerRadius = mainButtonSize.x / 2 + 100.0f;
//        float gapSize = 5.0f;
//
//        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove;
//        float maxButtonSize = fmax(buttonSize.x, buttonSize.y);
//        float windowRadius = backgroundOuterRadius + maxButtonSize;
//
//        if (!isMenuOpen) {
//            windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
//            windowRadius = mainButtonSize.x;
//        }
//
//        ImVec2 windowPos = ImVec2(center.x - windowRadius, center.y - windowRadius);
//        ImVec2 windowSize = ImVec2(windowRadius * 2, windowRadius * 2);
//        ImGui::SetNextWindowPos(windowPos);
//        ImGui::SetNextWindowSize(windowSize);
//
//        ImGui::Begin("MainButtonWindow", nullptr, windowFlags);
//        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
//
//        ImDrawList* drawList = ImGui::GetWindowDrawList();
//
//        if (isMenuOpen) {
//            float arcStep = (endAngle - startAngle) / (buttonCount - 1);
//
//            for (int i = 0; i < buttonCount; i++) {
//                int index;
//                if (mainButtonPosition == Right) {
//                    index = (buttonCount - 1) - i; // Reverse order for right side
//                } else {
//                    index = i;
//                }
//
//                float angle = startAngle + (index * arcStep);
//                float btnArcRad = MainMenuSelected == i ? buttonArcRadius + 5 : buttonArcRadius;
//
//                ImVec2 pos = ImVec2(center.x + cos(angle) * btnArcRad,
//                                    center.y + sin(angle) * btnArcRad);
//
//                float arcStart = angle - arcStep / 2;
//                float arcEnd = angle + arcStep / 2;
//
//                DrawButtonArc(drawList, center, arcStart, arcEnd,
//                              backgroundInnerRadius, backgroundOuterRadius,
//                              gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40), MainMenuSelected == i);
//
//                ImGui::SetCursorScreenPos(ImVec2(pos.x - buttonSize.x / 2, pos.y - buttonSize.y / 2));
//                ImGui::PushID(("MainMenu" + std::to_string(i)).c_str());
//                if (ImGui::ImageButton(MainMenu[i].texture, buttonSize)) {
//                    MainMenuSelected = (MainMenuSelected == i) ? -1 : i;
//                    if (MainMenuSelected == 5) {
//                        mainButtonPosition = Right;
//                    } else if (MainMenuSelected == 4) {
//                        mainButtonPosition = Left;
//                    } else if (MainMenuSelected == 3) {
//                        mainButtonPosition = Bottom;
//                    }
//                }
//                ImGui::PopID();
//            }
//        }
//
//        ImVec2 mainButtonPos = ImVec2(center.x - mainButtonSize.x / 2, center.y - mainButtonSize.y / 2);
//        ImGui::SetCursorScreenPos(mainButtonPos);
//        if (ImGui::ImageButton(ImageLogo, mainButtonSize)) {
//            isMenuOpen = !isMenuOpen;
//        }
//
//        ImGui::PopStyleVar();
//        ImGui::End();
//    }


}
