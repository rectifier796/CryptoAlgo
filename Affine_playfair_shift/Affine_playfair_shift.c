#include <stdio.h>


//for searching in the keymatrix
void search(char first,char second, int arr[],char keymatrix[5][5]){

for(int i=0;i<5;i++){
for(int j=0;j<5;j++){

if(first==keymatrix[i][j]){
arr[0]=i;
arr[1]=j;
}
if(second==keymatrix[i][j]){
arr[2]=i;
arr[3]=j;
}
}
}
}


//Logic for encryption using playfair cipher
void playfairEncryption(char cipher1[],char str[],char keymatrix[5][5],int n){

for(int i=0;i<n;i=i+2){
int arr[4];
char first=str[i];
char second=str[i+1];
search(first,second,arr,keymatrix);


if(arr[0]==arr[2]){
cipher1[i]=keymatrix[arr[0]][(arr[1]+1)%5];
cipher1[i+1]=keymatrix[arr[2]][(arr[3]+1)%5];
}
else if(arr[1]==arr[3]){
cipher1[i]=keymatrix[(arr[0]+1)%5][arr[1]];
cipher1[i+1]=keymatrix[(arr[2]+1)%5][arr[3]];
}
else{
cipher1[i]=keymatrix[arr[0]][arr[3]];
cipher1[i+1]=keymatrix[arr[2]][arr[1]];
}


}

}


//login for decryption using playfair
void playfairDecryption(char decrypt1[],char str[],char keymatrix[5][5],int n){

for(int i=0;i<n;i=i+2){
int arr[4];
char first=str[i];
char second=str[i+1];
search(first,second,arr,keymatrix);


if(arr[0]==arr[2]){
decrypt1[i]=keymatrix[arr[0]][(arr[1]+5-1)%5];
decrypt1[i+1]=keymatrix[arr[2]][(arr[3]+5-1)%5];
}
else if(arr[1]==arr[3]){
decrypt1[i]=keymatrix[(arr[0]+5-1)%5][arr[1]];
decrypt1[i+1]=keymatrix[(arr[2]+5-1)%5][arr[3]];
}
else{
decrypt1[i]=keymatrix[arr[0]][arr[3]];
decrypt1[i+1]=keymatrix[arr[2]][arr[1]];
}


}

}



//Encryption using Affine cipher
void encrypt(char cipher2[],char plain[],int l,int a, int b){
for(int i=0;i<l;i++){
cipher2[i]=(a*(plain[i]-'a') + b)%26 + 'a';
}
}

//Decryption using Affine Cipher
int decrypt(char cipher[],int l,int a_inverse, int b){
for(int i=0;i<l;i++){
cipher[i]=(((cipher[i]-'a') - b + 26)*a_inverse)%26 + 'a';
}
}


//Calculating Inverse
int calculateInverse(int a,int m){
for(int i=1;i<m;i++){
if((a*i)%m==1)
return i;
}
return -1;
}


//Calculating GCD
int calculateGCD(int x , int y){
if(x==0)
return y;

return calculateGCD(y%x,x);
}






int main(){
int n;
printf("Enter the length of plain text : ");
scanf("%d",&n);
char str[2*n + 1];
printf("Enter plain text : ");

scanf("%s",str);


//Converting 'j' to 'i'
for(int i=0;i<n;i++){
if(str[i]=='j'){
str[i]='i';
}
}

//Removing Repeatation
char tempstr[2*n+1];
int j=0;
for(int i=0;i<n;i++){
if((i+1)<n && str[i]==str[i+1]){
tempstr[j]=str[i];
tempstr[j+1]='x';
j=j+2;
}
else{
tempstr[j]=str[i];
j++;
}
}
n=j;

for(int i=0;i<j;i++){
str[i]=tempstr[i];
}
str[j]='\0';

//Making string of even length
if(n%2!=0){
str[n]='x';
n=n+1;
}

printf("Delta : ");
for(int i=0;i<n;i++){
printf("%c",str[i]);
}
printf("\n");


int k1;
printf("Enter the length of key of playfair cipher : ");
scanf("%d",&k1);
printf("Enter first Key (key 1) : ");
char key1[k1];
//for(int i=0;i<k1;i++){
scanf("%s",key1);
//}
printf("%s",key1);

//Converting 'j' to 'i'
for(int i=0;i<k1;i++){
if(key1[i]=='j'){
key1[i]='i';
}
}

int flag[26];
int k=0,q=0;
char temp='a';
char keymatrix[5][5];

//Building the key matrix
for(int i=0;i<5;i++){
for(int j=0;j<5;j++){

if(k>=k1){
while(flag[temp-'a']!=0 || temp=='j'){
temp=temp+1;
}
keymatrix[i][j]=temp;
temp++;
}
else {
while(flag[key1[k]-'a']!=0){
k++;
}
if(k>=k1){
j--;
continue;
}
keymatrix[i][j]=key1[k];
flag[key1[k]-'a']++;
}
k++;
}
}

printf("Key Matrix of Playfair Cipher : \n");
for(int i=0;i<5;i++){
for(int j=0;j<5;j++){
printf("%c ",keymatrix[i][j]);
}
printf("\n");
}

char cipher1[n];
playfairEncryption(cipher1,str,keymatrix,n);

printf("Cipher Text of Playfair Cipher : ");
for(int i=0;i<n;i++){
printf("%c",cipher1[i]);
}
printf("\n");

printf("------------------------------------------------\n");

//Beginning of Affine Cipher Encryption

int a=11,b=15;

int a_inverse;

if(calculateGCD(a,26)!=1){
printf("Invalid Input 'a'\n");
return -1;
}

a_inverse=calculateInverse(a,26);

char cipher2[n];


encrypt(cipher2,cipher1,n,a,b);

printf("Cipher Text of Affine Cipher : ");
for(int i=0;i<n;i++){
printf("%c",cipher2[i]);
}
printf("\n");



printf("----------------------------------------\n");

//Beginning of Shift Cipher Encryption
getchar();
printf("Enter the key for Shift Cipher (small letter only) : ");
char key3;
scanf(" %c",&key3);

char cipher3[n];

for(int i=0;i<n;i++){
cipher3[i]=((cipher2[i]-'a')+(key3-'a'))%26 + 'a';
}


printf("Cipher Text of Shift Cipher : ");
printf("\n--------------------------------------------\n");
for(int i=0;i<n;i++){
printf("%c",cipher3[i]);
}
printf("\n");

//Shift Cipher Decryption

char decrypted3[n];

for(int i=0;i<n;i++){
decrypted3[i]=((cipher3[i]-'a') + 26 - (key3-'a'))%26 + 'a';
}
printf("Decrypted Text of Shift Cipher : ");
for(int i=0;i<n;i++){
printf("%c",decrypted3[i]);
}
printf("\n");

printf("--------------------------------------------\n");

//Affine Decryption
decrypt(decrypted3,n,a_inverse,b);
printf("Decrypted Text of Affine Cipher : ");
for(int i=0;i<n;i++){
printf("%c",decrypted3[i]);
}
printf("\n");

printf("--------------------------------------------\n");

//Playfair Decryption

char finaldecryption[n];
playfairDecryption(finaldecryption,decrypted3,keymatrix,n);
printf("Final Decrypted Text of Playfair Cipher : ");
for(int i=0;i<n;i++){
printf("%c",finaldecryption[i]);
}
printf("\n");

return 0;


}



