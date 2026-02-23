/******************************************************************************
filename    EggFunctions.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "egg".

******************************************************************************/
#include "stdafx.h" /* NULL, UNREFERENCED_PARAMETER */
#include "EggFunctions.h" /* Function declarations */
#include "GameState.h" /* struct GameState, GameState_ChangeScore, GameState_EndGame */
#include "GameFlags.h" /* GameFlags_IsInList, GameFlags_Add */
#include "Item.h" /* Item_Create */
#include "CommandData.h" /* struct CommandData */
#include "Room.h" /* struct Room, Room_GetItemList */
#include "WorldData.h" /* WorldData_GetRoom */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Add, ItemList_Remove */

#include "RoomExit.h" // RoomExit_Free
#include "WorldDataFactory.h" /*  Room4_Build_DeadWizard, Room4_Build_SavedWizard */

typedef struct WorldData WorldData;


/* Helper: The action performed when the egg is taken. */
void Egg_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the egg has already been scored */
	if (!GameFlags_IsInList(gameState->gameFlags, "eggScored"))
	{
		/* tell the user that something cool happens when they pick up the egg */
		printf("The fragile egg shines in the dim light as you put it in your pocket.\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 25);
		/* the egg has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "eggScored");
	}
	// hand portal: take in room 5 to blow up room 6
	if (gameState->currentRoomIndex == 5)
	{
		//blow up room 6: kill wizard if hes in room 4, take away room 4 east exit and update room 4 description
		if (!GameFlags_IsInList(gameState->gameFlags, "wizardMoved"))
		{
			WorldData_SetRoom(worldData, 4, Room4_Build_DeadWizard());
		}
		else
		{
			WorldData_SetRoom(worldData, 4, Room4_Build_SavedWizard());
		}
		//Room *room4 = WorldData_GetRoom(worldData, 4);
		//RoomExit *roomExitListPtr = room4->roomExitHead;
		//RoomExit_Free(&roomExitListPtr);

	}
}


/* Helper: The action performed when the egg is dropped. */
void Egg_Drop(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* don't drop the egg!  if you do, it shatters and you can't finish the game */
	GameState_EndGame(gameState, "The egg shatters, and you know that you can never leave...\n");

	/* 
	Note: if we wanted to really implement "shattering", we'd remove the egg from the room where it was dropped.
	However, that's not needed, as we quit the game and the user can't look at the room anymore.
	*/
}

/* Helper: The action performed when the egg is dropped. */
void Egg_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	// indiana jones
	printf("You replace the gold piece on the pedestal with the egg. The pedestal rises up slightly, then sinks down. \nThere is a mechanical thunk, and a whirring, ticking sound.\n");
	printf("What do you do? 1: Put the coin back. 2: Leave it as is.\n");
	int ans = 0;
	scanf_s("%d", &ans);
	printf("The whirring stops, and for a moment, everything is quiet. (Enter to continue)");
	scanf_s("");
	if (ans == 1)
	{
		printf("The tense silence dissapates. \n");
	}
	else if (ans == 2)
	{
		printf("The tense silence dissapates. You made the right choice, and now you have the gold piece!\n");

		Item* takenItem; /* the item removed from the room and added to the user's inventory */
		Room* room; /* the current room */
		ItemList** roomItemPtr; /* the list of items in the current room */

		/* retrieve the current room */
		room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

		/* get the current room's item list */
		roomItemPtr = Room_GetItemList(room);
		if (roomItemPtr == NULL)
		{
			return; /* there was no room or item list pointer - something is wrong.  take no action */
		}

		/* find the item in the current room's item list, using the command noun */
		takenItem = ItemList_FindItem(*roomItemPtr, "gold piece");
		/* remove the item from the room */
		*roomItemPtr = ItemList_Remove(*roomItemPtr, takenItem);

		/* add the item to the user's inventory */
		gameState->inventory = ItemList_Add(gameState->inventory, takenItem);

		/* tell the user that something cool happens when they pick up the gold piece */
		printf("The gold piece burns in your hand.  You're rich!\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 5);

	}
	return;
}

/* Build a "egg" object */
Item* Egg_Build()
{
	/* Create a "egg" item, using the functions defined in this file */
	return Item_Create("egg", "The fragile egg is beautiful iridescent green, and it is obviously very valuable. Its large, but lighter than it looks.\n", true, NULL, Egg_Take, Egg_Drop);
}