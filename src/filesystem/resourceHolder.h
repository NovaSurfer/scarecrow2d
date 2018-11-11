//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_FILE_MANAGER_H
#define INC_2D_GAME_FILE_MANAGER_H

#include <unordered_map>
#include <string>
#include <experimental/string_view>
#include <fstream>
#include <sstream>


#include "shader.h"
#include "texture.h"
#include "../../deps/stb/stb_image.h"

using string_view = std::experimental::string_view;

class FileManager {
public:
    static Shader load_shader_program(string_view name, const GLchar *vert_file, const GLchar *frag_file, const GLchar *geom_file = nullptr);
    static const Shader get_shader(string_view shader_name);
    static Texture2d load_texture(const std::string& img_file, bool alpha, string_view name);
    static const Texture2d get_texture(string_view texture_name);
    static void clean();

    FileManager() = delete;
    FileManager(const FileManager& other) = delete;
    FileManager(FileManager&& other) = delete;
    FileManager &operator=(const FileManager& other) = delete;
    FileManager &operator=(FileManager&& other) = delete;

private:
    static std::unordered_map<string_view, Shader> shaders;
    static std::unordered_map<string_view, Texture2d> textures;
    static std::string load_shader(Shader::ShaderType shader_type, const GLchar *file_path);
};


#endif //INC_2D_GAME_FILE_MANAGER_H
