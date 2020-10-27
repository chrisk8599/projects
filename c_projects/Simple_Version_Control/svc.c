#include "svc.h"


 // a function which copies the content of the received file path
 // and creates a new file and returns the path of this new file

char* saveContents(char* fileName){
  FILE* fp  = fopen(fileName,"rb");

  //check if the contents of what i am saving is empty or not
  if(fp == NULL){
    return NULL;
  }

  //determining filelength
  fseek(fp, 0, SEEK_END);
  int file_length = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  //allocating space for the new file name where the contents
  // of the file being saved will be stored

  char* name = malloc(sizeof(char)*3);

  name[0] = 'a';
  name[1] = number;
  name[2] = '\0';

  number++;

  FILE* store = fopen(name ,"w");
  unsigned char byte2;

  for(int i =0 ; i<file_length ; i ++){
    // read each byte of the file
    fread(&byte2,1,1,fp);
    // then save each byte into the new file
    fputc((unsigned char)byte2,store);
  }

  fclose(fp);
  fclose(store);

  return name;

}


// copy the contents of fileName into the dest file path.
void restoreContents(char* fileName,char* dest){

//check file that we are reading is has some contents
  FILE* fp  = fopen(fileName,"rb");
  if(fp == NULL){
    return ;
  }


  fseek(fp, 0, SEEK_END);
  int file_length = ftell(fp);


  fseek(fp, 0, SEEK_SET);
  FILE* store = fopen(dest ,"w");
  unsigned char byte2;

  for(int i =0 ; i<file_length ; i ++){
    //for every byte read
    fread(&byte2,1,1,fp);
    //write it into the destination file
    fputc((unsigned char)byte2,store);
  }



  fclose(fp);
  fclose(store);


}

 //freeing memory involving changes detected during commits or any other place            .
// where uncommitted changes were required to be detected.

void freeChanges(struct changes* help){
  struct changes * current  = help;
  struct changes*  next;

  while (current != NULL) {
    // this loop simply iterates through all changes and frees
    //memory allocated towards it.
     next = current;
     current = current->next;
     free(next->type);
     free(next->file_name);
     free(next);
  }
}


//freeing the removed array.
// the removed array kept track of all files
// which were removed before committing happened.

void freeRemoved(struct branch* help){

  for(int i = 0 ; i< help->n_rmv ; i ++){
    free(help->removed[i]);
  }

  free(help->removed);

  help->removed = NULL;

    help->n_rmv = 0;

}


// THe init function initialises a branch called master and allocates
// space within a branches struct to store this master branch. all
// appropriate variables are set in this step.
// The return variable of this function is the branches STRUCT
//such that a user can have access to all branches made in the program.


void *svc_init(void) {
    // TODO: Implement
  struct branches* program = malloc(sizeof(struct branches));
  program->branches = malloc(sizeof(struct branch*));
  program->branches[0] = malloc(sizeof(struct branch ));
  program->branches[0]->n_commits = 0;
  program->branches[0]->n_tracked = 0 ;
  program->branches[0]->n_add = 0 ;
  program->branches[0]->n_rmv = 0;
  program->branches[0]->merged = 0;
  char name[] = "master";
  program->branches[0]->name = malloc(sizeof(char)*(strlen(name)+1));
  memcpy(    program->branches[0]->name,&name,sizeof(char)*(strlen(name)+1));


  program -> n_branch = 1;
  program -> current = 0 ;
  return   program;
}

void cleanup(void *helper) {

  struct branches* help = (struct branches*)helper;

  //this for loop iterates through each branch created
  for(int i = 0 ; i < help->n_branch ; i++){

    // checks if the branch has any tracked files
    if(  help->branches[i]->n_tracked > 0 ){

      struct file * current  =   help->branches[i]->tracked_files;
      struct file*  next;

      //for every tracked file frees the associated filename

      while (current != NULL) {

         next = current;
         current = current->next;


         free(next->file_name);
         free(next);
      }
    }


    if(  help->branches[i]->n_commits>0){
      // checks if the branch has any commits

      struct commit * current  = help->branches[i]->commits;
      struct commit*  next;

      // for every commit made in this branch free memory
      while (current != NULL) {
         next = current->next;

         if(current->resetNext == NULL){
            // do nothing if reset has not been called this is only
            // for if reset has been called
         }
         else{
           // inside this else statement is freeing all commits
           //which have been deallocated from their respective branches
           //due to reset.

           struct commit * a  = current->resetNext;
           struct commit * b;
           while(a!=NULL){
             b = a->next;

             //each commit has a set of tracked files that have
              // to be freed of any memory allocated
             for(int i = 0 ; i< a->n_tracked;i++){
               free(a->tracked[i]->content->orig);
               free(a->tracked[i]->content->saved);
               free(a->tracked[i]->content);
               free(a->tracked[i]);
             }

            //freeing attributes of a struct commit which were allocated
            //memory

             free(a->tracked);
             free(a->commit_id);
             free(a->message);
             freeChanges(a->changes);
             free(a);
             a = b;
           }
         }


         //whether reset has been called or not, this is freeing all commits
         // that the branch still has reference to .

         for(int i = 0 ; i< current->n_tracked;i++){
           free(current->tracked[i]->content->orig);
           free(current->tracked[i]->content->saved);
           free(current->tracked[i]->content);
           free(current->tracked[i]);
         }



         free(current->tracked);
         free(current->commit_id);
         free(current->message);
         freeChanges(current->changes);
         free(current);

         current = next;

      }
    }

    //if there are any removed files that were uncommitted
    //free the memory which stores these filenames

    if(help->branches[i]->n_rmv>0){

      freeRemoved(help->branches[i]);
    }





    free(help->branches[i]->name);

      //free the branches name

    free(help->branches[i]);

    // free the specific branch itself


  }

  //free the pointer which holds all branches and the program itself.
  free(help->branches);
  free(helper);


}

