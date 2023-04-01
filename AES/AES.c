//Name - Ayush Singh
//Id - 202051042

#include <stdio.h>
#include <stdint.h>

//Subbyte table
unsigned char sub[16][16]={{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};


//Function to multiply a polynomial(8 bit number) by x
unsigned char multiplyByX(unsigned char temp){

unsigned char res=temp<<1; 

if(temp>>7==1){ //checking for 8th bit
res=res^27;
}

return res;
}


//Function to multiply a polynomial(8 bit number) by x^2
unsigned char multiplyByXsquare(unsigned char temp){

unsigned char res=temp<<2;

if(temp>>7 == 1 && ((temp>>6)&0x01) == 1){
res=res^27^54;
}
else if(temp>>7==1){
res=res^54;
}
else if((temp>>6)&0x01==1){
res=res^27;
}


return res;

}

//multiply a polynomial(8 bit number) with X^k
unsigned char multiplyByX_ToThePowerK(unsigned char temp, int power){
unsigned char result=temp;
for(int i=1;i<=power;i++){
result=multiplyByX(result);

}

return result;
}


//Subbyte of round functions
unsigned char calculateSubbyte(unsigned char temp){
temp=multiplyByX(temp);
if(temp & 0x01 == 1){ //Adding 1
temp=(temp>>1)<<1;
}
else{
temp=temp | 0x01;
}

return sub[temp>>4][temp&0x0f];  //extracting corresponding values from subyte table
}

//Shift row of round functions
void calculateShiftRow(unsigned char input[4][4],unsigned char result[4][4]){
for(int i=0;i<4;i++){
result[0][i]=input[0][i]; //first row remains unaffected
}

//Shifting remaining row by ith position
for(int i=1;i<4;i++){
unsigned char temp[i];
for(int j=0;j<i;j++){
temp[j]=input[i][j];
}
for(int j=i;j<4;j++){
result[i][j-i]=input[i][j];
}
for(int j=4-i;j<4;j++){
result[i][j]=temp[j-(4-i)];
}

}

}

//Mix Column of round functions
void calculateMixColumn(unsigned char input[4][4],unsigned char result[4][4]){

for(int i=0;i<4;i++){
for(int j=0;j<4;j++){

result[j][i]=input[j][i] ^ multiplyByXsquare(input[(j+1)%4][i]) ^ multiplyByXsquare(input[(j+2)%4][i]) ^ multiplyByXsquare(input[(j+3)%4][i])^input[(j+3)%4][i];

}
}


}

//SUBWORD of key scheduling algorithm
uint32_t SUBWORD(uint32_t temp){

uint32_t result=0x00000000;

unsigned char first=temp>>24;  //first 8 bit from MSB
unsigned char second=(temp>>16) & 0x00ff; //next 8 bit from MSB
unsigned char third=(temp>>8) & 0x0000ff; //next 8 bit from MSB
unsigned char forth=(temp & 0x000000ff); //Last 8 LSB

return ((((((result | sub[first>>4][first&0x0f])<<8) | sub[second>>4][second&0x0f])<<8) | sub[third>>4][third&0x0f])<<8) | sub[forth>>4][forth&0x0f];

}


//ROTWORD of key scheduling algorithm
uint32_t ROTWORD(uint32_t temp){

uint32_t result=0x00000000;

unsigned char first=temp>>24;//first 8 bit from MSB
unsigned char second=(temp>>16) & 0x00ff;//next 8 bit from MSB
unsigned char third=(temp>>8) & 0x0000ff;//next 8 bit from MSB
unsigned char forth=(temp & 0x000000ff);//Last 8 LSB

return ((((((result | second)<<8) | third)<<8) | forth)<<8) | first; //concatenation

}


//concatenate four 32 bits to form 128 bits
void concatenate(uint32_t first, uint32_t second, uint32_t third, uint32_t forth, unsigned   char rkeys[16]){

rkeys[0]=first>>24;
rkeys[1]=(first>>16)&0x00ff;
rkeys[2]=(first>>8)&0x0000ff;
rkeys[3]=first & 0x000000ff;

rkeys[4]=second>>24;
rkeys[5]=(second>>16)&0x00ff;
rkeys[6]=(second>>8)&0x0000ff;
rkeys[7]=second & 0x000000ff;

rkeys[8]=third>>24;
rkeys[9]=(third>>16)&0x00ff;
rkeys[10]=(third>>8)&0x0000ff;
rkeys[11]=third & 0x000000ff;

rkeys[12]=forth>>24;
rkeys[13]=(forth>>16)&0x00ff;
rkeys[14]=(forth>>8)&0x0000ff;
rkeys[15]=forth & 0x000000ff;


}


//Produces 11 round keys from given secret key using key scheduling algorithm
void keySchedulingAlgorithm(unsigned char key[16], unsigned char roundKeys[11][16]){

uint32_t constants[]={0x01000000,0x02000000,0x04000000,0x08000000,
			0x10000000,0x20000000,0x40000000,0x80000000,0x1b000000,0x36000000};

uint32_t word[44];

	
for(int i=0;i<=3;i++){
uint32_t temp=0x00000000;
word[i]=((((((temp | key[4*i])<<8) | key[4*i+1])<<8) | key[4*i+2])<<8) | key[4*i+3];
}

for(int i=4;i<44;i++){
uint32_t temp=word[i-1];

if(i%4==0){
temp=SUBWORD(ROTWORD(temp)) ^ constants[(i/4)-1];
}

word[i]=word[i-4] ^ temp;
}

unsigned char res[16];

concatenate(word[0],word[1],word[2],word[3],roundKeys[0]);

concatenate(word[4],word[5],word[6],word[7],roundKeys[1]);

concatenate(word[8],word[9],word[10],word[11],roundKeys[2]);

concatenate(word[12],word[13],word[14],word[15],roundKeys[3]);

concatenate(word[16],word[17],word[18],word[19],roundKeys[4]);

concatenate(word[20],word[21],word[22],word[23],roundKeys[5]);

concatenate(word[24],word[25],word[26],word[27],roundKeys[6]);

concatenate(word[28],word[29],word[30],word[31],roundKeys[7]);

concatenate(word[32],word[33],word[34],word[35],roundKeys[8]);

concatenate(word[36],word[37],word[38],word[39],roundKeys[9]);

concatenate(word[40],word[41],word[42],word[43],roundKeys[10]);


}


//Function to xor text with keys
void calculateXor(unsigned char cipher[4][4], unsigned char key[16]){

int k=0;
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){

cipher[j][i]=cipher[j][i]^key[k];
k++;

}
}

}

