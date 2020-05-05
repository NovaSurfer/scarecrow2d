//
// Created by Maksim Ruts on 29-Aug-18.
//

#include "resourceHolder.h"
#include "../../deps/stb/stb_image.h"
#include "core/log2.h"

namespace sc2d
{

    std::unordered_map<std::string, Shader> ResourceHolder::shaders;
    std::unordered_map<std::string, Texture2d> ResourceHolder::textures;
    std::unordered_map<std::string, tiled::Map> ResourceHolder::tilemaps;
    std::unordered_map<std::string, TextureAtlas> ResourceHolder::texture_atlases;

    void ResourceHolder::load_shader_program(ShaderSource shader_source, const std::string& name,
                                             const GLchar* vert_file, const GLchar* frag_file,
                                             const GLchar* geom_file)
    {
        Shader shader;
        if(shader_source == ShaderSource::FILE) {
            std::string v_shader, f_shader, g_shader;
            v_shader = load_shader(vert_file);
            f_shader = load_shader(frag_file);
            if(geom_file != nullptr)
                g_shader = load_shader(geom_file);
            ShaderUtil::compile(shader, v_shader.c_str(), f_shader.c_str(),
                           geom_file != nullptr ? g_shader.c_str() : nullptr);
        } else {
            ShaderUtil::compile(shader, vert_file, frag_file, geom_file != nullptr ? geom_file : nullptr);
        }
        shaders.insert({name, shader});
    }

    const Shader& ResourceHolder::get_shader(const std::string& shader_name)
    {
        return shaders[shader_name];
    }

    void ResourceHolder::load_texture(const std::string& img_file, bool alpha,
                                      const std::string& name)
    {
        int width, height, nr_channels;
        unsigned char* image =
            stbi_load(img_file.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);

        textures[name] = Texture2d(image, width, height, alpha ? GL_RGBA : GL_RGB);
    }

    const Texture2d& ResourceHolder::get_texture(const std::string& texture_name)
    {
        return textures[texture_name];
    }

    void ResourceHolder::clean()
    {
        for(auto [name, shader] : shaders)
            glDeleteProgram(shader.get_program());
        for(auto [name, texture] : textures)
            glDeleteTextures(1, &texture.get_obj_id());
        for(auto [name, tex_array] : texture_atlases)
            glDeleteTextures(1, &tex_array.get_obj_id());
    }

    // TODO: remove C++ streams and exceptions
    std::string ResourceHolder::load_shader(const char* file_path)
    {
        //        try {
        std::ifstream shader_file(file_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        return shader_stream.str();
        //        }
        //        catch(const std::exception& e) {
        log_err_file("Failed to read shader file %s", file_path);
        //        }
        //        return {};
    }

    void ResourceHolder::load_tiled_map(const std::string& name, const tiled::Data& tiled_data)
    {
        tiled::Map tiled_map {tiled_data};
        tilemaps[name] = tiled_map;
    }

    const tiled::Map& ResourceHolder::get_tiled_map(const std::string& map_name)
    {
        return tilemaps[map_name];
    }
    void ResourceHolder::load_texture_atlas(const std::string& img_file, const uint rows,
                                            const uint columns, bool alpha, const std::string& name)
    {
        int width, height, nr_channels;
        unsigned char* image =
            stbi_load(img_file.c_str(), &width, &height, &nr_channels, STBI_rgb_alpha);

        texture_atlases[name] =
            TextureAtlas(image, width, height, rows, columns, alpha ? GL_RGBA : GL_RGB);
    }
    const TextureAtlas& ResourceHolder::get_texture_atlas(const std::string& name)
    {
        return texture_atlases[name];
    }
}
