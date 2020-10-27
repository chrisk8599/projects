#include "server.h"


//defining error and passing variables
#define ERROR 1
#define PASSED 0

//shared memory between threads
static struct information* info ;


int main(int argc,char** argv){

  // intitalising the shared memory for threads.
  info = NULL;

  //Checking if a config file is given or not.
  if(argc !=2){
    puts("Please enter a configuration file");
    exit(1);
  }


  //saving the path to the config_file
  char* config_file = argv[1];

  //opening the contents of config_file
  FILE* fp  = fopen(config_file,"rb");

  //check if the contents config file is empty
  if(fp == NULL){
    return PASSED;
  }

  //Getting the file length of the config_file
  fseek(fp, 0, SEEK_END);
  int file_length = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  //variable to read each byte of config_file
  unsigned char byte;

  //array to save ipAddress in bytes
  uint8_t ipAddress[4];

  //array to save the 2 bytes that make the port number
  unsigned char port[2];

  //variable to save the path to the directory
  char* directory  = malloc(sizeof(char)*(file_length-6+2));

  int count  = 0 ;
  // until file is at the EOF
  while (!feof(fp)){
      //read a byte at a time
      byte=fgetc(fp);

      //if count is less than 4 it is the ipAddress
      if(count<4){
        ipAddress[count] =(uint8_t) byte;
      }
      //if count is less than 6 but greater than 3 it is the port
      else if(count<6){
        port[count-4] = byte;
      }
      //else if the count is larger than 6 these bytes are the directory
      else if(count>=6){
        directory[count-6] = byte;
      }


      count++;
   }

   directory[file_length-6] = '/';
   directory[file_length-5] = '\0';

   fclose(fp);




  //combine the two bytes given into 1 resulting 2 byte port number.
  unsigned int result = ((unsigned int)port[0]<<8) |(unsigned int)port[1];


  //combine the given 4 bytes to a 4byte ipAddress.
  uint32_t res =  ipAddress[0] | (ipAddress[1] << 8) |
  (ipAddress[2] << 16) | (ipAddress[3] << 24);

  //initialise the serversocket and the client socket.
  int serversocket = -1;
  int clientsocket = -1;

  struct sockaddr_in address;

  serversocket = socket(AF_INET,SOCK_STREAM,0);

  if(serversocket < 0){

    exit(1);
  }

  //set the ip address to the given address
  address.sin_addr.s_addr = res;
  address.sin_family = AF_INET;

  // set the port to the given port number.
  address.sin_port = htons(result);


  //bind port to address
  if(bind(serversocket,(struct sockaddr*)&address,sizeof(struct sockaddr_in))){
    printf("Could not bind\n" );
     exit(1);
  }

  listen(serversocket,SOMAXCONN);



  //Constantly accept clients who attempt to connect to the server.
  while(1){
    uint32_t address_len = sizeof(struct sockaddr_in);

    clientsocket = accept(serversocket,(struct sockaddr*)&address,&address_len);

    if(clientsocket<0){
      printf("Cannot connect with client\n" );
      exit(1);
    }

    //intitalise a struct to send the clientsocked fd.
    struct client_connect* data = malloc(sizeof(struct client_connect));
    data->socketfd = clientsocket;
    data->directory = directory;



    void* retVal = NULL;


    // create a separate thread to handle the client's requests
    pthread_t thread;
    pthread_create(&thread,retVal,client_interaction,data);


    if(retVal != NULL){
      free(retVal);
      close(serversocket);
      exit(0);
    }

    pthread_detach(thread);
  }


  free(directory);
  return PASSED;

}


//This function handles the interaction between a single client and the server.
void* client_interaction(void* arg){

  //receive the client socket.
  struct client_connect* data  = (struct client_connect*)arg;

  size_t ret;

  //create the compression dictionary array
  char** dictionary = makeDictArray();
  //create the decompression tree
  struct node* head  = makeDictTree();

  //constantly listen for requests from the client
  //if there are no more requests, close the client socket and stop communication
  // to this client
  while ((ret = recv(data->socketfd, NULL, 1, MSG_PEEK)) != 0){

  //get the important information from the client's request.
  struct request_data* request = analyse_request(data);

  //allocate space for the message to send back to client.
  uint8_t * msg = malloc(sizeof(uint8_t)*(request->payload_len+9));


  int checker  =0 ;


  //Check the type of the request.
  switch(request->type_num)  {

          //echo request
          case 0:

              //satisfy client's echo request.
              echo(request,msg,data,dictionary);

              break;

          case 2:

              checker = directory_listing(request,msg,data,dictionary);
              if(checker == ERROR){
                freeDict(dictionary);
                return NULL;
              }
              break;

          case 4:

              checker = file_size(request,msg,data,dictionary);

               if(checker == ERROR){
                  freeDict(dictionary);
                 return NULL;
               }
              break;

          case 6:

            checker = retrieve_file(request, msg, data,dictionary,head);
            if(checker == ERROR){
               freeDict(dictionary);
              return NULL;
            }
           break;

          case 8:
              freeDict(dictionary);
              return shut_down(request,msg,data);

          // A unknown type was specified, Error
          default:

              error(request,msg,data);
              freeDict(dictionary);
              return NULL;
    }
  }

    //close the clients socket and suspend any communication to this client.
    close(data->socketfd);
    free(data);
    freeDict(dictionary);
    return NULL;
}


//This function analyses any request from the client and extracts important
//information

struct request_data* analyse_request(struct client_connect* data){

  //intialise the struct to hold all important information from the client
  //request
  struct request_data* result = malloc(sizeof(struct request_data));

  //variable to store the byte representing the message_header/ ie the type.
  uint8_t  message_header;

  //read the 1 byte representing the message_header/ ie the type.
  read(data->socketfd,&message_header,1);

