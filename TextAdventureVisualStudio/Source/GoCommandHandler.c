/******************************************************************************
filename    GoCommandHandler.c
author      Matthew Picioccio, Diana Everman
DP email    mattpic@digipen.edu, diana.everman@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "go" user command, which moves
the user from one room to another using defined exits. Edited to add some conditional
exits.

******************************************************************************/
#include "stdafx.h" /* NULL, printf */
#include "GoCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetNextRoomIndex, Room_Print, INVALID_DIRECTION_ID */
#include "ItemList.h" /* ItemList_ContainsItem */

#include "GameFlags.h" /* GameFlags_IsInList, GameFlags_Add */


/* Handles the "go" command, which moves the user to another room */
void HandleGoCommand(CommandData* command, GameState* gameState, WorldData* worldData)
{
	Room* currentRoom; /* the room we are currently in */
	int nextRoomIndex; /* the index of hte next room */


	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	//built-in shortcuts for cardinal directions
	if (strcmp(command->noun,"n") == 0)
	{
		strcpy_s(command->noun, MAX_COMMAND_NOUN_LENGTH, "north");
	}
	else if (strcmp(command->noun, "s") == 0)
	{
		strcpy_s(command->noun, MAX_COMMAND_NOUN_LENGTH, "south");
	}
	else if (strcmp(command->noun,  "e") == 0)
	{
		strcpy_s(command->noun, MAX_COMMAND_NOUN_LENGTH, "east");
	}
	else if (strcmp(command->noun, "w") == 0)
	{
		strcpy_s(command->noun, MAX_COMMAND_NOUN_LENGTH, "west");
	}
	
	/* get the current room, based on the user state */
	currentRoom = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

	/* get the next room index, based on the noun used with "go" */
	if (Room_GetNextRoomIndex(currentRoom, command->noun, &nextRoomIndex) == false)
	{
		/* there is no exit in that direction, so let the user know and take no other action */
		printf("You cannot move %s.\n", command->noun);
		return;
	}

	//don't let player go through certain exits if they don't have the right item
	if (gameState->currentRoomIndex == 2 && nextRoomIndex == 3)
	{
		if (ItemList_FindItem(gameState->inventory, "egg") == NULL && !GameFlags_IsInList(gameState->gameFlags, "eggDoorOpened"))
		{
			printf("The egg-shaped door does not budge.\n");
			return;
		}
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "eggDoorOpened");

	}
	else if (gameState->currentRoomIndex == 2 && nextRoomIndex == 5)
	{
		if (ItemList_FindItem(gameState->inventory, "orb") == NULL && !GameFlags_IsInList(gameState->gameFlags, "orbDoorOpened"))
		{
			printf("The door has a magical aura to it. It does not budge.\n");
			return;
		}
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "orbDoorOpened");
	}
	else if (gameState->currentRoomIndex == 4 && nextRoomIndex == 6)
	{
		if (ItemList_FindItem(gameState->inventory, "key") == NULL && !GameFlags_IsInList(gameState->gameFlags, "keyDoorOpened"))
		{
			printf("The door has a keyhole. It does not budge.\n");
			return;
		}
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "keyDoorOpened");
	}

	/* update the game state to move to the new room */
	gameState->currentRoomIndex = nextRoomIndex;

	/* output the successful action */
	printf("You move %s.\n\n", command->noun);

	/* get the new room */
	currentRoom = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

	/* print the description of the new room */
	Room_Print(currentRoom);
}