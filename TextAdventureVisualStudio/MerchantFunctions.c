#include "stdafx.h"
#include "MerchantFunctions.h"
#include "GameState.h"
#include "GameFlags.h"
#include "Item.h"
#include "Room.h"

typedef struct WorldData WorldData;


void Merchant_Use(CommandContext context, GameState* gameState, WorldData* worldData)
{
    /* avoid W4 warnings on unused parameters - this function conforms to a function typedef */
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(worldData);

    int ans;   /* use a real int, not an uninitialized pointer */

    if (gameState == NULL || worldData == NULL)
    {
        return; /* take no action if the parameters are invalid */
    }

    printf("What would you like to talk about?\n1: Riddle\n2: Orb\n");
    scanf_s("%d", &ans);   /* pass the ADDRESS of ans */

    if (ans == 1)
    {
        printf("Riddle\n");
    }
    else if (ans == 2)
    {
        printf("Pay 3 coins");
    }

    printf("\n");
}


Item* Merchant_Build()
{
	/* Create a "gold piece" item, using the functions defined in this file */
	return Item_Create("merchant", "the merchant\n", true, Merchant_Use, NULL, NULL);
}