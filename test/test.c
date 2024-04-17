#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	char* shell=malloc(0x1000);
	read(0,shell,0x1000);
	mprotect((size_t)shell&(~0xfff),0x2000,7);
	void (*startFunc)() = (void(*)())shell;
	startFunc();
	return 0;
}
