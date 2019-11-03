/*
    wav_example.c

    originally created by Sungwoo Jeon
    created & modified by Juan Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../wav/wave.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <audiofile.wav>\n", argv[0]);
        exit(-1);
    }

    // get header info
    struct HEADER head = wave_header(argv[1]);

    // get wav data
    char *data = wave_data_list(argv[1]);

    // write wav to the file
    create_wave(head, data, "../../audio/modified/copied.wav");

    free(data);
    return 0;
}