int hash_file(void *helper, char *file_path) {
    // creates the hash for the filepath

    if(file_path == NULL){
      return -1;
    }

    FILE* file_contents;

    file_contents = fopen(file_path,"rb");

    if(file_contents == NULL){
      return -2;
    }

    int hash = 0;

    fseek(file_contents, 0, SEEK_END);
    int file_length = ftell(file_contents);

    fseek(file_contents, 0, SEEK_SET);

    unsigned char byte1;
    unsigned char byte2;

    int size = strlen(file_path);
    int sum1 = 0;


    for(int i = 0 ; i < size ;i++){
      //read each byte of the file name and sum it
      byte1 = (unsigned char)file_path[i];
      sum1 += byte1;
    }

    // calculate the hash

    hash = (hash + sum1) % 1000;

    int sum2 = 0 ;

    for(int i =0 ; i<file_length ; i ++){

      // read each byte of the contents of the file
      //and sum it.
      fread(&byte2,1,1,file_contents);
      sum2 += (unsigned char)byte2;
    }

    // calculate hash
    hash = (hash + sum2 ) % 2000000000;

    fclose(file_contents);

    return hash;
}




/* USYD CODE CITATION ACKNOWLEDGEMENT
* I declare that the following lines of code have been copied from the
 * website titled: "Merge Sort for Doubly Linked List" with minor changes and it is not my own work.
 *
 * Original URL
 * https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
 * Last access April, 2020
 */

struct changes *split(struct changes *head);

void insert(struct changes **head, char* file_name,struct branch* help,char* type){
  // creates a changes struct. A changes struct tells a commit or anything
  //that detects uncommitted changes the type of change and the file name of the
  //change

    struct changes * temp = malloc(sizeof(struct changes));
    temp->file_name = malloc(sizeof(char)*(strlen(file_name)+1));
    memcpy(temp->file_name,file_name,sizeof(char)*(strlen(file_name)+1));
    temp->next  = NULL;
    temp->prev = NULL ;
    temp->type = malloc(sizeof(char)*(strlen(type)+1));
    memcpy(temp->type,type,sizeof(char)*(strlen(type)+1));

    if ((*head) == NULL ){
      (*head) = temp;
    }
    else {
        temp->next = *head;
        (*head)->prev = temp;
        (*head) = temp;
    }
}

struct changes *merge(struct changes *file1, struct changes *file2)
{
    if (file1 == NULL){
        return file2;
    }
    if (file2 == NULL){
      return file1;
    }

    int flag = 0 ;
    for(int i = 0 ; i < strlen(file1->file_name); i++){
      if(tolower((int)(file1->file_name[i])) < tolower((int)(file2->file_name[i]))) {
        flag = 1;
        break;
      }
      else if(tolower((int)(file1->file_name[i])) > tolower((int)(file2->file_name[i]))) {
        flag = 0 ;
        break;
      }
    }
    if (flag == 1) {
        file1->next = merge(file1->next,file2);
        file1->prev = NULL;
        file1->next->prev = file1;

        return file1;
    }
    else {
        file2->next = merge(file1,file2->next);
        file2->prev = NULL;
        file2->next->prev = file2;

        return file2;
    }
}

struct changes *mergeSort(struct changes *head)
{
    if (head==NULL || head->next == NULL){
        return head;
    }

    struct changes *half = split(head);
    head = mergeSort(head);
    half = mergeSort(half);
    return merge(head,half);
}


struct changes *split(struct changes *head)
{
    struct changes *fast = head;
    struct changes *slow = head;

    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct changes *temp = slow->next;
    slow->next = NULL;
    return temp;
}

/* end of copied code */




struct changes* makeChanges(void * helper){
  //makeChanges is a function called whenever you want to discover
  //what uncommitted changes the branch currently has.

  struct branches* help = (struct branches*)helper;
  if(help->branches[help->current]->n_commits == 0 && (help->current == 0)){
    // if it is considering the master branch and the first ever commit

      struct changes * head  = NULL;
      struct file* temp = help->branches[help->current]->tracked_files;

      for(int i= 0 ; i<help->branches[help->current]->n_tracked ; i ++){

        if( access( temp->file_name, F_OK ) != -1 ) {

            // if we can still access the file then intitalise it
            // as a uncommitted change of type add

            if(temp->tracked == 1){
              insert(&head,temp->file_name,help->branches[help->current],"add");

            }
        }
        else{

          // if we cannot access it and it is the first commit it has been
          // manually removed.

          // NOTE : temp->tracked = 1 means it is being tracked
          // NOTE : temp-> tracked = 0  means it is not being tracked


          if(help->branches[help->current]->commitCalled==1){
          temp->tracked = 0 ;
          }
        }

        temp = temp->next;

      }

      head = mergeSort(head);
      return head;

  }
  else{
    // else if it is not the first commit, consider if the change is either adding
    // deletion or modification


    // if any additions have been identified , add to uncommitted changes

    struct changes * head  = NULL;
    struct file* temp = help->branches[help->current]->tracked_files;
    if(help->branches[help->current]->n_add > 0){

      if(flag!= -1){
          struct file* t = help->branches[help->current]->tracked_files;

          for(int i = 0 ; i<help->branches[help->current]->n_tracked;i++){
            if(i == flag){

              insert(&head,t->file_name,help->branches[help->current],"add");
            }
            t = t->next;
          }

      }


        if(flag!=-1){
          for(int i= 0 ; i<help->branches[help->current]->n_add -1; i ++){

              if (temp->tracked == 1){
                insert(&head,temp->file_name,help->branches[help->current],"add");
                temp = temp->next;
              }
          }
        }
        else{
          for(int i= 0 ; i<help->branches[help->current]->n_add ; i ++){

              if (temp->tracked == 1){
                insert(&head,temp->file_name,help->branches[help->current],"add");
                temp = temp->next;
              }
          }
        }



        flag = -1;

      }



      // if any removes have been identified , add to uncommitted changes

       if(help->branches[help->current]->n_rmv > 0 ){

         for(int i = 0 ; i<help->branches[help->current]->n_rmv;i++){
           insert(&head,help->branches[help->current]->removed[i],help->branches[help->current],"del");
         }

      }


      // check for manually removed files and add to uncommitted changes.

      struct file* temp1 = help->branches[help->current]->tracked_files;

      for(int i= 0 ; i<help->branches[help->current]->n_tracked ; i ++){

        if(temp1->tracked == 1){


          if( access( temp1->file_name, F_OK ) != -1 ) {

          }
          else{
            if(help->branches[help->current]->commitCalled==1){
              // commit called is used so that we can actually make it not tracked
              insert(&head,temp1->file_name,help->branches[help->current],"del");
              temp1->tracked = 0 ;
            }
            else{
              // if commit called is not used, then we dont actually want to
              //make the file not tracked but merely identify it,
              // this is due to the fact that i want to be able to identify
              // this change if a commit is called

              insert(&head,temp1->file_name,help->branches[help->current],"del");

            }

          }

        }
        temp1 = temp1->next;
      }


      // detect any modifications and add to uncommited changes

      struct file* temp2 = help->branches[help->current]->tracked_files;

      int checker = 0 ;

      for(int i= 0 ; i<help->branches[help->current]->n_tracked ; i ++){

          if(temp2 -> tracked == 1){

            if(temp2->hash != hash_file(helper,temp2->file_name)){

              // compare the stored hash of the file to the
              // hash calculated if there is a difference
              // a modification has occurred.


              if(checker>=help->branches[help->current]->n_add){

                // this checker is just checking whether the modification
                // identified is simply from a file that was added in this
                //commit as well. Eg you cannot have a file being both
                // added and modified.

                if(help->branches[help->current]->commitCalled==1){
                    temp2->oldHash = temp2->hash;
                    temp2->hash  =  hash_file(helper,temp2->file_name);
                    insert(&head,temp2->file_name,help->branches[help->current],"mod");
                }
                else{
                  insert(&head,temp2->file_name,help->branches[help->current],"mod");
                }
              }
              else{
                    if(help->branches[help->current]->commitCalled==1){
                      temp2->oldHash = temp2->hash;
                      temp2->hash  =  hash_file(helper,temp2->file_name);
                    }
              }


            }

          }

          checker++;

            temp2 = temp2->next;
      }



      head = mergeSort(head);

      return head;
  }
  return NULL;
  }




