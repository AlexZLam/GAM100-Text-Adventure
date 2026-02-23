/******************************************************************************
filename    TeleportCommandFunctions.c
author      Alexander Lam
DP email    alexander.lam@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
Teleports a player to a given room index. Moslty for debugging

******************************************************************************/
#include "stdafx.h" /* NULL, printf */
#include "GoCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetNextRoomIndex, Room_Print, INVALID_DIRECTION_ID */
#include "ItemList.h" /* ItemList_ContainsItem */


/* Handles the "TP" command, which moves the user to another room */
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