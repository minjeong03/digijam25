#include "WillDisplayObject.h"
#include "Engine.h"


void WillDisplayObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]WillDisplay");
	SetRenderLayer("[Layer]Cursor");

	currLineText = "";
	currWholeText = currLineText;
	maxCharCountPerLine = 150;
	textObject = static_cast<TextObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(
		std::make_unique<TextObject>(engineContext.renderManager->GetFontByTag("[Font]default"), currWholeText, TextAlignH::Left, TextAlignV::Top),
		"[Object]WillDisplay"));

	const float w = engineContext.windowManager->GetWidth();
	glm::vec2 textBoxSize = { w - 50,180};
	textObject->SetRenderLayer("[Layer]Top");
	textObject->GetTransform2D().SetPosition(GetWorldPosition() + textBoxSize*0.5f* glm::vec2(-1,1));
	textObject->GetTransform2D().SetScale({ 0.4f,0.4f });
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

void WillDisplayObject::PushWord(const std::string& str)
{
	std::string newText = currLineText;
	std::string str1 = str;
	if (currLineText.empty())
	{
		str1 = str;
		newText = str;
	}
	else
	{
		str1 = " " + str;
		newText = currLineText + " " + str;
	}

	if (newText.length() > maxCharCountPerLine)
	{
		currWholeText = currWholeText + "\n" + str;
		currLineText = "";
	}
	else
	{
		currWholeText = currWholeText + str1;
		currLineText = newText;
	}

	textObject->SetText(currWholeText);
}
