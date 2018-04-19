//
// Created by Maksim Ruts on 19-Apr-18.
//

#include "levelmap.h"

LevelMap::LevelMap() {
    dirt    = TextureManager::load_texture("res/sprites/dirt.png");
    grass   = TextureManager::load_texture("res/sprites/grass.png");
    water   = TextureManager::load_texture("res/sprites/water.png");

    scrRect.x  = scrRect.y   = 0;
    destRect.x = destRect.y  = 0;
    scrRect.w  = destRect.w  = 32;
    scrRect.h  = destRect.h  = 32;

    load_map(lvl1);
}

void LevelMap::load_map(int mapArray[20][25]) {
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            map[row][column] = mapArray[row][column];
        }
    }
}

void LevelMap::draw_map() {
    int type = 0;
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            type = map[row][column];

            destRect.x = column * 32;
            destRect.y = row    * 32;

            switch (type){
                case 0:
                    TextureManager::draw_texture(water, scrRect, destRect);
                    break;
                case 1:
                    TextureManager::draw_texture(grass, scrRect, destRect);
                    break;
                case 2:
                    TextureManager::draw_texture(dirt, scrRect, destRect);
                    break;
                default:
                    break;
            }
        }
    }
}

