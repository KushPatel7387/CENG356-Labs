/* Name: Kush Patel */                                      // Student name comment
/* Student ID: N01657387 */                                 // Student ID comment

#include <stdio.h>                                          // Provides printf

struct Account {                                            // Define struct Account as required
    unsigned int account_number;                            // Account number field
    char account_type;                                      // Account type field
    char *last_name;                                        // Pointer to last name
    char *first_name;                                       // Pointer to first name
    float balance;                                          // Balance field
    char reserved[6];                                       // Reserved bytes
};

int main(void) {                                            // Program starting point

    char ant = 'A';                                         // char variable (animal name)
    short bear = 10;                                        // short variable (animal name)
    int cat = 100;                                          // int variable (animal name)
    long dog = 1000L;                                       // long variable (animal name)
    float eagle = 1.5f;                                     // float variable (animal name)
    double fox = 2.5;                                       // double variable (animal name)

    int *iguana = &cat;                                     // pointer to int (animal name)
    long *jaguar = &dog;                                    // pointer to long (animal name)
    float *koala = &eagle;                                  // pointer to float (animal name)
    double *lion = &fox;                                    // pointer to double (animal name)

    struct Account monkey;                                  // struct Account variable (animal name)
    struct Account *newt = &monkey;                         // pointer to struct Account (animal name)

    printf("Sizes in bytes (sizeof):\n");                   // Print title line

    printf("char (%c): %zu\n", ant, sizeof(ant));           // Print char size
    printf("short (%d): %zu\n", bear, sizeof(bear));        // Print short size
    printf("int (%d): %zu\n", cat, sizeof(cat));            // Print int size
    printf("long (%ld): %zu\n", dog, sizeof(dog));          // Print long size
    printf("float (%.2f): %zu\n", eagle, sizeof(eagle));    // Print float size
    printf("double (%.2f): %zu\n", fox, sizeof(fox));       // Print double size

    printf("pointer to int: %zu\n", sizeof(iguana));        // Print pointer-to-int size
    printf("pointer to long: %zu\n", sizeof(jaguar));       // Print pointer-to-long size
    printf("pointer to float: %zu\n", sizeof(koala));       // Print pointer-to-float size
    printf("pointer to double: %zu\n", sizeof(lion));       // Print pointer-to-double size

    printf("struct Account: %zu\n", sizeof(monkey));        // Print struct size
    printf("pointer to struct Account: %zu\n", sizeof(newt));// Print pointer-to-struct size

    return 0;                                               // End program successfully
}
