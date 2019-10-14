#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "Rock.h"
#include "cstdlib"


Rock::Rock()
{
	active = FALSE;
}

void Rock::Initalise()
{
	angle = rand() % 628 / 100.0f;
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(L"rock1.bmp");
	position.setBearing(rand() % 628/100.0f, rand() % 600 + 400);
	rockVelocity.setBearing(rand() % 628 / 100.0f, 4.0f);
	active = TRUE;
}


void Rock::Update(float time)
{
	position = position + rockVelocity*time;
	hitBox.PlaceAt(position, 50);
}

IShape2D* Rock::getShape()
{
	return &hitBox;
}

void Rock::ProcessCollision(GameObject* pOther)
{
	active = FALSE;
}