#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "GameObject.h"


class Explosions : public GameObject
{
private:
	//PictureIndex picArray[];
	float currentImage;

public:
	Explosions();
	void Render();
	void Update(float time);
};