  int type[4];
  int reqCompression ;
  int resCompression;

    //This for loop gets the binary representation of the byte in message header.
   for (int i = 7; i >= 0; i--) {

     //extract each bit from the message header.
     int bit = message_header >> i;

     //if a&1 is true, this particular bit is 1.
     if (bit & 1){

        //if i>3 it is one of 4 bits that represent the type which is a 4 bit num.
        if(i>3){
          type[(i-7)*-1] = 1;
        }

        // if i ==3 it is the compression bit.

        if(i==3){
          reqCompression =1;
        }

        if(i == 2){
          resCompression = 1;
        }
     }

     // else it is a 0 bit.

     else{
       //if i>3 it is one of 4 bits that represent the type which is a 4 bit num.
       if(i>3){
         type[(i-7)*-1] = 0;
       }

       // if i ==3 it is the compression bit.

       if(i==3){
         reqCompression = 0;
       }
       if(i ==2){
         resCompression = 0 ;
       }
     }
  }

  //combine the 4 bits to get the number representing the type_num.

  int type_num = type[0]*pow(2,3) + type[1]*pow(2,2) + type[2]*pow(2,1) + type[3]*pow(2,0);

  //set an array to hold the 8 bytes representing the payload length.
  uint64_t payload[8];

  //get rid of any garbage values.
  memset(payload,0,sizeof(payload));

  //read byte at a time, the bytes representing the payload length.
  for(int i =0;i<8;i++){
    read(data->socketfd,&payload[i],1);
  }

  //combine the 8 bytes into the 8 byte number representing the payload length
  uint64_t payload_len = (payload[0]<<56) |
  (payload[1]<<48) |(payload[2]<<40) |
  (payload[3]<<32) |(payload[4]<<24) |
  (payload[5]<<16) |(payload[6]<<8) |
  payload[7];


  //allocate space for the payload given the payload length found above.
  unsigned char* pay = malloc(sizeof(unsigned char)*(payload_len));

  //read and store a byte at a time, the payload.
  for(int i = 0 ; i < payload_len; i++){
    read(data->socketfd,&pay[i],1);
  }

  //save all the important information to return .
  result->type_num = type_num;
  result->reqCompression = reqCompression;
  result->resCompression = resCompression;
  result->payload_len = payload_len;
  result->pay = pay;

  for(int i = 0 ; i < 8;i++){
      result->payload[i] = (uint8_t)payload[i];
  }


  return result;
}


//This function performs the echo requirements of a client request.

void echo(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary){

  //clear any garbage in the message to send back to the client.
    memset(msg,0,request->payload_len+9);

    //assign the correct type as the first byte.

    //if the compression bit is 1 the payload has been compressed, handle this.
    if(request->reqCompression == 1 || request->resCompression == 1 ){
        msg[0] = makeType(1,1);
    }
    else{
        msg[0] = makeType(1,0);
    }


    if(request->resCompression == 0 || request->reqCompression == 1){
    //copy the payload lenght into the message.
    for(int i = 1 ; i<9;i++){
      msg[i] = (unsigned int)request->payload[i-1] ;
    }

    //copy the payload into the message.
    for(int i = 9 ; i < (request->payload_len+9);i++){
      msg[i] = request->pay[i-9];
    }
    //send the response to the client
    send(data->socketfd,msg,(9+request->payload_len),0);

  }
  else{
    uint8_t* payload = getPayload(request,dictionary,request->payload_len , request->pay);

    for(int i = 1 ; i<9;i++){
      msg[i] = (unsigned int)request->comm_payload[i-1] ;
    }

    for(int i = 9 ; i < (request->comm_payload_len+9);i++){
      msg[i] = payload[i-9];
    }

    //send the response to the client
    send(data->socketfd,msg,(9+request->comm_payload_len),0);

  }


    //free any unnecessary variables.
    free(msg);
    free(request->pay);
    free(request);

}


//This function will be called whenever there is an error in the client's request.
void error(struct request_data* request,uint8_t* msg,struct client_connect* data){

  //generate the error response.
  uint8_t err[9];
  memset(err,0,9);
  err[0] = makeType((uint8_t)15,0);

  for(int i = 1; i<9;i++){
    err[i] = (unsigned int)0;
  }

  //send the error message.
  send(data->socketfd, err, 9, 0);

  //close the client socket.
  close(data->socketfd);

  //free any unnecessary variables
  free(msg);
  free(request->pay);
  free(request);
  free(data);
}

//this function will shut down the server.
void* shut_down(struct request_data* request,uint8_t* msg,struct client_connect* data){


      //close the client socket.
      close(data->socketfd);

      //free any unnecessary variables
      free(msg);
      free(request->pay);
      free(request);
      free(data);

      struct thread_return*  ret = malloc(sizeof (struct thread_return));

      return ret;
}

