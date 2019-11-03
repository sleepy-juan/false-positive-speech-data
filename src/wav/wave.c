/*
    wave.c

    created by Sungwoo Jeon
    modified by Juan Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wave.h"

/* get wave header. ex filename = "weather.wav" */
struct HEADER wave_header(char *filename)
{
    FILE *wave = fopen(filename, "r");
    if (wave == NULL)
    {
        exit(-1);
    }
    struct HEADER head;
    fread(&head, sizeof(head), 1, wave);
    fclose(wave);
    return head;
}

/* get wave data size. It needs to create data storage list */
int wave_data_size(struct HEADER header)
{
    return header.data_size;
}

/* get wave data list (data size = wave_data_size(header)). */
void get_wave_data(char* data_list, char *filename)
{
    FILE *wave = fopen(filename, "r");
    if (wave == NULL)
    {
        exit(-1);
    }
    struct HEADER head;
    fread(&head, sizeof(head), 1, wave);
    if (data_list == NULL)
    {
        fclose(wave);
        exit(-1);
    }
    fread(data_list, head.data_size, 1, wave);
    fclose(wave);
}

/* create new .wav file with header and data_list[]. ex filename = "new_wave.wav" */
void create_wave(struct HEADER header, char *data_list, char *filename)
{
    FILE *new_wave = fopen(filename, "w");
    if (new_wave == NULL)
    {
        exit(-1);
    }
    fwrite(&header, sizeof(header), 1, new_wave);
    fwrite(data_list, header.data_size, 1, new_wave);
    fclose(new_wave);
}