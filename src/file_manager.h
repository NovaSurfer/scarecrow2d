//
// Created by Maksim Ruts on 29-Aug-18.
//

#ifndef INC_2D_GAME_FILE_MANAGER_H
#define INC_2D_GAME_FILE_MANAGER_H

#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

//TODO: add config files support
class FileManager {
public:
static Shader load_shader(const GLchar *vert_file, const GLchar *frag_file, const GLchar *geom_file, std::string name);
static Shader get_shader(std::string shader_name);
static Texture2d load_texture(const GLchar *img_file, bool alpha, std::string name);
static Texture2d get_texture(std::string shader_name);
static void clean();

FileManager() = delete;
FileManager(const FileManager& other) = delete;
FileManager(FileManager&& other) = delete;
FileManager &operator=(const FileManager& other) = delete;
FileManager &operator=(FileManager&& other) = delete;

private:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2d> textures;
};


#endif //INC_2D_GAME_FILE_MANAGER_H
