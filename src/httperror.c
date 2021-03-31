#define _GNU_SOURCE

#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errortable.h"

int main(int argc, char *argv[]) {
    static struct option longopts[] = {
        {"list", no_argument, 0, 'l'},
        {"search", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    int i, j;
    int retval = 0;

    int ch;
    int action = '\0';

    long val;
    char *endptr;
    int found;

    while((ch = getopt_long(argc, argv, "ls", longopts, NULL)) != -1) {
        switch(ch) {
            case 'l':
            case 's':
                action = ch;
                break;

            default:
                return 1;
        }
    }

    argc -= optind;
    argv += optind;

    switch(action) {
    case 'l':
        for(i = 0; i < ERROR_NAMES_LEN; i++) {
            if(error_names[i]) {
                printf("%d %s\n", i, error_names[i]);
            }
        }
        break;

    case 's':
        for(i = 0; i < ERROR_NAMES_LEN; i++) {
            if(!error_names[i]) {
                continue;
            }

            found = 1;
            for(j = 0; j < argc; j++) {
                if(!strcasestr(error_names[i], argv[j])) {
                    found = 0;
                    break;
                }
            }

            if(found) {
                printf("%d %s\n", i, error_names[i]);
            }
        }
        break;

    default:
        for(i = 0; i < argc; i++) {
            errno = 0;
            val = strtol(argv[i], &endptr, 10);
            if(val < 0 || val > (long)INT_MAX || *endptr != 0 || errno != 0) {
                retval = 1;
                continue;
            }

            if(val < ERROR_NAMES_LEN && error_names[val]) {
                printf("%d %s\n", (int)val, error_names[val]);
            }
            else {
                retval = 1;
            }
        }
        break;
    }

    return retval;
}
