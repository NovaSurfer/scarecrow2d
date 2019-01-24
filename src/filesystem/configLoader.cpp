//
// Created by Maksim Ruts on 02-Nov-18.
//

#include "configLoader.h"

template<typename T>
bool Config<T>::open(const std::string &path)
{
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


void ResourcesConfigLoad::operator()(const json &obj_json)
{
    auto sprites_section = obj_json[ConfigNames::RES_SPRITE];
    auto shaders_section = obj_json[ConfigNames::RES_SHADER];

    for (const auto &sprite : sprites_section)
    {
        std::string s_path = sprite["file"].get<std::string>();
        std::string s_name = sprite["name"].get<std::string>();
        bool s_alpha = sprite["alpha"].get<bool>();

        log_info_cmd("Loading sprite file: %s", s_path.c_str());
        ResourceHolder::load_texture(s_path, s_alpha, s_name);
    }

    for (const auto& shader : shaders_section)
    {
        std::string frag_path = shader["frag_file"].get<std::string>();
        std::string vert_path = shader["vert_file"].get<std::string>();
        std::string s_name = shader["name"].get<std::string>();

        log_info_cmd("Loading shader files\nVERTEX: %s\nFRAGMENT: %s", vert_path.c_str(), frag_path.c_str());
        ResourceHolder::load_shader_program(s_name, vert_path.c_str(), frag_path.c_str());
    }
}

// TODO:
void SceneConfigLoad::operator()(const json &obj_json)
{

}

// Explicitly instantiating Config template
template class Config<ResourcesConfigLoad>;
template class Config<SceneConfigLoad>;