char *svc_commit(void *helper, char *message) {

  struct branches* help = (struct branches*)helper;




  if(message == NULL){
    return NULL;
  }



  int id = 0 ;

  // hash the message first

  unsigned char byte1;
  int size = strlen(message);

  int sum = 0;
  for(int i = 0 ; i < size ;i++){
    byte1 = (unsigned char)message[i];
    sum +=byte1;

  }

    id = (id + sum) % 1000;



  struct commit* commit = malloc(sizeof(struct commit));

  // create a commit struct and allocate memory for it
  // this will be the memory where we will allocate all
  // attributes of this particular commit to it.

  help->branches[help->current]->commitCalled = 1;

  // make sure the make changes function knows that this is
  //from a commit call and apply appropriate Changes
  // eg removing from tracked files eg explained above
  // in makechanges function

  commit->changes = makeChanges(helper);

  help->branches[help->current]->commitCalled = 0;

  if(commit->changes==NULL){
    // if there are no uncommitted changes then return null
    free(commit);
    return NULL;
  }

    struct changes* temp = commit->changes;


    while(temp!=NULL){
      // iterate through each type of changes
      // and calculate appropriate hash

      if(strcmp(temp->type,"add")==0  ){

        id = id + 376591;
      }
      else if(strcmp(temp->type,"del")==0 ){

        id = id + 85973;
      }
      else if(strcmp(temp->type,"mod")==0 ){

        id = id + 9573681;
      }

        unsigned char byte1;
        int size = strlen(temp->file_name);

        for(int i = 0 ; i < size ;i++){
          byte1 = (unsigned char)temp->file_name[i];
          id = (id * (byte1 % 37)) % 15485863 + 1;

        }


      temp = temp->next;
    }



    char hex[7];

    sprintf(hex, "%06x", id);
    // convert to hexadecimal string

    if(help->branches[help->current]->n_rmv > 0){
      // free any memory of the removed files
          freeRemoved(help->branches[help->current]);
    }

    // apply appropriate values to attributes of the commits

    commit->resetPrev = NULL;
    commit->resetNext = NULL;
    commit->mergePrev = NULL;

    commit->commit_id = malloc(sizeof(char)*(strlen(hex) +1));
    memcpy(commit->commit_id , &hex[0] , sizeof(char)*(strlen(hex)+1));

    commit->message =  malloc(sizeof(char)*(strlen(message) +1));
    memcpy(commit->message , message , sizeof(char)*(strlen(message)+1));



    if(help->branches[help->current]->n_commits==0){

      // if the number of commits is  0 for the current branch then
      // set this commit as the first of the branch.

      help->branches[help->current]->commits = commit;
      help->branches[help->current]->n_commits++;

      if(help->current == 0 ){
        // if this is the master branch this commit has no previous commit
        help->branches[help->current]->commits->next = help->branches[help->current]->commits->prev = NULL;
      }
      else{
        // if not the master branch this commit has a previous commit in  another branch.
        help->branches[help->current]->commits->next = NULL;
        help->branches[help->current]->commits->prev = help->branches[help->current]->last_commit;
      }



      struct file* p = help->branches[help->current]->tracked_files;
      int score = 0 ;
      for(int i = 0 ; i <help->branches[help->current]->n_tracked; i++){
        if(p->tracked == 0){
          // check how many files have been manually removed.
          // these files will not be added to this commits tracked files
          score++;
        }
          p =p->next;
      }

      //decremented the n_tracked to account for the manually removed
      for(int i = 0 ; i<score; i++){
        help->branches[help->current]->n_tracked--;
      }

      // storing the current tracked files of the branch to this particular commit

      help->branches[help->current]->commits->tracked = malloc(sizeof(struct file*)*help->branches[help->current]->n_tracked);

      //since decremented the exact amount of memory needed for the tracked files is calculated

      for(int i = 0 ; i<score; i++){
        help->branches[help->current]->n_tracked++;
      }

      // the number of tracked is incremented back up to normal

      struct file* temp = help->branches[help->current]->tracked_files;


      help->branches[help->current]->commits->n_tracked =0;
      for(int i = 0 ; i <help->branches[help->current]->n_tracked; i++){
        if(temp->tracked == 1){
          help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked] =
          malloc(sizeof(struct file));
          memcpy(help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]
            ,temp, sizeof(struct file));

          help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]->content =
           malloc(sizeof(struct contents));
           help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]->content->hash =
           temp->hash;
           help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]->content->saved =
           saveContents(temp->file_name);
           help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]->content->orig =
           malloc(sizeof(char)*(strlen(temp->file_name)+1));
           memcpy(help->branches[help->current]->commits->tracked[help->branches[help->current]->commits->n_tracked]->content->orig,
          temp->file_name,sizeof(char)*(strlen(temp->file_name)+1));

           help->branches[help->current]->commits->n_tracked++;
        }

          temp = temp->next;




      }

      help->branches[help->current]->last_commit = commit;
      help->branches[help->current]->n_add = 0;
      help->branches[help->current]->n_rmv = 0 ;

      return help->branches[help->current]->commits->commit_id;

    }
    else{

      //similar logic if there is a commit present in the branch
      // the only difference is to add this commit to the last added commit.
      // eg the head.

      struct commit* temp = help->branches[help->current]->commits;

      while(1){
        if(temp->next == NULL){
          temp->next = commit;

          struct file* b = help->branches[help->current]->tracked_files;
          int man = 0 ;
          for(int i = 0 ; i <help->branches[help->current]->n_tracked; i++){
            if(b->tracked == 0){
              // check how many files have been manually removed.
              // these files will not be added to this commits tracked files
              man++;
            }
              b =b->next;
          }


          for(int i = 0 ; i<man; i++){
            help->branches[help->current]->n_tracked--;
          }

          //decremented the n_tracked to account for the manually removed

          temp->next->n_tracked = 0 ;
          temp->next->tracked = malloc(sizeof(struct file*)*help->branches[help->current]->n_tracked);

          //since decremented the exact amount of memory needed for the tracked files is calculated

          for(int i = 0 ; i<man; i++){
            help->branches[help->current]->n_tracked++;
          }

          // the number of tracked is incremented back up to normal

          struct file* a = help->branches[help->current]->tracked_files;

          for(int i = 0 ; i <help->branches[help->current]->n_tracked; i++){

            //store the tracked files into the commit

            if(a->tracked==1){

              temp->next->tracked[temp->next->n_tracked] = malloc(sizeof(struct file));
              memcpy(  temp->next->tracked[temp->next->n_tracked] ,a, sizeof(struct file));
              temp->next->tracked[temp->next->n_tracked]->content = malloc(sizeof(struct contents));
              temp->next->tracked[temp->next->n_tracked]->content->hash = a->hash;
              temp->next->tracked[temp->next->n_tracked]->content->saved = saveContents(a->file_name);
              temp->next->tracked[temp->next->n_tracked]->content->orig = malloc(sizeof(char)*(strlen(a->file_name)+1));
              memcpy(temp->next->tracked[temp->next->n_tracked]->content->orig,a->file_name,sizeof(char)*(strlen(a->file_name)+1));


              temp->next->n_tracked++;
            }
            else{

            }
                      a = a->next;
          }

          help->branches[help->current]->n_commits++;

          temp->next->prev =temp;
          temp->next->next = NULL;
          help->branches[help->current]->last_commit = commit;
          help->branches[help->current]->n_add = 0;
          help->branches[help->current]->n_rmv = 0 ;

          return temp->next->commit_id;

        }
        else{
          temp = temp->next;
        }

      }

    }

}

