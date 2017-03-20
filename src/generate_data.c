#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

char *usage = "Usage: generate_data <-s size> [-t text]\nSize must be greater than 0\n";

int main (int argc, char **argv)
{
    char *text = NULL;
    uint64_t data_size = 0;
    uint64_t text_length;
    int read_len;
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
                read_len = text_length;
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

    if (data_size <= 0 && text == NULL) {
        printf(usage);
        return 1;
    }

    uint64_t total_output;
    while (total_output < data_size) {
        if ((data_size - total_output) < read_len) {
            read_len = data_size - total_output;
        }
        printf("%.*s", read_len, text);
        total_output += read_len;
    }

    return 0;
}
