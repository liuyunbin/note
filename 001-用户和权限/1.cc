
#include <pwd.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>

int main() {
    // 登录用户
    const char *login_user = getlogin();

    // 实际用户 UID
    uid_t ruid = getuid();

    // 有效用户 UID
    uid_t euid = geteuid();

    printf("登录用户 : %s\n", login_user ? login_user : "(unknown)");

    printf("实际用户 : %d", ruid);

    struct passwd *rpw = getpwuid(ruid);
    if (rpw) {
        printf(" (%s)", rpw->pw_name);
    }
    printf("\n");

    printf("有效用户 : %d", euid);

    struct passwd *epw = getpwuid(euid);
    if (epw) {
        printf(" (%s)", epw->pw_name);
    }
    printf("\n");

    return 0;
}
