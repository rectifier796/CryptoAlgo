//Name - AYUSH SINGH
// ID  - 202051042

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t calculateRoundKeys(uint32_t key, int r){
    if(r==1){
        return key>>16;
    }
    if(r==2){
        return key>>12;
    }
    if(r==3){
        return key>>8;
    }
    if(r==4){
        return key>>4;
    }
    if(r==5){
        return key;
    }

}

uint16_t calculateXor(uint16_t a, uint16_t b){
    return a^b;
}

uint16_t performSubstitutionEncryption(uint16_t temp){

    int substituteBox[]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
    uint16_t beforeValue[4];
    uint16_t afterValue[4];


    beforeValue[0]=temp>>12;
    afterValue[0]=substituteBox[beforeValue[0]];

    beforeValue[1]=(temp&0x0f00)>>8;
    afterValue[1]=substituteBox[beforeValue[1]];

    beforeValue[2]=(temp&0x00f0)>>4;
    afterValue[2]=substituteBox[beforeValue[2]];

    beforeValue[3]=temp&0x000f;
    afterValue[3]=substituteBox[beforeValue[3]];

    uint16_t result=0x0000;

    int i=0;
    while(i<4){
        result=result<<4;
        result=result | afterValue[i];
        i++;
    }

    return result;


}

uint16_t performSubstitutionDecryption(uint16_t temp){

    int substituteBox[]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
    uint16_t beforeValue[4];
    uint16_t afterValue[4];


    beforeValue[0]=temp>>12;
    afterValue[0]=substituteBox[beforeValue[0]];

    beforeValue[1]=(temp&0x0f00)>>8;
    afterValue[1]=substituteBox[beforeValue[1]];

    beforeValue[2]=(temp&0x00f0)>>4;
    afterValue[2]=substituteBox[beforeValue[2]];

    beforeValue[3]=temp&0x000f;
    afterValue[3]=substituteBox[beforeValue[3]];


    uint16_t result=0x0000;

    int i=0;
    while(i<4){
        result=result<<4;
        result=result | afterValue[i];
        i++;
    }

    return result;


}


uint16_t performPermutation(uint16_t text){
    uint16_t beforeValue[]={text>>12,(text&0x0f00)>>8,(text&0x00f0)>>4,text&0x000f};
    uint16_t afterValue[]={0x0000,0x0000,0x0000,0x0000};

        uint16_t temp=0x0000;
        for(int j=0;j<4;j++){
            temp=temp<<1;
            temp=temp | (beforeValue[j]>>3);
        }
        afterValue[0]=temp;

        temp=0x0000;
        for(int j=0;j<4;j++){
            temp=temp<<1;
            temp=temp | ((beforeValue[j]&0x0004)>>2);
        }
        afterValue[1]=temp;

        temp=0x0000;
        for(int j=0;j<4;j++){
            temp=temp<<1;
            temp=temp | ((beforeValue[j]&0x0002)>>1);
        }
        afterValue[2]=temp;

        temp=0x0000;
        for(int j=0;j<4;j++){
            temp=temp<<1;
            temp=temp | (beforeValue[j]&0x0001);
        }
        afterValue[3]=temp;

        uint16_t result=0x0000;

        int i=0;
        while(i<4){
            result=result<<4;
            result=result | afterValue[i];
            i++;
        }

    return result;
}



