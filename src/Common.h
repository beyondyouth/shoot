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
	GAME_SELECT,
	GAME_LINK,
	GAME_FIGHT,
	GAME_OVER,
	GAME_EXIT
};

enum G_signal
{
	SIGN_NO,
	SIGN_PAUSE,
	SIGN_EXIT
};

struct Node
{
	char data[15];
	struct Node* prev;
	struct Node* next;
};
typedef struct Node Node;

void push(Node* n);
void erase(Node* n);
Node* find(char* d);
void output(void);
int getlen(void);

L_state getLinkState();
G_state getGameState();
G_signal getSignal();
void setSignal(G_signal S);

#endif/*COMMON_H__*/