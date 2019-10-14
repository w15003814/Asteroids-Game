#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "GameObject.h"
#include <list>

// class to handle the storage of all the GameObjects within a list and to allow for handling of the objects in the list.
class ObjectManager
{
private:
	std::list<GameObject*> pobjects;// the list stores a pointer to the gameobjects for later access.
	GameTimer theTimer;// variable for the frame time within the game.

public:
	ObjectManager(); // constructor for ObjectManager.
	void AddObject(GameObject* pNewObject); // method to add a new object to the list, 
	// pNewObject is a pointer to the object that is wanting to be added.
	void UpdateAll(float time); // updates all of the objects in the list at oncec using a single method. with time being the frame time.
	void RenderAll(); // renders all of the object within the list one by one instead of one by one.
	void DeleteAll(); // deletes all the objects within the list.
	void DeleteInactive(); // deletes only the objects which boolean value is set to false for inactive.
	void CheckAllCollisions(); // checks all of the collisions within the game waiting for one to occur.
};