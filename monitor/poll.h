#ifdef ANDROID

#include <asm/unistd.h>

#ifndef EPOLL_CLOEXEC
#define EPOLL_CLOEXEC 02000000
#endif

static inline int epoll_create1(int flags)
{
	return syscall(__NR_epoll_create1, flags);
}

#endif
