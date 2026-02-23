/******************************************************************************
filename    TeleportCommandFunctions.h
author      Alexander Lam
DP email    alexander.lam@digipen.edu
course      GAM100 ** Do not use this code in your team project

Brief Description:
This file declares functions that handle the "tp" user command, which moves
the user from one room to another 

******************************************************************************/
#pragma once

typedef struct CommandData CommandData;
typedef struct GameState GameState;
typedef struct WorldData WorldData;


/* Handles the "go" command, which moves the user to another room */
void HandleTPCommand(CommandData* command, GameState* gameState, WorldData* worldData);