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
#include "rock.h"
#include "GameObject.h"

GameObject::GameObject()
{

}

void GameObject::Render()
{
	if (active == TRUE)
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		pDE->DrawAt(position, image, 1.0f, angle, 0.0f);
	}
	else
	{

	}
}

bool GameObject::isActive()
{
	return active;
}