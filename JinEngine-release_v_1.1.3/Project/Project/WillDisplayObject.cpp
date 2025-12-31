#include "WillDisplayObject.h"
#include "Engine.h"


void WillDisplayObject::Init(const EngineContext& engineContext)
{
	SetMesh(engineContext, "[EngineMesh]default");
	SetMaterial(engineContext, "[Material]WillDisplay");
	SetRenderLayer("[Layer]Cursor");

	currWholeText = "";
	lines.push_back(currWholeText);
	maxCharCountPerLine = 175;
	maxLinesPerDisplay = 8;
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
	if (lines.size() >= maxLinesPerDisplay - 1)
	{
		textObject->GetTransform2D().AddPosition(
			glm::vec2(0, 1) * scrollSpeed * dt
		);
	}
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
	std::string newText = lines.back();
	std::string str1 = str;
	if (newText.empty())
	{
		str1 = str;
		newText = str;
	}
	else
	{
		str1 = " " + str;
		newText = newText + " " + str;
	}

	if (newText.length() > maxCharCountPerLine)
	{
		currWholeText = currWholeText + "\n" + str;
		lines.push_back(str);
	}
	else
	{
		currWholeText = currWholeText + str1;
		lines.pop_back();
		lines.push_back(newText);
	}

	textObject->SetText(currWholeText);
}
