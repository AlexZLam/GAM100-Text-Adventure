/******************************************************************************
filename    GoldPieceFunctions.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the functions to create a specific item, the "gold piece".

******************************************************************************/
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "WorldData.h" /* WorldData_GetRoom */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "GoldPieceFunctions.h"

typedef struct WorldData WorldData;


/* Helper: The action performed when the gold piece is taken. */
void GoldPiece_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}
	Room* room;
	room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);
	if (gameState->currentRoomIndex == 3)
	{
		Room_SetDescription(room, "This is room 3. There is skeleton in the corner of the room. He looks very tired. There is a door north\n");
	}
	if (gameState->currentRoomIndex == 6)
	{
		// indiana jones
		printf("You take the gold piece from the pedestal. The pedestal rises up slightly. \nThere is a mechanical thunk, and a whirring, ticking sound.\n");
		printf("What do you do? 1: Put the coin back. 2: Leave it as is.\n");
		int ans = 0;
		scanf_s("%d", &ans);
		while (getchar() != '\n');
		printf("The whirring stops, and for a moment, everything is quiet. (Enter to continue)");
		scanf_s("");
		while (getchar() != '\n');
		if (ans == 1)
		{
			printf("The tense silence dissapates. You made the right choice.\n");
		}
		else if (ans == 2)
		{
			GameState_EndGame(gameState, "Then, the room explodes.\n");
		}
		return;
	}
	else
	{
		/* tell the user that something cool happens when they pick up the gold piece */
		printf("The gold piece burns in your hand. You're rich!\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 5);

	}
}


/* Build a "gold piece" object */
Item* GoldPiece_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("gold piece", "A small piece of gold. It's got a nice weight - not too heavy, not too light.\n", true, NULL, GoldPiece_Take, NULL);
}