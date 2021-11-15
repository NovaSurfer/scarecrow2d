//
// Created by Maksim Ruts on 02-Nov-18.
//

#include "configLoader.h"
#include "core/log2.h"
#include "core/rendering/scene/tiled_map.h"
#include "filesystem/shader_files.h"
#include "fs_constants.h"
#include "resourceHolder.h"
#include <vector>

namespace sc2d
{

    template <typename T>
    bool Config<T>::open(const std::string& path)
    {
        std::fstream jConfig(path);

        // If file can't be open
        if(!jConfig)
            return false;

        // Parsing json config
        json j = json::parse(jConfig, nullptr, false);

        // If json can't be parsed
        if(j.is_discarded())
            return false;

        // Load config data / values
        T()(j);

        return true;
    }

    void ResourcesConfigLoad::operator()(const json& obj_json)
    {
        const auto sprites_section = obj_json[fs_const::RES_SPRITE];
        const auto shaders_section = obj_json[fs_const::RES_SHADER];

        for(const auto& sprite : sprites_section) {
            const std::string s_path = sprite["file"].get<const std::string>();
            const std::string s_name = sprite["name"].get<const std::string>();
            bool s_alpha = sprite["alpha"].get<bool>();
            bool s_atlas = sprite["atlas"].get<bool>();

            log_info_cmd("Loading sprite file: %s", s_path.c_str());

            if(!s_atlas)
                ResourceHolder::load_texture(s_path, s_alpha, s_name);
            else {
                const u32 rows = sprite["rows"].get<u32>();
                const u32 columns = sprite["columns"].get<u32>();
                ResourceHolder::load_texture_atlas(s_path, rows, columns, s_alpha, s_name);
            }
        }

        // Builtin shaders
        for(const auto& shader : sc2d::cshaders::SHADERS_ARRAY) {
            ResourceHolder::load_shader_program(ShaderSource::BUILTIN, shader.name, shader.vs_src,
                                                shader.fs_src);
        }

        // External shaders
        for(const auto& shader : shaders_section) {
            const std::string frag_path = shader["frag_file"].get<const std::string>();
            const std::string vert_path = shader["vert_file"].get<const std::string>();
            const std::string s_name = shader["name"].get<const std::string>();

            log_info_cmd("Loading shader files\nVERTEX: %s\nFRAGMENT: %s", vert_path.c_str(),
                         frag_path.c_str());
            ResourceHolder::load_shader_program(ShaderSource::FILE, s_name, vert_path.c_str(), frag_path.c_str());
        }
    }

    void SceneConfigLoad::operator()(const json& obj_json)
    {
        const int width = obj_json[fs_const::SCN_WIDTH].get<const int>();
        const int height = obj_json[fs_const::SCN_HEIGHT].get<const int>();
        const int tile_with = obj_json[fs_const::SCN_TILE_WIDTH].get<const int>();
        const int tile_height = obj_json[fs_const::SCN_TILE_HEIGHT].get<const int>();

        // Getting value of first property - 'content_count'
        const size_t content_count = obj_json["properties"][0]["value"].get<const size_t>();
        log_info_cmd("content count: %d", content_count);

        const auto layers_section = obj_json[fs_const::SCN_LAYERS];
        std::vector<tiled::Layer> tls;
        tls.reserve(layers_section.size());
        for(const auto& layer : layers_section) {
            const std::string data = layer[fs_const::SCN_LAYERS_DATA].get<const std::string>();
            const std::string name = layer[fs_const::SCN_LAYERS_NAME].get<const std::string>();

            tiled::Layer tile_layer;
            tile_layer.set_data(data);
            tile_layer.set_name(name);

            tls.emplace_back(tile_layer);
        }

        const auto tileset_section = obj_json[fs_const::SCN_TILESETS];
        std::vector<tiled::Set> tss;
        tss.reserve(tileset_section.size());
        for(const auto& tileset : tileset_section) {
            const std::string img_path =
                tileset[fs_const::SCN_TILESETS_IMAGE].get<const std::string>();

            tiled::Set tile_set;
            tile_set.set_img_path(img_path);

            tss.emplace_back(tile_set);
        }

        tiled::Data tiledData {width,         height,         tile_with,     tile_height,
                               content_count, std::move(tls), std::move(tss)};
        ResourceHolder::load_tiled_map("wasd", tiledData);
    }

    // Explicitly instantiating Config template
    template class Config<ResourcesConfigLoad>;
    template class Config<SceneConfigLoad>;
}
