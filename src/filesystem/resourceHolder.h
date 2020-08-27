//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_FILE_MANAGER_H
#define INC_2D_GAME_FILE_MANAGER_H

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "core/rendering/scene/tiled_map.h"
#include "core/rendering/shader.h"
#include "core/rendering/texture.h"
#include "core/rendering/texture_atlas.h"

namespace sc2d
{

    enum class ShaderSource
    {
        BUILTIN,
        FILE
    };

    class ResourceHolder
    {
    public:
        static void load_shader_program(ShaderSource shader_source, const std::string& name,
                                        const GLchar* vert_file, const GLchar* frag_file,
                                        const GLchar* geom_file = nullptr);
        static const Shader& get_shader(const std::string& shader_name);
        static void load_texture(const std::string& img_file, bool alpha, const std::string& name);
        static const Texture2d& get_texture(const std::string& texture_name);
        static void load_tiled_map(const std::string& name, const tiled::Data& tiled_data);
        static const tiled::Map& get_tiled_map(const std::string& map_name);
        static const TextureAtlas& get_texture_atlas(const std::string& name);
        static void load_texture_atlas(const std::string& img_file, const uint rows,
                                       const uint columns, bool alpha, const std::string& name);

        static void clean();

        ResourceHolder() = delete;
        ResourceHolder(const ResourceHolder& other) = delete;
        ResourceHolder(ResourceHolder&& other) = delete;
        ResourceHolder& operator=(const ResourceHolder& other) = delete;
        ResourceHolder& operator=(ResourceHolder&& other) = delete;

    private:
        static std::unordered_map<std::string, Shader> shaders;
        static std::unordered_map<std::string, Texture2d> textures;
        static std::unordered_map<std::string, tiled::Map> tilemaps;
        static std::unordered_map<std::string, TextureAtlas> texture_atlases;

        static std::string load_shader(const GLchar* file_path);
    };
}

#endif //INC_2D_GAME_FILE_MANAGER_H
