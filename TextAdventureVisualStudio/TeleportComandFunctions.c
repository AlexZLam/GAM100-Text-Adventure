/******************************************************************************
filename    GoCommandHandler.c
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "go" user command, which moves
the user from one room to another using defined exits.

******************************************************************************/
#include "stdafx.h" /* NULL, printf */
#include "GoCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetNextRoomIndex, Room_Print, INVALID_DIRECTION_ID */
#include "ItemList.h" /* ItemList_ContainsItem */


/* Handles the "go" command, which moves the user to another room */
void HandleTPCommand(CommandData* command, GameState* gameState, WorldData* worldData)
{
	Room* currentRoom;
	int tpRoomIndex; /* the index of hte next room */


	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}
	tpRoomIndex = atoi(command->noun);

	currentRoom = WorldData_GetRoom(worldData, tpRoomIndex);

	if (currentRoom == NULL)
	{
		printf("That room does not exist.\n");
		return;
	}

	gameState->currentRoomIndex = tpRoomIndex;

	/* print the description of the new room */
	Room_Print(currentRoom);
}