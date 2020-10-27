#ifndef SRC_CHANNEL_H
#define SRC_CHANNEL_H

#include <stdlib.h>

extern int fd[2];


struct sender{
  size_t size;
  void* data;
  int fd[2];
};

struct receiver{
  size_t size;
  void* data;
  int fd[2];
};

void channel_init(struct receiver* recv, struct sender* sender,
  size_t msg_sz);

void channel_get(struct receiver* channel, void* data);

void channel_send(struct sender* channel, void* data);

void sender_dup(struct sender* dest, struct sender* src);

void channel_destroy(struct receiver* recv, struct sender* sender);

#endif
