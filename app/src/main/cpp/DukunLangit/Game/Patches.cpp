#include "Patches.h"
#include "CryptoHelper.h"
#include "OnlineUpdate.h"
#include <fstream>
#include <iostream>

namespace Patches {
    std::unordered_map<std::string, std::vector<Patch>> patches;
    int version = 0;

    void Init(int gameType) {
        std::ifstream file("patches.json");
        std::string jsonData;

        if (file) {
            std::getline(file, jsonData, '\0');
            file.close();
        } else {
            jsonData = GetPatchesJson(gameType);
        }

        LoadFromJson(jsonData);
    }

    void LoadFromJson(const std::string& jsonData) {
        try {
            nlohmann::json j = nlohmann::json::parse(jsonData);
            version = j["version"];
            patches = j["patches"].get<std::unordered_map<std::string, std::vector<Patch>>>();
        } catch (const std::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }
    }

    bool CheckForUpdates() {
        std::string encryptedData;
        if (OnlineUpdate::FetchLatestPatch(encryptedData)) {
            return ApplyUpdate(encryptedData);
        }
        return false;
    }

    bool ApplyUpdate(const std::string& encryptedData) {
        std::string decryptedData = CryptoHelper::Decrypt(encryptedData);

        try {
            nlohmann::json j = nlohmann::json::parse(decryptedData);
            int newVersion = j["version"];
            if (newVersion > version) {
                std::ofstream file("patches.json");
                file << decryptedData;
                file.close();
                LoadFromJson(decryptedData);
                return true;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error applying update: " << e.what() << std::endl;
        }
        return false;
    }
}
