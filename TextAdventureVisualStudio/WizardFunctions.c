/******************************************************************************
filename    WizardFunctions.c
author      Alexander Lam, Diana Everman
DP email    alexander.lam@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file defines the wizard interface, which is an npc in the game

******************************************************************************/
#include "stdafx.h"
#include "ItemList.h"   
#include "WizardFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "WorldData.h"
#include "OrbFunctions.h"
#include "KeyFunctions.h"
#include "GoldPieceFunctions.h"


int takeCnt = 0;

void Wizard_Talk(CommandContext context, GameState* gameState, WorldData* worldData)
{
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(worldData);

    if (gameState == NULL || worldData == NULL)
        return;
    Item* orb = Orb_Build();
    Item* key = Key_Build();
    int ans;
    int ridAns;
    printf("What would you like to talk about?\n1: Riddle\n2: Orb\n");
    if (GameFlags_IsInList(gameState->gameFlags, "portalUsed"))
    {
        printf("3: Save\n");
    }    
    scanf_s("%d", &ans);
    while (getchar() != '\n');

    if (ans == 1)
    {
        printf("I am the count of heads of a 5 headed hydra after three of its heads are cut away...\n");
        printf("The wizard stutters and says he forgot the rest.\n");

        printf("\nAnswer?: ");
        scanf_s("%d", &ridAns);
        while (getchar() != '\n');

        if (ridAns == 10)
        {
            printf("The wizard grins, impressed. \"Correct!\"\n");
            printf("He hands you the key\n");
            gameState->inventory = ItemList_Add(gameState->inventory, key);
            //Update room description
            Room* room4 = WorldData_GetRoom(worldData, 4);
            Room_SetDescription(room4, "This is room 4. There is small wizard standing on an apple crate to look over the table of his pop up shop. His cloak is much too big for him.\n");
        }
        else if (ridAns == 4)
        {
            printf("The wizard laughs. \"Close, but remember, hydras have unique properties.\"\n");
        }
        else if (ridAns == 2 || ridAns == 8)
        {
            printf("The wizard hums. \"You'll have to look elsewhere for the second half of the riddle.\"\n");
        }
        else
        {
            printf("The wizard sighs. \"Wrong... better luck next time.\"\n");

        }
    }
    else if (ans == 2)
    {
        int goldRemoved = 0;

        // Try to remove 3 gold pieces, one at a time
        for (int i = 0; i < 3; i++)
        {
            Item* gold = ItemList_FindItem(gameState->inventory, "gold piece");
            if (gold == NULL)
            {
                break; // No more gold found
            }

            gameState->inventory = ItemList_Remove(gameState->inventory, gold);
            goldRemoved++;
        }

        if (goldRemoved == 3)
        {
            gameState->inventory = ItemList_Add(gameState->inventory, orb);
            printf("You pay 3 gold and receive the orb.\n");
        }
        else
        {
            // If not enough gold, return any removed gold
            for (int i = 0; i < goldRemoved; i++)
            {
                Item* gold = GoldPiece_Build(); // or however you create gold items
                gameState->inventory = ItemList_Add(gameState->inventory, gold);
            }

            printf("You don't have enough gold.\n");
        }
    }

    else if (ans == 3 && GameFlags_IsInList(gameState->gameFlags, "portalUsed"))
    {
        gameState->wizardReadyToCarry = true;
        printf("\"I'M GONNA EXPLODE?!!?!\"\n");
        printf("The wizard jumps off the apple crate he was standing on and runs towards the exit.\nHe then runs into the door frame and is knocked out.\n");
        printf("His little body looks so easy carry.\n");
        //Update room description
        Room* room4 = WorldData_GetRoom(worldData, 4);
        Room_SetDescription(room4, "This is room 4. There is an apple crate behind the table of the wizard's pop up shop.\n");
    }
}

void Wizard_Take(CommandContext context, GameState* gameState, WorldData* worldData)
{
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(worldData);

    if (gameState == NULL || worldData == NULL)
        return;
    takeCnt++;
    if (takeCnt < 2)
    {
        printf("\"Don't touch me!\"\n");
        GameState_ChangeScore(gameState, 1);
    }
    if (takeCnt == 2)
    {
        printf("\"Stop it!\"\n");
        GameState_ChangeScore(gameState, 2);
    }
    if (takeCnt == 3)
    {
        printf("He begins to run in circles\n");
        gameState->wizardReadyToCarry = true;
        GameState_ChangeScore(gameState, 2);
    }
    if (takeCnt >= 4)
    {
        printf("You catch him and tie him to your back\n");
        GameState_ChangeScore(gameState, 5);
        //Update room description
        Room* room4 = WorldData_GetRoom(worldData, 4);
        Room_SetDescription(room4, "This is room 4. There is an apple crate behind the table of the wizard's pop up shop.\n");
    }
}



Item* Wizard_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create_NPC("wizard", "the wizard\n", true, NULL, Wizard_Take, NULL, Wizard_Talk);
}