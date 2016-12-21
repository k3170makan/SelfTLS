#include <stdio.h>
//#define GET_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8)] & ( 0x80 >> ( bit % 8 ) ) }
/*
						^									^
						|									|	
			grab the correct 				use 0x10000000 to and with the bit 
			byte in the array				if the bit is set it will return a non-zero because only 1 and 1 will return 1, 1 and 0 will return a 0
*/
//#define SET_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8) ] |= (0x80 >> ( bit % 8 ) ) }
//#define CLEAR_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8) ] &= ~(0x80 >> ( bit % 8) ) }

//need to test these

static unsigned char GET_BIT(const unsigned char *stream, int bit){
	#ifdef DEBUG
		printf("[i] getting bit %d from array with value [%0x]\n",bit,stream[ (int) (bit / 8 )]	& (0x80 >> ( bit % 8)));
	#endif
	return stream[ (int) (bit / 8 )]	& (0x80 >> ( bit % 8));
}
static void SET_BIT(unsigned char *stream, int bit){

	#ifdef DEBUG
		printf("[i] setting bit %d from array with value [%0x]\n",bit,stream[ (int) (bit / 8 )] | (0x80 >> ( bit % 8)));
	#endif
	stream[ (int) (bit / 8)] |= (0x80 >> (bit % 8)) ;
}
static void CLEAR_BIT( unsigned char *stream, int bit){
	#ifdef DEBUG
		printf("[i] clearing bit %d from array with value [%0x]\n",bit,stream[ (int) (bit / 8 )] & ~(0x80 >> ( bit % 8)));
	#endif
	stream[ (int) (bit / 8)] &= ~(0x80 >> (bit % 8));
}
static void xor( unsigned char *target, const unsigned char *src, int len){
	while(len--){
		*target++ ^= *src++;
	}
}
static void permute ( unsigned char target[], 
		const unsigned char src[], 
		const char permute_table[],
		int len){
	//the permutation is a road map for which array position in src should be reflected in the corresponding position in target
	//target[i] = src[permutation[i]] 
	//because we are working with 1's and 0's it is as simple as checking if the src[permutation[i]] is set, if not we just clear the position in the target
	int i;
	for (i =0; i < len; i++){
		if ( GET_BIT(src, permute_table[i] - 1)){
			SET_BIT(target,i);
		}
		else{
			CLEAR_BIT(target,i);
		}
	}
}
static void initial_permutation(unsigned char target[], unsigned char src[]){
	static const char ip_table[] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9,  1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};		
	permute(target,src,ip_table,sizeof(ip_table));
}

static void final_permutation(unsigned char target[], unsigned char src[],int len){
	static const char fp_table[] = {
	40, 8, 48, 16, 56, 24, 64, 32
	};
}
int main(int argc, char **argv){
	//test permutation
	unsigned char src[] = {
	1,   2,  3,  4,  5,  6,  7,  8,
	9, 10, 11, 12, 13, 14 ,15, 16,
	17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64 };
	unsigned char target[64] = {
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	0,0,0,0,0,0,0
	};
	//test inital permutation
  // initial_permutation(target,src);
	xor(target,src,sizeof(target));	
	int i;
	for (i=0;i<sizeof(target);i++){ //no need to divide by the char type size anymore since they are all one byte wide anyway
		
		if (target[i] > 9 && target[i] <= 99){
			printf("0%d ",target[i]);
		}
		else if (target[i] > 99) { 
			printf("%d ",target[i]); 
		} else { 
			printf( "00%d ", target[i]);
		}
		if (i%8 == 7){
			printf("\n");
		}
	}
	printf("\n");
	return 0;
}


