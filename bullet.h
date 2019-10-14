#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "GameObject.h"

//A GameObeject Sub Class for the bullets in the game
class Bullet : public GameObject
{
private:
	Vector2D bulletVelocity; //Contains the velocity for the bullet both speed and direction
	float bulletSpeed; //Value to hold the Speed of the bullet
	float bulletTime; //Value to hold the length of time  between bullets being fired.
	Circle2D hitBox; // The collision detection box for the bullet.

public:
	Bullet(); //Constructor for Bullet
	void Initalise(Vector2D pos, float startAngle); //function to give the bullet its inital 
	//values such as its position speed angle etc.
	void Update(float time); //function to update the values relavent to the bullet, with time giving update information in regards to the frame time.
	IShape2D* GetShape(); // function to return the memory location of a IShape2D.
	void ProcessCollision(GameObject* pOther); // function to process a collion between 2 objects in the game.
};