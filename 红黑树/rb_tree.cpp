#include <iostream>
#include <string>
using namespace std;
#include <windows.h>
#define REGS_FOREACH(_) _(x) _(y)
#define RUN_LOGIC x1= !x && y;\
                  y1=!x && !y;
#define DEFINE(x) static int x,x##1;
#define UPDATE(x) x=x##1;
#define PRINT(x) printf(#x" =%d;",x);
int main()
{
	REGS_FOREACH(DEFINE);
	while (1)
	{
		RUN_LOGIC;
		REGS_FOREACH(PRINT);
		REGS_FOREACH(UPDATE);
		putchar('\n');
		Sleep(1000);
	}
}
/*int main()
{
	static int x, x1,y, y1;
	while (true)
	{
		x1 = (!x) && y;
		y1 = !x && !y;
		printf("x""=%d", x);
		printf("y""=%d",y);
		x = x1;
		y = y1;
		putchar('\n');
		Sleep(1000);
	}
}*/

void hanoi(int n, char from, char to, char via)
{
	if (n == 1) printf("%c->%c\n", from, to);
	else
	{
		hanoi(n - 1, from, via, to);
		hanoi(1, from, to, via);
		hanoi(n - 1, via, to, from);
	}
	return;
}

typedef struct {
	int pc, n;
	char from, to, via;
}Frame;
#define call(...) ({*(++top)=(Frame){ .pc=0,_VA_ARGS};})
#define ret() ({top--;})
#define goto(loc)  ({f->pc=(loc)-1;})
void hanoi(int n, char from, char to, char via)
{
	Frame stk[64], * top = stk - 1;
	call(n, from, to, via);
	for (Frame* f; (f = top) >= stk; f->pc++) {
		switch (f->pc)
		{
		case 0:if (f->n == 1)
		       {
			printf("%c->%c\n", f->from, f->to); goto(4);
		       }
			  break;
		case 1:call(f->n - 1, f->from, f->via, f->to);
		case 2:call(1, f->from, f->to, f->via);
		case 3:call(f->n - 1, f->via, f->to, f->from);
		case 4:ret();
		default:assert(0);//’‚ «∂œ—‘ 		 
		}
	}
}



