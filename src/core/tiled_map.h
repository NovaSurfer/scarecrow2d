//
// Created by novasurfer on 6/22/19.
//

#ifndef INC_2D_GAME_TILED_MAP_H
#define INC_2D_GAME_TILED_MAP_H

#include "shader.h"
#include "sprite_sheet_inst.h"
#include "texture_atlas.h"
#include "types.h"
#include <string>
#include <vector>

namespace sc2d::tiled
{

    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    constexpr unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    constexpr unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    constexpr unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    class Layer
    {
    public:
        void set_data(const std::string& d)
        {
            data = d;
        }

        const std::string& get_data()
        {
            return data;
        }

        void set_name(const std::string& n)
        {
            name = n;
        }

        const std::string& get_name()
        {
            return name;
        }

    private:
        std::string data;
        std::string name;
    };

    class Set
    {
    public:
        void set_img_path(const std::string& path)
        {
            img_path = path;
        }

        const std::string& get_data_path()
        {
            return img_path;
        }

    private:
        std::string img_path;
    };

    //    struct Tile
    //    {};

    struct Data
    {
        Data()
            : width {}
            , height {}
            , tile_width {}
            , tile_height {}
            , content_count {}
        {}
        Data(int width, int height, int tile_width, int tile_height, size_t content_count,
             std::vector<Layer>&& layers, std::vector<Set>&& tilesets)
            : width {width}
            , height {height}
            , tile_width {tile_width}
            , tile_height {tile_height}
            , content_count {content_count}
            , layers {layers}
            , tilesets {tilesets}
        {}

        int width;
        int height;
        int tile_width;
        int tile_height;
        size_t content_count;
        std::vector<Layer> layers;
        std::vector<Set> tilesets;
    };

    class Map
    {
    public:
        Map() = default;
        explicit Map(const Data& tiled_data);
        void init(const Shader& map_shader);
        void set_sheet_texture(GLuint texid);
        void draw_map() const;

    private:
        Data tiled_data;
        Shader shader;
        std::vector<u32> map_gids;
        SpriteSheetInstanced sprite_sheet;

        void crack_layer_data();
    };
}

#endif //INC_2D_GAME_TILED_MAP_H
