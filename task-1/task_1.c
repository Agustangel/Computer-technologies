
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

//#define DEBUG


int main(int argc, char** argv) {

    int res = 0;
    uid_t uid = getuid();
    gid_t gid = getgid();

    #ifdef DEBUG
    printf("uid: %d\n", uid);
    printf("guid: %d\n", gid);
    #endif
    printf("%d ", uid);
    printf("%d ", gid);

    struct passwd* passwd = getpwuid(uid);
    if (passwd == NULL) {
        printf("Error in getpwuid()");
    }
    char* user_name = passwd->pw_name;
    #ifdef DEBUG
    printf("user name: %s\n", user_name);
    #endif

    struct group* user_group = getgrgid(gid);
    if (user_group == NULL) {
        printf("Error in getgrgid()");
    }
    #ifdef DEBUG
    printf("group name: %s\n", user_group->gr_name);
    #endif

    struct group* group = NULL;
    while ((group = getgrent()) != NULL) {

        char* group_user = *(group->gr_mem);
        while (group_user != NULL) {

            if (strcmp(group_user, user_name) == 0) {
                printf("%s ", group->gr_name);
            }
            group->gr_mem++;
            group_user = *(group->gr_mem);

        }
        
    }

    printf("\n");

    return 0;
}
