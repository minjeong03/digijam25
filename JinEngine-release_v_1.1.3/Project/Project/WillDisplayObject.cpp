#include "WillDisplayObject.h"
#include "Engine.h"


void WillDisplayObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]WillDisplay");
	SetRenderLayer("[Layer]Cursor");

	textObject = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
		std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), "", TextAlignH::Center, TextAlignV::Middle),
		"[Object]WillDisplay"));
	textObject->SetRenderLayer("[Layer]Top");
	textObject->GetTransform2D().SetPosition(GetWorldPosition());
	textObject->GetTransform2D().SetScale({ 0.3f,0.3f });
}

void WillDisplayObject::LateInit(const EngineContext& engineContext)
{
	GameObject::LateInit(engineContext);
}

void WillDisplayObject::Update(float dt, const EngineContext& engineContext)
{
}

void WillDisplayObject::Draw(const EngineContext& engineContext)
{
	GameObject::Draw(engineContext);
}

void WillDisplayObject::Free(const EngineContext& engineContext)
{
	GameObject::Free(engineContext);
}

void WillDisplayObject::LateFree(const EngineContext& engineContext)
{
	GameObject::LateFree(engineContext);
}

void WillDisplayObject::OnCollision(Object* other)
{
}
