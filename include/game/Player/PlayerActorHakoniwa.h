#pragma once
/**
 * @file PlayerActorBase.h
 * @brief Main Class for the PlayerActor (Mario)
 * Player Pose: TQGMSV
*  Vtable loc: 1D780C0
*/

#include "game/Interfaces/IUseDimension.h"
#include "al/actor/ActorDimensionKeeper.h"
#include "al/actor/ActorInitInfo.h"
#include "PlayerActorBase.h"
#include "PlayerPuppet.h"
#include "PlayerInput.h"
#include "PlayerAnimator.h"
#include "HackCap.h"
#include "PlayerModelKeeper.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerConst.h"
#include "PlayerHackKeeper.h"
#include "PlayerInfo.h"
#include "PlayerModelChangerHakoniwa.h"
#include "PlayerFormSensorCollisionArranger.h"
#include "PlayerInitInfo.h"
#include "PlayerRecoverySafetyPoint.h"

#include "Attacks/PlayerSpinCapAttack.h"

//#define PACTORSIZE 0xC8
/*
class PlayerActorHakoniwa : public PlayerActorBase , public IUseDimension {
    public: 
        int *getPortNo(void) const;
        PlayerHackKeeper *getPlayerHackKeeper() const;
        void attackSensor(al::HitSensor *target, al::HitSensor *source);
        void startDemoPuppetable(void);
        void startPlayerPuppet(void);
        void initPlayer(al::ActorInitInfo const&, PlayerInitInfo const&);

        unsigned char padding_E8[0xE0 - PACTORSIZE];
        int portNo; // 0xE8
        unsigned char padding_130[0x38];
        PlayerInfo *mPlayerInfo; // 0x128
        PlayerConst *mPlayerConst; // 0x130
        PlayerInput *mPlayerInput; //0x138 
        unsigned char padding_148[0x8]; // PlayerTrigger
        HackCap *mHackCap; // 0x148
        ActorDimensionKeeper *mDimKeeper; // 0x150
        PlayerModelKeeper *mPlayerModelKeeper; // 0x158
        PlayerModelChangerHakoniwa *mModelChanger; // 0x160
        PlayerAnimator *mPlayerAnimator; // 0x168 
        PlayerColliderHakoniwa *mPlayerCollider; // 0x170
        PlayerPuppet *mPlayerPuppet; // 0x178
        // 0x180 PlayerAreaChecker
        // 0x188 WaterSurfaceFinder
        // 0x190 unk
        // 0x198 unk
        // 0x1A0 unk
        // 0x1A8 unk
        // 0x1B0 unk
        // 0x1B8 unk
        // 0x1C0 unk
        // 0x1C8 unk
        // 0x1D0 unk
        // 0x1D8 unk
        // 0x1E0 unk
        // 0x1E8 unk
        // 0x1F0 unk
        // 0x1F8 PlayerBindKeeper
        unsigned char padding_208[0x208 - 0x180];
        PlayerHackKeeper *mHackKeeper; // 0x208
        PlayerFormSensorCollisionArranger *mCollArranger; // 0x210
        void *unkPtr2; // 0x218
        void *unkPtr3; // 0x220
        PlayerSpinCapAttack *mSpinCapAttack; // 0x228
        unsigned char padding[0x270 - 0x228];
        PlayerRecoverySafetyPoint *mPlayerRecoverPoint; // 0x270
        
};

*/

namespace al {
    class WaterSurfaceFinder;
    class FootPrintHolder;
}

