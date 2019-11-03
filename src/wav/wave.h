struct HEADER
{
    /* RIFF */
    char riff[4];              // RIFF string
    unsigned int overall_size; // overall size of file in bytes
    char wave[4];              // WAVE string
    /* FMT */
    char fmt[4];                    // fmt string with trailing null char
    unsigned int fmt_size;          // length of the format data
    unsigned short audio_format;    // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned short n_channels;      // no.of channels
    unsigned int sample_rate;       // sampling rate (blocks per second)
    unsigned int avg_byte_rate;     // SampleRate * NumChannels * BitsPerSample/8
    unsigned short block_align;     // NumChannels * BitsPerSample/8
    unsigned short bits_per_sample; // bits per sample, 8- 8bits, 16- 16 bits etc
    /* DATA */
    char DATA[4];           // DATA string or FLLR string
    unsigned int data_size; // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

/* get wave header. ex filename = "weather.wav" */
struct HEADER wave_header(char *filename);

/* get wave data size. It needs to create data storage list */
int wave_data_size(struct HEADER header);

/* create wave data list (char*, data size = wave_data_size(header)). */
/* IMPORTANT!! you should free this pointer after use it. */
char *wave_data_list(char *filename);

/* create new .wav file with header and data_list[]. ex filename = "new_wave.wav" */
void create_wave(struct HEADER header, char *data_list, char *filename);
