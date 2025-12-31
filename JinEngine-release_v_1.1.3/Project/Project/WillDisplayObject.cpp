#include "WillDisplayObject.h"
#include "Engine.h"


void WillDisplayObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]WillDisplay");
	SetRenderLayer("[Layer]Cursor");

	textObject = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
		std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), u8"안녕하세요", TextAlignH::Left, TextAlignV::Top),
		"[Object]WillDisplay"));

	const float w = engineContext.windowManager->GetWidth();
	glm::vec2 textBoxSize = { w - 100,180};
	textObject->SetRenderLayer("[Layer]Top");
	textObject->GetTransform2D().SetPosition(GetWorldPosition() + textBoxSize*0.5f* glm::vec2(-1,1));
	textObject->GetTransform2D().SetScale({ 0.3f,0.3f });
	textObject->SetColor(glm::vec4(0, 0, 0, 1));
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
