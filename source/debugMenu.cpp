#include "debugMenu.h"
#include "drawer.h"
#include "main.h"

// These files must exist in your romfs! they are not there by default, and must be added in order for the debug font to work correctly.
static const char *DBG_FONT_PATH = "DebugData/Font/nvn_font_jis1.ntx";
static const char *DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char *DBG_TBL_PATH = "DebugData/Font/nvn_font_jis1_tbl.bin";

sead::TextWriter *gTextWriter;
sead::PrimitiveDrawer *drawer;

sead::PtrArray<TransparentWall> transparentWalls;

void createWallHook(TransparentWall *wall) {
    al::trySyncStageSwitchAppearAndKill(wall);

    transparentWalls.pushBack(wall);
}

void destroyWalls() {
    transparentWalls.freeBuffer();
    __asm("MOV X0, X19");
}

void setupDebugMenu(GameSystem *gSys) {
    transparentWalls.tryAllocBuffer(50, nullptr);
    // gLogger->LOG("Preparing Debug Menu.\n");

    sead::Heap *curHeap = al::getCurrentHeap();

    agl::DrawContext *context = gSys->mSystemInfo->mDrawInfo->mDrawContext;

    if (curHeap) {
        if (context) {

            sead::DebugFontMgrJis1Nvn::sInstance = sead::DebugFontMgrJis1Nvn::createInstance(curHeap);

            if (al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_TBL_PATH)) {
                sead::DebugFontMgrJis1Nvn::sInstance->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH, 0x100000);
                sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::sInstance);
                gTextWriter = new sead::TextWriter(context);
                gTextWriter->setupGraphics(context);
            }

            sead::PrimitiveDrawer drawer(context);

        } else {
            // gLogger->LOG("Failed to get Context!\n");
        }
    } else {
        // gLogger->LOG("Failed to get Heap!\n");
    }

    __asm("MOV W23, #0x3F800000");
    __asm("MOV W8, #0xFFFFFFFF");
}

void drawBackground(agl::DrawContext *context) {

    sead::Vector3<float> p1; // top left
    p1.x = -1.0;
    p1.y = 0.3;
    p1.z = 0.0;
    sead::Vector3<float> p2; // top right
    p2.x = -0.2;
    p2.y = 0.3;
    p2.z = 0.0;
    sead::Vector3<float> p3; // bottom left
    p3.x = -1.0;
    p3.y = -1.0;
    p3.z = 0.0;
    sead::Vector3<float> p4; // bottom right
    p4.x = -0.2;
    p4.y = -1.0;
    p4.z = 0.0;

    sead::Color4f c;
    c.r = 0.1;
    c.g = 0.1;
    c.b = 0.1;
    c.a = 0.9;

    agl::utl::DevTools::beginDrawImm(context, sead::Matrix34<float>::ident, sead::Matrix44<float>::ident);
    agl::utl::DevTools::drawTriangleImm(context, p1, p2, p3, c);
    agl::utl::DevTools::drawTriangleImm(context, p3, p4, p2, c);
}

