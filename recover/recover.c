#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define BYTE type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Define buffer size
    const int BLOCK_SIZE = 512;

    // Open the memory card
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 2;
    }

    // Create a buffer for a block of data
    unsigned char buffer[BLOCK_SIZE];

    // Create pointer to outfile
    FILE *outptr = NULL;

    // Create space for file name
    char image[10];

    // Initialise JPEG counter
    int n = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Check if JPEG is found
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] & 0xF0) == 0xE0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(image, "%03d.jpg", n);

            // Open nth image file
            outptr = fopen(image, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", image);
                fclose(inptr);
                return 3;
            }

            // Increment number of image files created
            n++;
        }

        // Continue writing to JPEG if new JPEG not found
        if (outptr != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }

    // Close last opened outfile
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    // Close input file (card.raw)
    if (outptr != NULL)
    {
        fclose(inptr);
    }

    return 0;
}
