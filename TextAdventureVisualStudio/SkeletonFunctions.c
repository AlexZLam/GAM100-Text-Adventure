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

int talkCnt = 0;


void Skeleton_Talk(CommandContext context, GameState* gameState, WorldData* worldData)
{
    if (gameState == NULL)
    {
        return; /* take no action if the parameters are invalid */
    }
    UNREFERENCED_PARAMETER(context);
    UNREFERENCED_PARAMETER(worldData);
    talkCnt++;
    if (talkCnt < 2)
    {
        printf("His heads turn to the side a little bit\n");
    }
    if (talkCnt == 2)
    {
        printf("He shifts back into the corner\n");
    }
    if (talkCnt == 3)
    {
        printf("He turn toward you but quickly turns back around\n");
    }
    if (talkCnt >= 4)
    {
        printf("\"Kanye wasn't that bad\"\n");
        printf("It was an evil skeleton. Maybe it's a good thing he died\n");
    }
}

Item* Skeleton_Build()
{
    /* Create a "gold piece" item, using the functions defined in this file */
    return Item_Create_NPC("skeleton", "It's a skeleton\n", false, NULL, NULL, NULL, Skeleton_Talk);
}