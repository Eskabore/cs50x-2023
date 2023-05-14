#include <stdio.h>
#include <stdlib.h>
// Add cs50 library for bool
#include <cs50.h>

#define BLOCK_SIZE 512 // size of each block in bytesne
#define FILE_NAME_LENGTH 8 // length of the file name, including ".jpg"

int main(int argc, char *argv[])
{
    // Check that the user provided the correct number of command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open forensic image file
    char *image_file = argv[1];
    FILE *inptr = fopen(image_file, "r");

    // Checck if the file was successfully opened
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image_file);
        return 1;
    }

    // Initialize variables
    bool jpeg_found = false; // flag to track if a JPEG has been found
    char *filename = malloc(FILE_NAME_LENGTH); // allocate memory for the file name
    int file_number = 0; // counter for the number of JPEGs found
    unsigned char *block = malloc(BLOCK_SIZE); // allocate memory for a block of data
    FILE *outptr = NULL; // declare outter pointer

    // Read the forensic image file block by block
    while (fread(block, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Check if block is the start of aJPEG file
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // Close previous JPEG file if one was found
            if (jpeg_found)
            {
                fclose(outptr);
            }
            else
            {
                jpeg_found = true;
            }

            // Generate the file name for the new JPEG
            sprintf(filename, "%03d.jpg", file_number);
            file_number++;

            // Open the new JPEG file for writing
            outptr = fopen(filename, "w");

            // Check if the file was successfully opened
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 1;
            }

            // Write the block to the JPEG file
            fwrite(block, BLOCK_SIZE, 1, outptr);
        }
        else if (jpeg_found)
        {
            // Write block to the JPEG file
            fwrite(block, BLOCK_SIZE, 1, outptr);
        }
    }

    // Close the last JPEG file, if one was found
    if (jpeg_found)
    {
        fclose(outptr);
    }

    // Close the forensic image file
    fclose(inptr);

    // Free the allocated memory
    free(filename);
    free(block);

    return 0;
}