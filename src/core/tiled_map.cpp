//
// Created by novasurfer on 6/22/19.
//

#include "tiled_map.h"
#include "../../deps/base64/base64.h"
#include "../../deps/miniz/miniz.h"
#include "log2.h"


TiledMap::TiledMap(const TiledData &tiled_data) : tiled_data{tiled_data}
{
    crack_layer_data();
}

// TODO: Move zlib / miniz stuff to another class and wrap it for C++
void TiledMap::crack_layer_data() {
    const std::string decoded_data = base64_decode(tiled_data.layers[0].get_data());
    log_info_cmd("DECODED_DATA: %s", decoded_data.c_str());
    unsigned *out = nullptr;

    uLongf outlen = tiled_data.width * tiled_data.height * 4;
    out = (unsigned*)malloc(outlen);
    int uncmp_status = uncompress((Bytef*)out, &outlen, (const Bytef*)decoded_data.c_str(), decoded_data.size());

    if(uncmp_status != Z_OK)
    {
        log_err_cmd("ERROR!");
        free(out);
    } else {
        for(size_t i = 0; i < outlen; ++i)
        {
            log_info_cmd("Value: %x", out[i]);
        }
    }
}
