//
// Created by Maksim Ruts on 02-Nov-18.
//

#include "configLoader.h"

template<typename T>
bool Config<T>::open(const std::string &path) {
    std::fstream jConfig(path);

    // If file can't be open
    if (!jConfig) return false;

    // Parsing json config
    json j = json::parse(jConfig, nullptr, false);

    // If json can't be parsed
    if (j.is_discarded()) return false;

    // Load config data / values
    T()(j);

    return true;
}

void ResourcesConfigLoad::operator()(const json &obj_json) {
    auto sprites_section = obj_json[ConfigNames::RES_SPRITE];
    auto shaders_section = obj_json[ConfigNames::RES_SHADER];

    for (const auto &s : sprites_section)
    {
        std::string s_path = s["file"].get<std::string>();
        std::string s_name = s["name"].get<std::string>();
        bool s_alpha = s["alpha"].get<bool>();

        std::clog << "Loading sprite:\t" << s_path << '\n';
        FileManager::load_texture(s_path, s_alpha, s_name);
    }
}

// TODO:
void SceneConfigLoad::operator()(const json &obj_json) {

}

// Explicitly instantiating Config template
template class Config<ResourcesConfigLoad>;
template class Config<SceneConfigLoad>;