#include "Graphic.h"

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
ImTextureID icAbout;

bool imagesInitialized = false;

void InitImages() {
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
    INCLUDE_IMG(icSpirits_png);
    INCLUDE_IMG(icSpiritShop_png);
    INCLUDE_IMG(icAbout_png);

    ImageLogo = getTextureID(&logo_png);

    icMain = getTextureID(&icMain_png);
    icEssentials = getTextureID(&icEssentials_png);
    icWitchcraft = getTextureID(&icWitchcraft_png);
    icMapHack = getTextureID(&icMapHack_png);
    icFakery = getTextureID(&icFakery_png);
    icExtra = getTextureID(&icExtra_png);
    icMiscellaneous = getTextureID(&icMiscellaneous_png);
    icAvatar = getTextureID(&icAvatar_png);
    icAmbience = getTextureID(&icAmbience_png);
    icCamera = getTextureID(&icCamera_png);
    icTeleport = getTextureID(&icTeleport_png);
    icWorldTP = getTextureID(&icWorldTP_png);
    icBlink = getTextureID(&icBlink_png);
    icFarming = getTextureID(&icFarming_png);
    icAutoCR = getTextureID(&icAutoCR_png);
    icSpirits = getTextureID(&icSpirits_png);
    icSpiritShop = getTextureID(&icSpiritShop_png);
    icAutoMusic = getTextureID(&icAutoMusic_png);
    icSettings = getTextureID(&icSettings_png);
    icSettings2 = getTextureID(&icSettings2_png);
    icAbout = getTextureID(&icAbout_png);

    icEdenRun = getTextureID(&icEdenRun_png);

    Graphic::MenuTextures = {
            {"icMain", icMain},
            {"icEssentials", icEssentials},
            {"icWitchcraft", icWitchcraft},
            {"icMapHack", icMapHack},
            {"icFakery", icFakery},
            {"icExtra", icExtra},
            {"icMiscellaneous", icMiscellaneous},
            {"icAvatar", icAvatar},
            {"icAmbience", icAmbience},
            {"icCamera", icCamera},
            {"icTeleport", icTeleport},
            {"icWorldTP", icWorldTP},
            {"icBlink", icBlink},
            {"icFarming", icFarming},
            {"icAutoCR", icAutoCR},
            {"icSpirits", icSpirits},
            {"icSpiritShop", icSpiritShop},
            {"icAutoMusic", icAutoMusic},
            {"icSettings", icSettings},
            {"icSettings2", icSettings2},
            {"icAbout", icAbout},
            {"icEdenRun", icEdenRun}
    };
}

namespace Graphic {

    std::unordered_map<std::string, ImTextureID> MenuTextures;

    ImTextureID GetMenuIcon(std::string iconName){
        if (MenuTextures.find(iconName) != MenuTextures.end()) {
            return MenuTextures[iconName];
        }
        return (ImTextureID)nullptr;
    }
}