#include "RealPlayer.h"
#include "Engine.h"

void RealPlayer::Init(const EngineContext& engineContext)
{
    transform2D.SetScale(glm::vec2(100.f));
    SetMesh(engineContext, "[EngineMesh]default");
    SetMaterial(engineContext, "[Material]Animation");
    SpriteSheet* sheet = engineContext.renderManager->GetSpriteSheetByTag("[SpriteSheet]MainCharacter");
    sheet->AddClip("[Clip]Idle", { 0,1 }, 0.15f, true);
    sheet->AddClip("[Clip]Running", {16,17,18,19}, 0.08f, true);
    AttachAnimator(sheet, 0.08f);
    auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
    collider->SetUseTransformScale(false);
    collider->SetSize({ 90,70 });
    collider->SetOffset({ glm::vec2(0,10.f) });
    SetCollider(std::move(collider));
    SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]player", { "[CollisionTag]flag" });
}

void RealPlayer::LateInit(const EngineContext& engineContext)
{

}

void RealPlayer::Update(float dt, const EngineContext& engineContext)
{
 

    checkIdle = true;
    if (engineContext.inputManager->IsKeyDown(KEY_A))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(-350 * dt, 0));
    }
    if (engineContext.inputManager->IsKeyDown(KEY_D))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(350 * dt, 0));
    }

    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_A))
    {
        SetFlipUV_X(true);
        spriteAnimator->PlayClip("[Clip]Running");
    }
    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_D))
    {
        SetFlipUV_X(false);
        spriteAnimator->PlayClip("[Clip]Running");
    }

    if (spriteAnimator && checkIdle && !checkIdle_prevFrame)
    {
        checkIdle_prevFrame = true;
        spriteAnimator->PlayClip("[Clip]Idle");
    }

}

void RealPlayer::Draw(const EngineContext& engineContext)
{


}

void RealPlayer::Free(const EngineContext& engineContext)
{
  
}

void RealPlayer::LateFree(const EngineContext& engineContext)
{

}

void RealPlayer::OnCollision(Object* other)
{
    //if (other->GetTag() == "enemyBullet")
    //{
    //    other->Kill();
    //}
    //if (other->GetTag() == "enemy" && this < other)
    //{
    //    glm::vec2 halfSize = GetWorldScale() / glm::vec2(2);
    //    glm::vec2 otherHalfSize = other->GetWorldScale() / glm::vec2(2);

    //    glm::vec2 center = GetWorldPosition() + halfSize;
    //    glm::vec2 otherCenter = other->GetWorldPosition() + otherHalfSize;

    //    glm::vec2 delta = center - otherCenter;
    //    glm::vec2 overlap = halfSize + otherHalfSize - glm::abs(delta);

    //    if (overlap.x > 0 && overlap.y > 0)
    //    {
    //        glm::vec2 correction = { 0, 0 };

    //        if (overlap.x < overlap.y)
    //        {
    //            correction.x = (delta.x > 0 ? overlap.x : -overlap.x) * 0.5f;
    //        }
    //        else
    //        {
    //            correction.y = (delta.y > 0 ? overlap.y : -overlap.y) * 0.5f;
    //        }
    //        if (!static_cast<Enemy*>(other)->CheckIdle())
    //            other->GetTransform2D().AddPosition(-correction);
    //        if (!checkIdle)
    //            GetTransform2D().AddPosition(correction);
				//
    //    }
    //}
    //if (other->GetTag() == "StartButton" || other->GetTag() == "QuitButton")
    //{
    //    other->SetColor({ 0.3,0.3,0.3,1.0 });
    //}
}

bool RealPlayer::CheckIdle()
{
    return checkIdle;
}
