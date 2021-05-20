// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) // TO USE: ./volume input.wav output.wav 2.0
{
    // CHECK COMMAND-LINE ARGUMENTS
    if (argc != 4) // No. of arguments must be 4
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r"); // Open file input.wav
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w"); // Open file output.wav
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); // Converts the sound-multiplier input string to a float number.

    // TODO: Copy header from input file to output file
    // 1. You’ll likely want to create an array of bytes to store the data from the WAV file header that you’ll read from the input file.
    //    Using the uint8_t type to represent a byte, you can create an array of n bytes for your header with syntax like uint8_t header[n]; , replacing n with the number of bytes.
    // 2. You can then use header as an argument to fread or fwrite to read into or write from the header.
    //    You’ll likely want to create a “buffer” in which to store audio samples that you read from the WAV file. USING the int16_t type to store an audio sample, you can create a buffer variable with syntax like int16_t buffer;
    // 3. You can then use &buffer as an argument to fread or fwrite to read into or write from the buffer. (Recall that the & operator is used to get the address of the variable.)

    // TODO: Read samples from input file and write updated data to output file

    int n = HEADER_SIZE;

    uint8_t header[n];

    fread(&header, n, 1, input);
    fwrite(&header, n, 1, output);

    int16_t buffer = sizeof(int16_t);

    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        int output_buffer = buffer * factor;

        fwrite(&output_buffer, sizeof(int16_t), 1, output);

    }

    // Close files (DONE)
    fclose(input);
    fclose(output);
}


// TO use: ./volume input.wav output.wav 2.0
