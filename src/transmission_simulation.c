#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#include "../include/transmission_simulation.h"

#define INFLUSH while (getchar() != '\n') continue

int main(int argc, char **argv)
{
    char toTrans;
    int myFlipBit = -1;
    int bitPatternSize = findBitPatternSize();
    char *code = (char *) malloc(bitPatternSize * sizeof (char));
    if(code == NULL)
    {
        printf("Memory could not be allocated");
        return -1;
    }
    printf("Please Input A Char To Be Transmitted:\n");
    toTrans = getchar();
    INFLUSH;
    while (1)
    {
        printf("Please Input Bit You Wish To Flip (Between 1 and %d, 0 Means No Bits Flipped):\n", bitPatternSize);
        scanf("%d", &myFlipBit);
        INFLUSH;
        if (myFlipBit >= 0 && myFlipBit <= bitPatternSize)
        {
            break;
        }
        printf("Error: You Must Input An Integer Between 0 and %d\n",
               bitPatternSize);
    }

    //General Information about Transmission
    printf("Each Packet is %d bits\n", CHAR_BIT);
    printf("Full Transmission will require %d packets, totalling %d bits sent\n",
           bitPatternSize / CHAR_BIT, bitPatternSize);

    //Encoding Message
    printf("Transmitting character '%c'\n", toTrans);
    encodeChar(toTrans, code, bitPatternSize);
    printf("Bit Pattern of '%c': ", toTrans);
    printCharPattern(decodeChar(code, bitPatternSize));
    putchar('\n');
    printf("Full Transmission Pattern: ");
    printFullPattern(code, bitPatternSize);
    putchar('\n');

    //Transmitting Message
    if (myFlipBit > 0)
    {
        printf("It is being corrupted by flipping bit %d\n", myFlipBit);
        flipBit(myFlipBit - 1, code, bitPatternSize);
        char corrupted = decodeChar(code, bitPatternSize);
        printf("The Corrupted Character is '%c'\n", corrupted);
        printf("Bit Pattern of '%c': ", corrupted);
        printCharPattern(corrupted);
        putchar('\n');
        printf("Full Transmission Pattern: ");
        printFullPattern(code, bitPatternSize);
        putchar('\n');
    }
    else
    {
        printf("No bit is being corrupted\n");
    }

    //Receiving and correcting Message
    printf("Correcting Transmission...\n");
    int checkFlipBit = checkCode(code, bitPatternSize);
    if(checkFlipBit > 0)
    {
        flipBit(checkFlipBit - 1, code, bitPatternSize);
    }
    printf("The Correct Character is '%c'\n", decodeChar(code, bitPatternSize));

    free(code);
    return 0;
}

int findBitPatternSize(void)
{
    int size = 0;
    int counter = 0;
    unsigned int power2 = 0x01;
    while(counter < CHAR_BIT)
    {
        if(size != power2)
        {
            ++counter;
        }
        else
        {
            power2 <<= 1;
        }
        ++size;
    }
    while(size % CHAR_BIT != 0)
    {
        ++size;
    }
    return size;
}

void encodeChar(char c, char *code, int size)
{
    unsigned int encode = 0x01 << (CHAR_BIT - 1);
    int counter = 1;
    unsigned int power2 = 0x01;
    int bitsPassed = 0;
    while(bitsPassed < CHAR_BIT)
    {
        if(counter != power2)
        {
            if(encode & c)
            {
                code[counter - 1] = 1;
            }
            else
            {
                code[counter - 1] = 0;
            }
            encode >>= 1;
            ++bitsPassed;
        }
        else
        {
            power2 <<= 1;
        }
        ++counter;
    }
    setCheckBits(code, size);
}

void setCheckBits(char *code, int size)
{
    unsigned int bitNum = 0x01;
    while(bitNum < size)
    {
        unsigned int checker = 0;
        int counter = 1;
        while(counter <= size)
        {
            if(counter & bitNum)
            {
                checker ^= code[counter - 1];
            }
            ++counter;
        }
        if(checker)
        {
            code[bitNum - 1] = 1;
        }
        else
        {
            code[bitNum - 1] = 0;
        }
        bitNum <<= 1;
    }
}

void flipBit(int bitNum, char *code, int size)
{
    if(code[bitNum] > 0)
    {
        code[bitNum] = 0;
    }
    else
    {
        code[bitNum] = 1;
    }
}

int checkCode(char *code, int size)
{
    int wrongBit = 0;
    unsigned int bitNum = 0x01;
    while(bitNum < size)
    {
        int checker = 0;
        int counter = 1;
        while(counter <= size)
        {
            if(counter & bitNum)
            {
                checker ^= code[counter - 1];
            }
            ++counter;
        }
        if(checker)
        {
            wrongBit += bitNum;
        }
        bitNum <<= 1;
    }
    return wrongBit;
}

char decodeChar(char *code, int size)
{
    char decode = 0;
    int counter = 1;
    unsigned int power2 = 0x01;
    int bitsLeft = 0;
    while(bitsLeft < CHAR_BIT)
    {
        if(counter != power2)
        {
            decode += code[counter - 1] * (1 << (CHAR_BIT - 1 - bitsLeft));
            ++bitsLeft;
        }
        else
        {
            power2 <<= 1;
        }
        ++counter;
    }
    return decode;
}

void printFullPattern(char *code, int size)
{
    int i;
    for(i = 0; i < size; ++i)
    {
        printf("%d", code[i]);
    }
}

void printCharPattern(char c)
{
    int mask = 0x01 << (CHAR_BIT - 1);
    int i;
    for(i = CHAR_BIT; i > 0; --i)
    {
        int code = c & mask;
        if(code)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
        mask >>= 1;
    }
}
