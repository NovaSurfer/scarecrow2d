//
// Created by Maksim Ruts on 02-Nov-18.
//

#ifndef INC_2D_GAME_CONFIGLOADER_H
#define INC_2D_GAME_CONFIGLOADER_H

#include "../../deps/nlohmann/json.hpp"
#include <fstream>

namespace sc2d
{

    using json = nlohmann::json;

    struct IConfigLoader
    {
        virtual void operator()(const json&) = 0;

        virtual ~IConfigLoader() = default;
    };

    struct SceneConfigLoad : IConfigLoader
    {
        void operator()(const json& obj_json) override;
    };

    struct ResourcesConfigLoad : IConfigLoader
    {
        void operator()(const json& obj_json) override;
    };

    template <typename T>
    struct Config : T
    {
        static_assert(std::is_base_of<IConfigLoader, T>::value,
                      "Template argument must be an IConfigLoader");

        static bool open(const std::string& path);
    };
}

#endif //INC_2D_GAME_CONFIGLOADER_H
