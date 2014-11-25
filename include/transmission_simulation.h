#ifndef TRANS_SIMUL_H_
#define TRANS_SIMUL_H_

/*
 * This program is used to simulate the encoding, transmission, integrity testing and
 * correction and decoding of a single char, as if passed over a network
 * The method for testing and correcting the bits is the Hamming Code.
 *
 * The parity of this simulation is even.
 *
 * Created by: Murray Christopherson 2009. Updated April 2010.
 */

/**
 * To ensure compiler and platform independence, this will calculate the size of the
 * array needed to store the bit pattern, with regards to CHAR_BIT
 * @pre no requirements
 * @post no change
 * @return the size of an array required to hold all bits nessessary for representing a char, and all check-bits. Also, for completionist sake,
 *         ensures total size fits in complete bytes (ie size is of form CHAR_BIT * n)
 */
int findBitPatternSize(void);
/**
 * Converts the char into a c-string representation
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to
 * 'size'. 'c' is the char to be represented
 * @post 'c' and 'size' unchanged. 'code' contains the string formatted as a bit pattern
 * to be transmitted
 */
void encodeChar(char c, char *code, int size);
/**
 * Goes through the 'code' and sets the check-bits (every bit with array index 2^n)
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to 'size'.
 * @post The check-bits in 'code' will be set appropriately
 */
void setCheckBits(char *code, int size);
/**
 * Flips the 'bitNum'th bit in 'code'. IE if the bit is 1, changes bit to 0 and vice versa
 * @pre 'bitNum' is not less than 0 and not greater than 'size'. 'code' is not NULL and
 * 'code' is accessible. 'code' array size is equal to 'size'.
 * @post 'code' will represent a bit pattern where the 'bitNum'th bit has been toggled
 */
void flipBit(int bitNum, char *code, int size);
/**
 * Using the check-bits and parity, returns the bit number that has been flipped.
 * Returns 0 if no bits have been flipped.
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to 'size'.
 * @post no change
 * @return the index that has been flipped. If no bit has been flipped, returns 0
 */
int checkCode(char *code, int size);
/**
 * Returns the char representation of 'code', as originally encoded by encodeChar()
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to 'size'.
 * @post no change
 * @return the char represented by the bit pattern in 'code'
 */
char decodeChar(char *code, int size);

/**
 * Prints every character of the code, check bits et al
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to 'size'.
 * @post no change
 */
void printFullPattern(char *code, int size);

/**
 * Prints the bit representation of the char
 * @pre 'code' is not NULL and 'code' is accessible. 'code' array size is equal to 'size'.
 * @post no change
 */

void printCharPattern(char c);

#endif