void *get_commit(void *helper, char *commit_id) {
    // TODO: Implement
struct branches* help = (struct branches*)helper;

    if(commit_id == NULL){
      return NULL;
    }
    else{
      for(int j = 0 ; j< help->n_branch ; j++){
        // find the commit in any branch
        struct commit* temp = help->branches[j]->commits;
        for(int i = 0 ; i<help->branches[j]->n_commits;i++){
          // search for the commit in this particular branch
          if(strcmp(temp->commit_id,commit_id)==0){
            return temp->commit_id;
          }

          temp = temp->next;

        }

      }

      return NULL;
    }
}

char **get_prev_commits(void *helper, void *commit, int *n_prev) {
  struct branches* help = (struct branches*)helper;

  //applying appropriate checks before attempting function

    if(n_prev == NULL){
      return NULL;
    }
    else if(commit == NULL){
      *n_prev = 0;
      return NULL;
    }
    else if(strcmp(commit,help->branches[0]->commits->commit_id)==0){

        *n_prev = 0;
        return NULL;
    }
    else{

      char** result;
      int count = 0 ;
      int found = 0 ;


      for(int i = 0 ; i < help->n_branch ; i++){
        // find the commit in every branch
      struct commit* temp  = help->branches[i]->commits;
      // find the commit in this particular branch

        while(1){
          if(temp == NULL){
            found = 0 ;
            break;
          }
          else if(strcmp(temp->commit_id,commit) == 0 ){
            found = 1;
            struct commit* prev  = temp->prev;
            result = malloc(sizeof(char*));
            result[count] = prev->commit_id;
            count++;

            break;
          }
          temp = temp->next;
        }

        if(found == 1){

          // if it has been found return prev commits

            if(temp->mergePrev !=NULL){
              result = realloc(  result, sizeof(char*)*2);
              result[count] =  temp->mergePrev->commit_id;
              count++;
            }

            *n_prev = count;
            return result;
        }

      }

    }

    return NULL;
}


void printer(struct commit* file){

}

