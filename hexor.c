#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 400

const int key = 0x42;

int input[BUFSIZE];
int encrypted[BUFSIZE];

int convert_to_number(char * hexs)
{
    if (strlen(hexs) < 3)
    {
        return (int)strtol(hexs, 0, 16);
    }
    return EXIT_FAILURE; 
}

int xor(int op1, int op2)
{
    return op1 ^ op2;
}


int main (int argc, char **argv)
{
    char chr = 0;
    int file_index = 0;
    int hex_index = 0;
    char hexs[3];

    FILE *fp = fopen(argv[1], "r");

    while ((chr = fgetc(fp)) != EOF && file_index < BUFSIZE )
    {
        if (('0' <= chr && chr <= '9') || ('a' <= chr && chr <= 'f') || ('A' <= chr && chr <= 'F'))
        {
            hexs[hex_index] = chr;
            hex_index++;
            if (hex_index == 2)
            {
                hex_index = 0;
                input[file_index] = convert_to_number(hexs);
                file_index++;
            }
        }
    }
    fclose(fp);

    if (file_index == BUFSIZE)
    {
        printf("input buffer limit of %d hex numbers was reached\n", BUFSIZE*2);
        printf("last hex that was read in and will be processed: %02x\n", input[file_index-1]);
    }

    printf("\nInput base16: \t\t");
    for (int i = 0; i < file_index; i++)
    {
        printf("%02x ", input[i]);
    }
    
    printf("\n");
    printf("\nInput base10: \t\t");
    for (int i = 0; i < file_index; i++)
    {
        printf("%d ", input[i]);
    }

    printf("\n\nEncrypting using XOR with Key = 0x%02x (0d%d)\n", key, key);

    printf("\nEncrypted base10:\t");
    for (int i = 0; i < file_index; i++)
    {
        encrypted[i] = xor(input[i], key);
        printf("%d ", encrypted[i]);
    }

    printf("\n");
    printf("\nEncrypted base16:\t");
    for (int i = 0; i < file_index; i++)
    {
        printf("%02x ", encrypted[i]);
    }

    printf("\n");
    printf("\nEncrypted base16:\t");
    for (int i = 0; i < file_index; i++)
    {
        printf("%02x", encrypted[i]);
    }

    return 0;
}