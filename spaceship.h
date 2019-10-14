#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "GameObject.h"
#include "gamecode.h"
#include "Shapes.h"


class Spaceship: public GameObject
{
private:
	Vector2D shipVelocity; //Contains the velocity for the ship both speed and direction
	Vector2D shipAcceleration; //Contains the acceleration for the ship both speed and direction
	Vector2D bulletVelocity; // Contains info on this ships bullet velocity.
	SoundIndex thrustSound; // Sound information for the thrusting of the ship for an external file.
	SoundIndex shootSound; // Sound information for the shooting of the ship for an external file.
	float shootDelayTimer; // Timer for use by the shootdelay calculation.
	float shootdelay; // the actual delay between shots of the ship is stored here.
	ObjectManager* pbulletObjectManager; // pointer of ObjectManager pointing to a bullet.
	Circle2D hitBox; //The collision detection box for the ship.

public:
	Spaceship(); // constructor for spaceship.
	void Initalise(ObjectManager* objectManager); //function to give the ship its inital 
	//values. objectManager contains a pointer to the bullets.
	void Update(float time); //function to update the values relavent to the ship, with time giving update information in regards to the frame time.
	IShape2D* getShape(); // function to return the memory location of a IShape2D.
	void ProcessCollision(GameObject* pOther); // function to process a collion between 2 objects in the game.
};