//This function will return the file size of a requested file by the client.
int file_size(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary){

      //Combine the directory path and the file name given to create the file path.
      char filepath[50];
      memcpy(filepath,data->directory,strlen(data->directory));
      memcpy(&filepath[strlen(data->directory)],&request->pay[0],sizeof(char)*request->payload_len);
      filepath[(strlen(data->directory) + request->payload_len)] = '\0';

      //opening the contents of config_file
      FILE* fp  = fopen(filepath,"rb");

      //check if the contents config file is empty
      if(fp == NULL){
        error(request,msg,data);
        return ERROR;
      }

      //Getting the file length of the config_file
      fseek(fp, 0, SEEK_END);
      uint64_t file_length = ftell(fp);
      fseek(fp, 0, SEEK_SET);

      fclose(fp);

      //gather each byte of the 8 byte file length
      unsigned char length_bytes[8];

      length_bytes[0] = (file_length >> 56) & 0xFF;
      length_bytes[1] = (file_length >> 48) & 0xFF;
      length_bytes[2] = (file_length >> 40) & 0xFF;
      length_bytes[3] = (file_length >> 32) & 0xFF;
      length_bytes[4] = (file_length >> 24) & 0xFF;
      length_bytes[5] = (file_length >> 16) & 0xFF;
      length_bytes[6] = (file_length >> 8) & 0xFF;
      length_bytes[7] = file_length & 0xFF;

      uint64_t len  = 8;


      //if the request requires the response to have compression
      if(request->resCompression == 1 ){

        //get the compressed payload.
        uint8_t* payload = getPayload(request,dictionary,len , length_bytes);
        //allocate space for the response
        uint8_t* ret_msg = malloc(sizeof(uint8_t)*(9 + request->comm_payload_len));

        // create the response.
        ret_msg[0] = makeType(5,1);
        memcpy(&ret_msg[1],&request->comm_payload[0],sizeof(uint8_t)*8);
        memcpy(&ret_msg[9],&payload[0],sizeof(uint8_t)*request->comm_payload_len);

        //send the response to the client
        send(data->socketfd,ret_msg,9 + request->comm_payload_len,0);
        //free any unnecessary variables.
        free(msg);
        free(request->pay);
        free(request);
        free(ret_msg);

        return PASSED;

      }

      // get the payload length in separate bytes.
      unsigned char len_bytes[8];
      len_bytes[0] = (len >> 56) & 0xFF;
      len_bytes[1] = (len >> 48) & 0xFF;
      len_bytes[2] = (len >> 40) & 0xFF;
      len_bytes[3] = (len >> 32) & 0xFF;
      len_bytes[4] = (len >> 24) & 0xFF;
      len_bytes[5] = (len >> 16) & 0xFF;
      len_bytes[6] = (len >> 8) & 0xFF;
      len_bytes[7] = len & 0xFF;

      uint8_t ret_msg[17];

      //make the response.
      ret_msg[0] = makeType(5,0);
      memcpy(&ret_msg[1],&len_bytes[0],sizeof(uint8_t)*8);
      memcpy(&ret_msg[9],&length_bytes[0],sizeof(uint8_t)*8);

      //send the response to the client
      send(data->socketfd,ret_msg,17,0);


      //free any unnecessary variables.
      free(msg);
      free(request->pay);
      free(request);


      return PASSED;

}

//this function will return all files within the given directory
int directory_listing(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary){

        //represents an entry in the directory.
       struct dirent *entry;

       //open the directory.
       DIR *directory = opendir(data->directory);

       //if directory doesnt exist it is an error.
       if (directory == NULL){
         error(request,msg,data);
         return ERROR;
       }

       //intialise array of filenames to store every fileName
       //in the directory.

      char** fileNames = malloc(sizeof(char*));

      int nameLength = 0 ;
      int count = 0 ;

      //check every entry in the given directory
       while ((entry = readdir(directory)) != NULL) {

            //create the filepath by concatenating the directory and the given entry name.
           char* path = malloc(sizeof(char)*(strlen(data->directory)+ strlen(entry->d_name) +1));
           memcpy(path,data->directory,sizeof(char)*(strlen(data->directory)+1));
           strncat(path,entry->d_name,(strlen(entry->d_name)+1));

           struct stat checker;
           stat(path, &checker);

           //check if the given file path is a file or not.
            if (S_ISREG(checker.st_mode) == 0 ){
              //it is not a file.
            }
            else{
              //It is a file if it enters here.
              count++;
              //add the filename to the fileNames array.
              if(count >1){
                fileNames = realloc(fileNames, sizeof(char*)*(count));
              }

              nameLength += (strlen(entry->d_name)+1);

              fileNames[count-1] = malloc(sizeof(char)*(strlen(entry->d_name)+1));
              memcpy(fileNames[count-1],entry->d_name,strlen(entry->d_name)+1);


            }

            free(path);
       }
       closedir(directory);

        //If the response requires compression.
       if(request->resCompression == 1 ){

         //compress the response
         uint8_t* payload = getDirPayload(request,dictionary,count , fileNames);

         //get the length of the compressed response
         uint64_t len = (uint64_t)request->comm_payload_len;

         unsigned char length_bytes[8];

         //get each byte of the 8byte length of the compressed payload
         length_bytes[0] = (len >> 56) & 0xFF;
         length_bytes[1] = (len >> 48) & 0xFF;
         length_bytes[2] = (len >> 40) & 0xFF;
         length_bytes[3] = (len >> 32) & 0xFF;
         length_bytes[4] = (len >> 24) & 0xFF;
         length_bytes[5] = (len >> 16) & 0xFF;
         length_bytes[6] = (len >> 8) & 0xFF;
         length_bytes[7] = len & 0xFF;

          //allocate enough space for the response
          uint8_t * ret_msg = malloc(sizeof(uint8_t)*(9+request->comm_payload_len));


          //make the response
          ret_msg[0] = makeType(3,1);
          memcpy(&ret_msg[1],&length_bytes[0],sizeof(uint8_t)*8);
          memcpy(&ret_msg[9],&payload[0],sizeof(uint8_t)*request->comm_payload_len);

          //send the response to the client
          send(data->socketfd,ret_msg,(9+request->comm_payload_len),0);


          //free any unnecessary variables.
          free(msg);
          free(request->pay);
          free(request);

          for(int i = 0 ; i < count;i++){
            free(fileNames[i]);
          }

          free(fileNames);

          free(ret_msg);

           return PASSED ;



      }

      //else if the response doesnt require compression.

      //get the length of the payload.
      uint64_t len = (uint64_t)nameLength;

      unsigned char length_bytes[8];

      //get each byte of the payload length
      length_bytes[0] = (len >> 56) & 0xFF;
      length_bytes[1] = (len >> 48) & 0xFF;
      length_bytes[2] = (len >> 40) & 0xFF;
      length_bytes[3] = (len >> 32) & 0xFF;
      length_bytes[4] = (len >> 24) & 0xFF;
      length_bytes[5] = (len >> 16) & 0xFF;
      length_bytes[6] = (len >> 8) & 0xFF;
      length_bytes[7] = len & 0xFF;


      //allocate space for the response
       uint8_t * ret_msg = malloc(sizeof(uint8_t)*(9+nameLength));

       //make the response.
       ret_msg[0] = makeType(3,0);
       memcpy(&ret_msg[1],&length_bytes[0],sizeof(uint8_t)*8);

       int oldLen = 0 ;
       for(int j = 0 ; j<count; j++){
         char* temp = fileNames[j];
         memcpy(&ret_msg[9+oldLen],&temp[0],sizeof(uint8_t)*(strlen(temp)+1));
         oldLen+= strlen(temp) +1;
       }


       //send the response to the client
       send(data->socketfd,ret_msg,(9+nameLength),0);


       //free any unnecessary variables.
       free(msg);
       free(request->pay);
       free(request);


       for(int i = 0 ; i < count;i++){
         free(fileNames[i]);
       }

       free(fileNames);

       free(ret_msg);

        return PASSED ;
     }


