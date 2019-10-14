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

Bullet::Bullet()
{
	active = FALSE; // sets the bullet to active upon construction.
	bulletSpeed = 200.0f; // sets the bullets speed as a fixed float value.
	bulletTime = 0.0f; // initalises bullet time as 0.
}

void Bullet::Initalise(Vector2D pos, float startAngle)
{
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	image = pDE->LoadPicture(L"plasma.bmp"); //loads the picture named into the variable named image and draws it on the screen.
	position = pos; // places the variable pos that was passed to this class to position.
	angle = startAngle; // places the variable startAngle that was passed to this class to angle.
	bulletVelocity.setBearing(angle, bulletSpeed); //sets the bullet velocity with an angle and a speed.
	bulletTime = 2.0f; // sets bullet time to 2.0f.
	active = TRUE; // sets the bullet active bool to true.
}

void Bullet::Update(float time)
{
	position = position + bulletVelocity*time; //calculates the bullets new position each frame.
	bulletTime = bulletTime - time; // adjusts the time the bullet will be alive for bring it closer to despawning.
	hitBox.PlaceAt(position, 2); // places the bullets hit box with a radius of 2.
	if (bulletTime <= 0) // if the bulletTime becomes less than or 0 then its set to inactive and disappears from the screen.
	{
		active = FALSE;
	}
}

IShape2D* Bullet::GetShape()
{
	return &hitBox; //returns a reference to the hitbox of the bullet.
}

void Bullet::ProcessCollision(GameObject* pOther)
{
	// logic to test what type of object the ship has colided with and makes the ship inactive accordingly.
	if (typeid(*pOther) == typeid(Spaceship))
	{

	}
	else
	{
		active = FALSE;
	}
}