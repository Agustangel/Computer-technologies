
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <stdarg.h>
#include <fcntl.h>
#include <assert.h>

/* TODO:
   - Add copying from directory above
*/

const char* USAGE = \
"Usage: cp [OPTION]... SOURCE DEST                                                                  \
Copy SOURCE to DEST.                                                                                \
Mandatory arguments to long options are mandatory for short options too.                            \
    -f, --force         if an existing destination file cannot be opened, remove it and try again   \
    -i, --interactive   promt before overwrite                                                      \
    -p  --preserve      preserve mode, ownership, timestamps                                        \
        --help          display this help and exit                                                  \
    -v  --verbose       explain what is being done                                                  \
";


enum opts {
    FORCE = 1,
    INTERACTIVE = 2,
    PRESERVE = 3,
    HELP = 4,
    VERBOSE = 5
};

struct opts_t {
    unsigned force;
    unsigned interactive;
    unsigned preserve;
    unsigned help;
    unsigned verbose;
};

#define PRINT_VERBOSE(msg, ...) do {                        \
                            if (flags.verbose) {            \
                                printf(msg, __VA_ARGS__);   \
                            }                               \
                        } while (0);                        \

int main(int argc, char** argv) {

    int ret = 0;
    static const char opts[] = "fipv";
    static struct option longopts[] = {
        {"force", 0, NULL, FORCE},
        {"interactive", 0, NULL, INTERACTIVE},
        {"preserve", 0, NULL, PRESERVE},
        {"help", 0, NULL, HELP},
        {"verbose", 0, NULL, VERBOSE}
    };

    struct opts_t flags = {0};
    while((ret = getopt_long(argc, argv, opts, longopts, &optind)) != -1) {
        
        switch (ret) {

            case FORCE:
            case 'f':
                flags.force = 1;
                break;
            case INTERACTIVE:
            case 'i':
                flags.interactive = 1;
                break;
            case PRESERVE:
            case 'p':
                flags.preserve = 1;
                break;
            case HELP:
                flags.help = 1;
                break;
            case VERBOSE:
                flags.verbose = 1;
                break;
            default:
                printf("cp: invalid usage\n");
                printf("Try 'cp --help' for more information.\n");
                exit(EXIT_FAILURE);

        }

    }

    char* src = argv[optind];
    char* dst = argv[optind + 1];

    if (src == NULL) {
        printf("cp: src argument required.\n");
        exit(EXIT_FAILURE);
    }

    if (dst == NULL) {
        printf("cp: dst argument required.\n");
        exit(EXIT_FAILURE);
    }

    PRINT_VERBOSE("src: %s\n", src);
    PRINT_VERBOSE("dst: %s\n", dst);

    struct stat stat_src;
    struct stat stat_dst;
    ret = stat(src, &stat_src);
    if (ret < 0) {
        perror("Error reading src file\n");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(stat_src.st_mode)) {
        printf("Error: src is a directory.\n");
        exit(EXIT_FAILURE);
    }

    int src_size = stat_src.st_size;
    char* buffer = (char*) calloc(src_size, sizeof(char));
    assert(buffer != NULL);
    int src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening src file\n");
    }

    ret = read(src_fd, buffer, src_size);
    if (ret != src_size) {
        perror("Error reading data from src file to buffer\n");
    }

    // rewrite dst file, if a directory, copy it to dir
    ret = stat(dst, &stat_dst);
    if (ret < 0) {
        perror("Error reading dst file\n");
        exit(EXIT_FAILURE);
    }

    char* abs_src_path = realpath(src, NULL);
    char* abs_dst_path = realpath(dst, NULL);
    printf("abs src path: %s\n", abs_src_path);
    printf("abs dst path: %s\n", abs_dst_path);

    int dst_fd = 0;
    char path[FILENAME_MAX];
    strcpy(path, abs_dst_path);
    printf("path: %s\n", path);

    if (S_ISDIR(stat_dst.st_mode)) {

        int overwrite = 1;
        strcat(path, "/");
        strcat(path, src);
        printf("path: %s\n", path);

        struct stat stat_path;
        ret = stat(path, &stat_path);
        if (ret >= 0) {
            if (flags.interactive) {

                char ans = 0;
                printf("Overwrite %s?\n", path);
                while (ans != 'y' && ans != 'n') {
                    ret = scanf("%c ", &ans);
                    if (ans == 'y') {
                        overwrite = 1;
                    } else {
                        overwrite = 0;
                    }
                }

            }
        }

        int force_write = 0;
        if (overwrite) {
            dst_fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
            // check if we don't have permissions
            if (dst_fd < 0) {
                if (errno == EACCES) {
                    if (flags.force) {
                        force_write = 1;
                        chmod(path, S_IRWXU);
                    }
                } else {
                    perror("Could not open dst\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (force_write) {
                ret = write(dst_fd, buffer, src_size);
                if (ret != src_size) {
                    perror("Error writing buffer to dst file\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        PRINT_VERBOSE("%s -> %s\n", src, dst);
        int overwrite = 1;
        int force_write = 0;
        if (overwrite) {
            dst_fd = open(path, O_WRONLY | O_CREAT, S_IRWXU);
            // check if we don't have permissions
            if (dst_fd < 0) {
                if (errno == EACCES) {
                    if (flags.force) {
                        force_write = 1;
                        chmod(path, S_IRWXU);
                    }
                } else {
                    perror("Could not open dst\n");
                    exit(EXIT_FAILURE);
                }
            }
            //if (force_write) {
                ret = write(dst_fd, buffer, src_size);
                if (ret != src_size) {
                    perror("Error writing buffer to dst file\n");
                    exit(EXIT_FAILURE);
                }
            //}
        }
    }

    PRINT_VERBOSE("%s -> %s\n", src, dst);

    free(buffer);
    close(src_fd);
    close(dst_fd);

    return 0;
}
