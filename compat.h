#ifdef ANDROID

#include <poll.h>
#include <sys/syscall.h>

#ifndef EPOLL_CLOEXEC
#define EPOLL_CLOEXEC 02000000
#endif

static inline int epoll_create1(int flags)
{
        return syscall(__NR_epoll_create1, flags);
}


static inline int ppoll(struct pollfd *fds, nfds_t nfds,
                const struct timespec *timeout_ts,
                const sigset_t *sigmask)
{
        return syscall(__NR_ppoll, fds, nfds, timeout_ts, sigmask);
}

#endif

