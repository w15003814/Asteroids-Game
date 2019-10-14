#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "spaceship.h"
#include "bullet.h"
#include "explosions.h"


Spaceship::Spaceship()
{
	active = FALSE;
	pbulletObjectManager = nullptr;
}

void Spaceship::Initalise(ObjectManager* objectManager)
{
	pbulletObjectManager = objectManager;
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(L"spaceship.bmp");
	angle = 2.0f;
	position.set(300, 300);
	shipVelocity.setBearing(angle, 0.5f);
	active = TRUE;
}

void Spaceship::Update(float time)
{
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	Vector2D shipFriction;
	shootDelayTimer	= shootDelayTimer - time;
	shootdelay = 0.35f;
	Vector2D front;
	front.setBearing(angle, 28.0f);
	if (pInputs->KeyPressed(DIK_W))
	{
		shipAcceleration.setBearing(angle, 200.0f);
		shipVelocity = shipVelocity + shipAcceleration*time;
		//pSE->Play(thrustSound, true);
	}
	if (pInputs->KeyPressed(DIK_S))
	{
		shipAcceleration.setBearing(angle, -200.0f);
		shipVelocity = shipVelocity + shipAcceleration*time;
		//pSE->Play(thrustSound, true);
	}
	if (pInputs->KeyPressed(DIK_A))
	{
		angle = angle + -0.01f;
	}
	if (pInputs->KeyPressed(DIK_D))
	{
		angle = angle + 0.01f;
	}
	shipFriction = -0.8f * shipVelocity;
	shipVelocity = shipVelocity + shipFriction*time;
	position = position + shipVelocity*time;
	if (pInputs->NewKeyPressed(DIK_SPACE) && shootDelayTimer <= 0)
	{
		Vector2D bulletPosition = front + position;
		Bullet* pNewBullet = new Bullet();
		pNewBullet->Initalise(bulletPosition, angle);
		if (pbulletObjectManager)
		{
			pbulletObjectManager->AddObject(pNewBullet);
		}
		shootDelayTimer = shootdelay;
	}
	hitBox.PlaceAt(position, 10);
}

IShape2D* Spaceship::getShape()
{
	return &hitBox;
}

void Spaceship::ProcessCollision(GameObject* pOther)
{
	Explosions* pNewExplosion = new Explosions();
	active = FALSE;
}