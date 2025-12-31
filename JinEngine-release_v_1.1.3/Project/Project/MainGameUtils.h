#pragma once
#include <memory>
#include <glm.hpp>
#include "ObjectManager.h"
#include "BulletSpawnConfig.h"

class BulletObject;
class BulletSpawnerObject;

namespace GameObjectUtils
{
	BulletObject* CreateBulletObject(ObjectManager& om, const glm::vec2& pos, const glm::vec2 scale, const glm::vec2& dir, const std::string&  word, float speed);

	BulletSpawnerObject* CreateBulletSpawnerObject(ObjectManager& om, const BulletSpawnConfig& config);
}