class PlayerContinuousJump;
class PlayerContinuousLongJump;
class PlayerCounterAfterUpperPunch;
class PlayerCounterQuickTurnJump;
class PlayerJumpMessageRequest;
class PlayerSandSinkAffect;
class PlayerActionDiveInWater;
class PlayerEffect;
class PlayerPushReceiver;
class PlayerHitPush;
class PlayerExternalVelocity;
class PlayerRippleGenerator;
class GaugeAir;
class WaterSurfaceShadow;
class PlayerSeCtrl;
class PlayerStateWait;
class PlayerStateSquat;
class PlayerStateRunHakoniwa2D3D;
class PlayerStateSlope;
class PlayerStateRolling;
class PlayerStateSpinCap;
class PlayerStateJump;
class PlayerStateCapCatchPop;
class PlayerStateWallAir;
class PlayerStateWallCatch;
class PlayerStateGrabCeil;
class PlayerStatePoleClimb;
class PlayerStateHipDrop;
class PlayerStateHeadSliding;
class PlayerStateLongJump;
class PlayerStateFallHakoniwa;
class PlayerStateSandSink;
class ActorStateSandGeyser;
class PlayerStateRise;
class PlayerStateSwim;
class PlayerStateDamageLife;
class PlayerStateDamageSwim;
class PlayerStateDamageFire;
class PlayerStatePress;
class PlayerStateBind;
class PlayerStateHack;
class PlayerStateEndHack;
class PlayerStateCameraSubjective;
class PlayerStateAbyss;
class PlayerJudgeAirForceCount;
class PlayerJudgeCameraSubjective;
class PlayerJudgeCapCatchPop;
//class PlayerJudgeDeadWipeStart;
class PlayerJudgeDirectRolling;
class PlayerJudgeEnableStandUp;
class PlayerJudgeForceLand;
class PlayerJudgeForceSlopeSlide;
class PlayerJudgeForceRolling;
class PlayerJudgeGrabCeil;
class PlayerJudgeInWater;
class PlayerJudgeInvalidateInputFall;
class PlayerJudgeLongFall;
class PlayerJudgeOutInWater;
class PlayerJudgeRecoveryLifeFast;
class PlayerJudgeSandSink;
class PlayerJudgeSpeedCheckFall;
class PlayerJudgeStartHipDrop;
class PlayerJudgeStartRise;
class PlayerJudgeStartRolling;
class PlayerJudgeStartRun;
class PlayerJudgeStartSquat;
class PlayerJudgeStartWaterSurfaceRun;
class PlayerJudgeSlopeSlide;
class PlayerJudgePoleClimb;
class PlayerJudgePreInputJump;
class PlayerJudgePreInputCapThrow;
class PlayerJudgePreInputHackAction;
class HackCapJudgePreInputHoveringJump;
class HackCapJudgePreInputSeparateThrow;
class HackCapJudgePreInputSeparateJump;
class PlayerJudgeWallCatch;
class PlayerJudgeWallCatchInputDir;
class PlayerJudgeWallHitDown;
class PlayerJudgeWallHitDownForceRun;
class PlayerJudgeWallHitDownRolling;
class PlayerJudgeWallKeep;


class PlayerActorHakoniwa : public PlayerActorBase, public IUseDimension {
    public: 

    _BYTE gap_0[0x50];
    PlayerInfo *mPlayerInfo; // 0x128
    PlayerConst *mPlayerConst;
    PlayerInput *mPlayerInput;
    PlayerTrigger *mPlayerTrigger;
    HackCap *mHackCap;
    ActorDimensionKeeper *mActorDimensionKeeper;
    PlayerModelHolder *mModelHolder;
    PlayerModelChangerHakoniwa *mModelChangerHakoniwa;
    PlayerAnimator *mAnimator;
    PlayerColliderHakoniwa *mColliderHakoniwa;
    PlayerPuppet *mPuppet;
    PlayerAreaChecker *mAreaChecker;
    al::WaterSurfaceFinder *mSurfaceFinder;
    PlayerOxygen *mOxygen;
    PlayerDamageKeeper *mDamageKeeper;
    PlayerDemoActionFlag *mDemoActionFlag;
    PlayerCapActionHistory *mCapActionHistory;
    PlayerCapManHeroEyesControl *mCapManHeroEyesControl;
    PlayerContinuousJump *mContinuousJump;
    PlayerContinuousLongJump *mContinuousLongJump;
    PlayerCounterAfterUpperPunch *mCounterAfterUpperPunch;
    PlayerCounterAfterCapCatch *mCounterAfterCapCatch;
    PlayerCounterIceWater *mCounterIceWater;
    PlayerCounterQuickTurnJump *mCounterQuickTurnJump;
    PlayerWallActionHistory *mWallActionHistory;
    PlayerBindKeeper *mBindKeeper;
    PlayerCarryKeeper *mCarryKeeper;
    PlayerEquipmentUser *mEquipmentUser;
    PlayerHackKeeper *mHackKeeper;
    PlayerFormSensorCollisionArranger *mFormSensorCollisionArranger;
    PlayerJumpMessageRequest *mJumpMessageRequest;
    PlayerSandSinkAffect *mSandSinkAffect;
    PlayerSpinCapAttack *mSpinCapAttack;
    PlayerActionDiveInWater *mActionDiveInWater;
    PlayerEffect *mEffect;
    PlayerEyeSensorHitHolder *mEyeSensorHitHolder;
    PlayerPushReceiver *mPushReciever;
    PlayerHitPush *mHitPush;
    PlayerExternalVelocity *mExternalVelocity;
    PlayerJointControlKeeper *mJointControlKeeper;
    PlayerPainPartsKeeper *mPainPartsKeeper;
    PlayerRecoverySafetyPoint *mRecoverySafetyPoint;
    PlayerRippleGenerator *mRippleGenerator;
    PlayerSeparateCapFlag *mSeparateCapFlag;
    PlayerWetControl *mWetControl;
    PlayerStainControl *mStainControl;
    al::FootPrintHolder *mFootPrintHolder;
    GaugeAir *mGaugeAir;
    WaterSurfaceShadow *mWaterSurfaceShadow;
    WorldEndBorderKeeper *mWorldEndBorderKeeper;
    al::HitSensor *unkSensor;
    PlayerSeCtrl *mPlayerSeCtrl;
    al::HitSensor *unkSensor2;
    bool *isLongShadow;

