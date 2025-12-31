#pragma once
#include <glm.hpp>


struct BulletSpawnConfig
{
    glm::vec2 InitPos;
    float CircleRadius = 0.0f; // when determine bullets pos
    float Delay = 0.0f; // delayed time in sec to activate spawning
    float PatternAngleSpacing = 0.0f; // delta angle (degree) when determine bullets pos
    float AngleVariance = 0.0f; // in degree, tweak the angle a bit when spawn bullet
    float SpawnInterval = 0.0f; // time in sec between spawning
    float Lifetime = 0.0f; // life time in sec after activation
    float StartAngle = 0.0f; // degree
    float EndAngle = 0.0f; // degree
    std::string WordDataFilepath;
    float BulletSpeed = 150;


};
