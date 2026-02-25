/******************************************************************************
filename    TalkCommandHandler.c
author      Diana Everman
DP email    diana.everman@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines functions that handle the "talk" user command, which removes
an item from the current room and adds it to the user's inventory.

******************************************************************************/
#include "stdafx.h" /* NULL, printf */
#include "TakeCommandHandler.h" /* Function declarations */
#include "CommandData.h" /* struct CommandData */
#include "GameState.h" /* struct GameState */
#include "WorldData.h" /* WorldData_GetRoom */
#include "Room.h" /* Room_GetItemList */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Add, ItemList_Remove */
#include "Item.h" /* Item_IsCarryable, ItemFunc, Item_GetTalkFunc */


/* Handles the "take" command, which removes an item from the current room and adds it to the user's inventory */
void HandleTalkCommand(CommandData* command, GameState* gameState, WorldData* worldData)
{
	Item* takenItem; /* the item removed from the room and added to the user's inventory */
	Room* room; /* the current room */
	ItemList** roomItemPtr; /* the list of items in the current room */
	ItemFunc talkFunc; /* The function to be called for the given item when it is taken */

	/* safety check on the parameters */
	if ((command == NULL) || (command->noun == NULL) || (gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* retrieve the current room */
	room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

	/* get the current room's item list */
	roomItemPtr = Room_GetItemList(room);
	if (roomItemPtr == NULL)
	{
		return; /* there was no room or item list pointer - something is wrong.  take no action */
	}

	/* find the item in the current room's item list, using the command noun */
	takenItem = ItemList_FindItem(*roomItemPtr, command->noun);
	if (takenItem == NULL)
	{
		/* the item was not found - inform the user of the problem and take no action */
		printf("You do not see a %s here.\n", command->noun);
		return;
	}

	/* inform the user of the successful action */
	printf("You go to talk to the %s.\n", command->noun);

	/* get the "take" function for this item, if any (it is optional) */
	talkFunc = Item_GetTalkFunc(takenItem);
	if (talkFunc != NULL)
	{
		/* call the take function with the Room context, since that's where the item was */
		talkFunc(CommandContext_Item_Room, gameState, worldData);
	}
}