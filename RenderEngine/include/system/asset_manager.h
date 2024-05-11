#pragma once
#include <string>
#include <vector>
#include "sqlite3.h"
#include "assettypes.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "asset_class.h"
#include <unordered_map>
#include "system/assets.h"



namespace wizm {




	class asset_manager {
    private:
        std::unordered_map<std::string, std::shared_ptr<core_asset>> m_assets;

    public:

        template <typename T>
        std::shared_ptr<T> load(const std::string& asset_id, const std::string& path) {
            auto it = m_assets.find(asset_id);
            if (it != m_assets.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }

            std::shared_ptr<T> asset = std::make_shared<T>();
            asset->load(path);
            m_assets[asset_id] = asset;
            return asset;
        }
		

	};
}