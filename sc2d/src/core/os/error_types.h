//
// Created by Maksim Ruts on 29/08/2019.
//

#ifndef INC_2D_GAME_ERROR_TYPES_H
#define INC_2D_GAME_ERROR_TYPES_H

namespace sc2d
{

#define FOREACH_ERROR(ERR)                                                                         \
    ERR(OK)                                                                                        \
    ERR(FAILED_TO_OPEN_FILE)                                                                       \
    ERR(FAILED_TO_PARSE_JSON)                                                                      \
    ERR(FAILED_TO_INIT_GLAD)                                                                       \
    ERR(FAILED)                                                                                    \
    ERR(RESOURCE_LOADING_FAIL)                                                                     \
    ERR(SCENE_LOADING_FAIL)                                                                        \
    ERR(ENGINE_INIT_FAIL)                                                                          \
    ERR(UNKNOWN)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

    enum class Err
    {
        FOREACH_ERROR(GENERATE_ENUM)
    };

    static const char* ERR_STR[] = {FOREACH_ERROR(GENERATE_STRING)};
}
#endif //INC_2D_GAME_ERROR_TYPES_H
