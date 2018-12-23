//
// Created by maksim on 6/10/18.
//

#ifndef INC_2D_ENGINE_INPUTMANAGER_H
#define INC_2D_ENGINE_INPUTMANAGER_H

#include "game.h"
#include "utils/ini_io.h"

class InputManager {
public:
    InputManager();

    bool get_key_down(const std::string &key);

    bool get_key_up(const std::string &key);


private:
    std::vector<std::pair<std::string, std::string>> key_values;
    std::map<std::string, std::string> key_names;


    bool is_same_key(const std::string &key);
};


#endif //INC_2D_ENGINE_INPUTMANAGER_H
