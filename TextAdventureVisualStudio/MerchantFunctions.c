#include "stdafx.h"
#include "ItemList.h"   
#include "MerchantFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"
#include "WorldData.h"
#include "OrbFunctions.h"
#include "KeyFunctions.h"



void Merchant_Talk(CommandContext context, GameState* gameState, WorldData* worldData)
{
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(worldData);

    if (gameState == NULL || worldData == NULL)
        return;
    Item* orb = Orb_Build();
    int ans;
    printf("What would you like to talk about?\n1: Riddle\n2: Orb\n");
    scanf_s("%d", &ans);
    while (getchar() != '\n');

    if (ans == 1)
    {
        printf("Riddle\n");
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

Item* Merchant_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create_NPC("merchant", "the merchant\n", false, NULL, NULL, NULL, Merchant_Talk);
}