void print_commit(void *helper, char *commit_id) {
struct branches* help = (struct branches*)helper;

// appropriate checks before printing the commits

    if(commit_id == NULL){
      printf("Invalid commit id\n");
    }
    else{
      int checker = 0;
      for(int j = 0 ; j < help->n_branch ; j++){

        // check every branch for the commits

      struct commit * temp = help->branches[j]->commits;
      for(int i = 0 ; i< help->branches[j]->n_commits;i++){

        // check every commit in this branch

        if(temp->resetNext != NULL){
          // check the commits that have been deallocated due to reset
          struct commit * reset = temp->resetNext;

          while(reset!=NULL){
            if(strcmp(reset->commit_id,commit_id)==0){

              // a commit which has been deallocated due to reset has been
              // called to print

              checker = 1;
              printf("%s [%s]: %s\n",reset->commit_id,help->branches[j]->name,reset->message );
              struct changes * a = reset->changes;
              while(1){

                // for each change recorded in this commit print the appropriate
                // data

                if(a->next == NULL){
                  if(strcmp(a->type,"add")==0){
                      printf("    + %s\n", a->file_name );
                  }
                  else if(strcmp(a->type,"del")==0){
                      printf("    - %s\n", a->file_name);
                  }
                  else if(strcmp(a->type,"mod")==0){
                    struct file * p = help->branches[help->current]->tracked_files;
                    for(int i  = 0 ;  i < help->branches[help->current]->n_tracked ; i++){


                      if(strcmp(p->file_name,a->file_name)==0){
                          printf("    / %s [%10d -> %10d]\n", a->file_name, p->oldHash , p->hash);
                      }
                      p = p ->next;

                    }
                  }

                  break;
                }
                if(strcmp(a->type,"add")==0){
                    printf("    + %s\n", a->file_name );
                }
                else if(strcmp(a->type,"del")==0){
                    printf("    - %s\n", a->file_name);
                }
                else if(strcmp(a->type,"mod")==0){
                  struct file * p = help->branches[help->current]->tracked_files;
                  for(int i  = 0 ;  i < help->branches[help->current]->n_tracked ; i++){


                    if(strcmp(p->file_name,a->file_name)==0){
                        printf("    / %s [%10d -> %10d]\n", a->file_name, p->oldHash , p->hash);
                    }
                    p = p ->next;

                  }

                }

                a = a->next;
              }

              printf("\n" );
              printf("    Tracked files (%d):\n", reset->n_tracked );



              for(int i  = 0 ;  i < reset->n_tracked ; i++){
                struct file * t = reset->tracked[i];
                  printf("    [%10d] %s\n", t->content->hash, t->content->orig);
              }



              break;
            }
            reset = reset->next;
          }
        }


        // if it is not from  the commits that have been deallocated due to
        // reset then check the commits in this branch

        if(strcmp(temp->commit_id,commit_id)==0){

            // a commit from within this branch has been asked to print
            // print appropriate data


          checker = 1;
          printf("%s [%s]: %s\n",temp->commit_id,help->branches[j]->name,temp->message );
          struct changes * a = temp->changes;
          while(1){
            if(a->next == NULL){
              if(strcmp(a->type,"add")==0){
                  printf("    + %s\n", a->file_name );
              }
              else if(strcmp(a->type,"del")==0){
                  printf("    - %s\n", a->file_name);
              }
              else if(strcmp(a->type,"mod")==0){
                struct file * p = help->branches[help->current]->tracked_files;
                for(int i  = 0 ;  i < help->branches[help->current]->n_tracked ; i++){

                  if(strcmp(p->file_name,a->file_name)==0){
                      printf("    / %s [%10d -> %10d]\n", a->file_name, p->oldHash , p->hash);
                  }
                  p = p ->next;

                }
              }

              break;
            }
            if(strcmp(a->type,"add")==0){
                printf("    + %s\n", a->file_name );
            }
            else if(strcmp(a->type,"del")==0){
                printf("    - %s\n", a->file_name);
            }
            else if(strcmp(a->type,"mod")==0){
              struct file * p = help->branches[help->current]->tracked_files;
              for(int i  = 0 ;  i < help->branches[help->current]->n_tracked ; i++){
                if(strcmp(p->file_name,a->file_name)==0){
                    printf("    / %s [%10d -> %10d]\n", a->file_name, p->oldHash , p->hash);
                }
                p = p ->next;
              }
            }

            a = a->next;
          }

          printf("\n" );
          printf("    Tracked files (%d):\n", temp->n_tracked );

          for(int i  = 0 ;  i < temp->n_tracked ; i++){
            struct file * t = temp->tracked[i];
              printf("    [%10d] %s\n", t->content->hash, t->content->orig);
          }
          break;
        }
        temp = temp->next;
      }
    }
      if(checker== 0){
          printf("Invalid commit id\n");
      }
    }

}



int svc_branch(void *helper, char *branch_name) {


  struct branches* help = (struct branches*)helper;
    // TODO: Implement

// apply checking before a successful branch occurs

    if(branch_name == NULL){
      return -1;
    }

    for(int i = 0 ; i<strlen(branch_name);i++){
      if(isalpha(branch_name[i]) != 0 ||  isdigit(branch_name[i])!=0
      || branch_name[i] == '_'|| branch_name[i] == '/'|| branch_name[i] == '-' ){

      }
      else{
        return -1;
      }
    }

    for(int i = 0 ; i<help->n_branch; i++){
      if(strcmp(help->branches[i]->name,branch_name) == 0 ){
        return -2;
      }
    }


//check for uncommited changes
  struct commit* commit = malloc(sizeof(struct commit));

  commit->changes = makeChanges(helper);

  if(commit->changes!=NULL){
    // uncommitted changes exist
      freeChanges(commit->changes);
        free(commit);

        return -3;
  }
  else{
        free(commit);
  }

  help->n_branch ++;
  help->branches = realloc(help->branches ,sizeof(struct branch*)*help->n_branch);

  // reallocate memory for the branches as a new branch is being made.

  help->branches[help->n_branch-1] = malloc(sizeof(struct branch ));
  memcpy(help->branches[help->n_branch-1],help->branches[help->current],sizeof(struct branch ));

  help->branches[help->n_branch-1]->name = malloc(sizeof(char)*(strlen(branch_name)+1));
  memcpy(   help->branches[help->n_branch-1]->name,branch_name,sizeof(char)*(strlen(branch_name)+1));

  // copy the name into the new branch


  struct file* head = NULL;
  struct file* end  = NULL;
  struct file* temp1 = help->branches[help->current]->tracked_files;

  //copy all tracked files in the current branch into the new branch
    while(temp1!=NULL){
      if(head == NULL){
        head = malloc(sizeof(struct file));
        memcpy(head,temp1,sizeof(struct file));
        head->file_name = malloc(sizeof(char)*(strlen(temp1->file_name) +1));
        memcpy(head->file_name , temp1->file_name , sizeof(char)*(strlen(temp1->file_name) +1));
        head->next = NULL;
        end = head;
      }

      else{
        end->next = malloc(sizeof(struct file));
        end = end->next;
        memcpy(end,temp1,sizeof(struct file));
        end->file_name = malloc(sizeof(char)*(strlen(temp1->file_name) +1));
        memcpy(end->file_name , temp1->file_name , sizeof(char)*(strlen(temp1->file_name) +1));
        end->next = NULL;
      }
      temp1 = temp1->next;
    }


  help->branches[help->n_branch-1]->tracked_files = head;
  help->branches[help->n_branch-1]->last_commit = help->branches[help->current]->last_commit;
  help->branches[help->n_branch-1]->n_commits = 0 ;



    return 0;
}

