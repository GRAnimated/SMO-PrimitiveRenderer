#pragma once

#include "game/StageScene/StageScene.h"
#include "sead/gfx/seadPrimitiveRenderer.h"
#include "agl/DrawContext.h"
#include "al/util.hpp"
#include "al/PlayerHolder/PlayerHolder.h"

#include "main.h"

bool tryDrawAreaGroup(al::Scene *curScene, char const *area, bool isDrawSolid, sead::Color4f wire, sead::Color4f solid, sead::Color4f cyl);