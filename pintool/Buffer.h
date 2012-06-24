#ifndef BUF_FER_H
#define BUF_FER_H

#include <map>
#include <queue>
#include <assert.h>
#include <pthread.h>
#include "feeder.h"

class Buffer
{
 public:
  Buffer();
  
  void push(handshake_container_t* handshake);
  void pop();
  
  handshake_container_t* front();
  handshake_container_t* back();

  bool empty();
  bool full();
  
  int size();
  
 private:
  handshake_container_t** handshakePool_;
  int head_;
  int tail_;

  int size_;
  int numPool_;
};

#endif
