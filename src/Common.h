#ifndef COMMON_H__
#define COMMON_H__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

enum L_state
{
	LINK_FAILED,
	LINK_ACCEPT,
	LINK_CONNECT,
	LINK_SUCCESS,
	LINK_ABORT
};

enum G_state
{
	GAME_START,
	GAME_MAINMENU,
	GAME_SCANING,
	GAME_LINKING,
	GAME_READY,
	GAME_FIGHT,
	GAME_OVER,
	GAME_EXIT
};

enum G_mode
{
	MODE_UNKNOW,
	MODE_CREATE,
	MODE_JOIN
};

enum G_signal
{
	SIGN_NO,
	SIGN_PAUSE,
	SIGN_EXIT
};

L_state getLinkState();
G_state getGameState();
G_mode getGameMode();
G_signal getKeySign();
void setAdvance();

#endif/*COMMON_H__*/