// this function creates the dictionary array required for compression
char** makeDictArray(){
  FILE* fp  = fopen("compression.dict","rb");

  //set an array to hold the 256 different bit sequences for each of the 256 bytes.
  char** dictArray = malloc(sizeof(char*)*256);

  unsigned char byte;
  int bits[8];
  int offset = 0;
  int bytes = -1 ;
  int count = 0 ;
  int flag = 1;
  int counter = 0 ;
  while (!feof(fp)){
      //read a byte at a time
       byte=fgetc(fp);

       //if the current byte is the beginning of the definition of the length
       //of the bit sequence .
       if(offset ==0 || count == offset){
         if(count == offset && bytes != -1){
            dictArray[bytes][offset] = '\0';
         }
         bytes++;
         if(bytes ==256){
           break;
         }
         offset = (byte);
         // allocate enough space for the bitsequence given its length
         dictArray[bytes] = malloc(sizeof(char)*offset+1);
         count = 0 ;
       }
       else{
           //This for loop gets the binary representation of the byte .
          for (int i = 7; i >= 0; i--) {
            //extract each bit.
            int bit = byte >> i;
            //if a&1 is true, this particular bit is 1.
            if (bit & 1){
              if(flag){
                  dictArray[bytes][count] = '1';
              }
              else{

                  bits[counter] = 1;
                  counter++;
              }

            }
            // else it is a 0 bit.
            else{
              if(flag){
                  dictArray[bytes][count] = '0';
              }
              else{

                  bits[counter] = 0;
                  counter++;
              }
            }



            count++;

            // if counter is 8, calculate the length of the current bit sequence
            if(counter == 8){

              counter = 0 ;
              flag = 1;
              offset  = bits[0]*pow(2,7) + bits[1]*pow(2,6) + bits[2]*pow(2,5)
              + bits[3]*pow(2,4) + bits[4]*pow(2,3) + bits[5]*pow(2,2)
              + bits[6]*pow(2,1) + bits[7]*pow(2,0);
              bytes++;

              //allocate enough space for the bit sequence given the length.
              dictArray[bytes] = malloc(sizeof(char)*offset+1);
              count  = 0 ;

            }

            //if the current bit read was the last bit of the sequence
            // begin reading the length of the next bit sequence.
            if(count == offset && i!=0){

               dictArray[bytes][offset] = '\0';

               flag = 0;

               if(bytes ==255){
                 break;
               }
            }
         }

       }

   }

   return dictArray;
}

//This function returns the compressed payload.
uint8_t* getPayload(struct request_data*  request, char** dictionary,int length , unsigned char* message){
  uint8_t* res ;
  char* bits;
  int oldLen = 0 ;

  //for each byte in the given payload,compress the byte to its correlated bit sequence
  //in the dict array
  for(int i = 0 ; i < length ; i ++){
    unsigned char byte = message[i];

    //the byte read, represents the index in which its bit sequence is located
    //in the dict array.
    int len = strlen(dictionary[(int)byte]);

    //allocate space for the bits to be read for the payload.
    if(i == 0 ){
      bits = malloc(sizeof(char)*len);
    }else{
      bits = realloc(bits,sizeof(char)*(len + oldLen));
    }

    //place each bit sequence of every byte read in the bits array.
    for(int j = (0 + oldLen) ; j <oldLen + len ; j++){

      bits[j]  = dictionary[(int)byte][j-oldLen];

    }

     oldLen += len;

  }

  //check if padding is necessary.
  int multiplier = 0;

  //it isnt necesary
  if((oldLen%8 == 0)){
    multiplier = oldLen/8 +1;
  }
  //it is necessary
  else{
    multiplier = oldLen/8 +2;

  }


  res = malloc(sizeof(unsigned char)*multiplier);

  int index = 0 ;
  int idx = 0 ;
  int bit[8];
  for(int i = 0 ; i< oldLen ; i ++){

    if(bits[i] == '1'){
      bit[idx] = 1;
    }
    else{
      bit[idx] = 0 ;
    }

    idx ++ ;

    //for every 8bits read, create a compressed byte which will form part of the compressed payload.
    if(idx == 8){

      idx = 0 ;
      uint8_t entry  = bit[0]*pow(2,7) + bit[1]*pow(2,6) + bit[2]*pow(2,5) +
      bit[3]*pow(2,4) + bit[4]*pow(2,3) + bit[5]*pow(2,2) + bit[6]*pow(2,1) + bit[7]*pow(2,0);
      res[index] = entry;

      index++;

    }
  }

  int padding = 0 ;

//check if padding is required.
  if(idx != 0){
    //padding is required and account for this.
    uint8_t entry = 0 ;

    for(int i =0 ; i < idx ; i ++){
      entry+=bit[i] * pow(2,7-i);
    }

    for(int i = idx ; i<8 ;i++){
      padding++;
    }

    //enter the byte with the padding
    res[index] = entry;

    index++;
    //enter the byte which represents how much padding is needed.
    res[index] = (uint8_t)padding;
      index++;

  }
  else{
    //not required.
    res[index] = (uint8_t)0;
      index++;

  }


  uint64_t payload_length = (uint64_t)index;

  uint64_t payload[8];

  //gather each byte of the compressed payload.
  payload[0] = (payload_length >> 56) & 0xFF;
  payload[1] = (payload_length >> 48) & 0xFF;
  payload[2] = (payload_length >> 40) & 0xFF;
  payload[3] = (payload_length >> 32) & 0xFF;
  payload[4] = (payload_length >> 24) & 0xFF;
  payload[5] = (payload_length >> 16) & 0xFF;
  payload[6] = (payload_length >> 8) & 0xFF;
  payload[7] = payload_length & 0xFF;

  //store the payload length bytes.
  for(int i = 0 ; i < 8;i++){
      request->comm_payload[i] = payload[i];
  }

  //store the payload length
  request->comm_payload_len = payload_length;


  free(bits);

  //return the compressed payload.
  return res;
}


