#include <stdio.h>

// prototypes for functions below
void printChar();
void printShort();
void printInt();
void printLong();
void printFloat();
void printDouble();

// main method where the logic of user input is taken care of
int main() {

    // from inClass project getLine
    ssize_t numchars = 0;
	char *buffer = NULL;
	size_t length = 0;

    // variable for the user input
    char userInput;

    // prompting the user for input
    printf("Enter c|s|i|l|f|d <cntl+D to exit>: ");

    // also from getLine project
    while((numchars = getline(&buffer, &length, stdin)) != -1) {
        buffer[numchars - 1] = '\0';
	    int input = sscanf(buffer, "%c", &userInput);
        // first switch is whether the user actually input anything
        switch (input) {
            case 1:
                // if there is user input, is the input only 1 character
                if ((numchars - 1) > 1) {
                    printf("Please enter a single lowercase character.\n");
                // if it is valid, then move to the cases of each valid data type
                } else {
                    // This switch case is for the user input, which ever case matches the input it will execute, unless none match
                    switch (userInput) {
                        case 'c':
                            printChar();
                            break;
                        case 's':
                            printShort();
                            break;
                        case 'i':
                            printInt();
                            break;
                        case 'l':
                            printLong();
                            break;
                        case 'f':
                            printFloat();
                            break;
                        case 'd':
                            printDouble();
                            break;
                        default:
                            // there is input, but it is not in proper format
                            printf("Invalid input.\n");
                            break;
                    }
                }
                break;
            default:
                printf("No input detected.\n");
                break;
        }
        // re-prompt so loop continues to run
        printf("Enter c|s|i|l|f|d <cntl+D to exit>: ");
    }

    // when loop is done (main) running, return a value
    return 0;
}

/* - for the signed and unsigned integral types (char, short, int, long), the code is exactly the same for every function
      - only difference is the type and the print formatting (i.e. char vs short vs long vs int, and %d vs %c vs %ld etc.)
   - for unsigned, they are unable to hold negative numbers, so i am setting all of the bits to 0 to find the minimum,
     and to find the maximum, i am taking the complement of the minimum
   - for the signed variables it is a little bit different since they are able to store negative numbers.
   - for the minimum value, i am performing a left shift of the value 1 (00000001), into the left most significant bit,
     this is possible by taking the sizeof the type (ex. sizeof(int) = 4), which i multiply by 8 to get the number of bits.
     from here, i am subtracting 1 because the left most bit is for the sign, so num - 1 is the bit we care about.
   - for the maximum value, i am simply taking the complement of the minimum value.
*/

// printing the ranges for 'char'
void printChar() {
    unsigned char uMin = 0;
    unsigned char uMax = ~0;
    char sMin = 1 << (sizeof(sMin) * 8 - 1);
    char sMax = ~sMin;
    printf("Unsigned Minimum Value: %u\nUnsigned Maximum Value: %u\n", uMin, uMax);
    printf("Signed Minimum Value: %d\nSigned Maximum Value: %d\n", sMin, sMax);
}

// printing the ranges for 'short'
void printShort() {
    unsigned short uMin = 0;
    unsigned short uMax = ~0;
    short sMin = 1 << (sizeof(sMin) * 8 - 1);
    short sMax = ~sMin;
    printf("Unsigned Minimum Value: %u\nUnsigned Maximum Value: %u\n", uMin, uMax);
    printf("Signed Minimum Value: %d\nSigned Maximum Value: %d\n", sMin, sMax);
}

// printing the ranges for 'int'
void printInt() {
    unsigned int uMin = 0;
    unsigned int uMax = ~0;
    int sMin = 1 << (sizeof(sMin) * 8 - 1);
    int sMax = ~sMin;
    printf("Unsigned Minimum Value: %u\nUnsigned Maximum Value: %u\n", uMin, uMax);
    printf("Signed Minimum Value: %d\nSigned Maximum Value: %d\n", sMin, sMax);
}

// printing the ranges for 'long'
void printLong() {
    unsigned long uMin = 0;
    unsigned long uMax = ~0;
    long sMin = 1L << (sizeof(sMin) * 8 - 1);
    long sMax = ~sMin;
    printf("Unsigned Minimum Value: %lu\nUnsigned Maximum Value: %lu\n", uMin, uMax);
    printf("Signed Minimum Value: %ld\nSigned Maximum Value: %lu\n", sMin, sMax);
}

