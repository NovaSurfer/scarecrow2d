//
// Created by novasurfer on 6/22/19.
//

#ifndef INC_2D_GAME_TILED_MAP_H
#define INC_2D_GAME_TILED_MAP_H

#include <string>
#include <vector>
#include "sprite_sheet.h"
#include "shader.h"
#include "texture_atlas.h"

namespace sc2d::tiled
{

    // Bits on the far end of the 32-bit global tile ID are used for tile flags
    constexpr unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    constexpr unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
    constexpr unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    class Layer
    {
    public:
        void set_data(const std::string& data)
        {
            this->data = data;
        }

        const std::string& get_data()
        {
            return data;
        }

        void set_name(const std::string& name)
        {
            this->name = name;
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
        void set_img_path(const std::string& img_path)
        {
            this->img_path = img_path;
        }

        const std::string& get_data_path()
        {
            return img_path;
        }

    private:
        std::string img_path;
};

    struct Tile
    {};

    struct Data
    {
        Data()
            : width{}
            , height{}
            , tile_width{}
            , tile_height{}
        {}
        Data(int width, int height, int tile_width, int tile_height, std::vector<Layer>&& layers,
             std::vector<Set>&& tilesets)
            : width{width}
            , height{height}
            , tile_width{tile_width}
            , tile_height{tile_height}
            , layers{layers}
            , tilesets{tilesets}
        {}

        int width;
        int height;
        int tile_width;
        int tile_height;
        std::vector<Layer> layers;
        std::vector<Set> tilesets;
    };

    class Map
    {
    public:
        Map() = default;
         explicit Map(const Data& tiled_data);
    	void draw_map(const sc2d::TextureAtlas& tex_atlas);
        void set_shader(const sc2d::Shader& s)
        {
            shader = s;
        }
    private:
        Data tiled_data;
        sc2d::Shader shader;
	    std::vector<uint32_t> map_gids;
        std::vector<std::shared_ptr<sc2d::SpriteSheet>> sprites;
	
        void crack_layer_data();
    };
}

#endif //INC_2D_GAME_TILED_MAP_H
