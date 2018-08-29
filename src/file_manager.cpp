//
// Created by Maksim Ruts on 29-Aug-18.
//

#include "file_manager.h"

Shader
FileManager::load_shader(const GLchar *vert_file, const GLchar *frag_file, const GLchar *geom_file, std::string name) {
        return Shader();
}

Shader FileManager::get_shader(std::string shader_name) {
    return Shader();
}

Texture2d FileManager::load_texture(const GLchar *img_file, bool alpha, std::string name) {
    return Texture2d(nullptr, 0, 0);
}

Texture2d FileManager::get_texture(std::string shader_name) {
    return Texture2d(nullptr, 0, 0);
}

void FileManager::clean() {

}