    // States
    PlayerStateWait *stateWait; // 0x2D8
    PlayerStateSquat *stateSquat;
    PlayerStateRunHakoniwa2D3D *stateRunHakoniwa2D3D;
    PlayerStateSlope *stateSlope;
    PlayerStateRolling *stateRolling;
    PlayerStateSpinCap *stateSpinCap;
    PlayerStateJump *stateJump;
    PlayerStateCapCatchPop *stateCapCatchPop;
    PlayerStateWallAir *stateWallAir;
    PlayerStateWallCatch *stateWallCatch;
    PlayerStateGrabCeil *stateGrabCeil;
    PlayerStatePoleClimb *statePoleClimb;
    PlayerStateHipDrop *stateHipDrop;
    PlayerStateHeadSliding *stateHeadSliding;
    PlayerStateLongJump *stateLongJump;
    PlayerStateFallHakoniwa *stateFallHakoniwa;
    PlayerStateSandSink *stateSandSink;
    ActorStateSandGeyser *stateSandGeyser;
    PlayerStateRise *stateRise;
    PlayerStateSwim *stateSwim;
    PlayerStateDamageLife *stateDamageLife;
    PlayerStateDamageSwim *stateDamageSwim;
    PlayerStateDamageFire *stateDamageFire;
    PlayerStatePress *statePress;
    PlayerStateBind *stateBind;
    PlayerStateHack *stateHack;
    PlayerStateEndHack *stateEndHack;
    PlayerStateCameraSubjective *stateCameraSubjective;
    PlayerStateAbyss *stateAbyss; // 0x3B8

    // Judges
    PlayerJudgeAirForceCount *judgeAirForceCount;
    PlayerJudgeCameraSubjective *judgeCameraSubjective;
    PlayerJudgeCapCatchPop *judgeCapCatchPop;
    PlayerJudgeDeadWipeStart *judgeDeadWipeStart;
    PlayerJudgeDirectRolling *judgeDirectRolling;
    PlayerJudgeEnableStandUp *judgeEnableStandUp;
    PlayerJudgeForceLand *judgeForceLand;
    PlayerJudgeForceSlopeSlide *judgeForceSlopeSlide;
    PlayerJudgeForceRolling *judgeForceRolling;
    PlayerJudgeGrabCeil *judgeGrabCeil;
    PlayerJudgeInWater *judgeInWater;
    PlayerJudgeInWater *judgeInWater2;
    PlayerJudgeInWater *judgeInWater3;
    PlayerJudgeInWater *judgeInWater4;
    PlayerJudgeInvalidateInputFall *judgeInvalidateInputFall;
    PlayerJudgeLongFall *judgeLongFall;
    PlayerJudgeOutInWater *judgeOutInWater;
    PlayerJudgeRecoveryLifeFast *judgeRecoveryLifeFast;
    PlayerJudgeSandSink *judgeSandSink;
    PlayerJudgeSpeedCheckFall *judgeSpeedCheckFall;
    PlayerJudgeStartHipDrop *judgeStartHipDrop;
    PlayerJudgeStartRise *judgeStartRise;
    PlayerJudgeStartRolling *judgeStartRolling;
    PlayerJudgeStartRun *judgeStartRun;
    PlayerJudgeStartSquat *judgeStartSquat;
    PlayerJudgeStartWaterSurfaceRun *judgeStartWaterSurfaceRun;
    PlayerJudgeSlopeSlide *judgeSlopeSlide;
    PlayerJudgePoleClimb *judgePoleClimb;
    PlayerJudgePreInputJump *judgePreInputJump;
    PlayerJudgePreInputCapThrow *judgePreInputCapThrow;
    PlayerJudgePreInputHackAction *judgePreInputHackAction;
    HackCapJudgePreInputHoveringJump *judgeHackCapPreInputHoveringJump;
    HackCapJudgePreInputSeparateThrow *judgeHackCapPreInputSeparateThrow;
    HackCapJudgePreInputSeparateJump *judgeHackCapPreInptuSeparateJump;
    PlayerJudgeWallCatch *judgeWallCatch;
    PlayerJudgeWallCatchInputDir *judgeWallCatchInputDir;
    PlayerJudgeWallHitDown *judgeWallHitDown;
    PlayerJudgeWallHitDownForceRun *judgeWallHitDownForceRun;
    PlayerJudgeWallHitDownRolling *judgeWallHitDownRolling;
    PlayerJudgeWallKeep *judgeWallKeep;

    int field_500; // 0x500
    int field_504; // 0x504
};