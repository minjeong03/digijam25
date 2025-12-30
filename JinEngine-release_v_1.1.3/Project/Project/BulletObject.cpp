#include "BulletObject.h"
#include "Engine.h"
BulletObject::BulletObject(const glm::vec2& Dir)
	: Direction(Dir)
{
}
void BulletObject::Init(const EngineContext& engineContext)
{
	soundManager = engineContext.soundManager;

	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]Bullet");

	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	collider->SetUseTransformScale(false);
	collider->SetSize({ 55,83 });
	collider->SetOffset({ glm::vec2(-15,-5.f) });
	SetCollider(std::move(collider));
	SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]flag", { "[CollisionTag]player" });


	BulletTextObject = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), BulletText, TextAlignH::Center, TextAlignV::Middle),
		"[Object]flagText"));
	BulletTextObject->SetRenderLayer("[Layer]UIText");
	BulletTextObject->GetTransform2D().SetPosition(GetWorldPosition());
	BulletTextObject->GetTransform2D().SetScale({ 0.3f,0.3f });
}

void BulletObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void BulletObject::Update(float dt, const EngineContext& engineContext)
{
	BulletActiveTimer += dt;
	
	if (BulletActiveTimer >= BulletActiveTime)
	{
		transform2D.AddPosition(Direction * Speed * dt);
		BulletTextObject->GetTransform2D().SetPosition(GetWorldPosition());
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
		
		BulletTextObject->Kill();
		Kill();

		soundManager->Play("[Sound]OuchSound");
	}
}

void BulletObject::SetWord(const std::string& word)
{
	BulletText = word;
	if (BulletTextObject)
		BulletTextObject->SetText(word);
}
