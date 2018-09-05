//
// Created by Maksim Ruts on 29-Aug-18.
//

#include "file_manager.h"

std::map<std::string, Shader> FileManager::shaders;
std::map<std::string, Texture2d> FileManager::textures;

Shader
FileManager::load_shader_program(const GLchar *vert_file, const GLchar *frag_file, const GLchar *geom_file, std::string name) {
    Shader shader;
    std::string v_shader, f_shader, g_shader;
    v_shader = load_shader(Shader::ShaderType::VERTEX, vert_file);
    f_shader = load_shader(Shader::ShaderType::FRAGMENT, frag_file);
    if(geom_file != nullptr)
        g_shader = load_shader(Shader::ShaderType::GEOMETRY, geom_file);
    shader.compile(v_shader.c_str(), f_shader.c_str(), geom_file != nullptr ? g_shader.c_str() : nullptr);
    shaders.insert({name, shader});
    return shaders[name];
}


Shader FileManager::get_shader(std::string shader_name) {
    return shaders[shader_name];
}

Texture2d FileManager::load_texture(const char *img_file, bool alpha, std::string name) {
    int width, height, nr_channels;
    unsigned char* image = stbi_load(img_file, &width, &height, &nr_channels, 0);

    if(alpha)
        textures[name] = Texture2d(image, width, height, GL_RGBA);
    textures[name] = Texture2d(image, width, height);
    return textures[name];
}

Texture2d FileManager::get_texture(std::string texture_name) {
    return textures[texture_name];
}

void FileManager::clean() {
    for (auto s : shaders)
        glDeleteProgram(s.second.get_program());
    for (auto t : textures)
        glDeleteTextures(1, &t.second.get_obj_id());
}

std::string FileManager::load_shader(Shader::ShaderType shader_type, const GLchar *file_path) {
    try
    {
        std::ifstream shader_file(file_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        return shader_stream.str();

    }catch (const std::exception &e)
    {
        std::cout << "ERROR :: SHADER :: Failed to read shader file" << '\n';
    }
    return{};
}