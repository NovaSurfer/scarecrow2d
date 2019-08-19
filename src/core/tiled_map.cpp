//
// Created by novasurfer on 6/22/19.
//

#include "tiled_map.h"
#include "../../deps/base64/base64.h"
#include "../../deps/miniz/miniz.h"
#include "log2.h"
#include "math/size2d.h"
#include "math/vector2.h"

namespace sc2d::tiled
{

    Map::Map(const Data& tiled_data)
        : tiled_data {tiled_data}
    {
        //        crack_layer_data();
    }

    // TODO: Move zlib / miniz stuff to another class and wrap it for C++
    void Map::crack_layer_data()
    {
        const std::string decoded_data = base64_decode(tiled_data.layers[0].get_data());
        log_info_cmd("DECODED_DATA: %s", decoded_data.c_str());
        unsigned* out = nullptr;

        uLongf outlen = tiled_data.width * tiled_data.height * 4;
        out = (unsigned*)malloc(outlen);
        int uncmp_status = uncompress((Bytef*)out, &outlen, (const Bytef*)decoded_data.c_str(),
                                      decoded_data.size());

        if(uncmp_status != Z_OK) {
            log_err_cmd("ERROR!");
            free(out);
        } else {

            map_gids.resize(tiled_data.width * tiled_data.height, 0);

            for(int x = 0; x < tiled_data.width; ++x) {
                for(int y = 0; y < tiled_data.height; ++y) {
                    unsigned gid = out[y * tiled_data.width + x];
                    unsigned tileset_index = gid;

                    // Get tileset index
                    tileset_index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG |
                                       FLIPPED_DIAGONALLY_FLAG);

                    for(int i = tiled_data.tilesets.size() - 1; i > -1; --i) {
                        if(tileset_index >= 1)
                            tileset_index = i;
                        else
                            tileset_index = -1;
                    }

                    if(tileset_index != -1) {
                        map_gids[y * tiled_data.width + x] = gid;
                        std::vector<math::vec2> positions;
                        positions.emplace_back(x * tiled_data.tile_width,
                                               y * tiled_data.tile_height);
                        if(gid > 0) {
                            shader.set_int("tile_index", gid - 2);
                            sprite_sheet = SpriteSheet(shader, std::move(positions));
//                            sprites.emplace_back(std::make_shared<sc2d::SpriteSheet>(
//                                shader,
//                                math::vec2(x * tiled_data.tile_width, y * tiled_data.tile_height)));
                        }
                        log_info_cmd("GID: %d", gid);
                    }
                }
            }
            log_info_cmd("VECSIZE: %d", map_gids.size());
//            log_info_cmd("SPRITES SIZE: %d", sprites.size());
        }
        free(out);
    }

    void Map::draw_map(const sc2d::TextureAtlas& tex_atlas)
    {
        sprite_sheet.draw(tex_atlas, math::size2d(5,5), 0);
//        for(const auto& s : sprites) {
//            s->draw(tex_atlas, math::size2d(5, 5), 0);
//        }
    }
}