int svc_checkout(void *helper, char *branch_name) {

    // TODO: Implement
    struct branches* help = (struct branches*)helper;

    //apply appropriate checking before checking out the branch

    if(branch_name ==NULL){
      return -1;
    }

    int check = -3;

    for(int i  = 0 ; i < help->n_branch ; i ++){
      if(strcmp(help->branches[i]->name,branch_name)==0){
        check = i;
      }
    }

    if(check == -3 ){
      return -1;
    }

    // check for uncommitted changes

    struct commit* commit = malloc(sizeof(struct commit));

    commit->changes = makeChanges(helper);

    if(commit->changes!=NULL ){

        freeChanges(commit->changes);
        free(commit);
        return -2;
    }
    else{
          free(commit);
    }


    help->current = check;


    // restore contents of any tracked files of the branch being checked
    // out to the contents it held after its last commit.


    for(int i = 0 ; i< help->branches[help->current]->last_commit->n_tracked ; i++){
      struct contents * temp = help->branches[help->current]->last_commit->tracked[i]->content;
      restoreContents(temp->saved , temp->orig);
    }


    return 0;
}

char **list_branches(void *helper, int *n_branches) {
    // TODO: Implement
struct branches* help = (struct branches*)helper;


    if(n_branches == NULL){
      return NULL;
    }
    else{
      *n_branches = help->n_branch;

      char** result = malloc(sizeof(char*)*(help->n_branch));

      for(int i = 0 ; i < help->n_branch ; i ++){
        printf("%s\n",help->branches[i]->name);
        result[i] = help->branches[i]->name;
      }
      return result;
    }



    return NULL;
}

int svc_add(void *helper, char *file_name) {

  struct branches* help = (struct branches*)helper;

    if(file_name == NULL){

      return -1;
    }
   else if(help->branches[help->current]->n_tracked>0){
      struct file* temp = help->branches[help->current]->tracked_files;
      for(int i = 0 ; i< help->branches[help->current]->n_tracked ; i++){

        // checking for any files which have been addded which were previously
        // manually removed.

        if(strcmp(temp->file_name,file_name) == 0 ){

          if(temp->tracked == 0){

            temp->tracked = 1;
            temp->hash = hash_file(helper,temp->file_name);
            flag = i ;
            help->branches[help->current]->n_add++;

            return temp->hash;
          }

          return -2;
        }

        temp = temp->next;

      }
    }



      int result  = hash_file(help->branches[help->current],file_name);

      // calculate hash of the file

      if(result == -2){

        return -3;
      }

      else{

        if(help->branches[help->current]->n_tracked == 0){
          // if this is the first file being tracked.
          struct file* new = malloc(sizeof(struct file));
          new->file_name =  malloc(sizeof(char)*(strlen(file_name) +1));
          memcpy(new->file_name , file_name , sizeof(char)*(strlen(file_name)+1));
          help->branches[help->current]->n_tracked++;
          new->hash = result;
          new->next = NULL;
          new->tracked = 1;
          help->branches[help->current]->tracked_files = new;
          help->branches[help->current]->n_add++;

        }
        else{

          // any additional file will be added to the front of the tracked files list.
          // tracked files under branch is a singly linked list adding new files to the
          //start of the list.

          struct file* temp = help->branches[help->current]->tracked_files;

          struct file* new = malloc(sizeof(struct file));

          help->branches[help->current]->n_add++;
          new->file_name =  malloc(sizeof(char)*(strlen(file_name) +1));
          memcpy(new->file_name , file_name , sizeof(char)*(strlen(file_name)+1));
          help->branches[help->current]->n_tracked++;
          new->tracked = 1;
          new->hash = result;
          new->next = temp;
          help->branches[help->current]->tracked_files = new;

        }

        return result;

      }
}

