//
// Created by novasurfer on 6/22/19.
//

#include "tiled_map.h"
#include "sprite_sheet.h"
#include "../../deps/base64/base64.h"
#include "../../deps/miniz/miniz.h"
#include "log2.h"

namespace sc2d::tiled
{

    Map::Map(const Data& tiled_data)
        : tiled_data {tiled_data}
    {
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

            unsigned tile_inx = 0;
            std::vector<uint32_t> tile_ids;

            for(int x = 0; x < tiled_data.tile_width; ++x) {
                for(int y = 0; y < tiled_data.height; ++y) {
                    unsigned gid = out[y * tiled_data.width + x];
                    unsigned tileset_index = gid;

                    // Get tileset index
                    tileset_index &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG |
                             FLIPPED_DIAGONALLY_FLAG);

                    for(int i = tiled_data.tilesets.size() - 1; i > -1; --i)
                    {
                        if(tileset_index >= 1)
                            tileset_index = i;
                        else
                            tileset_index = -1;
                    }
		            
                    map_gids[x][y] = gid; 
                    
                    if(tileset_index != -1)
                    {
                        tile_ids.push_back(gid);
                        log_info_cmd("GID: %d", gid - 1);
                    }
                }
            }
            log_info_cmd("VECSIZE: %d", tile_ids.size());
        }
    }

    void Map::draw_map()
    {
	    for(int x = 0; x < tiled_data.tile_width; ++x) {
            for(int y = 0; y < tiled_data.tile_height; ++y) {
                
            }
        }
    }
}
