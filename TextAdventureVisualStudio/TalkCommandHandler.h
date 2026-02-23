/******************************************************************************
filename    TalkCommandHandler.h
author      Diana Everman
DP email    diana.everman@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the "talk" user command, which 
lets the player talk to a npc

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "use" command, which calls an item-specific function on a given item */
void HandleUseCommand(CommandData* command, GameState* gameState, WorldData* worldData);