int svc_rm(void *helper, char *file_name) {


  struct branches* help = (struct branches*)helper;

  // appropriate checks before removal

  if(file_name == NULL){
    return -1;
  }


  int special = 0 ;

  // special refers to if the file has been added and removed before a commit has occured

  if(help->branches[help->current]->n_add>0){
    struct file* repeat = help->branches[help->current]->tracked_files;

    for(int i = 0 ; i <help->branches[help->current]->n_add;i++ ){
      if(strcmp(repeat->file_name,file_name) == 0){
        special = 1;
      }

      repeat = repeat->next;
    }
  }




   if(help->branches[help->current]->n_tracked>0){
     // check if there are any tracked files to remove.

      struct file* temp = help->branches[help->current]->tracked_files;

      if(strcmp(help->branches[help->current]->tracked_files->file_name,file_name) == 0 ){
        // found the file to remove. this file is the first tracked file.

        struct file* next  = temp->next;
        help->branches[help->current]->n_tracked -- ;
        help->branches[help->current]->tracked_files = next;
        int result = temp->hash;
        free(temp->file_name);
        free(temp);

        //free memory associated with the file

        help->branches[help->current]->n_rmv++;

        if(special == 1){
          help->branches[help->current]->n_rmv--;
          help->branches[help->current]->n_add -- ;
          return result;
        }

        //save the file name that was removed into a removed array which will later
        //be accessed by commit to detect the appropriate changes

        if(help->branches[help->current]->n_rmv == 1){
          help->branches[help->current]->removed = malloc(sizeof(char*));

          help->branches[help->current]->removed[0] =
          malloc(sizeof(char)*(strlen(file_name) +1));
          memcpy(  help->branches[help->current]->removed[0], file_name ,
            sizeof(char)*(strlen(file_name)+1));
        }
        else{
          help->branches[help->current]->removed = realloc(help->branches[help->current]->removed,
            sizeof(char*)*help->branches[help->current]->n_rmv);
          help->branches[help->current]->removed[help->branches[help->current]->n_rmv - 1] =
          malloc(sizeof(char)*(strlen(file_name) +1));
          memcpy(  help->branches[help->current]->removed[help->branches[help->current]->n_rmv - 1],
             file_name , sizeof(char)*(strlen(file_name)+1));

        }



        return result;
      }

      // if reaches here, the file is not the first tracked file and thus
      // we must find it by iterating through the tracked file list.

      while(1){
          if(temp->next == NULL){

            return -2;
          }
          else if(strcmp(temp->next->file_name,file_name) == 0 ){
                struct file* next  = temp->next->next;
                help->branches[help->current]->n_tracked -- ;
                int result = temp->next->hash;
                free(temp->next->file_name);
                free(temp->next);
                temp->next = next;
                help->branches[help->current]->n_rmv++;

                if(special == 1){
                  help->branches[help->current]->n_rmv--;
                  help->branches[help->current]->n_add -- ;
                  return result;
                }

                // same logic as above.

                if(help->branches[help->current]->n_rmv == 1){
                  help->branches[help->current]->removed =
                  malloc(sizeof(char*));

                  help->branches[help->current]->removed[0] =
                   malloc(sizeof(char)*(strlen(file_name) +1));
                  memcpy(  help->branches[help->current]->removed[0],
                    file_name , sizeof(char)*(strlen(file_name)+1));

                }
                else{
                  help->branches[help->current]->removed =
                  realloc(help->branches[help->current]->removed,
                    sizeof(char*)*help->branches[help->current]->n_rmv);
                  help->branches[help->current]->removed[help->branches[help->current]->n_rmv - 1]
                  =  malloc(sizeof(char)*(strlen(file_name) +1));
                  memcpy(  help->branches[help->current]->removed[help->branches[help->current]->n_rmv - 1],
                  file_name , sizeof(char)*(strlen(file_name)+1));
                }
                return result;

          }
          else{
            temp = temp->next;
          }
      }

    }
    else {

      return -2;
    }
return 0 ;
}

int svc_reset(void *helper, char *commit_id) {

    struct branches* help = (struct branches*)helper;

    if(commit_id == NULL){
      return -1;
    }
    int check = -5;


    for(int j = 0 ; j< help->n_branch ; j++){
      //check every branch
    struct commit * temp  = help->branches[j]->commits;

    for(int i = 0 ; i < help->branches[j]->n_commits;i++){
      // check every commit within the branch
      if(strcmp(temp->commit_id,commit_id)==0){
        check = i;
        // this is the index in which the commit was found
        if(strcmp(temp->commit_id,help->branches[j]->last_commit->commit_id)==0){
          // if this is the last commit of the branch
          temp->next = NULL;
          help->branches[j]->last_commit = temp;

          help->branches[help->current]->last_commit = temp;

          for(int i = 0 ; i<temp->n_tracked ;i++){
            restoreContents(temp->tracked[i]->content->saved,temp->tracked[i]->content->orig);
            // restore contents of any tracked files of this commit
          }

          for(int i = 0 ; i < help->branches[j]->last_commit->n_tracked ; i ++){
            struct file* n = help->branches[j]->last_commit->tracked[i];
            struct file* u = help->branches[help->current]->tracked_files;
            for(int i = 0 ; i < help->branches[help->current]->n_tracked;i++){

              if(strcmp(n->file_name,u->file_name)==0){
                u->hash = n->content->hash;
                //update the hash values for any of these.
              }
                u = u ->next;
            }

          }

          if(j != help->current){
              // if the reset was made to another branch

              struct commit * current  = help->branches[help->current]->commits;
              if(help->branches[j]->last_commit->resetNext == NULL){
                  help->branches[j]->last_commit->resetNext = current;
              }
              else{

                struct commit * a = current;
                struct commit * b ;
                  while(a!=NULL){
                    b = a->next;
                    for(int i = 0 ; i< a->n_tracked;i++){
                      free(a->tracked[i]->content->orig);
                      free(a->tracked[i]->content->saved);
                      free(a->tracked[i]->content);
                      free(a->tracked[i]);
                    }

                    free(a->tracked);
                    free(a->commit_id);
                    free(a->message);
                    freeChanges(a->changes);
                    free(a);

                    a = b;
                  }
              }

            help->branches[help->current]->n_commits = 0 ;
          }


          if(help->branches[help->current]->n_add >0){
            struct file* resetRemove = help->branches[help->current]->tracked_files;
            for(int a = 0 ;a<help->branches[help->current]->n_add;a++ ){
              svc_rm(helper,resetRemove->file_name);
              resetRemove = resetRemove->next;
                help->branches[help->current]->n_tracked --;
            }
          }


          return 0 ;
        }

        // if it reaches here it means the commit is not the last
        // commit of its branch

        while(1){
          if(temp->next==NULL){
            break;
          }
          temp = temp->next;
        }

        // iterate through to the last commit of the branch.

        struct commit * prev = temp->prev;


        help->branches[j]->n_commits--;

        while(1){
          if(strcmp(prev->commit_id,commit_id)==0){
            struct commit* k = prev->next;
            prev->next = NULL;

            if(prev->resetNext == NULL){
              // add the commits to the right of the resetted commits
              //reset next so it still has access to these commits.
              prev->resetNext = k;
            }
            else{
              struct commit * a = k;
              struct commit * b ;
                while(a!=NULL){
                  b = a->next;
                  for(int i = 0 ; i< a->n_tracked;i++){
                    free(a->tracked[i]->content->orig);
                    free(a->tracked[i]->content->saved);
                    free(a->tracked[i]->content);
                    free(a->tracked[i]);
                  }

                  free(a->tracked);
                  free(a->commit_id);
                  free(a->message);
                  freeChanges(a->changes);
                  free(a);

                  a = b;
                }

            }



            help->branches[j]->last_commit = prev;
            help->branches[help->current]->last_commit = prev;

            for(int i = 0 ; i<prev->n_tracked ;i++){
              restoreContents(prev->tracked[i]->content->saved,prev->tracked[i]->content->orig);
              //restore contents of the tracked files
            }




            struct commit* m = prev;
            struct file * h = help->branches[help->current]->tracked_files;
            for(int i = 0 ; i < help->branches[help->current]->n_tracked ; i ++){
                int found = 0;
                for(int j = 0; j < m->n_tracked; j++){
                  if(strcmp(h->file_name,m->tracked[j]->content->orig)==0){
                    //found the tracked file in the stored tracked files of the
                    //commit to reset to
                    found = 1;
                  }
                }

                if(found ==0){
                  h->tracked = 0 ;
                  // if the tracked file of the branches current state is not
                  //existent in the commit when resetted then make it not
                  //tracked.
                }

                h = h -> next;
            }

          if(help->branches[help->current]->n_add >0){
          struct file* resetRemove = help->branches[help->current]->tracked_files;
          for(int a = 0 ;a<help->branches[help->current]->n_add;a++ ){
              struct file* remove = resetRemove->next;
            svc_rm(helper,resetRemove->file_name);
            resetRemove = remove;

          }
          }

            return 0;
          }

          prev = prev->prev;
          help->branches[j]->n_commits--;
        }
      }
      temp = temp->next;
    }
  }

    if(check==-5){
      return -2;
    }

    return 0;
}

