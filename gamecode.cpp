// GameCode.cpp		


#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include <list>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "GameObject.h"
#include "Rock.h"
#include "spaceship.h"
#include "ObjectManager.h"



Game::Game()
{
   // No-op
}

Game::~Game()
{
   // No-op
}

Game Game::instance;    // Singleton instance

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()

{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err=SUCCESS;

	switch(m_currentState)
	{
	case MENU:

		err= MainMenu();     // Menu at start of game
		break;
	case PAUSED:
		err = PauseMenu();   // Player has paused the game
		break;
	case RUNNING:           // Playing the actual game
		err= Update();
		break;
   case GAMEOVER:
		err = FAILURE;       // Error return causes the window loop to exit
	default:
		// Not a valid state
		err = FAILURE;       // Error return causes the window loop to exit
	}

	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	case MENU:
      // Not needed
		break;
	case PAUSED:
      // Not needed
		break;
	case RUNNING:
      // Not needed
		break;
	}
}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}



// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
   // Any clean up code here 





	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}




// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450,220, L"Paused", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

   // Display menu options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;       // If not selected, should be grey
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;       // Current selection is white
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

   // Get user input
	pInputs->SampleKeyboard();

   // Move choice up and down
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // If player chooses an option ....
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)      // Resume
		{
			ChangeState(RUNNING);  // Go back to running the game
		}
		if(m_menuOption ==1)      // Quit
		{
			EndOfGame();           // Clear up the game
			ChangeState(MENU);     // Go back to the menu
		}

	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	MyDrawEngine::GetInstance()->WriteText(450,220, L"Main menu", MyDrawEngine::WHITE);

	const int NUMOPTIONS = 3;
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Go Fullscreen",L"Exit"};

   // If the window is currently fullscreen, change the second option to read "Go Windowed" instead
	if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
	{
		wcscpy_s( options[1], 15, L"Go Windowed");
	}

   // Display the options
	for(int i=0;i<NUMOPTIONS;i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		MyDrawEngine::GetInstance()->WriteText(450,300+50*i, options[i], colour);
	}

   // Get keyboard input
	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard();
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption<0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption=NUMOPTIONS-1;
	}

   // User selects an option
	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption ==0)          // Play
		{  
			StartOfGame();             // Initialise the game
			ChangeState(RUNNING);      // Run it
		}

		if(m_menuOption ==1)          // Toggle full screen
		{
			if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed();
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen();
			}
		}
		if(m_menuOption ==2)          //Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}


// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
   // Code to set up your game *********************************************
   // **********************************************************************
	Spaceship* pshiptemp = new Spaceship();
	pshiptemp->Initalise(&om);
	om.AddObject(pshiptemp);
	//pobjects.push_back(pshiptemp);
	Rock* procktemp;
	for (int i = 0; i < 11; i++) 
	{
			procktemp = new Rock();
			procktemp->Initalise();
			om.AddObject(procktemp);
			//pobjects.push_back(procktemp);
	}
	theTimer.mark();

	return SUCCESS;
}


// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	//MyInputs* pInputs = MyInputs::GetInstance();
	//pInputs->SampleKeyboard();
	//MySoundEngine* pSE = MySoundEngine::GetInstance();
	//MySoundEngine* pSE2 = MySoundEngine::GetInstance();

	////Vector2D move(-1.5f, 2.0f); // The first value is its X vector the 2nd is the Y.
	//if (pInputs->KeyPressed(DIK_W))
	//{
	//	velocity.setBearing(rotation, 4.0f);
	//	pos = pos + velocity;
	//	//pSE->Play(thrustSound, true);
	//}
	//if (pInputs->KeyPressed(DIK_A))
	//{
	//	rotation = rotation + -0.01f;
	//}
	//if (pInputs->KeyPressed(DIK_S))
	//{
	//	velocity.setBearing(rotation, -4.0f);
	//	pos = pos + velocity;
	//}
	//if (pInputs->KeyPressed(DIK_D))
	//{
	//	rotation = rotation + 0.01f;
	//}
	//if (pInputs->NewKeyPressed(DIK_SPACE))
	//{
	//	pSE->Play(shootSound);
	//}
	//MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	//pDE->DrawAt(pos, image, 1.0f, rotation, 0.0f); // the three variables after image change size, rotation and transparency
	theTimer.mark();
	float time = theTimer.mdFrameTime;
	om.UpdateAll(time);
	om.RenderAll();
	om.CheckAllCollisions();
	om.DeleteInactive();
	//std::list<GameObject*>::iterator it;
	//for (it=pobjects.begin() ; it!=pobjects.end(); it++)
	//{
	//	(*it)->Update(time);
	//	(*it)->Render();
	//}
	//for (int i = 0; i < 11; i++)
	//{
	//	if (i == 0)
	//	{
	//		pobject[i]->Update(time);
	//		pobject[i]->Render();
	//	}
	//	else
	//	{
	//		pobject[i]->Update(time);
	//		pobject[i]->Render();
	//	}
	//}
	static bool escapepressed = true; // Check for entry to pause menu
	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
			ChangeState(PAUSED);
		escapepressed=true;
	}
	else
		escapepressed=false;


   // Your code goes here *************************************************
   // *********************************************************************






   // *********************************************************************
   // *********************************************************************

	return SUCCESS;
}

// Called when the player ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
   // Add code here to tidy up ********************************************
   // *********************************************************************



	
	om.DeleteAll();
	return SUCCESS;
}
void Game::AddObject(GameObject* pNewObject)
{
	pObjects.push_back(pNewObject);
}

