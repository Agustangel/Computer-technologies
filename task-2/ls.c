
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

enum opts
{
    ALL = 1,
    LONG = 2,
    RECURSIVE = 3
};

struct opts_t
{
    unsigned all;
    unsigned llong;
    unsigned recursive;
};

void parse_dir(const char* dir)
{
    DIR* dir = opendir(dir);
    if (dir == NULL)
    {
        perror("Error opening dir");
        exit(1);
    }

    struct dirent* entry;
    struct stat statbuf;

    while ((entry = readdir(dir)) != NULL)
    {
        int ret = stat(entry->d_name, &statbuf);

        if (!S_ISREG(statbuf.st_mode))
        {
            parse_dir(entry->d_name);
        }
        printf("%s ", entry->d_name);
    }

    return;
}

int main(int argc, char** argv)
{
    static const char opts[] = "alR";
    static struct option longopts[] =
    {
        {"all", 0, NULL, ALL},
        {"long", 0, NULL, LONG},
        {"recursive", 0, NULL, RECURSIVE}
    };

    struct opts_t flags = {0};
    int ret = 0;

    while((ret = getopt_long(argc, argv, opts, longopts, &optind)) != -1)
    {
        switch (ret)
        {
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

    int all_args = 3;
    char* target_dir = NULL;

    if (optind > all_args)
    {
        target_dir = argv[all_args + 1];
    }
    else
    {
        target_dir = ".";
    }

    DIR* dir = opendir(target_dir);
    if (dir == NULL)
    {
        perror("Error opening dir");
        exit(1);
    }

    struct dirent* entry;
    struct stat statbuf;

    while ((entry = readdir(dir)) != NULL)
    {
        ret = stat(entry->d_name, &statbuf);
        struct passwd* passwd = getpwuid(statbuf.st_uid);
        struct group* group = getgrgid(statbuf.st_gid);

        if (flags.recursive) 
        {
            if (!S_ISREG(statbuf.st_mode)) 
            {
                parse_dir(entry->d_name);
            }
        }

        if (flags.llong) 
        {
            if (flags.all) 
            {
                printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);
            } 
            else 
            {
                if (strcmp(entry->d_name, ".") != 0)
                {
                    printf("%d %ld %s %s %ld %ld %s\n",  statbuf.st_mode, statbuf.st_nlink, passwd->pw_name, group->gr_name,
                                                            statbuf.st_size, statbuf.st_mtim.tv_sec, entry->d_name);

                }
            }
        } 
        else 
        {
            if (flags.all) 
            {
                printf("%s ", entry->d_name);
            } 
            else 
            {
                if (strcmp(entry->d_name, ".") != 0)
                {
                    printf("%s ", entry->d_name);
                }
            }
        }
    }

    printf("\n");

    return 0;
}
