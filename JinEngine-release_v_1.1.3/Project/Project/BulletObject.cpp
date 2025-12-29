#include "BulletObject.h"
#include "Engine.h"
void BulletObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]Bullet");

	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	collider->SetUseTransformScale(false);
	collider->SetSize({ 55,83 });
	collider->SetOffset({ glm::vec2(-15,-5.f) });
	SetCollider(std::move(collider));
	SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]flag", { "[CollisionTag]player" });
}

void BulletObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void BulletObject::Update(float dt, const EngineContext& engineContext)
{
	BulletActiveTimer += dt;
	
	if (BulletActiveTimer >= 3.0f)
	{
		transform2D.AddPosition(glm::vec2(-10 * dt, 10 * dt));
	}

}

void BulletObject::Draw(const EngineContext& engineContext)
{
	GameObject::Draw(engineContext);
}

void BulletObject::Free(const EngineContext& engineContext)
{
	GameObject::Free(engineContext);
}

void BulletObject::LateFree(const EngineContext& engineContext)
{
	GameObject::LateFree(engineContext);
}

void BulletObject::OnCollision(Object* other)
{
	if (other->GetTag()=="[Object]player")
	{
		
	}
}
