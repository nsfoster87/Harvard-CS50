#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int make_images_from_file(FILE *file);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect Usage: ./recover");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Invalid file type");
        return 1;
    }

    if (make_images_from_file(infile) != 0)
    {
        return 2;
    }

    return 0;
}

int make_images_from_file(FILE *file)
{
    BYTE buffer[512];
    int jpg_counter = 0;
    char *jpgfilename = malloc(sizeof(char) * 8);
    FILE *img = NULL;

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // If the start of a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not the first jpg
            if (jpg_counter != 0)
            {
                fclose(img);
            }

            sprintf(jpgfilename, "%03i.jpg", jpg_counter);
            img = fopen(jpgfilename, "w");
            if (jpgfilename == NULL)
            {
                printf("Could not create %s\n", jpgfilename);
                fclose(file);
                fclose(img);
                return 1;
            }
            // Write from buffer to the img file
            fwrite(buffer, sizeof(BYTE), 512, img);
            jpg_counter++;
        }
        else if (jpg_counter == 0)
        {
            continue;
        }
        else
        {
            // continue writing to the current jpg file
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    fclose(file);
    fclose(img);
    free(jpgfilename);
    return 0;
}
