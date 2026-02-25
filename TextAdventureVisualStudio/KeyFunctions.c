/******************************************************************************
filename    KeyFunctions.c
author      Alexander Lam
DP email    alexander.lam@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the functions to create the key which is used to open a door

******************************************************************************/
#include "stdafx.h"
#include "KeyFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"

typedef struct WorldData WorldData;

void Key_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
	/* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(worldData);

	/* safety check on the parameters */
	if (gameState == NULL)
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the gold piece has already been scored */
	if (!GameFlags_IsInList(gameState->gameFlags, "keyScored"))
	{
		/* tell the user that something cool happens when they pick up the gold piece */
		printf("Where should I put this?\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 10);
		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "keyScored");
	}
}

void Key_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the brick out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("You must have the key before you can use it.\n");
		return;
	}
	printf("This a key from the little wizard.\n");
}

Item* Key_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("key", "the riddle key\n", true, Key_Use, Key_Take, NULL);
}