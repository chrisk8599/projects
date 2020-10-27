#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "channel.h"
#include <signal.h>
int fd[2];

void channel_init(struct receiver* recv, struct sender* sender,
  size_t msg_sz) {

  if(recv == NULL || sender == NULL){
    return;
  }

  int res =   pipe(fd);
  recv->size = msg_sz;
  sender->size = msg_sz;

}

void channel_get(struct receiver* channel, void* data) {
  if(data == NULL || channel == NULL){
    return;
  }
  read(fd[0],data,channel->size);
}

void channel_send(struct sender* channel, void* data) {

  while(data == NULL || channel == NULL){
    return;
  }

    write(fd[1],data,channel->size);

}

void sender_dup(struct sender* dest, struct sender* src) {
  if(dest== NULL || src == NULL){
    return;
  }
  dest->size = src->size;
}

void channel_destroy(struct receiver* recv, struct sender* sender) {

}
