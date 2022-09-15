
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

//#define DEBUG

typedef struct flags_t
{
    int flag_u;
    int flag_g;
    int flag_G;
} flags_t;

void print_group_id(uid_t uid, gid_t gid)
{
    struct passwd* passwd = getpwuid(uid);
    if (passwd == NULL)
    {
        printf("Error in getpwuid()");
    }
    char* user_name = passwd->pw_name;

    struct group* group = NULL;
    while ((group = getgrent()) != NULL)
    {
        char* group_user = *(group->gr_mem);
        while (group_user != NULL)
        {
            if (strcmp(group_user, user_name) == 0)
            {
                gid = group->gr_gid;
                printf("%d ", gid);
            }

            group->gr_mem++;
            group_user = *(group->gr_mem);
        }
    }
    printf("\n");
}

int parse_args(int argc, char** argv, flags_t* flags)
{
    if(argc < 2)
    {
        flags->flag_u = 0;
        flags->flag_g = 0;
        flags->flag_G = 0;

        return 0;       
    }

    if(strcmp(argv[1], "-u") == 0)
    {
        flags->flag_u = 1;
        flags->flag_g = 0;
        flags->flag_G = 0;

        return 0;
    }
    else if(strcmp(argv[1], "-g") == 0)
    {
        flags->flag_u = 0;
        flags->flag_g = 1;
        flags->flag_G = 0;

        return 0;
    }
    else if(strcmp(argv[1], "-G") == 0)
    {
        flags->flag_u = 0;
        flags->flag_g = 0;
        flags->flag_G = 1;

        return 0;
    }
    else
    {
        printf("Incorrect flag\n");

        flags->flag_u = 0;
        flags->flag_g = 0;
        flags->flag_G = 0;

        return 0;
    }
}

int main(int argc, char** argv)
{
    flags_t flags;
    parse_args(argc, argv, &flags);

    uid_t uid = getuid();
    gid_t gid = getgid();

    if(flags.flag_u == 1)
    {
        printf("uid=%d\n", uid);
        exit(0);
    }
    if(flags.flag_g == 1)
    {
        printf("gid=%d\n", gid);
        exit(0);
    }
    if(flags.flag_G == 1)
    {
        print_group_id(uid, gid);
        exit(0);
    }

    struct passwd* passwd = getpwuid(uid);
    if (passwd == NULL)
    {
        printf("Error in getpwuid()");
    }
    char* user_name = passwd->pw_name;

    struct group* user_group = getgrgid(gid);
    if (user_group == NULL) 
    {
        printf("Error in getgrgid()");
    }

    printf("uid=%d(%s) ", uid, user_name);
    printf("gid=%d(%s) ", gid, user_name);

    struct group* group = NULL;

    while ((group = getgrent()) != NULL)
    {
        char* group_user = *(group->gr_mem);
        while (group_user != NULL)
        {
            if (strcmp(group_user, user_name) == 0)
            {
                gid = group->gr_gid;
                printf("%d(%s),", gid, group->gr_name);
            }

            group->gr_mem++;
            group_user = *(group->gr_mem);
        }    
    }
    printf("\n");

    return 0;
}
