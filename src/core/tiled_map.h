//
// Created by novasurfer on 6/22/19.
//

#ifndef INC_2D_GAME_TILED_MAP_H
#define INC_2D_GAME_TILED_MAP_H

#include <string>
#include <vector>

class TileLayer {
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

class TileSet {
public:
    void set_img_path(const std::string &img_path)
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

struct TiledData {
    int width;
    int height;
    int tile_width;
    int tile_height;
    std::vector<TileLayer> layers;
    std::vector<TileSet> tilesets;
};


class TiledMap {
public:
    TiledMap(const TiledData& tiled_data) : tiled_data{tiled_data} {}



private:
    TiledData tiled_data;


};


#endif //INC_2D_GAME_TILED_MAP_H
