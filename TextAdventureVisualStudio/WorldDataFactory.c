/******************************************************************************
filename    WorldDataFactory.c
author      Justin Chambers, Alexander Lam, Diana Everman
DP email    justin.chambers@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the WorldData factory, which creates the WorldData objects used
in this game.

This could be used to create default states as well as loaded state.

******************************************************************************/
#include "WorldDataFactory.h" /* Function declarations */
#include "WorldData.h" /* WorldData_Create, WorldData_SetRoom */
#include "Room.h" /* Room_Create, Room_AddRoomExit, Room_GetItemList */
#include "ItemList.h" /* ItemList_Add */
#include "Item.h" /* Item_Create */
#include "BrickFunctions.h" /* Brick_Build */
#include "GoldPieceFunctions.h" /* GoldPiece_Build */
#include "ExitDoorFunctions.h" /* ExitDoor_Build */
#include "WizardFunctions.h"
#include "SkeletonFunctions.h"
#include "PortalFunctions.h"
#include "NotebookFunctions.h" /* Notebook_Build */


/******************************************************************************
	Build room TEMPLATE
    Use this example function to build additional rooms
******************************************************************************/
Room* RoomN_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room;

	/* Create the room
	   include an initial room description */
	//room = Room_Create("DEBUG: This is a template - Include a description for the room here\n");

	/* Exits
	   add one or more exits to allow navigation between rooms */
	Room_AddRoomExit(room, "north", 1);  /* 1 = the room index this exit connects to */

	/* Items
	   add items to the room */
	ItemList_AddItem(Room_GetItemList(room), ExitDoor_Build());

	/* Return the new room */
	return room;
}


/* TODO REQUIRED: Build room 0 */
Room* Room0_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 1 description:
	"This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit through it from this side.\n" */
	room = Room_Create("This is room 0. It is a display room with a cage in the middle. You can see a jeweled egg inside the cage.  There is a crack in the west wall, but you can't fit through it from this side.\n");
	
	/* TODO REQUIRED: Add an Exit "north" to Room 1 */
	Room_AddRoomExit(room, "north", 1);
	/* TODO BASIC: Add room exit shortcut for "n" */
	Room_AddRoomExitShortcut(room, "n", 1);
	/* TODO REQUIRED: add an exit door to the list of items in the room, ExitDoor_Build() */
	ItemList_AddItem(Room_GetItemList(room), ExitDoor_Build());
	/* TODO ADVANCED: (not required) update the description and add a room exit to the "east" */

	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 1 */
Room* Room1_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 1 description:
	"This is room 1.  There is a large mirror here, and it shimmers as you approach.\n" */
	room = Room_Create("This is room 1.  There is a large mirror here, and it shimmers as you approach.\n");

	/* TODO REQUIRED: Add an Exit "through the mirror" to Room 2 */
	Room_AddRoomExit(room, "through the mirror", 2);
	/* TODO BASIC: Add exit shortcuts for "through mirror" and "mirror" */
	Room_AddRoomExitShortcut(room, "through mirror", 2);
	Room_AddRoomExitShortcut(room, "mirror", 2);
	/* TODO REQUIRED: Add an Exit "south" back to Room 0 */
	Room_AddRoomExit(room, "south", 0);
	/* TODO BASIC: Add room exit shortcut for "s" */
	Room_AddRoomExitShortcut(room, "s", 0);
	/* TODO REQUIRED: Add a brick to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), Brick_Build());
	ItemList_AddItem(Room_GetItemList(room), Item_Create("mirror", "The large mirror shimmers magically.", false, NULL, NULL, NULL));
	/* return the new room */
	return room;
}


