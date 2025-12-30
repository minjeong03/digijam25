#include "WallObject.h"
#include "Engine.h"



void WallObject::Init(const EngineContext& engineContext)
{
	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	SetCollider(std::move(collider));
	SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), 
		"[CollisionTag]wall", 
		{  
		"[CollisionTag]bullet" });
}

void WallObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void WallObject::Update(float dt, const EngineContext& engineContext)
{


}

void WallObject::Draw(const EngineContext& engineContext)
{
	GameObject::Draw(engineContext);
}

void WallObject::Free(const EngineContext& engineContext)
{
	GameObject::Free(engineContext);
}

void WallObject::LateFree(const EngineContext& engineContext)
{
	GameObject::LateFree(engineContext);
}

void WallObject::OnCollision(Object* other)
{

}

