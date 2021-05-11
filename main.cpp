#include <iostream>
#include <string.h>

using namespace std;
int fromBytesToDec(char* data, int bit_start, int bit_length);
void fromBitToDec(char* data, int bit_start, int bit_length, int* dst);
static  char *hex2bin( char *s);

int main(){
    cout<<"hello, diva2 world!\n";
    char data[8];
    data[0] = 0xFF;
    data[1] = 0xFF;
    data[2] = 0xFF;
    data[3] = 0x68;
    data[4] = 0x13;
    data[5] = 0x10;
    data[6] = 0xFF;
    data[7] = 0xFF;
    // printf("generate data\n");


    int bin[1];
    fromBitToDec(data, 25, 1, bin);
    for(int i=0; i<1; i++){
        printf("dec = %d\n",bin[i]);
    }
    
}




void fromBitToDec(char* data, int bit_start, int bit_length, int* dst){
	int byte_start = bit_start/8;
    int offset = bit_start % 8;
    printf("[BIT] from %d (length:%d, offset = %d)\n", bit_start, bit_length, offset);

    // <read to hex>
    printf("[HEX] \n");
    char hex[1];
    hex[0] = data[byte_start];
    printf("hex[%d] %02X \n", 0, hex[0]);
    
    // hex to dec
    printf("[DEC]\n");
    int dec = 0;
    for(int i=0; i<1; i++){
        // dec = (dec << 8) | hex[i];
        printf("[%d] %d + %d", i, dec*0x100, hex[i]);
        dec = (dec * 0x100) + hex[i];
        printf(" = %d\n", dec);
    }
    printf("dec=%d\n",dec);

    // <dec to binary>
    int bin[8];
    printf("[BIN]\n");
    //for(int i=0; dec>0; i++)    
    for(int i=0; i<8; i++)    
    {    
        bin[i]=dec%2;
        dec= dec/2;
        printf("[%d] bin=%d dec=%d\n", i, bin[i], dec);
    }

    // <binary parsing>
    printf("[TARGET]\n");
    for(int i=offset; i<offset+bit_length; i++){
        printf("bin[%d] = %d\n", 7-i, bin[7-i]);
        // bin[7-i]
        dst[i-offset] = bin[7-i];
    }

}

int fromBytesToDec(char* data, int bit_start, int bit_length){
	// <bit to byte>
    int byte_start = bit_start/8;
    int byte_length = bit_length/8;
    printf("[BYTE] from %d (length:%d)\n", byte_start, byte_length);

    // <read to hex>
    printf("[HEX] \n");
    char hex[8] = {0};
    for(int i=byte_start; i<byte_start+byte_length; i++){
        hex[i-byte_start] = data[i];
        printf("hex[%d] %02X \n", i-byte_start, hex[i-byte_start]);
    }
    hex[byte_length] = '\0';

    // <little endian>
    printf("[LITTLE ENDIAN] \n");
    char tmp;
    for(int i=0; i<byte_length/2; i++){
        tmp = hex[i];
        hex[i] = hex[byte_length-i-1];
        hex[byte_length-i-1]=tmp;
        
    }
    for(int i=0; i<byte_length; i++){
        printf("hex[%d] = %02X\n", i, hex[i]);
    }
    
    // hex to dec
    printf("[DEC]\n");
    int dec = 0;
    for(int i=0; i<byte_length; i++){
        // dec = (dec << 8) | hex[i];
        printf("[%d] %d + %d", i, dec*0x100, hex[i]);
        dec = (dec * 0x100) + hex[i];
        printf(" = %d\n", dec);
    }
    printf("dec=%d\n",dec);
	return dec;
}

static  char *hex2bin( char *hex)
{
    // 출처: https://stackoverflow.com/questions/18906027/missing-punctuation-from-c-hex2bin
    static  char bin[2048];
    unsigned int i,e,l=0,L=strlen(hex);
    for (i=0; i<L; i+=2) { sscanf(hex+i, "%02x",&e); bin[l++]=(char)e; }
    bin[l]=0;
    return bin;
}