#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>

typedef int (*unlink_args_t)(int, const char*, int);

int unlinkat(int dir_fd, const char *pathname, int flags) {
    char buf[1024];
    int fd = openat(dir_fd, pathname, flags);
    int rd = 0;
    int status = 0, nodel = 0;
//    printf("inject\n");
    while (rd = read(fd, buf, 1023)) {
        for (int i = 0; i < rd; i++) {
            if (status == 0 && buf[i] == 'F') {
                status = 1;
            } else if (status == 1 && buf[i] == 'I') {
                status = 2;
            } else if (status == 2 && buf[i] == 'X') {
//                printf("nodel\n");
                status = 3;
                nodel = 1;
                break;
            }
        }
        if (nodel) {
            break;
        }
    }
    close(fd);
    if (nodel) {
        errno = EPERM;
        return -1;
    }
    return ((unlink_args_t)dlsym(RTLD_NEXT, "unlinkat"))(dir_fd, pathname, flags);
}
