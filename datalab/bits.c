/* 
 * CS:APP Data Lab 
 * 
 * <Atij Mahesh 905954423>
 */

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
       /*uses negation and legal ops to check if x is the signed max value*/
       return !((x + 1) ^ (~x)) & !!(~x);
}
//2
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /*Sets x to 0x55 (which is 01010101), adds 8 0s at the end with
artithmetic shift right then "adds" x to the end with or, then does the
same for the remaning 16 bits*/
  int x = 0x55;
  x = (x<<8) | x;
  return (x<<16) | x;
}
//3
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  /*^ operator to check overlap between x and y, which should be 0 if x = y*/
  return !(x^y);
}
//4
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /*Shifts x by 32-n right (so only important bits are included), then arithmitically right shifts
so that the first 32-n bits are filled with 1s or 0s depending on n's sign. then checks the union between x and
the shortened number, returning the opposite to denote if two's compliment is possible*/
  int shortened = (x<<(33+~n))>>(33+~n);
  return !(shortened^x);
}
//5
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*finds false and true shift values, then compares them to determine weather to output y or z*/
  int falseShift = (!!x)<<4;
  int trueShift = 17 + ~falseShift;
  return ((y<<trueShift)<<trueShift) | ((z<<falseShift)<<falseShift);
}
//6
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*finds sign of x and y and checks that y is not greater than or equal to x*/
  int signX = x>>31;
  int signY = y>>31;
  int areEqual = !(signX ^ signY) & ((~y + x) >> 31);
  int notEqual = signX & !signY;
  return !(areEqual | notEqual);
}
//7
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  /*first multiplies x by 5, then bias it to account for overflow behavior before finally dividing it by 8*/
  int fiveX = (x<<2)+x;
  int bias = (fiveX>>31)&7;
  return (fiveX+bias)>>3;
}
//8
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*get an int all ones, then right shifting it, then adding 1 to get either all zeros due to overflow or 1*/
  int allOnes = (~x+1) | x;
  return (allOnes>>31) +1;
}
//9
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  /*extract sign form x, then get the absolute value of x, returning the sign union (or) between a 4 byte int that is 0s or 1s with absolute val of x*/
  int sign = x >> 31;
  int absX = (x ^ sign) + (~sign + 1);
  return (sign << 31) | absX;
}
//10
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  /*check if x is positive and not zero (small catches), then if its a power of2*/
  int sign = x>>31;
  int notZero = !!x;
  int powerOfTwo = !(x&(x+~0));
  return notZero & !sign & powerOfTwo;
}
