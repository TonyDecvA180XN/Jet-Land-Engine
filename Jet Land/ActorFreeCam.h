#pragma once



#include "Actor.h"
#include "Camera.h"

class ActorFreeCam : public Actor
{
public:
    ActorFreeCam();
    ~ActorFreeCam();

    VOID Update(BOOL on_axis);

    Camera * GetCamera();
    VOID SetCamera(Camera * camera);

	VOID Move(DirectX::XMVECTOR move);

	VOID Look(FLOAT x, FLOAT y);

//    VOID Pitch(FLOAT angle);
//    VOID RotateY(FLOAT angle);
//
//private:
//    VOID Reorthonormalize();

private:
    Camera * camera_;
};

