//
// Created by novasurfer on 6/22/19.
//

#include "tiled_map.h"
#include "../../deps/base64/base64.h"
#include "../../deps/miniz/miniz.h"
#include "log2.h"
#include "math/size2d.h"

namespace sc2d::tiled
{

    Map::Map(const Data& tiled_data)
        : tiled_data {tiled_data}
    {}

    void Map::init(const sc2d::Shader& map_shader)
    {
        shader = map_shader;
        crack_layer_data();
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
            map_gids.reserve(tiled_data.width * tiled_data.height);
            uint32_t data_gids[tiled_data.content_count];
            math::vec2 data_pos[tiled_data.content_count];
            uint32_t sid_idx = 0;

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
                        if(gid > 0) {
                            data_pos[sid_idx].x = x * tiled_data.tile_width;
                            data_pos[sid_idx].y = y * tiled_data.tile_height;
                            data_gids[sid_idx] = gid - 1;
                            ++sid_idx;
                        }
                        log_info_cmd("GID: %d", gid);
                    }
                }
            }

            SpriteSheetInstanceData sids(data_gids, data_pos);
            sprite_sheet.init_data(
                shader, math::size2d(tiled_data.tile_width, tiled_data.tile_height),
                tiled_data.content_count, sids);
            log_info_cmd("VECSIZE: %d", map_gids.size());
        }
        free(out);
    }

    void Map::draw_map(const GLuint texatlas_id) const
    {
        sprite_sheet.draw(texatlas_id);
    }
}
