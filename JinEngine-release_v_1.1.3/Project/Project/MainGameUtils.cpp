#include "MainGameUtils.h"
#include "BulletObject.h"
#include "BulletSpawnerObject.h"

namespace GameObjectUtils
{
	BulletObject* CreateBulletObject(ObjectManager& om, const glm::vec2& pos, const glm::vec2 scale, const glm::vec2& dir, const std::string& word, float speed)
	{
		std::unique_ptr<BulletObject> Bullet = std::make_unique<BulletObject>(dir);
		BulletObject* BulletPtr = Bullet.get();
		Bullet->SetRenderLayer("[Layer]Player");
		Bullet->GetTransform2D().SetDepth(00.0f);
		Bullet->GetTransform2D().SetScale(scale);
		Bullet->GetTransform2D().SetPosition(pos);
		Bullet->SetWord(word);
		Bullet->Speed = speed;
		om.AddObject(std::move(Bullet), "[Object]bullet");
		return BulletPtr;
	}

	BulletSpawnerObject* CreateBulletSpawnerObject(ObjectManager& om, const BulletSpawnConfig& config)
	{
		std::unique_ptr<BulletSpawnerObject> Spawner = std::make_unique<BulletSpawnerObject>(config);
		BulletSpawnerObject* Ptr = Spawner.get();
		om.AddObject(std::move(Spawner), "[Object]BulletSpawner");
		return Ptr;
	}
}
