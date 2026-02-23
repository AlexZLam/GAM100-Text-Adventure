/******************************************************************************
filename    WizardFunctions.h
author      Alexander Lam
DP email    alexander.lam@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares the functions to create a specific item, the "wizard".

******************************************************************************/
#pragma once

typedef struct Item Item;

typedef struct ItemList ItemList;

#pragma once

/* Build a "brick" object */
Item* Wizard_Build();