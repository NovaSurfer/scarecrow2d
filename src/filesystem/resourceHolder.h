//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_FILE_MANAGER_H
#define INC_2D_GAME_FILE_MANAGER_H

#include <unordered_map>
#include <string_view>
#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

#include "core/texture.h"
#include "core/shader.h"
#include "core/tiled_map.h"

//class Texture2d;

namespace sc2d {

    using string_view = std::string_view;

    class ResourceHolder {
    public:
        static void load_shader_program(std::string name, const GLchar* vert_file, const GLchar* frag_file,
                const GLchar* geom_file = nullptr);

        static const Shader& get_shader(std::string shader_name);

        static void load_texture(const std::string& img_file, bool alpha, std::string name);

        static const Texture2d& get_texture(std::string texture_name);

        static void load_tiled_map(const std::string& name, const tiled::Data& tiled_data);

        static const tiled::Map& get_tiled_map(std::string map_name);

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

        static std::string load_shader(const GLchar* file_path);
    };

}


#endif //INC_2D_GAME_FILE_MANAGER_H
