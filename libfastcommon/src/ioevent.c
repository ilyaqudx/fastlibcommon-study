#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ioevent.h"

#if IOEVENT_USE_KQUEUE
/* we define these here as numbers, because for kqueue mapping them to a combination of
     * filters / flags is hard to do. */
int kqueue_ev_convert(int16_t event, uint16_t flags)
{
  int r;

  if (event == EVFILT_READ) {
    r = KPOLLIN;
  }
  else if (event == EVFILT_WRITE) {
    r = KPOLLOUT;
  }
  else {
    r = 0;
  }

  if (flags & EV_EOF) {
    r |= KPOLLHUP;
  }
  return r;
}
#endif

/**
 * 初始化线程的IO事件
 *
 * 每个线程对应一个epoll
 * 分配内存空间
 * */
int ioevent_init(IOEventPoller *ioevent, const int size,
    const int timeout_ms, const int extra_events)
{
  int bytes;

  ioevent->size = size;
  ioevent->extra_events = extra_events;
  ioevent->iterator.index = 0;
  ioevent->iterator.count = 0;

#if IOEVENT_USE_EPOLL
  ioevent->poll_fd = epoll_create(ioevent->size);
  bytes = sizeof(struct epoll_event) * size;
  ioevent->events = (struct epoll_event *)malloc(bytes);
#elif IOEVENT_USE_KQUEUE
  ioevent->poll_fd = kqueue();
  bytes = sizeof(struct kevent) * size;
  ioevent->events = (struct kevent *)malloc(bytes);
  ioevent->care_events = 0;
#elif IOEVENT_USE_PORT
  ioevent->poll_fd = port_create();
  bytes = sizeof(port_event_t) * size;
  ioevent->events = (port_event_t *)malloc(bytes);
#endif

  if (ioevent->events == NULL) {
    return errno != 0 ? errno : ENOMEM;
  }
  ioevent_set_timeout(ioevent, timeout_ms);

  return 0;
}

void ioevent_destroy(IOEventPoller *ioevent)
{
  if (ioevent->events != NULL) {
    free(ioevent->events);
    ioevent->events = NULL;
  }

  if (ioevent->poll_fd >= 0) {
    close(ioevent->poll_fd);
    ioevent->poll_fd = -1;
  }
}

int ioevent_attach(IOEventPoller *ioevent, const int fd, const int e,
    void *data)
{
#if IOEVENT_USE_EPOLL
  struct epoll_event ev;
  memset(&ev, 0, sizeof(ev));
  ev.events = e | ioevent->extra_events; //events就是SelectionKey.OPT_READ | OPT_WRITE | ACCEPT | CONNECT
  ev.data.ptr = data; //这个DATA设置了 pipe read fd 和 callback方法
  /**
   * 2、epoll_ctl函数  相当于java中Channel.register方法
    函数声明：int epoll_ctl(int epfd, int op, int fd, struct epoll_event event)
    该函数用于控制某个文件描述符上的事件，可以注册事件，修改事件，删除事件。
    参数：epfd：由 epoll_create 生成的epoll专用的文件描述符；(应该是JAVA中的ServerSocketChannel)
         op：要进行的操作例如注册事件，可能的取值
					EPOLL_CTL_ADD 注册、
					EPOLL_CTL_MOD 修改、
					EPOLL_CTL_DEL 删除
		  fd：关联的文件描述符；
		  event：指向epoll_event的指针；
	如果调用成功返回0,不成功返回-1
   * */
  return epoll_ctl(ioevent->poll_fd, EPOLL_CTL_ADD, fd, &ev);
#elif IOEVENT_USE_KQUEUE
  struct kevent ev[2];
  int n = 0;
  if (e & IOEVENT_READ) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD | ioevent->extra_events, 0, 0, data);
  }
  if (e & IOEVENT_WRITE) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD | ioevent->extra_events, 0, 0, data);
  }
  ioevent->care_events = e;
  return kevent(ioevent->poll_fd, ev, n, NULL, 0, NULL);
#elif IOEVENT_USE_PORT
  return port_associate(ioevent->poll_fd, PORT_SOURCE_FD, fd, e, data);
#endif
}

int ioevent_modify(IOEventPoller *ioevent, const int fd, const int e,
    void *data)
{
#if IOEVENT_USE_EPOLL
  struct epoll_event ev;
  memset(&ev, 0, sizeof(ev));
  ev.events = e | ioevent->extra_events;
  ev.data.ptr = data;
  return epoll_ctl(ioevent->poll_fd, EPOLL_CTL_MOD, fd, &ev);
#elif IOEVENT_USE_KQUEUE
  struct kevent ev[2];
  int n = 0;
  if (e & IOEVENT_READ) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_ADD | ioevent->extra_events, 0, 0, data);
  }
  else if ((ioevent->care_events & IOEVENT_READ)) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
  }

  if (e & IOEVENT_WRITE) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_ADD | ioevent->extra_events, 0, 0, data);
  }
  else if ((ioevent->care_events & IOEVENT_WRITE)) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
  }

  ioevent->care_events = e;
  if (n > 0) {
      return kevent(ioevent->poll_fd, ev, n, NULL, 0, NULL);
  }
  else {
      return 0;
  }
#elif IOEVENT_USE_PORT
  return port_associate(ioevent->poll_fd, PORT_SOURCE_FD, fd, e, data);
#endif
}

int ioevent_detach(IOEventPoller *ioevent, const int fd)
{
#if IOEVENT_USE_EPOLL
  return epoll_ctl(ioevent->poll_fd, EPOLL_CTL_DEL, fd, NULL);
#elif IOEVENT_USE_KQUEUE
  struct kevent ev[2];
  int n = 0;
  if ((ioevent->care_events & IOEVENT_READ)) {
    EV_SET(&ev[n++], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
  }
  if ((ioevent->care_events & IOEVENT_WRITE)) {
    EV_SET(&ev[n++], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
  }

  ioevent->care_events = 0;
  if (n > 0) {
      return kevent(ioevent->poll_fd, ev, n, NULL, 0, NULL);
  }
  else {
      return 0;
  }
#elif IOEVENT_USE_PORT
  return port_dissociate(ioevent->poll_fd, PORT_SOURCE_FD, fd);
#endif
}

int ioevent_poll(IOEventPoller *ioevent)
{
#if IOEVENT_USE_EPOLL
  return epoll_wait(ioevent->poll_fd, ioevent->events, ioevent->size, ioevent->timeout);
#elif IOEVENT_USE_KQUEUE
  return kevent(ioevent->poll_fd, NULL, 0, ioevent->events, ioevent->size, &ioevent->timeout);
#elif IOEVENT_USE_PORT
  int result;
  int retval;
  unsigned int nget = 1;
  if((retval = port_getn(ioevent->poll_fd, ioevent->events,
          ioevent->size, &nget, &ioevent->timeout)) == 0)
  {
    result = (int)nget;
  } else {
    switch(errno) {
      case EINTR:
      case EAGAIN:
      case ETIME:
        if (nget > 0) {
          result = (int)nget;
        }
        else {
          result = 0;
        }
        break;
      default:
        result = -1;
        break;
    }
  }
  return result;
#else
#error port me
#endif
}