/* TODO REQUIRED: Build room 2 */
Room* Room2_Build()
{
	/* TODO: Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* TODO REQUIRED: Call Room_Create with the Room 2 description:
	"This is room 2.  The room is isolated from the others, but you can see a crack in the east wall, just large enough to get through.\n" */
	room = Room_Create("This is room 2. The room is isolated from the others, but you can see a crack in the west wall, just large enough to get through. There is a strange door to the east that has an egg shaped outline on it. There is also a strange circular door to the south\n");
	/* TODO REQUIRED: Add an Exit "east" to Room 0 */
	Room_AddRoomExit(room, "east", 3);
	/* TODO BASIC: Add exit shortcuts for "e" and "crack" */
	Room_AddRoomExitShortcut(room, "e", 3);
	Room_AddRoomExit(room, "west", 0);
	Room_AddRoomExitShortcut(room, "w", 0);
	Room_AddRoomExitShortcut(room, "crack", 0);
	Room_AddRoomExit(room, "south", 5);
	Room_AddRoomExitShortcut(room, "s", 5);
	/* TODO REQUIRED: Add a gold piece to the list of items in the room */
	ItemList_AddItem(Room_GetItemList(room), GoldPiece_Build());
	/* return the new room */
	return room;
}
//Room 3
Room* Room3_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* Create the room and include an initial room description */
	room = Room_Create("This is room 3.  There is skeleton in the corner of the room. He looks very tired. He also has a notebook. there is a door north\n");
	/* Exits */
	Room_AddRoomExit(room, "north", 4);
	Room_AddRoomExitShortcut(room, "n", 4);
	Room_AddRoomExit(room, "west", 2);
	Room_AddRoomExitShortcut(room, "w", 2);
	/* Items */
	ItemList_AddItem(Room_GetItemList(room), Notebook_Build());
	ItemList_AddItem(Room_GetItemList(room), Skeleton_Build());
	/* return the new room */
	return room;
}
//Room 4
Room* Room4_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/* Create the room and include an initial room description */
	room = Room_Create("This is room 4. There is small wizard stand on an apple crate to look over the table of his pop up shop. There is a small key glimmering in the pocket of the cloak that is much too big for him.\n");
	/* Exits */
	Room_AddRoomExit(room, "east", 6);
	Room_AddRoomExitShortcut(room, "e", 6);
	Room_AddRoomExit(room, "south", 3);
	Room_AddRoomExitShortcut(room, "s", 3);
	/* Items */
	ItemList_AddItem(Room_GetItemList(room), Wizard_Build());
	/* return the new room */
	return room;
}

//Room 4 after blown up
Room* Room4_Build_DeadWizard()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/*  Create the room and include an initial room description  */
	room = Room_Create("This is room 4. There is small cloaked body in the corner of the room, covered in rubble. The explosion seems to have come from the east exit, which is now blocked off.\n");
	/* Exits */
	Room_AddRoomExit(room, "south", 3);
	Room_AddRoomExitShortcut(room, "s", 3);
	/* return the new room */
	return room;
}

//Room 4 after blown up, if wizard saved
Room* Room4_Build_SavedWizard()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/*  Create the room and include an initial room description  */
	room = Room_Create("This is room 4. It is covered in rubble. The explosion seems to have come from the east exit, which is now blocked off.\n");
	/* Exits */
	Room_AddRoomExit(room, "south", 3);
	Room_AddRoomExitShortcut(room, "s", 3);
	/* return the new room */
	return room;
}

//Room 5
Room* Room5_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/*  Create the room and include an initial room description  */
	room = Room_Create("This is room 5. There is portal on the far wall barely bigger than your arm. The room is filled with a blue-purple glow that is eminating from the portal.\n");
	/* Exits */
	Room_AddRoomExit(room, "north", 2);
	Room_AddRoomExitShortcut(room, "n", 2);
	/* Items */
	ItemList_AddItem(Room_GetItemList(room), Portal_Build());
	/* return the new room */
	return room;
}
//Room 6
Room* Room6_Build()
{
	/* Pre-declare a room pointer which we will use to build the new room */
	Room* room = NULL;

	/*  Create the room and include an initial room description  */
	room = Room_Create("This is room 6. There is a pedestal with a gold piece on it and an egg looking inscription above it. There is rune carved into the base of the pedestal that looks like an explosion. \n");
	/* Exits */
	Room_AddRoomExit(room, "west", 4);
	Room_AddRoomExitShortcut(room, "w", 4);
	/* Items */
	ItemList_AddItem(Room_GetItemList(room), GoldPiece_Build());
	/* return the new room */
	return room;
}

/* ------------------------------------------------------- */
/* Create the world data for a new game */
/* ------------------------------------------------------- */
WorldData* CreateInitialWorldData()
{
	/* The new world data */
	WorldData* worldData;

	/* TODO REQUIRED: update room count to match the number of rooms you have created and added to the world
	   if this number doesn't match then your game will either crash or you will end up stuck in a broken room with no exits */
	int roomCount = 7;/* create the new WorldData object with 3 rooms */
	worldData = WorldData_Create("Welcome to my GAM100 Game!\n\n", roomCount);

	/* build each room and assign them to the world data */
	WorldData_SetRoom(worldData, 0, Room0_Build());
	/* TODO REQUIRED: add rooms 1 and 2 to the world data */
	WorldData_SetRoom(worldData, 1, Room1_Build());
	WorldData_SetRoom(worldData, 2, Room2_Build());
	WorldData_SetRoom(worldData, 3, Room3_Build());
	WorldData_SetRoom(worldData, 4, Room4_Build());
	WorldData_SetRoom(worldData, 5, Room5_Build());
	WorldData_SetRoom(worldData, 6, Room6_Build());
	/* TODO ADVANCED: add additional advanced rooms */

	/* return the new object */
	return worldData;
}