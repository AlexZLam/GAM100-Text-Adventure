#include "stdafx.h"
#include "NotebookFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "WorldData.h" /* WorldData_GetRoom */
#include "ItemList.h" /* ItemList_FindItem, ItemList_Remove, ItemList_Add */
#include "GoldPieceFunctions.h" /* Egg_Build */

typedef struct WorldData WorldData;

void Notebook_Take(CommandContext context, GameState* gameState, WorldData* worldData)
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
	if (!GameFlags_IsInList(gameState->gameFlags, "notebookScored"))
	{
		/* tell the user that something cool happens when they pick up the gold piece */
		printf("The old skeletons secrets are now in your hands!\n");
		/* add to the user's score */
		GameState_ChangeScore(gameState, 5);
		/* the gold piece has not been scored, so mark the flag */
		gameState->gameFlags = GameFlags_Add(gameState->gameFlags, "notebookScored");
	}
}

void Notebook_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
	Room* room; /* The current room */
	ItemList** roomItemsPtr; /* The list of items in the current room */

	room = WorldData_GetRoom(worldData, gameState->currentRoomIndex);

	/* get the list of items in the current room */
	roomItemsPtr = Room_GetItemList(room);
	if (roomItemsPtr == NULL)
	{
		return; /* take no action, as something is wrong - we should always have an item list */
	}

	if ((gameState == NULL) || (worldData == NULL))
	{
		return; /* take no action if the parameters are invalid */
	}

	/* check if the user is using the brick out of their inventory */
	if (context != CommandContext_Item_Inventory)
	{
		/* the user doesn't have the brick - inform the user of the problem and take no action */
		printf("You must have the notebook before you can use it.\n");
		return;
	}

	Room_SetDescription(room, "This is room 3. There is a coin on the floor.\n");

	*roomItemsPtr = ItemList_Add(*roomItemsPtr, GoldPiece_Build());
	printf("You see soemthing shiny fall out of the book");
}

Item* Notebook_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("notebook", "the skeleton's notebook\n", true, Notebook_Use, Notebook_Take, NULL);
}