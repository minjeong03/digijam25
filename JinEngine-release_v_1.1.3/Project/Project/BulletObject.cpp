#include "BulletObject.h"
#include "Engine.h"
BulletObject::BulletObject(const glm::vec2& Dir)
	: Direction(Dir)
{
}
void BulletObject::Init(const EngineContext& engineContext)
{
	const float windowWidthHalf = engineContext.windowManager->GetWidth() * 0.5f;
	const float windowHeightHalf = engineContext.windowManager->GetHeight() * 0.5f;
	float scalar = 1.5f;
	boundaryMin = glm::vec2(-windowWidthHalf* scalar, -windowHeightHalf* scalar);
	boundaryMax = glm::vec2(windowWidthHalf * scalar, windowHeightHalf * scalar);

	soundManager = engineContext.soundManager;

	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]Bullet");


	BulletTextObject = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), BulletText, TextAlignH::Center, TextAlignV::Middle),
		"[Object]flagText"));
	BulletTextObject->SetRenderLayer("[Layer]UIText");
	BulletTextObject->GetTransform2D().SetPosition(GetWorldPosition());
	BulletTextObject->GetTransform2D().SetScale({ 0.3f,0.3f });
	BulletTextObject->SetColor({0,0,0,1});

	auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
	collider->SetUseTransformScale(false);
	collider->SetSize(BulletTextObject->GetWorldScale());
	SetCollider(std::move(collider));
	SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), 
		"[CollisionTag]bullet", { "[CollisionTag]player"});

	transform2D.SetScale(BulletTextObject->GetWorldScale() * 1.3f);
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

	
	glm::vec2 pos = transform2D.GetPosition();
	if (pos.x < boundaryMin.x || pos.x > boundaryMax.x || pos.y > boundaryMax.y || pos.y < boundaryMin.y)
	{
		BulletTextObject->Kill();
		Kill();
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
	if (other->GetTag() == "[Object]player")
	{
		BulletTextObject->Kill();
		Kill();
		if (OnCollectedWord)
		{
			OnCollectedWord(BulletText);
		}

		soundManager->Play("[Sound]OuchSound");
	}
}

void BulletObject::SetWord(const std::string& word)
{
	BulletText = word;
	if (BulletTextObject)
		BulletTextObject->SetText(word);
}
