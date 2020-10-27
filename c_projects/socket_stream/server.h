#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdint.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <math.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


struct client_connect{
  int socketfd;
  char* directory;
};

struct information{
  uint32_t* session_id;
  uint64_t* offset;
  char** filenames;
  int n_entries;
  uint64_t* length;
  int max;
  int count;
  uint64_t newOffset;
  int n_connections;
};



struct node{
  uint8_t value;
  struct node* left;
  struct node* right;
};

struct thread_return{
  int value;
};

struct request_data{
  int type_num;
  int reqCompression;
  int resCompression;
  uint64_t payload_len;
  unsigned char* pay;
  uint64_t payload[8];
  uint64_t comm_payload_len;
  uint8_t comm_payload[8];


};

struct decompress_result{
    uint8_t* result;
    int num;
};

void* client_interaction(void* arg);
void freeInfo(struct information * info);
void echo(struct request_data* request,uint8_t* msg,struct client_connect* data,char**dictionary);
uint8_t makeType(uint8_t type, int compression );
void error(struct request_data* request,uint8_t* msg,struct client_connect* data);
struct request_data* analyse_request(struct client_connect* data);
void* shut_down(struct request_data* request,uint8_t* msg,struct client_connect* data);
int file_size(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary);
int directory_listing(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary);
char** makeDictArray();
uint8_t* getPayload(struct request_data* request, char** dictionary,int length , unsigned char* message);
void freeDict(char** dictionary);
uint8_t* getDirPayload(struct request_data*  request, char** dictionary,int n_files,char** message);
struct node* makeDictTree();
struct decompress_result* decompress(uint8_t* bytes,struct node* head,int size);
int retrieve_file(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary,struct node* head);