//Round Function 1 to 9
void roundFunction1_9(unsigned char input[4][4],int roundNumber){

//performing subbyte prime
unsigned char subbyteResult[4][4];
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
subbyteResult[j][i]=calculateSubbyte(input[j][i]);
}
}

//performing shift row
unsigned char shiftRowResult[4][4];
calculateShiftRow(subbyteResult,shiftRowResult);

//performing mixcolumn
unsigned char mixColumnResult[4][4];
calculateMixColumn(shiftRowResult,mixColumnResult);


//printing each round result
printf("-------Round %d Result---------\n",roundNumber);
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
input[j][i]=mixColumnResult[j][i];
printf("%hhx ",input[j][i]);
}
}
printf("\n\n");


}

//Round Function 10
void roundFunction10(unsigned char input[4][4],int roundNumber){

//performing subbyte
unsigned char subbyteResult[4][4];
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
subbyteResult[j][i]=calculateSubbyte(input[j][i]);
}
}

//performing shift row
unsigned char shiftRowResult[4][4];
calculateShiftRow(subbyteResult,shiftRowResult);

//printing round 10 result
printf("-------Round %d Result---------\n",roundNumber);
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
input[j][i]=shiftRowResult[j][i];
printf("%hhx ",input[j][i]);
}


}
printf("\n\n");


}

//function which performs encryption
void performEncryption(unsigned char input[4][4],unsigned char roundKeys[11][16]){

for(int i=1;i<=9;i++){

calculateXor(input,roundKeys[i-1]);
roundFunction1_9(input,i);

}

//----------Round 10 ------------
calculateXor(input,roundKeys[9]);
roundFunction10(input,10);

calculateXor(input,roundKeys[10]);

printf("------Final Encrypted Text----------\n");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
printf("%hhx ",input[j][i]);
}

}
printf("\n\n\n");

}

//Calculating and multiplying by inverse of X
unsigned char multiplyByInverseOfX(unsigned char temp){
return multiplyByX_ToThePowerK(temp,7)^multiplyByX_ToThePowerK(temp,3) ^multiplyByX_ToThePowerK(temp,2)^temp;
}

//traversing through subbyte table and finding i and j
unsigned char inverseSubbyte(unsigned char temp){
for(int i=0;i<16;i++){
for(int j=0;j<16;j++){
if(sub[i][j]==temp){
return (i<<4)|j;
}
}
}
}

//inverse of subbyte prime
unsigned char inverseSubbyte_Prime(unsigned char temp){
temp=inverseSubbyte(temp);
if(temp & 0x01 == 1){
temp=(temp>>1)<<1;
}
else{
temp=temp | 0x01;
}
temp=multiplyByInverseOfX(temp);
return temp;
}

//Inverse of Shift row (right circular shift by ith position)
void inverseShiftRow(unsigned char input[4][4],unsigned char result[4][4]){
for(int i=0;i<4;i++){
result[0][i]=input[0][i]; //first row remains unchanged
}

//for remaining rows
for(int i=1;i<4;i++){
int k=0;
for(int j=4-i;j<4;j++){
result[i][k]=input[i][j];
k++;
}
for(int j=0;j<4-i;j++){
result[i][k]=input[i][j];
k++;
}
}

}




