#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

char *usage = "Usage: generate_data <-s size> [-t text]\nSize must be greater than 0\n";

void print_progress(double progress, uint64_t max);

int main (int argc, char **argv)
{
    char *text = NULL;
    uint64_t data_size = 0;
    uint64_t text_length;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "s:t:")) != -1) {
        switch (c) {
            case 's':
                sscanf(optarg, "%"PRIu64, &data_size);
                break;
            case 't':
                text = optarg;
                text_length = strlen(text);
                break;
            case '?':
                if (optopt == 's') {
                    fprintf(stderr, "Option -%c requires a size.\n", optopt);
                } else if (optopt == 't') {
                    fprintf(stderr, "Option -%c requires text.\n", optopt);
                }

                return 1;
            default:
                return 1;
        }
    }

    if (data_size <= 0 || text == NULL) {
        fprintf(stderr, usage);
        return 1;
    }

    // Begin calculating buffer to write to file.
    // writing entire buffers is faster than writing smaller pieces
    char buf_text[BUFSIZ];
    memset(buf_text, '\0', BUFSIZ);

    int times_fit_into_buf_text = BUFSIZ/text_length;
    // This isn't bufsize because rounding
    int buf_text_length = times_fit_into_buf_text * text_length;
    int i;
    int j;
    for (i = 0; i < times_fit_into_buf_text; i++) {
        for (j = 0; j < text_length; j++) {
            buf_text[(i*text_length) + j] = text[j];
        }
    }

    int read_len = buf_text_length;

    fprintf(stderr, "Creating a file of size: %" PRIu64"\n", data_size);

    uint64_t total_output = 0;

    // Progress bar initialization
    int iteration = 0;
    int total_iterations = ceil((double)data_size/read_len);
    int iteration_cycle = ceil((double)total_iterations/100);

    while (total_output < data_size) {
        if ((data_size - total_output) < read_len) {
            read_len = data_size - total_output;
        }
        fprintf(stdout, "%.*s", read_len, buf_text);
        total_output += read_len;

        if (iteration % iteration_cycle == 0 || data_size == total_output) {
            print_progress(total_output, data_size);
        }

        iteration+=1;
    }

    fprintf(stderr, "\nSuccessfully created file!");

    return 0;
}

void print_progress(double progress, uint64_t max)
{

    int bar_width = 70;
    int i;

    fprintf(stderr, "\r[");
    int pos = progress/max * bar_width;
    for (i = 0; i < bar_width; ++i) {
        if (i < pos) {
            fprintf(stderr, "=");
        } else if (i == pos) {
            fprintf(stderr, ">");
        } else {
            fprintf(stderr, " ");
        }
    }
    fprintf(stderr, "] %.*f%%", 2, progress/max * 100);
    fflush(stderr);
}
