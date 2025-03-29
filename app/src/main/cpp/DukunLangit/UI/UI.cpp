#define _USE_MATH_DEFINES

#include <string>
#include "UI.h"
#include <cmath>

#include "Menu.h"
#include "Graphic.h"
#include <Styles.h>

namespace UI {
    int MainMenuSelected = -1;
    int SubMenuSelected = -1;

    bool isMenuOpen = false;
    bool isSubMenuOpen = false;

    enum MainButtonPos {
        Bottom = 0,
        Left = 1,
        Right = 2
    };

    MainButtonPos mainButtonPosition = Right; // Change this to Left or Right as needed

    void InitPages(){
        TestPage::InitPages();
    }

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


    void DrawMainMenu() {
        if (Menu::Menus.empty()) return;
        int buttonCount = Menu::Menus.size();
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


                Menu::MenuItem menuItem = Menu::Menus[i];

                if (ImGui::ImageButton(("##MainMenu" + std::to_string(i)).c_str(), Graphic::GetMenuIcon(menuItem.icon) , buttonSize)) {
                    MainMenuSelected = (MainMenuSelected == i) ? -1 : i;
                    if (MainMenuSelected > -1 && menuItem.submenus.size() > 0) {
                        isSubMenuOpen = true;
                    } else {
                        isSubMenuOpen = false;
                    }
                    if (menuItem.hasUI) {
                        if (Menu::ActiveMenu == menuItem.id){
                            Menu::ActiveMenu = "";
                        } else {
                            Menu::ActiveMenu = menuItem.id;
                        }
                    }
                }
//                ImGui::PopID();
            }

            if (MainMenuSelected > -1){
                Menu::MenuItem menuItem = Menu::Menus[MainMenuSelected];
                if (menuItem.submenus.size() > 0) {

                    int subMenuCount = menuItem.submenus.size();
                    float subMenuArcStep = M_PI / 8;

                    // **Fix: Correct the submenu center angle mirroring**
                    float subMenuCenterAngle = startAngle + (MainMenuSelected * arcStep);
                    if (mainButtonPosition == Right) {
                        subMenuCenterAngle = endAngle - (subMenuCenterAngle - startAngle);
                    }

                    float subStartAngle =
                            subMenuCenterAngle - (subMenuArcStep * (subMenuCount - 1) / 2);
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

                        DrawButtonArc(drawList, center, subAngle - subArcStep / 2,
                                      subAngle + subArcStep / 2,
                                      subMenuInnerRadius, subMenuOuterRadius,
                                      gapSize, IM_COL32(0, 0, 0, 80), IM_COL32(255, 255, 255, 40),
                                      menuItem.submenus[j].id == Menu::ActiveMenu);

                        ImGui::SetCursorScreenPos(
                                ImVec2(subPos.x - buttonSize.x / 2, subPos.y - buttonSize.y / 2));

                        if (ImGui::ImageButton(("SubMenu" + std::to_string(j)).c_str(),
                                               Graphic::GetMenuIcon(menuItem.submenus[j].icon),
                                               buttonSize)) {
                            SubMenuSelected = (SubMenuSelected == MainMenuSelected) ? -1 : j;

                            if (menuItem.submenus[j].hasUI) {
                                if (Menu::ActiveMenu == menuItem.submenus[j].id){
                                    Menu::ActiveMenu = "";
                                } else {
                                    Menu::ActiveMenu = menuItem.submenus[j].id;
                                }
                            }
                        }
//                    ImGui::PopID();
                    }

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

        if (ImGui::ImageButton("##MainLogo", ImageLogo, mainButtonSize)) {
            isMenuOpen = !isMenuOpen;
        }

        ImGui::PopStyleVar();
        ImGui::End();
    }

    void DrawPage(std::string& pageID){
        std::string caption = pageID + "###MainPage";

        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

        if (ImGui::Begin("##CustomWindow", nullptr,
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
        {
            TestPage::DrawContent();
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void DrawUI(){
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0,0,0,0));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        DrawMainMenu();
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);


        if (!Menu::ActiveMenu.empty()) {
            Styles::ApplyStyle();
//            DrawPage(Menu::ActiveMenu);
            DrawMainPage();
            Styles::ResetStyle();

        }
    }



}
