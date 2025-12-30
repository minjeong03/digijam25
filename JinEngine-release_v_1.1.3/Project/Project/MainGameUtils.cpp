#include "MainGameUtils.h"
#include "BulletObject.h"
#include "BulletSpawnerObject.h"

namespace GameObjectUtils
{
	BulletObject* CreateBulletObject(ObjectManager& om, const glm::vec2& pos, const glm::vec2 scale)
	{
		std::unique_ptr<BulletObject> Bullet = std::make_unique<BulletObject>();
		BulletObject* BulletPtr = Bullet.get();
		Bullet->SetRenderLayer("[Layer]Player");
		Bullet->GetTransform2D().SetDepth(00.0f);
		Bullet->GetTransform2D().SetScale(scale);
		Bullet->GetTransform2D().SetPosition(pos);
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
