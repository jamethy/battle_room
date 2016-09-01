#include "sdl_font_manager.h"
#include "battle_room/engine/graphics/get_resource_path.h"

#include <unordered_map>
#include <iostream>

namespace BattleRoom {

std::unordered_map<std::string,TTF_Font*> m_fontMap; ///< Container of loaded fonts

// other functions
TTF_Font* SdlFontManager::getFont(std::string fontKey, int size) {

    std::string fullFontKey = fontKey + std::to_string(size);

    //TODO Add error checking
    if (m_fontMap.count(fullFontKey) == 0) {
        std::string font_path = getResourcePath() + "/fonts/" + fontKey;

        TTF_Font* font = TTF_OpenFont(font_path.c_str(), size);
        if (font == NULL) {
            std::cerr << "Could not find font " << fontKey << std::endl;
        }
        m_fontMap[fullFontKey] = font;
    }

    return m_fontMap[fullFontKey];
}

void SdlFontManager::clear() {

    for (auto& font : m_fontMap) {
        TTF_CloseFont(font.second);
    }
    m_fontMap.clear();
}

} // BattleRoom namespace
