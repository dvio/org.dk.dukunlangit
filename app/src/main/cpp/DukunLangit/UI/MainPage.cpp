#include "UI.h"

void UI::DrawMainPage(){
    ImGuiIO& io = ImGui::GetIO();

    float padding = 50.0f;
    float maxHeight = io.DisplaySize.y - (padding * 2); // Max height with padding

// Set fixed height constraint for the main window
    ImGui::SetNextWindowSizeConstraints(ImVec2(0, maxHeight), ImVec2(FLT_MAX, maxHeight));

// Centering logic
//    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
//                            ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f)); // Pivot to center

// Parent window: Fixed height, auto width

//    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.3f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    if (ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0.3f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 20.0f);

        ImGui::BeginChild("##MainContainer", ImVec2(0,0), ImGuiChildFlags_Border | ImGuiChildFlags_FrameStyle | ImGuiChildFlags_AutoResizeX);

        ImGui::PopStyleVar();
        ImGui::PopStyleColor();

        UI::BeginScrollingChild("Content", ImVec2(0, 0), ImGuiChildFlags_AutoResizeX );

        ImGui::Text("Dynamic Content:");
        static char textBuffer[256] = "Resize me and this is so so fkn looooong, really really loooong!";
        ImGui::InputText("##txt", textBuffer, IM_ARRAYSIZE(textBuffer));
        UI::DrawStyleSelector("Style:");
        static int buttonCount = 10;
        if (ImGui::Button("Add Button")){
            buttonCount++;
        }
        ImGui::SameLine();
        if (ImGui::Button("Remove Button")){
            buttonCount--;
        }
        for (int i = 0; i < buttonCount; i++){
            if (ImGui::Button(("Button " + std::to_string(i)).c_str())){
                ImGui::SameLine();
                ImGui::Text("Clicked");
            }
        }

        UI::EndScrollingChild();
        ImGui::EndChild();

//        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, ImGui::GetStyle().ItemSpacing.y));
        ImGui::SameLine();
//        ImGui::PopStyleVar();

        ImGui::BeginChild("Toolbar", ImVec2(0, 0), ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AlwaysUseWindowPadding); // Fixed height
        ImGui::Text("Tools");
        ImGui::Button("Option 1");
        ImGui::Button("Option 2");
        ImGui::EndChild();
        ImGui::PopStyleVar();

    }

    ImGui::End();

//    ImGui::PopStyleColor();
}
