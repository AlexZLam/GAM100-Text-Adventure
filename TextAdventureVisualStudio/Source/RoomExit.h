/******************************************************************************
filename    RoomExit.h
author      Matthew Picioccio
DP email    mattpic@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the RoomExit interface, which is used to manage room exits
in the game.

******************************************************************************/
#pragma once
#include "stdafx.h" /* bool */

/* The maximum length of an exit string */
#define MAX_DIRECTION_LENGTH 32

/* A linked list of exits from a room to another room */
typedef struct RoomExit
{
	char direction[MAX_DIRECTION_LENGTH]; /* The name of the exit, matched to command nouns */
	bool showInHelp;
	int nextRoomIndex; /* The index of the room in the specified direction */
	struct RoomExit* next; /* The next exit in the list */
} RoomExit;

/* Adds an exit to a given list, which might be NULL (an empty list).  Returns the new head of the list */
RoomExit* RoomExit_Add(RoomExit* existingList, const char* direction, int nextRoomIndex, bool showInHelp);

/* Free the memory associated with a linked list of RoomExits */
void RoomExit_Free(RoomExit** roomExitListPtr);

/* Find the next room index associated with a given direction */
bool RoomExit_Find(RoomExit* roomExitList, const char* direction, int* outNextRoomIndex);

/* Print the list of exits to standard output */
void RoomExit_Print(RoomExit* roomExitList);