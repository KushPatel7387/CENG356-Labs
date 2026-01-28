/*
 ============================================================================
 Name        : Lab2.c
 Author      : Kush Patel
 Version     :
 Copyright   :
 Description : Lab 2 - Signed integer and IEEE-754 float conversion
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 32   // maximum size of the binary number is 32 bit.
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"

void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);

// Menu text (fixed formatting)
char *menu =
    "\n"
    "===================================================================\n"
    "************Please select the following options********************\n"
    " *    1. Binary number to signed decimal number conversion.(Lab 2) *\n"
    " *    2. Binary number to Floating number conversion (Lab 2)       *\n"
    " *******************************************************************\n"
    " *    e. To Exit, Type 'e'                                         *\n"
    " *******************************************************************\n";

// Helper: clear leftover characters from input buffer after getchar()
static void clear_stdin_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard
    }
}

// Helper: remove newline from fgets (if used)
static void strip_newline(char *s)
{
    if (s == NULL) return;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

int main(void)
{
    char options;         // menu choice
    char inputs[33] = {0}; // 32-bit string + '\0'

    while (1) {
        puts(menu);

        options = getchar();
        clear_stdin_buffer(); // remove the newline after the option input

        switch (options) {

            case '1':
                puts("Please input your 8-bit BINARY number (example: 11111111):");
                // Read up to 32 chars, but we will validate length = 8 inside function
                if (fgets(inputs, sizeof(inputs), stdin) == NULL) {
                    puts("Input error.");
                    continue;
                }
                strip_newline(inputs);

                // Convert 8-bit binary string to signed decimal
                convert_binary_to_signed(inputs);
                continue;

            case '2':
                puts("Please input your 32-bit floating point number in binary:");
                puts("Tip: You can test using the PDF examples:");
                puts("     number1: " number1);
                puts("     number2: " number2);

                if (fgets(inputs, sizeof(inputs), stdin) == NULL) {
                    puts("Input error.");
                    continue;
                }
                strip_newline(inputs);

                // Convert 32-bit binary string to IEEE-754 float
                convert_binary_to_float(inputs);
                continue;

            case 'e':
            case 'E':
                puts("Code finished, exit now");
                return EXIT_SUCCESS;

            default:
                puts("Not a valid entry. Please try again.");
                continue;
        }
    }
}

/*
 * Option 1:
 * Convert an 8-bit binary string into a SIGNED decimal value using two's complement.
 */
void convert_binary_to_signed(const char *binary)
{
    if (binary == NULL) {
        puts("Error: null input");
        return;
    }

    int len = (int)strlen(binary);
    if (len != 8) {
        printf("Error: Option 1 requires exactly 8 bits (you entered %d bits).\n", len);
        return;
    }

    // Validate only 0/1
    for (int i = 0; i < 8; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            puts("Error: Input must contain only 0 or 1.");
            return;
        }
    }

    // Convert to integer (0..255)
    int value = 0;
    for (int i = 0; i < 8; i++) {
        value = (value << 1) | (binary[i] - '0');
    }

    // Two's complement signed conversion
    // If MSB is 1, value is negative: value - 256
    if (binary[0] == '1') {
        value -= 256;
    }

    printf("Binary (8-bit): %s\n", binary);
    printf("Signed decimal value: %d\n", value);
}

/*
 * Option 2:
 * Convert a 32-bit binary string into an IEEE-754 single precision float (decimal).
 * Format: [1 sign bit][8 exponent bits][23 fraction bits]
 */
void convert_binary_to_float(const char *binary)
{
    if (binary == NULL) {
        puts("Error: null input");
        return;
    }

    int len = (int)strlen(binary);
    if (len != 32) {
        printf("Error: Option 2 requires exactly 32 bits (you entered %d bits).\n", len);
        return;
    }

    // Validate only 0/1
    for (int i = 0; i < 32; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            puts("Error: Input must contain only 0 or 1.");
            return;
        }
    }

    int sign = binary[0] - '0';

    // Exponent (bits 1..8)
    int exp = 0;
    for (int i = 1; i <= 8; i++) {
        exp = (exp << 1) | (binary[i] - '0');
    }

    // Fraction/Mantissa (bits 9..31)
    double frac = 0.0;
    double place = 0.5; // first fraction bit = 2^-1
    for (int i = 9; i < 32; i++) {
        if (binary[i] == '1') frac += place;
        place /= 2.0;
    }

    printf("Binary (32-bit): %s\n", binary);

    // IEEE-754 special cases
    if (exp == 255) {
        if (frac == 0.0) {
            printf("Floating-point value: %sInfinity\n", sign ? "-" : "+");
        } else {
            printf("Floating-point value: NaN\n");
        }
        return;
    }

    double value;

    if (exp == 0) {
        // Denormalized: (-1)^sign * (0.fraction) * 2^(1-127) = 2^-126
        value = (sign ? -1.0 : 1.0) * (frac) * pow(2.0, -126);
    } else {
        // Normalized: (-1)^sign * (1.fraction) * 2^(exp-127)
        value = (sign ? -1.0 : 1.0) * (1.0 + frac) * pow(2.0, (double)(exp - 127));
    }

    printf("Floating-point value: %.10g\n", value);
}

