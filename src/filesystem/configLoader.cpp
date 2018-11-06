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
}

void SceneConfigLoad::operator()(const json &obj_json) {

}
