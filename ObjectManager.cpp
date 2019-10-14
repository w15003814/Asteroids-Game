#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "spaceship.h"
#include "bullet.h"
#include "gametimer.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include <algorithm>

ObjectManager::ObjectManager()
{

}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pobjects.push_back(pNewObject);
}

void ObjectManager::UpdateAll(float time)
{
	std::list<GameObject*>::iterator it;
	for (it = pobjects.begin(); it != pobjects.end(); it++)
	{
			(*it)->Update(time);
	}
}

void ObjectManager::RenderAll()
{
	std::list<GameObject*>::iterator it;
	for (it = pobjects.begin(); it != pobjects.end(); it++)
	{
			(*it)->Render();
	}
}

void ObjectManager::DeleteAll()
{
	for (GameObject* &nextObjectPointer : pobjects) // The & is critical. Check.
	{
		if (nextObjectPointer->isActive() == false)
		{
			delete nextObjectPointer;
			nextObjectPointer = nullptr; // Always do this when deleting! 
		}
	}
	pobjects.clear();
}

void ObjectManager::DeleteInactive() 
{
	for (GameObject* &nextObjectPointer : pobjects) // The & is critical. Check.
	{
		if (nextObjectPointer->isActive() == false)
		{
			delete nextObjectPointer;
			nextObjectPointer = nullptr; // Always do this when deleting! 
		}
	}
	auto it = std::remove(pobjects.begin(), pobjects.end(), nullptr);
	pobjects.erase(it, pobjects.end());
}

void ObjectManager::CheckAllCollisions()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = pobjects.begin(); it1 != pobjects.end(); it1++)
	{
		for (it2 = std::next(it1);it2 != pobjects.end(); it2++)
		{
			if ((*it1)->getShape()->Intersects(*((*it2)->getShape())))
			{
				(*it1)->ProcessCollision((*it2));
				(*it2)->ProcessCollision((*it1));
				// Do something 
			}
		}
	}
}