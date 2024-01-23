#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of each element :
#define sizze 512
// I defined the unsigned byte :
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *filee1 = fopen(argv[1], "r");

    BYTE bavafa[sizze];
    int count = 0;

    char *fileename = malloc(12);

    if (fileename == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    FILE *imgg = NULL;

    while (fread(bavafa, sizeof(BYTE), sizze, filee1))
    {
        if (bavafa[0] == 0xff && bavafa[1] == 0xd8 && bavafa[2] == 0xff && (bavafa[3] & 0xf0) == 0xe0)
        {
            // I want it not to be closed only in the first stage because it is not opened yet,
            // it will be closed first from other times, then the rest of the loop will happen
            if (imgg != NULL)
            {
                fclose(imgg);
            }
            sprintf(fileename, "%03i.jpg", count);
            imgg = fopen(fileename, "a");
            if (imgg == NULL)
            {
                printf("can not open imgg\n");
                return 1;
            }
            fwrite(bavafa, 1, sizze, imgg);
            count++;
        }
        // When the reading of a picture is not finished and the writing process continues:
        else if (count != 0)
        {
            fwrite(bavafa, 1, sizze, imgg);
        }
    }

    fclose(imgg);
    fclose(filee1);
    free(fileename);
    return 0;
}