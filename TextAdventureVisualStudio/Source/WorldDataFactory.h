/******************************************************************************
filename    WorldDataFactory.h
author      Matthew Picioccio, Diana Everman
DP email    mattpic@digipen.edu, diana.everman@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the WorldData factory, which creates the WorldData objects used
in this game.

This could be used to create default states as well as loaded state.

******************************************************************************/
#pragma once

#include "Room.h"

typedef struct WorldData WorldData;


/* Create the world data for a new game */
WorldData* CreateInitialWorldData();

// used in egg_take
Room* Room4_Build_DeadWizard();
Room* Room4_Build_SavedWizard();