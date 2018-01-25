#include <stdio.h>
#include "shootThread.h"

#if 1
#define GAME_READY 1
#define GAME_START 2
#define GAME_OVER 0

static unsigned char game_status = 0;


int analyze(int iCmd, char* sCmd[]);
int create_room();
int join_room();

int main(int argc, char* argv[])
{
	analyze(argc, argv);
	while(game_status == GAME_OVER)
	{
//		get_keyboard();
//		responding();
	}
	return 0;
}

int create_room()
{
	Shoot InsShoot(SERVER);
	InsShoot.start();
	InsShoot.wait();
	return 0;
}

int join_room()
{
	Shoot InsShoot(CLIENT);
	InsShoot.start();
	InsShoot.wait();
	return 0;
}

int analyze(int iCmd, char* sCmd[])
{
	if(iCmd < 2)
		return -1;
	if(!strcmp(sCmd[1], "create"))
	{
		/*create socket server thread*/
		create_room();
	}
	else if(!strcmp(sCmd[1], "join"))
	{
		/*create socket client thread*/
		join_room();
	}
	return 0;
}

#else

class abstract
{
	public:
	void start();
	protected:
	virtual void run() =0;
	private:
	static void entryPoint(void* ptr);
};
void abstract::entryPoint(void* ptr)
{
	abstract* p = (abstract*)ptr;
	p->run();
}
class instance : public abstract
{
	protected:
	virtual void run();
};

void abstract::start()
{
	entryPoint(this);
}

void instance::run()
{
	printf("------------1-----------\n");
}

int main()
{
	instance* a = new instance;
	a->start();
	delete a;
}

#endif