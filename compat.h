#ifdef ANDROID

#include <poll.h>
#include <sys/syscall.h>

#ifndef EPOLL_CLOEXEC
#define EPOLL_CLOEXEC 02000000
#endif


#define _NSIG_KERNEL		64

#ifdef __i386__
# define _NSIG_BPW_KERNEL	32
#else
# define _NSIG_BPW_KERNEL	64
#endif

#define _NSIG_WORDS_KERNEL	(_NSIG_KERNEL / _NSIG_BPW_KERNEL)

typedef struct {
	unsigned long sig[_NSIG_WORDS_KERNEL];
} sigset_kernel_t;


static inline int epoll_create1(int flags)
{
	return syscall(__NR_epoll_create1, flags);
}


static inline int ppoll(struct pollfd *fds, nfds_t nfds,
                const struct timespec *timeout_ts,
                const sigset_t *sigmask)
{
	if (sizeof(sigset_t) < sizeof(sigset_kernel_t)) {
		/* Translate Bionic sigset_t to Kernel sigset_t */
		sigset_kernel_t sigmask_k;

		memset(&sigmask_k, 0, sizeof(sigset_kernel_t));
		memcpy(&sigmask_k, sigmask, sizeof(sigset_t));

		return syscall(__NR_ppoll, fds, nfds, timeout_ts, &sigmask_k,
				sizeof(sigset_kernel_t));
	} else {
		return syscall(__NR_ppoll, fds, nfds, timeout_ts, sigmask,
				sizeof(sigset_t));
	}
}

#endif