//Inverse of Mix Column
void inverseMixColumn(unsigned char input[4][4],unsigned char result[4][4]){

for(int i=0;i<4;i++){
for(int j=0;j<4;j++){

//multiply by 165
unsigned char firstMult=multiplyByX_ToThePowerK(input[j][i],7) ^ multiplyByX_ToThePowerK(input[j][i],5) ^ multiplyByX_ToThePowerK(input[j][i],2) ^ input[j][i];

//multiply by 7
unsigned char secondMult=multiplyByX_ToThePowerK(input[(j+1)%4][i],2) ^ multiplyByX_ToThePowerK(input[(j+1)%4][i],1) ^ input[(j+1)%4][i];

//multiply by 26
unsigned char thirdMult=multiplyByX_ToThePowerK(input[(j+2)%4][i],4) ^ multiplyByX_ToThePowerK(input[(j+2)%4][i],3) ^ multiplyByX_ToThePowerK(input[(j+2)%4][i],1);

//multiply by 115
unsigned char forthMult=multiplyByX_ToThePowerK(input[(j+3)%4][i],6) ^ multiplyByX_ToThePowerK(input[(j+3)%4][i],5) ^ multiplyByX_ToThePowerK(input[(j+3)%4][i],4) ^ multiplyByX_ToThePowerK(input[(j+3)%4][i],1) ^ input[(j+3)%4][i];



result[j][i]=firstMult ^ secondMult ^ thirdMult ^ forthMult;

}
}
}

//Inverse of Round Function 1 to 9
void inverseOfRoundFunction1_9(unsigned char input[4][4],int roundNumber){

//Inverse of mixcolumn
unsigned char inverseMixColumnResult[4][4];
inverseMixColumn(input,inverseMixColumnResult);

//Inverse of Shift Row
unsigned char inverseShiftRowResult[4][4];
inverseShiftRow(inverseMixColumnResult,inverseShiftRowResult);


//Inverse of Subbyte
unsigned char inverseSubbyteResult[4][4];
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
inverseSubbyteResult[j][i]=inverseSubbyte_Prime(inverseShiftRowResult[j][i]);
}
}

for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
input[i][j]=inverseSubbyteResult[i][j];

}


}



}

//Inverse of Round Function 10
void inverseOfRoundFunction10(unsigned char input[4][4],int roundNumber){

//Inverse of Shift Row
unsigned char inverseShiftRowResult[4][4];
inverseShiftRow(input,inverseShiftRowResult);

//Inverse of subbyte
unsigned char inverseSubbyteResult[4][4];
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
inverseSubbyteResult[j][i]=inverseSubbyte_Prime(inverseShiftRowResult[j][i]);
}
}


for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
input[i][j]=inverseSubbyteResult[i][j];
}

}


}

//Performs Decryption
void performDecryption(unsigned char input[4][4],unsigned char roundKeys[11][16]){

calculateXor(input,roundKeys[10]);

printf("-------Decryption Begins  ---------\n\n");
printf("---------Result After cipherText xor 11th round key-------\n");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
printf("%hhx ",input[j][i]);  
}

}
printf("\n\n");


//----------Round 10 ------------
inverseOfRoundFunction10(input,10);
calculateXor(input,roundKeys[9]);

printf("-------Decrypting Round 10 ---------\n");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
printf("%hhx ",input[j][i]);
}

}
printf("\n\n");

//Round 9-1 decryption
for(int i=9;i>=1;i--){

inverseOfRoundFunction1_9(input,i);
calculateXor(input,roundKeys[i-1]);

printf("-------Decrypting Round %d ---------\n",i);
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
printf("%hhx ",input[j][i]);
}
}
printf("\n\n");

}

printf("------Final Decrypted Text----------\n");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
printf("%hhx ",input[j][i]);
}

}
printf("\n\n");

}







int main(){
//32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 7 34
unsigned char plaintext[4][4];
printf("Enter plain text(128 bits) : ");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
scanf("%hhx",&plaintext[j][i]);
}
}
//2b 7e 15 16 28 ae d2 a6 ab f7 15 88 9 cf 4f 3c
unsigned char key[16];
printf("Enter Key(128 bits) : ");
for(int i=0;i<16;i++){
scanf("%hhx",&key[i]);
}

//unsigned char plaintext[4][4]={{0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34}};
//unsigned char key[16]={0xaf,0xcd,0xea,0xe4,0xf6,0xa0,0x5c,0x1e,0xf0,0x99,0x92,0x59,0x12,0x4f,0x39,0x48};
//unsigned char key[16]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};

unsigned char input[4][4];
printf("\n------Plain Text----------\n");
for(int i=0;i<4;i++){
for(int j=0;j<4;j++){
input[j][i]=plaintext[j][i];
printf("%hhx ",plaintext[j][i]);
}

}
printf("\n\n");


printf("------------Round Keys---------\n");
unsigned char roundKeys[11][16];
//Generating round keys
keySchedulingAlgorithm(key,roundKeys);
for(int i=0;i<11;i++){
for(int j=0;j<16;j++){
printf("%hhx ",roundKeys[i][j]);
}
printf("\n");
}
printf("\n");

//Calling Encryption Function
performEncryption(input,roundKeys);

//Calling Decryption Function
performDecryption(input,roundKeys);



return 0;


}