void drawMainHook(HakoniwaSequence *curSequence, sead::Viewport *viewport, sead::DrawContext *drawContext) {

    // int dispWidth = al::getLayoutDisplayWidth();
    int dispHeight = al::getLayoutDisplayHeight();
    gTextWriter->mViewport = viewport;
    gTextWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);
    al::Scene *curScene = curSequence->curScene;

    if (curScene && isInGame && showMenu) {

        drawBackground((agl::DrawContext *)drawContext);

        // edit this area when you want to make changes to whats displayed with text writer (currently, there doesnt seem to be an easy way to get text writer to properly display info in other functions)

        al::PlayerHolder *pHolder = al::getScenePlayerHolder(curScene);
        PlayerActorHakoniwa *player = al::tryGetPlayerActor(pHolder, 0);
        sead::Vector3f &playerTrans = al::getTrans(player);
        sead::Vector3f *playerVel = al::getVelocity(player);
        sead::Quatf *playerQuat = al::getQuat(player);
        sead::Vector3f eulerAngles = QuatToEuler(*playerQuat);
        sead::Vector3f playerRot = sead::Vector3f(DEG(eulerAngles.x), DEG(eulerAngles.y), DEG(eulerAngles.z));

        gTextWriter->beginDraw();

        gTextWriter->setCursorFromTopLeft(sead::Vector2f(10.f, (dispHeight / 3) + 30.f));

        gTextWriter->setScaleFromFontHeight(20.f);

        gTextWriter->printf("sead::PrimitiveRenderer rendering!\n");

        gTextWriter->printf("Mario Pos:\nX: %f\nY: %f\nZ: %f\n", playerTrans.x, playerTrans.y, playerTrans.z);
        gTextWriter->printf("Mario Velocity:\nX: %f\nY: %f\nZ: %f\n", playerVel->x, playerVel->y, playerVel->z);
        gTextWriter->printf("Mario Rotation:\nX: %f\nY: %f\nZ: %f\n", playerRot.x, playerRot.y, playerRot.z);
        gTextWriter->printf("Horizontal Speed: %f\n", al::calcSpeedH(player));

        gTextWriter->endDraw();
    }

    if (curScene && isInGame) {
        sead::LookAtCamera *cam = al::getLookAtCamera(curScene, 0);
        sead::Projection *projection = al::getProjectionSead(curScene, 0);

        sead::PrimitiveRenderer *renderer = sead::PrimitiveRenderer::instance();
        renderer->setDrawContext(drawContext);
        renderer->setCamera(*cam);
        renderer->setProjection(*projection);

        renderer->begin();

        // draw in here
        sead::Vector3f pos = {0, 0, 0};

        sead::Color4f color = sead::Color4f(0, 255, 0, 1);

        sead::Matrix34f mat = sead::Matrix34f::ident;
        mat.setBase(3, pos); // Sets the position of the matrix.
                             // For cubes, you need to put this at the location.
                             // For spheres, you can leave this at 0 0 0 since you set it in its draw function.
        renderer->setModelMatrix(mat);

        // sead::BoundBox3f box = sead::BoundBox3f(sead::Vector3f(-100, -100, -100), sead::Vector3f(100, 100, 100));
        // sead::PrimitiveDrawer::CubeArg cube(box, color);
        //  renderer->drawWireCube(cube);

        al::PlayerHolder *pHolder = al::getScenePlayerHolder(curScene);
        PlayerActorHakoniwa *player = al::tryGetPlayerActor(pHolder, 0);
        sead::Vector3f &playerTrans = al::getTrans(player);

        if (showAreas)
            renderer->drawSphere8x16(playerTrans, 20, color); // Draws a sphere at Mario's location

        if (showAreas)
            renderer->drawAxis(sead::Vector3f(0, 0, 0), 200); // Draws a 3-line axis at 0 0 0

        if (transparentWalls[0] && showAreas && showTransparentWalls) {
            for (int i = 0; i < transparentWalls.size(); i++) {
                al::LiveActor *wall = transparentWalls[i];

                sead::Vector3f &wScale = al::getScale(wall);

                sead::Matrix34f wallMtx = sead::Matrix34f::ident;
                al::makeMtxRT(&wallMtx, wall);

                renderer->setModelMatrix(wallMtx);

                sead::PrimitiveDrawer::QuadArg wallQuad(sead::Vector3f(0, 0, 0), sead::Vector2f(wScale.x * 1000, wScale.y * 1000), sead::Color4f(0, 0, 255, .2), sead::Color4f(0, 0, 255, .2));
                renderer->drawQuad(wallQuad);
            }
        }

        renderer->end();

        if (showAreas) {
            if (show2DMoveAreas)
                tryDrawAreaGroup(curScene, "2DMoveArea", true, sead::Color4f(255, 128, 255, .2), sead::Color4f(255, 0, 255, .2), sead::Color4f(255, 0, 255, .2));

            if (showWaterAreas)
                tryDrawAreaGroup(curScene, "WaterArea", true, sead::Color4f(0, 150, 255, .1), sead::Color4f(0, 150, 255, .2), sead::Color4f(0, 150, 255, .1));

            if (showDeathAreas)
                tryDrawAreaGroup(curScene, "DeathArea", false, sead::Color4f(192, 0, 0, 1), sead::Color4f(0, 150, 255, .2), sead::Color4f(128, 0, 0, .1));

            if (showWarpAreas)
                tryDrawAreaGroup(curScene, "WarpArea", true, sead::Color4f(255, 128, 0, .3), sead::Color4f(255, 128, 0, .3), sead::Color4f(255, 128, 0, .3));

            if (showRaceCourseOutAreas)
                tryDrawAreaGroup(curScene, "RaceCourseOutArea", false, sead::Color4f(0, 240, 245, 1), sead::Color4f(0, 240, 245, .3), sead::Color4f(0, 240, 245, .3));

            if (showChangeStageAreas)
                tryDrawAreaGroup(curScene, "ChangeStageArea", true, sead::Color4f(255, 0, 0, .3), sead::Color4f(255, 0, 0, .3), sead::Color4f(255, 0, 0, .3));

            if (showCameraAreas)
                tryDrawAreaGroup(curScene, "CameraArea", false, sead::Color4f(255, 255, 255, 1), sead::Color4f(0, 0, 255, .1), sead::Color4f(0, 0, 255, .1));
        }
    }

    isInGame = false;
    al::executeDraw(curSequence->mLytKit, "２Ｄバック（メイン画面）");
}
