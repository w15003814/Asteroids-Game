#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "explosions.h"

Explosions::Explosions()
{
	active = FALSE;
}

void Explosions::Render()
{
	for (int i = 0; i <= 7; i++)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, picArray[i], 1.0f, angle, 0.0f);
	}
}
void Explosions::Update(float time)
{
	currentImage = currentImage + 5.0f * time;
}