//free all allocated memory with the dictionary.
void freeDict(char** dictionary){
  for(int i = 0 ; i <256;i++){
    free(dictionary[i]);

  }
  free(dictionary);
}

//This function does the equivalent of getPayload, except it is specifically for the
//function of compressing the payload of a directory listing request as the payload is in a different form
uint8_t* getDirPayload(struct request_data*  request, char** dictionary,int n_files,char** message){
  uint8_t* res ;
  char* bits;
  int oldLen = 0 ;

//for each file name
for(int a  = 0 ; a< n_files ; a++){
  char* temp = message[a];
  //for each byte in the filename
  for(int i = 0 ; i < strlen(temp)+1 ; i ++){
     char byte = temp[i];

    //find the bit sequence and store it in the bits array
    int len = strlen(dictionary[(int)byte]);

    if(i == 0 && a==0){
      bits = malloc(sizeof(char)*len);
    }else{
      bits = realloc(bits,sizeof(char)*(len + oldLen));
    }

    for(int j = (0 + oldLen) ; j <oldLen + len ; j++){

      bits[j]  = dictionary[(int)byte][j-oldLen];

    }

     oldLen += len;

  }
}

  int multiplier = 0;

  if((oldLen%8 == 0)){
    multiplier = oldLen/8 +1;
  }
  else{
    multiplier = oldLen/8 +2;

  }


  res = malloc(sizeof(unsigned char)*multiplier);

  int index = 0 ;
  int idx = 0 ;
  int bit[8];
  for(int i = 0 ; i< oldLen ; i ++){

    if(bits[i] == '1'){
      bit[idx] = 1;
    }
    else{
      bit[idx] = 0 ;
    }

    idx ++ ;

    if(idx == 8){

      idx = 0 ;
      uint8_t entry  = bit[0]*pow(2,7) + bit[1]*pow(2,6) + bit[2]*pow(2,5) +
      bit[3]*pow(2,4) + bit[4]*pow(2,3) + bit[5]*pow(2,2) + bit[6]*pow(2,1) + bit[7]*pow(2,0);
      res[index] = entry;

      index++;



    }
  }

  int padding = 0 ;

  if(idx != 0){

    uint8_t entry = 0 ;

    for(int i =0 ; i < idx ; i ++){
      entry+=bit[i] * pow(2,7-i);
    }

    for(int i = idx ; i<8 ;i++){
      padding++;
    }

    res[index] = entry;

    index++;

    res[index] = (uint8_t)padding;
      index++;

  }
  else{
    res[index] = (uint8_t)0;
      index++;

  }



  uint64_t payload_length = (uint64_t)index;

  uint64_t payload[8];

  payload[0] = (payload_length >> 56) & 0xFF;
  payload[1] = (payload_length >> 48) & 0xFF;
  payload[2] = (payload_length >> 40) & 0xFF;
  payload[3] = (payload_length >> 32) & 0xFF;
  payload[4] = (payload_length >> 24) & 0xFF;
  payload[5] = (payload_length >> 16) & 0xFF;
  payload[6] = (payload_length >> 8) & 0xFF;
  payload[7] = payload_length & 0xFF;

  for(int i = 0 ; i < 8;i++){
      request->comm_payload[i] = payload[i];
  }



  request->comm_payload_len = payload_length;


  free(bits);

  return res;
}

//this function is required to decompress a payload. It forms a binary tree
// which can transform a bit sequence into a single byte given the dictionary.

struct node* makeDictTree(){
  FILE* fp  = fopen("compression.dict","rb");

  //set the head of the tree.
  struct node* head = malloc(sizeof(struct node));
  head->left= NULL;
  head->right = NULL;

  struct node* currentPrev = NULL;

  unsigned char byte;
  int bits[8];
  int offset = 0;
  int bytes = -1 ;
  int count = 0 ;
  int flag = 1;
  int counter = 0 ;


