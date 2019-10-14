#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "GameObject.h"

// A GameObeject Sub Class for the rocks in the game
class Rock : public GameObject
{
private:
	Vector2D rockVelocity; //Contains the velocity for the rock both speed and direction
	Vector2D rockAcceleration; //Contains the acceleration for the rock both speed and direction
	Circle2D hitBox; //The collision detection box for the rock.


public:
	Rock(); // constructor for the rock class.
	void Initalise(); //function to give the rock its inital 
	//values such as its position speed angle etc.
	void Update(float time); //function to update the values relavent to the rock, with time giving update information in regards to the frame time.
	IShape2D* getShape(); // function to return the memory location of a IShape2D.
	void ProcessCollision(GameObject* pOther); // function to process a collion between 2 objects in the game.
};

