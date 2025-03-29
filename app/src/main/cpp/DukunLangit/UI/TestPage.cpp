#include "UI.h"

#include <imgui.h>
#include <vector>
#include <string>
#include <algorithm> // For std::max

#include <GlobalVars.h>
#include <Styles.h>

namespace TestPage
{
    static int activePage = 2;

    //Sample values
    bool checkboxValue = false;
    float sliderValue = 50.0f;

    struct Page {
        std::string name;
        void (*drawFunc)();
    };

    static std::vector<Page> Pages;

    void DrawSamplePage1() {
        ImGui::Text("This is Page 1");
        if (ImGui::Button("Sample Button 1")){
            GlobalVars::ActiveStyle = "LightMode";
        }
        ImGui::Spacing();
        ImGui::Text("Active style: %s", GlobalVars::ActiveStyle.c_str());
        UI::DrawStyleSelector("Select Style:");

        for (int i = 0; i < 50; i++){
            ImGui::Button(("Button " + std::to_string(i)).c_str());
        }
    }

    void DrawSamplePage2() {
        ImGui::Text("This is Page 2");
        ImGui::Checkbox("Checkbox Example", &checkboxValue);
        if (ImGui::BeginTable("ScrollableTable", 3))
        {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Value");

            // Ensure touch events scroll the table, not the window
//            if (ImGui::IsItemHovered() && ImGui::GetIO().MouseDown[0])
//            {
//                float scrollAmount = -ImGui::GetIO().MouseDelta.y;
//                ImGui::SetScrollY(ImGui::GetScrollY() + scrollAmount);
//            }

            for (int i = 0; i < 100; i++)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", i);
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("Item %d", i);
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%.2f", i * 1.5f);
            }

            ImGui::EndTable();
        }
    }

    void DrawSamplePage3() {
        ImGui::Text("This is Page 3");
        ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 100.0f);
    }

    void InitPages() {
        Pages.clear();
        Pages.push_back({ "Page 1", DrawSamplePage1 });
        Pages.push_back({ "Page 2", DrawSamplePage2 });
        Pages.push_back({ "Page 3", DrawSamplePage3 });
    }

    // Enable touch scrolling (for Android)
    void HandleTouchScrolling()
    {
        ImGuiIO& io = ImGui::GetIO();
        static bool isTouchActive = false;
        static float lastTouchY = 0.0f;

        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
        {
            if (io.MouseDown[0])
            {
                if (!isTouchActive)
                {
                    // First touch detected, store initial position
                    isTouchActive = true;
                    lastTouchY = io.MousePos.y;
                }

                // Calculate scroll delta relative to last touch position
                float scrollAmount = (lastTouchY - io.MousePos.y);
                ImGui::SetScrollY(ImGui::GetScrollY() + scrollAmount);

                // Update last touch position for smooth scrolling
                lastTouchY = io.MousePos.y;
            }
            else
            {
                // Reset when touch is released
                isTouchActive = false;
            }
        }
    }

//    void HandleTouchScrolling()
//    {
//        ImGuiIO& io = ImGui::GetIO();
//        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
//        {
//            float scrollAmount = -io.MouseDelta.y;
//            ImGui::SetScrollY(ImGui::GetScrollY() + scrollAmount);
//        }
//    }


    void DrawContent(){
//        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 5));
//        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        float buttonWidth = 0.0f, buttonHeight = 0.0f;
        ImVec2 framePadding = ImGui::GetStyle().FramePadding;
        float borderSize = ImGui::GetStyle().FrameBorderSize;
        float windowPadding = ImGui::GetStyle().WindowPadding.x;
        float scrollbarSize = ImGui::GetStyle().ScrollbarSize;

// 🔹 Calculate max button size considering paddings & borders
        for (const Page& page : Pages) {
            ImVec2 textSize = ImGui::CalcTextSize(page.name.c_str());
            buttonWidth = std::max(buttonWidth, textSize.x + framePadding.x * 2 + 20);
            buttonHeight = std::max(buttonHeight, textSize.y + framePadding.y * 2 + 15);
        }

// 🔹 Final toolbar width = Button + padding + border + scrollbar
        float toolbarWidth = buttonWidth + framePadding.x * 2 + borderSize * 2 + windowPadding + scrollbarSize;


        // 🔹 Use columns for layout
//        ImGui::Columns(2, nullptr, false);
//        ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() - toolbarWidth);

        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.0f);

        // 🖼️ Main content (Scrollable)
        ImGui::BeginChild("##MainContent", ImVec2(300, 300));
//        HandleTouchScrolling(); // 🔹 Apply scrolling behavior
        if (activePage >= 0 && activePage < Pages.size()) {
            Pages[activePage].drawFunc(); // Draw active page
        }
        ImGui::EndChild();

        ImGui::PopStyleVar();

//        ImGui::NextColumn();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));

        // 📌 Toolbar (Now behaves the same as content)
        ImGui::BeginChild("##Toolbar", ImVec2(toolbarWidth, 0), ImGuiChildFlags_None, ImGuiWindowFlags_AlwaysUseWindowPadding);
//        HandleTouchScrolling(); // 🔹 Apply same scrolling logic
        for (size_t i = 0; i < Pages.size(); i++) {
            if (ImGui::Button(Pages[i].name.c_str(), ImVec2(toolbarWidth - (borderSize + scrollbarSize), buttonHeight)))
                activePage = i;
        }
        ImGui::EndChild();

        ImGui::PopStyleVar(2);
    }
}

