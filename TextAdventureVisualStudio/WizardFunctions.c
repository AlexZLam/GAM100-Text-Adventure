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
    scanf_s("%d", &ans);
    while (getchar() != '\n');

    if (ans == 1)
    {
        if (ans == 1)
        {
            printf("I am the count of crowns worn by the hydra after three of its heads are cut away...\n");
            printf("The wizard stutters and says he forgot the rest.\n");

            printf("\nAnswer?: ");
            scanf_s("%d", &ridAns);
            while (getchar() != '\n');

            if (ridAns == 4)
            {
                printf("The wizard grins, impressed. \"Correct!\"\n");
                printf("He hands you the key\n");
                gameState->inventory = ItemList_Add(gameState->inventory, key);
            }
            else
            {
                printf("The wizard sighs. \"Wrong... better luck next time.\"\n");
          
            }
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
}

Item* Wizard_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create_NPC("wizard", "the wizard\n", false, NULL, NULL, NULL, Wizard_Talk);
}