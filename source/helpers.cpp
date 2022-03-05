
#include "helpers.h"
#include "constants.h"

float calcFadeoff(al::LiveActor const* actor, sead::Vector3f pos2)
{
    if (enableFadeoff == false)
        return constants::maxAlpha;
    return (constants::maxDist - al::calcDistance(actor, pos2)) / constants::maxDist * constants::maxAlpha;
}

sead::Matrix34f MatrixFromYawPitchRollTrans(sead::Vector3f euler, sead::Vector3f trans)
{
    float cosY = cosf(euler.y); // Yaw
    float sinY = sinf(euler.y);

    float cosP = cosf(euler.x); // Pitch
    float sinP = sinf(euler.x);

    float cosR = cosf(euler.z); // Roll
    float sinR = sinf(euler.z);

    sead::Matrix34f mat = sead::Matrix34f::ident;

    mat.m[0][0] = cosY * cosR + sinY * sinP * sinR;
    mat.m[1][0] = cosR * sinY * sinP - sinR * cosY;
    mat.m[2][0] = cosP * sinY;

    mat.m[0][1] = cosP * sinR;
    mat.m[1][1] = cosR * cosP;
    mat.m[2][1] = -sinP;

    mat.m[0][2] = sinR * cosY * sinP - sinY * cosR;
    mat.m[1][2] = sinY * sinR + cosR * cosY * sinP;
    mat.m[2][2] = cosP * cosY;

    mat.m[0][3] = trans.x;
    mat.m[1][3] = trans.y;
    mat.m[2][3] = trans.z;

    return mat;
}

sead::Vector3f QuatToEuler(sead::Quatf quat)
{

    f32 x = quat.z;
    f32 y = quat.y;
    f32 z = quat.x;
    f32 w = quat.w;

    f32 t0 = 2.0 * (w * x + y * z);
    f32 t1 = 1.0 - 2.0 * (x * x + y * y);
    f32 roll = atan2f(t0, t1);

    f32 t2 = 2.0 * (w * y - z * x);
    t2 = t2 > 1.0 ? 1.0 : t2;
    t2 = t2 < -1.0 ? -1.0 : t2;
    f32 pitch = asinf(t2);

    f32 t3 = 2.0 * (w * z + x * y);
    f32 t4 = 1.0 - 2.0 * (y * y + z * z);
    f32 yaw = atan2f(t3, t4);

    return sead::Vector3f(yaw, pitch, roll);
}