// printing the ranges for 'float'
void printFloat() {
    // creat a union to manipulate the bits of the unsigned int
    union {
        unsigned int change;
        float out;
    } u32;
    // initalize all bits to 0
    u32.change = 0;
    /* putting a 0 in the sign bit, and then putting the value of 1 in the exponent, 0's for the entire fraction
       since the exponent is biased (127), having 1 - 127 will give you the smallest possible number for the minimum value
    */
    u32.change = (1 << (sizeof(u32.change) * 8 - 9));
    printf("Minimum Value: %.10e\n", u32.out);
    // reset bits to 0
    u32.change = 0;
    // keeping the sign bit to 0, but placing 1s for the other 31 values
    for(int i = sizeof(u32.change) * 8 - 2; i >= 0; i--) {
        // if we used = instead of |= it would reset the bits everytime, this fully updates
        u32.change |= 1 << i;
    }
    /* using the and operator to prioritize 0 value
       u32.change                        = 0111 1111 1111 1111 1111 1111 1111 1111
       1 << (sizeof(u32.change) * 8 - 9) = 0000 0000 1000 0000 0000 0000 0000 0000
       complement of this ^              = 1111 1111 0111 1111 1111 1111 1111 1111 
       after & operation                 = 0111 1111 0111 1111 1111 1111 1111 1111 
    */
    u32.change &= ~(1 << (sizeof(u32.change) * 8 - 9));
    printf("Maximum Value: %.10e\n", u32.out);
    // reset to 0
    u32.change = 0;
    printf("Hex representation of +0: %a\n", u32.out);
    // keep value as 0, but change sign to negative
    u32.change = 1 << (sizeof(u32.change) - 1);
    printf("Hex representation of -0: %a\n", u32.out);
    // reset
    u32.change = 0;
    // set all exponent bits and sign bit to 1
    for(int i = (sizeof(u32.change) * 8 - 1); i >= 23; i--) {
        u32.change |= 1 << i;
    }
    printf("Hex representation of -INF: %x\n", u32.change);
    // change sign
    u32.change &= ~(1 << (sizeof(u32.change) * 8 - 1));
    printf("Hex representation of +INF: %x\n", u32.change);
    // reset
    u32.change = 0;
    // all 1s
    u32.change = ~0;
    printf("Hex representation of -NaN: %x\n", u32.change);
    // change sign
    u32.change &= ~(1 << (sizeof(u32.change) * 8 - 1));
    printf("Hex representation of +NaN: %x\n", u32.change);
}

// printing the ranges for 'double', same as float except for size of bits
void printDouble() {
    union {
        // float is 4 bytes, unsigned int is 32 bits. double is 8 bytes, unsigned long long is 64 bits
        unsigned long long change;
        double out;
    } u64;
    u64.change = 0;
    u64.change = (1LL << (sizeof(u64.change) * 8 - 12));
    printf("Minimum Value: %.10e\n", u64.out);
    u64.change = 0;
    for(int i = sizeof(u64.change) * 8; i >= 0; i--) {
        u64.change |= 1 << i;
    }
    u64.change = u64.change & ~(1LL << (sizeof(u64.change) * 8 - 1)) & ~(1LL << (sizeof(u64.change) * 8 - 12));
    printf("Maximum Value: %.10e\n", u64.out);
    u64.change = 0;
    printf("Hex representation of +0: %a\n", u64.out); // a - .out
    u64.change = 1LL << ((sizeof(u64.change) * 8 - 1));
    printf("Hex representation of -0: %a\n", u64.out); // a - .out
    u64.change = 0;
    for(int i = (sizeof(u64.change) * 8 - 1); i >= 52; i--) {
        u64.change |= 1LL << i;
    }
    // change format to long long x instead of x
    printf("Hex representation of -INF: %llx\n", u64.change);
    u64.change &= ~(1LL << (sizeof(u64.change) * 8 - 1));
    printf("Hex representation of +INF: %llx\n", u64.change);
    u64.change = 0;
    u64.change = ~0;
    printf("Hex representation of -NaN: %llx\n", u64.change);
    u64.change &= ~(1LL << (sizeof(u64.change) * 8 - 1));
    printf("Hex representation of +NaN: %llx\n", u64.change);
}