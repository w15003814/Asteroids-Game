 #pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "Shapes.h"

//parent class that contains methods and variables useful to all objects within the game.
class GameObject
{
protected:
	Vector2D position; //contains infromation regarding the position/location for the object on the game screen.
	float angle; //variable to store the angle that the object will be facing.
	bool active; // bool to represent if an object is active or not if it is active it is rendered on the screen.
	PictureIndex image; // variable to store the picture to be used as the sprite for the game object.


public:
	GameObject(); // Constructor for GameObject.
	bool isActive(); // retrives method to retrive if the object is active.
	virtual void Render(); // method to draw the object in the game.
	virtual void Update(float time)=0; // function to update the values relavent to the bullet, with time giving
	//update information in regards to the frame time. But in GameObject it is real virtual in order to allow for
	//each object to have their own version of it.
	virtual IShape2D* getShape()=0; // function to get the shape that object is going to use. But in GameObject it is
	//real virtual in order to allow for each object to have their own version of it.
	virtual void ProcessCollision( GameObject* pOther )=0; // function that tells the objects what to do if the objects
	//collide with one another. But in GameObject it is real virtual in order to allow for
	//each object to have their own version of it.
};
