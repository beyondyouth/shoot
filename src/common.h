#ifndef COMMON_H__
#define COMMON_H__

#include "basetype.h"

enum L_state
{
	LINK_FAILED,
	LINK_ACCEPT,
	LINK_CONNECT,
	LINK_SUCCESS
};

enum G_state
{
	GAME_OVER,
	GAME_MENU,
	GAME_WAIT,
	GAME_FIGHT
};

enum Mode
{
	MODE_UNKNOW,
	MODE_SERVER,
	MODE_CLIENT
};

L_state getLinkState();
G_state getGameState();
Mode getGameMode();

#endif/*COMMON_H__*/