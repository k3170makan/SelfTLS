#include <stdio.h>
/**
TODO: finish confirming the permutation tables
*/
//#define GET_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8)] & ( 0x80 >> ( bit % 8 ) ) }
/*
						^									^
						|									|	
			grab the correct 				use 0x10000000 to and with the bit 
			byte in the array				if the bit is set it will return a non-zero because only 1 and 1 will return 1, 1 and 0 will return a 0
*/
//#define SET_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8) ] |= (0x80 >> ( bit % 8 ) ) }
//#define CLEAR_BIT ( bit_stream, bit ) { bit_stream[ (int) (bit / 8) ] &= ~(0x80 >> ( bit % 8) ) }
//oh shit the permutation arrays need to be integers!
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
void print_byte(unsigned char byte){
	int i;
	unsigned char array[] = {byte};
	for (i=0;i<8;i++){
		if (GET_BIT(array,i) != 0){
			printf("1");
		}
		else{
			printf("0");
		}
	}	
	printf("\n");
}

static void xor( unsigned char *target, const unsigned char *src, int len){
	while(len--){
		*target++ ^= *src++;
	}
}
//the permutation is a road map for which array position in src should be reflected in the corresponding position in target
/*
	permute: permute src, under the permutation table described by permute_table, and save the result in target, do this for len number of elements
	* each entry of permute_table, is a bit position in the target[] that must be set by the corresponding bit value of src[] (we treat the arrays as streams of bits)
	
	return: void
*/
static void permute ( unsigned char target[], //target array in which the result of the operation will be saved
		const unsigned char src[],  //src array, dictates the original state of the operation 
		const unsigned int permute_table[], //permutation table, describes the permutation to apply, permute bit i with with permute_table[i] 
		int len){
	//target[i] = src[permutation[i]] 
	//because we are working with 1's and 0's it is as simple as checking if the src[permutation[i]] is set, if not we just clear the position in the target
	#ifdef DEBUG
		printf("[i] permutating arrays...\n");
	#endif
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
static void expansion_permutation(unsigned char target[], const unsigned char src[]){
	#ifdef DEBUG
		printf("[i] expansion permutation...\n");
	#endif
	static const unsigned int e_table[] = {
		32, 1,   2,  3,  4,  5,
		 4, 5,   6,  7,  8,  9,
		 8, 9,  10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32,  1
	};
	permute(target,src,e_table,sizeof(e_table)/4);
	return;
}
static void initial_permutation(unsigned char target[],  //target array, in which the result of the operation will be saved
											unsigned char src[]){ //src array, dictates the origin argument of the operation
	#ifdef DEBUG
		printf("[i] initial permutation...\n");
	#endif
	const unsigned int ip_table[] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9,  1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};		
	permute(target,src,ip_table,sizeof(ip_table)/4);
}

static void final_permutation(unsigned char target[], 
											unsigned char src[]){

	#ifdef DEBUG
		printf("[i] final permutation...\n");
	#endif
	const unsigned int fp_table[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};
	permute(target,src,fp_table,sizeof(fp_table)/4);
}
static void key_permutation_1(unsigned char target[], 
											unsigned char src[]){
	const unsigned int pc1[] = {
	57,49, 41,  33, 25, 17,  9, 1,
	58, 50, 42, 34, 26, 18, 10, 2,
	59, 51, 43, 35, 27, 19, 11, 3,
	60, 52, 44, 36, 
	63, 55, 47, 39, 31, 23, 15, 7,
	62, 54, 46, 38, 30, 22, 14, 6,
	61, 53, 45, 37, 29, 21, 13, 5,
	28, 20, 12, 4};
	permute(target,src,pc1,sizeof(pc1)/4);
}
static void key_permutation_2(unsigned char target[], 
											unsigned char src[]){
	const unsigned int pc2[] = {
		14, 17, 11, 24,  1,  5,
		 3, 28, 15,  6, 21, 10,
		23, 19, 12,  4, 26,  8,
		16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32	
	};
	permute(target,src,pc2,sizeof(pc2)/4);
}

void print_array(unsigned char target[],int len){
	int i;
	for (i=0;i<len;i++){ //no need to divide by the char type size anymore since they are all one byte wide anyway
		
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
	unsigned char permute_test_src[] = {15};
	unsigned char permute_test_target[] = {0};
	unsigned int permute_test_table[] = {
		8,7,6,5,4,3,2,1
	};
	printf("[*] src array: \n");
	print_array(src,sizeof(src));
	printf("[*] target array: \n");
	print_array(target,sizeof(target));
	//test inital permutation
	//printf("[*] initial permutation array test...\n");
  	//initial_permutation(target,src);
 	//xor(target,src,sizeof(target));	
	//expansion_permutation(target,src);
	//initial_permutation(target,src);
	//print_array(target,sizeof(target));
	//final_permutation(target,src);
	//print_array(target,sizeof(target));
	//int i;	
	//for (i = 0; i < 255;i++){
	//	printf("[*] %d: ",i);
	//	print_byte((char) i);
	//}	
	print_byte(permute_test_src[0]);
	permute(permute_test_target,permute_test_src,permute_test_table,sizeof(permute_test_table)/4);	
	print_byte(permute_test_target[0]);	
	return 0;
}