int main()
{
    uint16_t plain;
    printf("Enter plain text (in Hex - 16 bit)  : ");
    scanf("%hx",&plain);


    uint32_t key;
    printf("Enter secret key (int Hex - 32 bit) : ");
    scanf("%x",&key);

    printf("Encryption Start-------------------------------------------------\n\n");
    //Round 1 Encryption-----------------------------------------------------
    printf("Round 1 Encryption : --------------------------------------------\n");
    uint16_t roundkey1=calculateRoundKeys(key,1);
    uint16_t cipherU1=calculateXor(roundkey1,plain);
    printf("Cipher U1 : %x\n",cipherU1);
    uint16_t cipherV1=performSubstitutionEncryption(cipherU1);
    printf("Cipher V1 : %x\n",cipherV1);
    uint16_t cipherW1=performPermutation(cipherV1);
    printf("Cipher W1 (Final Cipher Text of Round 1) : %x\n",cipherW1);


    //Round 2 Encryption-----------------------------------------------------
    printf("\n\nRound 2 Encryption : --------------------------------------------\n");
    uint16_t roundkey2=calculateRoundKeys(key,2);
    uint16_t cipherU2=calculateXor(roundkey2,cipherW1);
    printf("Cipher U2 : %x\n",cipherU2);
    uint16_t cipherV2=performSubstitutionEncryption(cipherU2);
    printf("Cipher V2 : %x\n",cipherV2);
    uint16_t cipherW2=performPermutation(cipherV2);
    printf("Cipher W2 (Final Cipher Text of Round 2) : %x\n",cipherW2);


    //Round 3 Encryption-----------------------------------------------------
    printf("\n\nRound 3 Encryption : --------------------------------------------\n");
    uint16_t roundkey3=calculateRoundKeys(key,3);
    uint16_t cipherU3=calculateXor(roundkey3,cipherW2);
    printf("Cipher U3 : %x\n",cipherU3);
    uint16_t cipherV3=performSubstitutionEncryption(cipherU3);
    printf("Cipher V3 : %x\n",cipherV3);
    uint16_t cipherW3=performPermutation(cipherV3);
    printf("Cipher W3 (Final Cipher Text of Round 3) : %x\n",cipherW3);


    //Round 4 Encryption-----------------------------------------------------
    printf("\n\nRound 4 Encryption : --------------------------------------------\n");
    uint16_t roundkey4=calculateRoundKeys(key,4);
    uint16_t cipherU4=calculateXor(roundkey4,cipherW3);
    printf("Cipher U4 : %x\n",cipherU4);
    uint16_t cipherV4=performSubstitutionEncryption(cipherU4);
    printf("Cipher V4 : %x\n",cipherV4);

    uint16_t roundkey5=calculateRoundKeys(key,5);
    uint16_t y=calculateXor(roundkey5,cipherV4);

    printf("\n----Final Cipher Text-----------\n");
    printf("Final Cipher Text : %x\n\n\n",y);


    //Decryption Start---------------------------------------------------------
    printf("Decryption Start-------------------------------------------------------\n\n");
    uint16_t decryptV4=calculateXor(y,roundkey5);
    printf("Decrypt Cipher V4 : %x\n",decryptV4);
    uint16_t decryptU4=performSubstitutionDecryption(decryptV4);
    printf("Decrypt Cipher U4 : %x\n",decryptU4);
    uint16_t decryptW3=calculateXor(decryptU4,roundkey4);
    printf("Decrypt Cipher W3 : %x\n",decryptW3);

    uint16_t decryptV3=performPermutation(decryptW3);
    printf("Decrypt Cipher V3 : %x\n",decryptV3);
    uint16_t decryptU3=performSubstitutionDecryption(decryptV3);
    printf("Decrypt Cipher U3 : %x\n",decryptU3);
    uint16_t decryptW2=calculateXor(decryptU3,roundkey3);
    printf("Decrypt Cipher W2 : %x\n",decryptW2);

    uint16_t decryptV2=performPermutation(decryptW2);
    printf("Decrypt Cipher V2 : %x\n",decryptV2);
    uint16_t decryptU2=performSubstitutionDecryption(decryptV2);
    printf("Decrypt Cipher U2 : %x\n",decryptU2);
    uint16_t decryptW1=calculateXor(decryptU2,roundkey2);
    printf("Decrypt Cipher W1 : %x\n",decryptW1);

    uint16_t decryptV1=performPermutation(decryptW1);
    printf("Decrypt Cipher V1: %x\n",decryptV1);
    uint16_t decryptU1=performSubstitutionDecryption(decryptV1);
    printf("Decrypt Cipher U1 : %x\n",decryptU1);
    uint16_t decryptPlain=calculateXor(decryptU1,roundkey1);
    printf("\n-------------Decrypted Text----------------------\n");
    printf("Final Plain Text After Decryption : %x\n",decryptPlain);

    return 0;
}
