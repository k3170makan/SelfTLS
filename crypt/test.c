#include <stdio.h>

int main(int argc, char **argv){
	static const int t[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	printf("[*] length %lu\n",sizeof(t));
}
