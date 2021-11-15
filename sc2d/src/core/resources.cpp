//
// Created by novasurfer on 4/24/20.
//

#include "resources.h"
#include "filesystem/configLoader.h"
#include "filesystem/resourceHolder.h"

namespace sc2d
{

    ResultBool Resources::load_all()
    {
        if(!sc2d::Config<sc2d::ResourcesConfigLoad>::open("resources.json"))
            return sc2d::ResultBool::throw_err(sc2d::Err::RESOURCE_LOADING_FAIL);

        if(!sc2d::Config<sc2d::SceneConfigLoad>::open("data/scenes/zone.json"))
            return sc2d::ResultBool::throw_err(sc2d::Err::SCENE_LOADING_FAIL);

        return {true};
    }

    void Resources::clean_all()
    {
        ResourceHolder::clean();
    }
}