  while (!feof(fp)){
      //read a byte at a time
       byte=fgetc(fp);

       //for each byte check if it is the beginning of the definition
       //of the length of a bit sequence.

       if(offset ==0 || count == offset){
         //if it is, read the length of the bit sequence.
         if(bytes!=-1 && count==offset){

           currentPrev->value = bytes;
           currentPrev = head;
         }

         bytes++;

         if(bytes ==256){
           break;
         }

         offset = (byte);
         count = 0 ;

       }
       else{

           //This for loop gets the binary representation of the byte .
          for (int i = 7; i >= 0; i--) {

            if(currentPrev == NULL){
              currentPrev = head;
            }

            //extract each bit
            int bit = byte >> i;
            //if a&1 is true, this particular bit is 1. and is to the right of
            // the current previous node.
            if (bit & 1){
              if(flag){

                if(currentPrev->right == NULL){

                  //if there doesnt exist a node to the right of the currentPrev
                  //make an entry.

                  struct node* entry = malloc(sizeof(struct node));
                  entry->right = NULL;
                  entry->left = NULL;


                  currentPrev->right = entry;

                  currentPrev = currentPrev ->right;


                }
                else{

                  currentPrev = currentPrev->right;
                }


              }
              else{
                  bits[counter] = 1;
                  counter++;
              }

            }
            // else it is a 0 bit. and thus is to the left of the current previous
            //node
            else{
              if(flag){

                if(currentPrev->left == NULL){
                  //if there doesnt exist a node to the left of the currentPrev
                  //make an entry.
                  struct node* entry = malloc(sizeof(struct node));
                  entry->right = NULL;
                  entry->left = NULL;


                  currentPrev->left = entry;

                  currentPrev = currentPrev ->left;

                }
                else{
                  currentPrev = currentPrev->left;
                }

              }
              else{
                  bits[counter] = 0;
                  counter++;
              }
            }



            count++;

            //if counter is 8 , the bits that form the length of the next
            //bit sequence have been read.
            if(counter == 8){

              counter = 0 ;
              flag = 1;
              offset  = bits[0]*pow(2,7) + bits[1]*pow(2,6) + bits[2]*pow(2,5)
              + bits[3]*pow(2,4) + bits[4]*pow(2,3) + bits[5]*pow(2,2)
              + bits[6]*pow(2,1) + bits[7]*pow(2,0);
              bytes++;

              currentPrev = head;

              count  = 0 ;

            }

            //if the current bit read was the last of bit sequence being read.
            //then set the current byte as the value of the current previous node.
            if(count == offset && i!=0){


              currentPrev->value = bytes;

              currentPrev = head;

               flag = 0;

               if(bytes ==255){
                 break;
               }
            }
         }

       }

   }




   return head;
}



//Using the dictionary tree, decompression occurs here. It returns the
//required information to send a decompressed payload.
struct decompress_result* decompress(uint8_t* bytes,struct node* head,int size){

    uint8_t* result = NULL;

    struct node* prev = head;

    int count = 0 ;
    int flag = 1;

    //get the number of padding in this compressed payload.
    uint8_t padding = bytes[size-1];

    int counter = 8 -  padding;


    for(int i = 0 ; i < size; i ++){

      //for each byte in the compressed payload.

      uint8_t temp = bytes[i];

      //read each bit of the byte.
      for (int j = 7; j >= 0; j--) {

        if(i == size-2){

          counter--;
        }

        if(flag){

        int bit = temp >> j;

        //if the bit is 1 then move to the right of the current prev.
        if (bit & 1){

            //If there doesnt exist a right node, the current node is the
            //uncompressed byte required.
            if(prev->right == NULL){
                if(count == 0 ){
                  result = malloc(sizeof(uint8_t));
                  result[count] = prev->value;

                }else{
                 result = realloc(result,sizeof(uint8_t)*(count + 1));
                  result[count] = prev->value;
                }

                count++;

                prev = head->right;
            }
            else{
              prev = prev->right;
            }
        }
        // else if it is 0, move to the left of the current prev.
        else{
          //If there doesnt exist a left node, the current node is the
          //uncompressed byte required.
          if(prev->left == NULL){
              if(count == 0 ){

                  result = malloc(sizeof(uint8_t));
                    result[count] = prev->value;
              }else{
                 result = realloc(result,sizeof(uint8_t)*(count + 1));
                   result[count] = prev->value;
              }


              count++;

              prev = head->left;
          }
          else{
            prev = prev->left;
          }
        }

        //if counter == 0 , the next bits to be read are the padding bits
        //hence dont read them and add the last current node.

        if(counter== 0){
          result = realloc(result,sizeof(uint8_t)*(count + 1));
          result[count] = prev->value;

          struct decompress_result * res = malloc(sizeof(struct decompress_result));
          res->result = result;
          res->num = count+1;


          return res;
        }

      }

    }

}

  return NULL;
}


void freeInfo(struct information * info){
  free(info->session_id);
  free(info->offset);
  free(info->length);
  free(info->filenames);
  free(info);
}


