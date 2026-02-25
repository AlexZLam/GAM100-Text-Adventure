/******************************************************************************
filename    PortalFunctions.c
author      Diana Everman
DP email    diana.everman@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the functions of the small portal in room 5.

******************************************************************************/
#include "stdafx.h"
#include "OrbFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "WorldData.h" /* WorldData_GetRoom */

typedef struct WorldData WorldData;
bool portalBoom = false;

void Portal_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}
	if (context != CommandContext_Item_Room)
	{
		/* the user doesn't see the portal - inform the user of the problem and take no action */
		printf("You don't see a portal in this room.\n");
		return;
	}
	if (portalBoom)
	{
		printf("This dissapeared remember?\n");
		return;
	}
	printf("Looking through the portal, you see the egg on the pedestal in room 6. You reach in.\n");
	//once the portal has been found, the player can go save the wizard
	gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "portalUsed");
	// indiana jones
	printf("You take the egg from the pedestal. The pedestal rises up slightly. \nThere is a mechanical thunk, and a whirring, ticking sound.\n");
	printf("What do you do? 1: Put the egg back. 2: Leave it as is.\n");
	int ans = 0;
	scanf_s("%d", &ans);
	while (getchar() != '\n');
	printf("You withdraw your hand. The whirring stops, and for a moment, everything is quiet. (Enter to continue)");
	scanf_s("");
	if (ans == 1)
	{
		printf("The tense silence dissapates.\n");
	}
	else if (ans == 2)
	{
		portalBoom = true;
		printf("Through the portal, you see a blast of fire and rubble. The portal closes. ");
		Room* room4 = WorldData_GetRoom(worldData, 4);
		//if the wizard hasn't been moved from room 4
		if (ItemList_FindItem(room4->itemList, "wizard") != NULL)
		{
			printf("You hear a shrill scream from outside the room. You've made the right choice to progress, but at what cost?\n");
		}
		else
		{
			//if the wizard has been picked up
			if (ItemList_FindItem(gameState->inventory, "wizard") != NULL)
			{
				printf("From your backpack, the wizard chirps, \"That coulda gone badly if you hadn't grabbed me. Thanks, adventurer!\". You made the right choice!\n");
			}
			//if the wizard has been picked dropped elsewhere
			else
			{
				printf("The wizard runs in and chirps, \"That coulda gone badly if you hadn't moved me. Thanks, adventurer!\". Then he scuttles off. You made the right choice!\n");
			}
			GameState_ChangeScore(gameState, 10);
		}
	}
	return;
}

Item* Portal_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("portal", "a small, hand-sized shimmering portal\n", false, Portal_Use, NULL, NULL);
}