//
// Created by novasurfer on 6/22/19.
//

#include "tiled_map.h"
#include "collections/arr.h"
#include "core/base64.h"
#include "core/log2.h"
#include "miniz/miniz.h"

namespace sc2d::tiled
{

    Map::Map(const Data& tiled_data)
        : tiled_data {tiled_data}
    { }

    void Map::init(const sc2d::Shader& map_shader, const math::mat4& projection)
    {
        shader = map_shader;

        // cracking layer data
        // TODO: Move zlib / miniz stuff to another class and wrap it for C++
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
            map_gids.resize(tiled_data.width * tiled_data.height);
            SpriteSheetInstData sids;
            u32 sid_idx = 0;

            for(int x = 0; x < tiled_data.width; ++x) {
                for(int y = 0; y < tiled_data.height; ++y) {
                    u32 gid = out[y * tiled_data.width + x];
                    u32 tileset_index = gid;

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
                            sids.pos[sid_idx].x = x * tiled_data.tile_width;
                            sids.pos[sid_idx].y = y * tiled_data.tile_height;
                            sids.gid[sid_idx] = gid - 1;
                            ++sid_idx;
                        }
                        log_info_cmd("GID: %d", gid);
                    }
                }
            }
//            log_gl_error_cmd();
            sprite_sheet.init(shader, math::vec2(tiled_data.tile_width, tiled_data.tile_height),
                              tiled_data.content_count, projection, sids);
//            sprite_sheet.set_size(math::vec2(tiled_data.tile_width, tiled_data.tile_height));
            sprite_sheet.set_color(Color::WHITE);
            log_info_cmd("VECSIZE: %d", map_gids.size());
        }
        free(out);
    }

    void Map::set_sheet_texture(GLuint texid)
    {
        sprite_sheet.set_texture_array(texid);
    }

    void Map::draw_map() const
    {
        sprite_sheet.draw();
    }
}
