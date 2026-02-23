/******************************************************************************
filename    WizardFunctions.c
author      Alexander Lam
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
    //check if flag is activated
    printf("3: Save\n");
    scanf_s("%d", &ans);
    while (getchar() != '\n');

    if (ans == 1)
    {
        printf("I am the count of crowns worn by the hydra after three of its heads are cut away...\n");
        printf("The wizard stutters and says he forgot the rest.\n");

        printf("\nAnswer?: ");
        scanf_s("%d", &ridAns);
        while (getchar() != '\n');

        if (ridAns == 10)
        {
            printf("The wizard grins, impressed. \"Correct!\"\n");
            printf("He hands you the key\n");
            gameState->inventory = ItemList_Add(gameState->inventory, key);
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
        for (int i = 0; i < 3; i++)
        {
            Item* gold = ItemList_FindItem(gameState->inventory, "gold piece");
            if (gold == NULL)
            {
                break;
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
            // Return removed gold if not enough? Optional
            printf("You don't have enough gold.\n");
        }
    }
    else if (ans == 3)
    {
        //is flag activated
        printf("\"I'M GONNA EXPLODE?!!?!\"");
        printf("The wizard jumps off the apple crate he was standing on and runs towards the exit.\nHe then runs into the door frame and is knocked out.\n");
        printf("His little body looks so easy carry.\n");
    }
}




Item* Wizard_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create_NPC("wizard", "the wizard\n", true, NULL, NULL, NULL, Wizard_Talk);
}