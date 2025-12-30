#include "RealPlayer.h"
#include "Engine.h"

void RealPlayer::Init(const EngineContext& engineContext)
{
    windowManager = engineContext.windowManager;
    transform2D.SetScale(glm::vec2(100.f));
    transform2D.SetPosition(glm::vec2(-300, 0));
    SetMesh(engineContext, "[EngineMesh]default");
    SetMaterial(engineContext, "[Material]Animation");
    SpriteSheet* sheet = engineContext.renderManager->GetSpriteSheetByTag("[SpriteSheet]MainCharacter");
    sheet->AddClip("[Clip]IdleFront", { 0,1 }, 0.15f, true);
    sheet->AddClip("[Clip]RunningRight", {16,17,18,19}, 0.08f, true);
    sheet->AddClip("[Clip]RunningFront", { 12,13,14,15 }, 0.08f, true);
    sheet->AddClip("[Clip]RunningBack", { 20, 21, 22 ,23 }, 0.08f, true);
    AttachAnimator(sheet, 0.08f);
    auto collider = std::make_unique<AABBCollider>(this, glm::vec2(1.0, 1.0));
    collider->SetUseTransformScale(false);
    collider->SetSize({ 90,70 });
    collider->SetOffset({ glm::vec2(0,10.f) });
    SetCollider(std::move(collider));
    SetCollision(engineContext.stateManager->GetCurrentState()->GetObjectManager(), "[CollisionTag]player",
        { "[CollisionTag]bullet" });
}

void RealPlayer::LateInit(const EngineContext& engineContext)
{

}

void RealPlayer::Update(float dt, const EngineContext& engineContext)
{
 
    //TODO : 대각선 이동속도 변경

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

    if (engineContext.inputManager->IsKeyDown(KEY_W))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(0, 350 * dt));
    }
    if (engineContext.inputManager->IsKeyDown(KEY_S))
    {
        checkIdle = false;
        checkIdle_prevFrame = false;
        transform2D.AddPosition(glm::vec2(0, -350 * dt));
    }

    glm::vec2 colliderHalfSize = static_cast<AABBCollider*>(GetCollider())->GetHalfSize();
    glm::vec2 pos = transform2D.GetPosition();
    if (pos.x - colliderHalfSize.x < -windowManager->GetWidth() * 0.5f) // left
    {
        transform2D.SetPosition(glm::vec2(-windowManager->GetWidth() * 0.5f + colliderHalfSize.x, pos.y));
    }
    if (pos.x + colliderHalfSize.x > windowManager->GetWidth() * 0.5f) // right
    {
        glm::vec2 pos = transform2D.GetPosition();
        transform2D.SetPosition(glm::vec2(windowManager->GetWidth() * 0.5f - colliderHalfSize.x, pos.y));
    }
    if (pos.y + colliderHalfSize.y > windowManager->GetHeight() * 0.5f) // top
    {
        glm::vec2 pos = transform2D.GetPosition();
        transform2D.SetPosition(glm::vec2(pos.x, +windowManager->GetHeight() * 0.5f - colliderHalfSize.y));
    }
    if (pos.y - colliderHalfSize.y < -windowManager->GetHeight() * 0.5f) // bot
    {
        glm::vec2 pos = transform2D.GetPosition();
        transform2D.SetPosition(glm::vec2(pos.x, -windowManager->GetHeight() * 0.5f + colliderHalfSize.y));
    }

    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_A))
    {
        SetFlipUV_X(true);
        spriteAnimator->PlayClip("[Clip]RunningRight");
    }
    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_D))
    {
        SetFlipUV_X(false);
        spriteAnimator->PlayClip("[Clip]RunningRight");
    }

    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_W))
    {
  
        spriteAnimator->PlayClip("[Clip]RunningBack");
    }
    if (spriteAnimator && engineContext.inputManager->IsKeyPressed(KEY_S))
    {

        spriteAnimator->PlayClip("[Clip]RunningFront");
    }



    if (spriteAnimator && checkIdle && !checkIdle_prevFrame)
    {
        checkIdle_prevFrame = true;
        spriteAnimator->PlayClip("[Clip]IdleFront");
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
    if (other->GetTag() == "[Object]wall")
    {
        //glm::vec2 otherPos = other->GetTransform2D().GetPosition();
        //glm::vec2 colliderHalfSize = static_cast<AABBCollider*>(GetCollider())->GetHalfSize();
        //glm::vec2 pos = transform2D.GetPosition();
        //if(otherPos.x < -windowManager->GetWidth() * 0.5f) // left
        //{
        //    transform2D.SetPosition(glm::vec2(-windowManager->GetWidth() * 0.5f + colliderHalfSize.x, pos.y));
        //}
        //else if(otherPos.x > windowManager->GetWidth() * 0.5f) // right
        //{
        //    transform2D.SetPosition(glm::vec2(windowManager->GetWidth() * 0.5f - colliderHalfSize.x, pos.y));
        //}
        //else if (otherPos.y > windowManager->GetHeight() * 0.5f) // top
        //{
        //    transform2D.SetPosition(glm::vec2(pos.x, +windowManager->GetHeight() * 0.5f - colliderHalfSize.y));
        //}
        //else if (otherPos.y < -windowManager->GetHeight() * 0.5f) // bot
        //{
        //    transform2D.SetPosition(glm::vec2(pos.x, -windowManager->GetHeight() * 0.5f + colliderHalfSize.y));
        //}
    }
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
