// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    /*
    Using `fseek` to move the file position indicator to the start of the input file
    bfore reading the header
    */
    fseek(input, 0, SEEK_SET);

    // Read header from input file
    uint8_t header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, input);

    // Write header to output file
    fwrite(header, 1, HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, 2, 1, input) == 1)
    {
        // Apply scaling factor to sample
        buffer = (int16_t)(buffer * factor);

        // Write modified sample to output file
        fwrite(&buffer, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
