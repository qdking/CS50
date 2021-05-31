#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Usage behaviour: $ ./recover Usage: ./recover card.raw
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // 1. Open memory card. OPENING the INPUT FILE.
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Usage: ./recover image\n");
        return 2;
    }

// Declaring and initializing variables

    typedef uint8_t BYTE;
    BYTE input_buffer[512] = {0};
    FILE *image = NULL;
    int image_number = 0;
    bool first_image_found = false;
    bool new_image_completed = false;
    char *filename = malloc(sizeof(char) * 8);
    if (filename == NULL)
    {
        return 3;
    }

    // 2. Repeat until end of card: Read 512 bytes into a buffer (some memory storage).
    while (fread(&input_buffer, sizeof(BYTE), 512, input))
    {
        // 3. If we now find the start of a new JPEG, then...
        if (input_buffer[0] == 0xff && input_buffer[1] == 0xd8 && input_buffer[2] == 0xff && (input_buffer[3] & 0xf0) == 0xe0)
        {
            // 3a. If we already found a JPEG, then we need to close the (previous) file so that we can open up a new file that I want to continue writing into.
            if (first_image_found == true)
            {
                fclose(image);
                new_image_completed = true;
            }

            // 3b. If it is the first JPEG, starting writing 000.jpg
            sprintf(filename, "%03i.jpg", image_number);
            image = fopen(filename, "w");

            image_number++;
            new_image_completed = false;
            first_image_found = true;
        }

        // 4. If it is not first JPEG and we already found a JPEG, and already been writing to it, then we should continue writing to it.
        if (first_image_found == true && new_image_completed == false)
        {
            fwrite(&input_buffer, sizeof(BYTE), 512, image);
        }
    }

    // 5. Close any remaining files
    printf("the final image number is %i\n", image_number);
    free(filename);
    fclose(input);

    return 0;
}