//this retrieves a file at a given offset and length.
int retrieve_file(struct request_data* request,uint8_t* msg,struct client_connect* data,char** dictionary,struct node* head){

  uint8_t session_id [4];
  uint64_t starting_offset_bytes[8];
  uint64_t length_bytes[8];
  char* file_name ;

  // if the request requires decompression.
    if(request->reqCompression == 1){

      //decompress the payload received.
      struct decompress_result* result = decompress((uint8_t*)request->pay,head,request->payload_len);

      //allocate space for the filename
       file_name = malloc(sizeof(char)*(result->num - 20));

       //get the decompressed session id
       memcpy(&session_id[0],&result->result[0],4*sizeof(uint8_t));

       //get the decompressed offset
       for(int i = 0 ; i < 8 ; i++){
         starting_offset_bytes[i] = result->result[i+4];
       }

        //get the decompressed length
       for(int i = 0 ; i < 8 ; i++){
         length_bytes[i] = result->result[i+12];
       }

        //get the decompressed filename

       memcpy(&file_name[0],&result->result[20],(result->num-20)*sizeof(char));


     free(result);

    }

    else{

      //allocate space for the filename
    file_name = malloc(sizeof(char)*(request->payload_len-20));

  //get the session id
    memcpy(&session_id[0],&request->pay[0],4*sizeof(uint8_t));

  //get the offset
    for(int i = 0 ; i < 8 ; i++){
      starting_offset_bytes[i] = request->pay[i+4];
    }

    //get the length
    for(int i = 0 ; i < 8 ; i++){
      length_bytes[i] = request->pay[i+12];
    }

    //get the filename
    memcpy(&file_name[0],&request->pay[20],(request->payload_len-20)*sizeof(char));

    }

    uint64_t starting_offset = (starting_offset_bytes[0]<<56) |
    (starting_offset_bytes[1]<<48) |(starting_offset_bytes[2]<<40) |
    (starting_offset_bytes[3]<<32) |(starting_offset_bytes[4]<<24) |
    (starting_offset_bytes[5]<<16) |(starting_offset_bytes[6]<<8) |
    starting_offset_bytes[7];


    uint64_t length = (length_bytes[0]<<56) |
    (length_bytes[1]<<48) |(length_bytes[2]<<40) |
    (length_bytes[3]<<32) |(length_bytes[4]<<24) |
    (length_bytes[5]<<16) |(length_bytes[6]<<8) |
    length_bytes[7];


    uint32_t session = (session_id[0]<<24) |
    (session_id[1]<<16) |(session_id[2]<<8) |
    session_id[3];


    //if info is null, set up the shared memory.
    if(info == NULL){
      info = malloc(sizeof(struct information));
      info->session_id = NULL;
      info->offset = NULL;
      info->filenames = NULL;
      info->n_entries = 0 ;
      info->length = NULL;
      info->max =0;
    }

    //if no entries exist in the shared memory, add this current thread's
    //information
    if(info->session_id == NULL ){
      info->session_id = malloc(sizeof(uint32_t));
      info->session_id[0] = session;
      info->offset = malloc(sizeof(uint64_t));
      info->offset[0] = starting_offset;
      info->filenames = malloc(sizeof(char*));
      info->filenames[0] = file_name;
      info->length = malloc(sizeof(uint64_t));
      info->length[0] = length;
      info->n_entries = 1;
      info->max = 1;
      info->count = 0 ;
      info->newOffset = info->offset[0];
      info->n_connections = 1;
    }
    else{

        //if the session ids match
        if(session == info->session_id[0]){

          //check the given offset, filename and length
          if(info->offset[0] != starting_offset ||
            strcmp(info->filenames[0],file_name) != 0
            || info->length[0] != length){
              //if it is different it is an error.

              error(request,msg,data);
              return ERROR;
          }


        }
        else{
          //else this is another connection
          info->n_connections++;
        }




    }



    //create the filepath given the file name and the directory
    char* path = malloc(sizeof(char)*(strlen(data->directory)+ strlen(file_name) +1));
    memcpy(path,data->directory,sizeof(char)*(strlen(data->directory)+1));

    strncat(path,file_name,(strlen(file_name)+1));



    FILE* fp  = fopen(path,"rb");

    //check if the file exists, else it is an error
    if(fp == NULL ){
      free(path);
      free(file_name);
      error(request,msg,data);
      return ERROR;
    }


    fseek(fp, 0, SEEK_END);
    int file_length = ftell(fp);


    //check if the length and offset given dont exceed the length of the file
    if(file_length < (starting_offset + length)){
      free(path);
      free(file_name);
      error(request,msg,data);
      return ERROR;
    }
    fclose(fp);

    uint64_t length_message;
    uint64_t message_offset;

    //this is an infinite while loop where all connections loop and send
    //portions of the required payload.

    while(1){


    //if the payload has been fully sent

    if((info->newOffset-info->offset[0]) == length){
       break;
    }

    //get the updated offset.
    message_offset = info->newOffset;

     uint64_t offset_bytes[8];
     offset_bytes[0] = (message_offset >> 56) & 0xFF;
     offset_bytes[1] = (message_offset >> 48) & 0xFF;
     offset_bytes[2] = (message_offset >> 40) & 0xFF;
     offset_bytes[3] = (message_offset >> 32) & 0xFF;
     offset_bytes[4] = (message_offset >> 24) & 0xFF;
     offset_bytes[5] = (message_offset >> 16) & 0xFF;
     offset_bytes[6] = (message_offset >> 8) & 0xFF;
     offset_bytes[7] = message_offset & 0xFF;


     // if the total file length is not over 1000000bytes then dont
     //send a portion, send the whole length required.
     if(1000000 + message_offset > file_length){
        length_message = length;
     }
     else{
       //if 1000000bytes will exceed the length required
       //get the amount required.
       if(message_offset + 1000000 > length){
         length_message = length-message_offset;
       }
       else{
         length_message = 1000000;
       }

     }

    uint64_t message_length_bytes[8];
    message_length_bytes[0] = (length_message >> 56) & 0xFF;
    message_length_bytes[1] = (length_message >> 48) & 0xFF;
    message_length_bytes[2] = (length_message >> 40) & 0xFF;
    message_length_bytes[3] = (length_message >> 32) & 0xFF;
    message_length_bytes[4] = (length_message >> 24) & 0xFF;
    message_length_bytes[5] = (length_message >> 16) & 0xFF;
    message_length_bytes[6] = (length_message >> 8) & 0xFF;
    message_length_bytes[7] = length_message & 0xFF;

    //update the offset for other threads to send
    info->newOffset = length_message + message_offset;


    int size = 0 ;


    FILE* fp  = fopen(path,"rb");
    //make file pointer point at the correct offset
    fseek(fp,message_offset, SEEK_SET);

    //allocate enough space for the data for the response.
    uint8_t* res = malloc(sizeof(uint8_t)*length_message);

    uint8_t byte;
    while (!feof(fp)){
      //read each byte of the file at the given offset

        byte=(uint8_t)fgetc(fp);

        res[size] = byte;

        size++;

        // if the given length has been reached, stop reading.
        if(size == length_message){
          break;
        }

     }


     fclose(fp);


     uint64_t payload_length;
     uint8_t* length_payload_bytes;
       uint8_t* ret_msg;

      // if the response requires compression.

     if(request->resCompression == 1){
        unsigned char* uncompressed = malloc(sizeof(unsigned char)*(20 +length_message));

        //set up the uncompressed payload.
        for(int i = 0 ; i < 4 ; i ++ ){
          uncompressed[i] = session_id[i];
        }

        for(int i = 4 ; i < 12 ; i ++ ){
          uncompressed[i] = offset_bytes[i-4];
        }
        for(int i = 12 ; i < 20 ; i ++ ){
          uncompressed[i] = message_length_bytes[i-12];
        }

        memcpy(&uncompressed[20],&res[0],sizeof(uint8_t)*length_message);

        //get the compressed payload.
        uint8_t* payload  = getPayload(request,dictionary, 20+length_message , uncompressed);

        payload_length = (uint64_t) request->comm_payload_len ;

        length_payload_bytes = malloc(sizeof(uint8_t)*8);

        length_payload_bytes[0] = (uint8_t)(payload_length >> 56) & 0xFF;
        length_payload_bytes[1] = (uint8_t)(payload_length >> 48) & 0xFF;
        length_payload_bytes[2] = (uint8_t)(payload_length >> 40) & 0xFF;
        length_payload_bytes[3] = (uint8_t)(payload_length >> 32) & 0xFF;
        length_payload_bytes[4] = (uint8_t)(payload_length >> 24) & 0xFF;
        length_payload_bytes[5] = (uint8_t)(payload_length >> 16) & 0xFF;
        length_payload_bytes[6] = (uint8_t)(payload_length >> 8) & 0xFF;
        length_payload_bytes[7] =(uint8_t) payload_length & 0xFF;

        //allocate space for the response.
        ret_msg = malloc(sizeof(uint8_t)*(9 + request->comm_payload_len));

        //set up the response
        ret_msg[0] = makeType(7,1);

        memcpy(&ret_msg[1],&length_payload_bytes[0],sizeof(uint8_t)*8);

        memcpy(&ret_msg[9],&payload[0],sizeof(uint8_t)*request->comm_payload_len);

        //send the response to the client
        send(data->socketfd,ret_msg,9 + request->comm_payload_len,0);

     }
     else{

       //else the reponse does not require compression

       //get the length of the payload.
        payload_length = (uint64_t)length_message + 20 ;

        length_payload_bytes = malloc(sizeof(uint8_t)*8);

       length_payload_bytes[0] = (uint8_t)(payload_length >> 56) & 0xFF;
       length_payload_bytes[1] = (uint8_t)(payload_length >> 48) & 0xFF;
       length_payload_bytes[2] = (uint8_t)(payload_length >> 40) & 0xFF;
       length_payload_bytes[3] = (uint8_t)(payload_length >> 32) & 0xFF;
       length_payload_bytes[4] = (uint8_t)(payload_length >> 24) & 0xFF;
       length_payload_bytes[5] = (uint8_t)(payload_length >> 16) & 0xFF;
       length_payload_bytes[6] = (uint8_t)(payload_length >> 8) & 0xFF;
       length_payload_bytes[7] = (uint8_t)payload_length & 0xFF;

       //allocate enough space for the response
        ret_msg = malloc(sizeof(uint8_t)*(9 + length_message + 20));

        //set up the response.
        ret_msg[0] = makeType(7,0);

        memcpy(&ret_msg[1],&length_payload_bytes[0],sizeof(uint8_t)*8);

        memcpy(&ret_msg[9],&session_id[0],sizeof(uint8_t)*4);

        for(int i = 13 ; i < 21 ; i ++ ){
          ret_msg[i] = offset_bytes[i-13];
        }
        for(int i = 21 ; i < 29 ; i ++ ){
          ret_msg[i] = message_length_bytes[i-21];
        }

        memcpy(&ret_msg[29],&res[0],sizeof(uint8_t)*length_message);

        //send the response to the client
        send(data->socketfd,ret_msg,29+ length_message,0);


     }

   }

   //if the thread has finished its work get rid of its information.
   for(int i = 0 ; i<info->n_entries;i++){
     if(session == info->session_id [i]){
       info->session_id = NULL;
       info->offset[i] = 0 ;
       info->length[i] = 0 ;
       info->filenames[i] = 0 ;
       info->n_entries--;

     }
   }

   free(msg);
   free(request->pay);
    free(request);

    free(path);
    free(file_name);
    return PASSED ;
}



//This function creates the first byte to be sent in any payload.
uint8_t makeType(uint8_t type, int compression ){

    int bits[8];

    //given a type, read the first 4 bits and add it to the final result.
    for (int i = 3; i >= 0; i--) {
      int bit = type >> i;
      if (bit & 1){

          bits[(i-3)*-1] = 1;

      }
      else{

        bits[(i-3)*-1] = 0;
      }


    }

    //allocate the 5th bit as the compression bit.
    bits[4] = compression;

    //pad the rest of the bits as 0
    for(int i = 5 ; i <8; i++ ){
      bits[i] = 0 ;
    }


    //get the final result of the stored bits.
     uint8_t res  = bits[0]*pow(2,7) + bits[1]*pow(2,6) + bits[2]*pow(2,5)
                  + bits[3]*pow(2,4) + bits[4]*pow(2,3) + bits[5]*pow(2,2)
                  + bits[6]*pow(2,1) + bits[7]*pow(2,0);

    return res;

}
