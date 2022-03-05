#pragma once

#include "al/util.hpp"
#include "game/StageScene/StageScene.h"

#include "debugMenu.h"

class TransparentWall : public al::LiveActor {
};

extern bool showMenu;
extern bool showAreas;
extern bool show2DMoveAreas;
extern bool showWaterAreas;
extern bool showDeathAreas;
extern bool showWarpAreas;
extern bool showMissRestartAreas;
extern bool showRaceCourseOutAreas;
extern bool showChangeStageAreas;
extern bool showCameraAreas;
extern bool showTransparentWalls;
extern bool enableFadeoff;

extern bool isInGame;