//
// Created by Maksim Ruts on 03/09/2019.
//

#ifndef SCARECROW2D_SHADER_FILES_H
#define SCARECROW2D_SHADER_FILES_H

namespace sc2d::cshaders
{

    constexpr const char* VS_SPRITESHEET =
#include "shaders/spritesheet.vert"
        ;

    constexpr const char* FS_SPRITESHEET =
#include "shaders/spritesheet.frag"
        ;

    constexpr const char* VS_SPRITE_DEFAULT =
#include "shaders/sprite_default.vert"
        ;

    constexpr const char* FS_SPRITE_DEFAULT =
#include "shaders/sprite_default.frag"
        ;

    struct ShadersArray
    {
        const char* vs_src;
        const char* fs_src;
        const char* name;
    };

    constexpr const ShadersArray SHADERS_ARRAY[] {
        {VS_SPRITESHEET, FS_SPRITESHEET, "spritesheet"},
        {VS_SPRITE_DEFAULT, FS_SPRITE_DEFAULT, "sprite_default"}};
};
#endif //SCARECROW2D_SHADER_FILES_H