char *svc_merge(void *helper, char *branch_name, struct resolution *resolutions, int n_resolutions) {


  struct branches* help = (struct branches*)helper;

//appropriate checking before merge.

    if(branch_name == NULL){
      printf("Invalid branch name\n" );
      return NULL;
    }

    int check = -5;
    for(int i = 0 ; i < help->n_branch ; i ++){
      if(strcmp(help->branches[i]->name,branch_name)==0){
        check = i ;
      }
    }

    if(check == -5){
      printf("Branch not found\n" );
      return NULL;
    }

    if(check  == help->current){

      printf("Cannot merge a branch with itself\n" );
      return NULL;
    }


    struct commit* commit = malloc(sizeof(struct commit));

    commit->changes = makeChanges(helper);
    // check for uncommitted changes.
    if(commit->changes!=NULL){

        freeChanges(commit->changes);
        free(commit);

        printf("Changes must be committed\n");
        return NULL;
    }
    else{
          free(commit);
    }


    for(int i = 0 ; i<help->branches[check]->last_commit->n_tracked; i++){
      //for every tracked file in the last commit of the branch to be Merged
      // if it exists within the current branch then a conflict occurs.
      struct file* temp  = help->branches[check]->last_commit->tracked[i];
      int found = 0;
        for(int j = 0 ; j < help->branches[help->current]->last_commit->n_tracked;j++){
          if(strcmp(temp->file_name,help->branches[help->current]->last_commit->tracked[j]->file_name)==0){
            found =1;

            // if found it is a conflicting file
          }
        }

      if(found == 0){
        // even if not found check if it exists within resolutions and apply
        // appropriate restoration of contents if required.
        int shouldDelete = 0;
        for(int k = 0 ; k< n_resolutions ; k++){
          if(strcmp(temp->file_name,resolutions[k].file_name) == 0){
            if(resolutions[k].resolved_file == NULL){
              shouldDelete = 1;
            }
            else{
              restoreContents(resolutions[k].resolved_file,resolutions[k].file_name);
            }

            break;
          }
        }



        if(shouldDelete == 0 ){
            // if there are files that dont exist in the current branch then simply add
            // them
            if(hash_file(helper,temp->file_name) == -2){
              restoreContents(temp->content->saved,temp->file_name);
            }

            help->branches[help->current]->mergeCalled = 5;
            svc_add(helper,temp->file_name);
            help->branches[help->current]->mergeCalled = 0;
        }
        else{
          // these files had a resolution path file that was null.
          temp->delete = -7;
        }



      }

      else if (found ==1){
        // if a conflicting file was found check resolutions
        // for appropriate restoration of contents.


        for(int k = 0 ; k< n_resolutions ; k++){
          if(strcmp(temp->file_name,resolutions[k].file_name) == 0){
            if(resolutions[k].resolved_file == NULL){
                temp->delete = -7;

            }
            else{

                restoreContents(resolutions[k].resolved_file,resolutions[k].file_name);
            }
          }
        }
      }


    }

      //check the opposite too. check if there are any files not in the branch to be
      // merged. and check the resolutions array if there are any resolutions.

      for(int i = 0 ; i<help->branches[help->current]->last_commit->n_tracked; i++){

            struct file* temp10  = help->branches[help->current]->last_commit->tracked[i];
            int p = 0;
              for(int j = 0 ; j < help->branches[check]->last_commit->n_tracked;j++){
                if(strcmp(temp10->file_name,help->branches[check]->last_commit->tracked[j]->file_name)==0){
                  p =1;
                }
              }

            if(p == 0){

              for(int k = 0 ; k< n_resolutions ; k++){
                if(strcmp(temp10->file_name,resolutions[k].file_name) == 0){
                  if(resolutions[k].resolved_file == NULL){
                    temp10->delete = -9;
                  }
                  else{
                      restoreContents(resolutions[k].resolved_file,resolutions[k].file_name);
                  }
                }
              }

            }
  }

    // delete the files that have a resolution file path that is null

      for(int i = 0 ; i<help->branches[check]->last_commit->n_tracked; i++){


        struct file* x  = help->branches[check]->last_commit->tracked[i];

        if(x->delete == -7){
          svc_rm(helper,x->file_name);
        }
      }

      // delete the files that have a resolution file path that is null


      for(int i = 0 ; i<help->branches[help->current]->last_commit->n_tracked; i++){


        struct file* x  = help->branches[help->current]->last_commit->tracked[i];

        if(x->delete == -9){
          svc_rm(helper,x->file_name);
        }

      }



    help->branches[help->current]->merged = 1;


    char *message = malloc(strlen("Merged branch ") + strlen(branch_name) + 1);
     strcpy(message, "Merged branch ");
     strcat(message, branch_name);

     // make the appropriate commit for the merge

    char* result = svc_commit(helper,message);

    help->branches[help->current]->last_commit->mergePrev = help->branches[check]->last_commit;

    printf("Merge successful\n" );

    free(message);

    return result;
}
