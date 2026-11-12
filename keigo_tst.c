#include<stdio.h>
#include<windows.h>

char buf[128] = "‚ ‚è‚ª‚Æ‚¤‚²‚´‚¢‚Ü‚·";

int main()
{
	while (1)
	{
		printf("%s ", buf);
		for(int i=0; i<16; i++)
		  printf("\\x%x", (unsigned char)buf[i]);
		Sleep(1);
	}
}
