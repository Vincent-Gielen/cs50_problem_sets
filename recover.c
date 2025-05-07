#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGESIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // check if file can be opened
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    int haveStarted = 0;
    int fileNumber = 0;
    char fileBuffer[8];
    FILE *images;
    BYTE buffer[IMAGESIZE];
    while (fread(&buffer, 1, IMAGESIZE, input))
    {
        // if the buffer starts with the 4 new jpg bytes -> create new jpg
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && ((buffer[3] & 240) == 224))
        {
            // if it's the first jpg
            if (fileNumber == 0)
            {
                haveStarted = 1;
                // create jpg name, create and open jpg, write to images
                sprintf(fileBuffer, "%03i.jpg", fileNumber);
                printf("%s\n", fileBuffer);
                images = fopen(fileBuffer, "a");
                fwrite(&buffer, 1, IMAGESIZE, images);

                // increase the fileNumber by 1
                fileNumber++;

            }
            else // if it's another new jpg
            {
                // close previous jpg
                fclose(images);

                // create jpg name, create and open jpg, write to images
                sprintf(fileBuffer, "%03i.jpg", fileNumber);
                printf("%s\n", fileBuffer);
                images = fopen(fileBuffer, "a");
                fwrite(&buffer, 1, IMAGESIZE, images);

                // increase the fileNumber by 1
                fileNumber++;
            }
        }
        else
        {
            if(haveStarted)
            {
            // append the contents of input in the jpg file
            fwrite(&buffer, 1, IMAGESIZE, images);
            }
        }
    }
    fclose(images);
    fclose(input);
}
