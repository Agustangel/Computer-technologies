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

enum opts {
    ALL = 1,
    LONG = 2,
    RECURSIVE = 3
};

struct opts_t {
    unsigned all;
    unsigned llong;
    unsigned recursive;
};

void parse_dir(const char* target_dir, struct opts_t* flags) {

    char entry_name[FILENAME_MAX];
    strcpy(entry_name, target_dir);
    DIR* dir = opendir(target_dir);
    if (dir == NULL) {
        perror("Error opening dir:");
        printf("ERROR in dir: %s\n", target_dir);
        exit(1);
    }

    struct dirent* entry;
    struct stat statbuf;
    while ((entry = readdir(dir)) != NULL) {
        
        char tmp[FILENAME_MAX];
        strcpy(tmp, entry_name);
        strcat(tmp, "/");
        strcat(tmp, entry->d_name);
        int ret = stat(tmp, &statbuf);

        struct passwd* passwd = getpwuid(statbuf.st_uid);
        struct group* group = getgrgid(statbuf.st_gid);
    
        if (S_ISDIR(statbuf.st_mode) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {
            if (entry->d_name[0] == '.' ) {
                if (flags->all) {
                    parse_dir(tmp, flags);
                }
            } else {
                parse_dir(tmp, flags);
            }
        }

       if (flags->llong) {

            if (flags->all) {
                printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);
            } else {
                if (entry->d_name[0] != '.') {
                    printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);

                }
            }

        } else {

            if (flags->all) {
                printf("%s ", entry->d_name);
            } else {
                if (entry->d_name[0] != '.') {
                    printf("%s ", entry->d_name);
                }
            }

        }
        strcpy(tmp, target_dir);
    }

    return;
}

int main(int argc, char** argv) {

    char target_dir[FILENAME_MAX];
    static const char opts[] = "alR";
    static struct option longopts[] = {
        {"all", 0, NULL, ALL},
        {"long", 0, NULL, LONG},
        {"recursive", 0, NULL, RECURSIVE}
    };

    struct opts_t flags = {0};
    int ret = 0;
    while((ret = getopt_long(argc, argv, opts, longopts, &optind)) != -1) {
        
        switch (ret) {

            case ALL:
            case 'a':
                flags.all = 1;
                break;
            case LONG:
            case 'l':
                flags.llong = 1;
                break;
            case RECURSIVE:
            case 'R':
                flags.recursive = 1;
                break;

        }

    }

    if (argv[optind] != NULL) {
        strcpy(target_dir, argv[optind]);
    } else {
        strcpy(target_dir, ".");
    }

    DIR* dir = opendir(target_dir);
    if (dir == NULL) {
        perror("Error opening dir");
        exit(1);
    }

    struct dirent* entry;
    struct stat statbuf;
    printf("%s:\n", target_dir);
    while ((entry = readdir(dir)) != NULL) {

        ret = stat(entry->d_name, &statbuf);
        struct passwd* passwd = getpwuid(statbuf.st_uid);
        struct group* group = getgrgid(statbuf.st_gid);

        if (flags.recursive) {
                char tmp[FILENAME_MAX];
                strcpy(tmp, target_dir);
                strcat(tmp, "/");
                strcat(tmp, entry->d_name);
                int ret = stat(tmp, &statbuf);
            
                if (S_ISDIR(statbuf.st_mode) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {
                    if (entry->d_name[0] == '.' ) {
                        if (flags.all) {
                            printf("%s:\n", entry->d_name);
                            parse_dir(tmp, &flags);
                        }
                    } else {
                        printf("%s:\n", entry->d_name);
                        parse_dir(tmp, &flags);
                    }
                }

                strcpy(tmp, target_dir);
        }

        if (flags.llong) {

            if (flags.all) {
                printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);
            } else {
                if (entry->d_name[0] != '.') {
                    printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);

                }
            }

        } else {

            if (flags.all) {
                printf("%s ", entry->d_name);
            } else {
                if (entry->d_name[0] != '.') {
                    printf("%s ", entry->d_name);
                }
            }

        }

    }

    printf("\n");

    return 0;
}