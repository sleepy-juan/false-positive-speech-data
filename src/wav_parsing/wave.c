#include <stdio.h>
#include <stdlib.h>
#include <wave.h>
#include <string.h>

// struct HEADER {
//     /* RIFF */ 
//     char riff[4];                               // RIFF string
//     unsigned int overall_size;                  // overall size of file in bytes
//     char wave[4];                               // WAVE string
//     /* FMT */
//     char fmt[4];                                // fmt string with trailing null char
//     unsigned int fmt_size;                      // length of the format data
//     unsigned short audio_format;                // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
//     unsigned short n_channels;                  // no.of channels
//     unsigned int sample_rate;                   // sampling rate (blocks per second)
//     unsigned int avg_byte_rate;                 // SampleRate * NumChannels * BitsPerSample/8
//     unsigned short block_align;                 // NumChannels * BitsPerSample/8
//     unsigned short bits_per_sample;             // bits per sample, 8- 8bits, 16- 16 bits etc
//     /* DATA */
//     char DATA[4];                               // DATA string or FLLR string
//     unsigned int data_size;                     // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
// };

struct HEADER wave_header(char* filename){
    FILE* wave = fopen(filename, "r");
    if (wave == NULL){
        exit(-1);
    }
    struct HEADER head;
    fread(&head, sizeof(head), 1, wave);
    fclose(wave);
    return head;
}

int wave_data_size(struct HEADER header){
    return header.data_size;
}

char* wave_data_list(char* filename){
    FILE* wave = fopen(filename, "r");
    if (wave == NULL){
        exit(-1);
    }
    struct HEADER head;
    fread(&head, sizeof(head), 1, wave);
    char* data = (char*) malloc(head.data_size);
    if (data == NULL){
        fclose(wave);
        exit(-1);
    }
    fread(data, head.data_size, 1, wave);
    fclose(wave);

    for (int i = 0; i < head.data_size; i++){
        data[i] = data[i] / 2 - 64;
    }
    
    return data;
}

void create_wave(struct HEADER header, char* data_list, char* filename){
    FILE* new_wave = fopen(filename, "w");
    if (new_wave == NULL){
        exit(-1);
    }
    fwrite(&header, sizeof(header), 1, new_wave);
    fwrite(data_list, header.data_size, 1, new_wave);
    fclose(new_wave);
}

int main(void){
    struct HEADER head;
    char* filename = "weather.wav";
    int data_size;
    
    // get wave header & data
    head = wave_header(filename);

    
    // get wave data into list
    char* data = wave_data_list(filename);
    
    // create new wav file
    char* new_filename = "new_wave.wav";
    create_wave(head, data, new_filename);  
    
    free(data);

    return 0;
}