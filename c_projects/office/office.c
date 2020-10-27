#include "office.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "office.h"

/**
 * Places an employee within the office, if the supervisor field is NULL
 *  it is assumed the employee will be placed under the next employee that is
 * not superivising any other employee (top-down, left-to-right).
 *
 * If the supervisor is not NULL, it will be added to the supervisor's subordinates list
 *  of employees (make sure the supervisor exists in hierarchy).
 * if the office or employee are null, the function not do anything.
 */

 struct queue {
   struct employee* wait[50];
 };


 int addQueue(struct queue* queue, struct employee* emp,int counter){
   if(emp->n_subordinates == 0 ){
     return counter;
   }
   else{
     for(size_t i = 0 ; i<emp->n_subordinates ; i++){
       queue->wait[counter+i]= &emp->subordinates[i];
     }
     return counter + emp->n_subordinates;
   }
 }




 void setSupervisor(struct employee* emp){
   if(emp->n_subordinates == 0){
     return;
   }
   else{
     for(size_t i=0 ; i< emp->n_subordinates ; i++){
       emp->subordinates[i].supervisor = emp;
       setSupervisor(&emp->subordinates[i]);
     }
   }
 }


 void office_employee_place(struct office* off, struct employee* supervisor,
   struct employee* emp) {


     if(off == NULL || emp == NULL){
       return;
     }

     if(supervisor == NULL){



       if(off->department_head == NULL){

           off->department_head = malloc(sizeof(struct employee));
           off->department_head->name = malloc(sizeof(char)*(strlen(emp->name)+1));
           memcpy(off->department_head->name,emp->name,sizeof(char)*(strlen(emp->name)+1));
           memcpy(off->department_head->subordinates,emp->subordinates,sizeof(struct employee) * emp->n_subordinates) ;
           off->department_head->n_subordinates = 0;


       }
       else  {

         if(off->department_head->n_subordinates == 0){

         off->department_head->subordinates = malloc(sizeof(struct employee));
         off->department_head->subordinates[0].name = malloc(sizeof(char)*(strlen(emp->name)+1));
         memcpy(off->department_head->subordinates[0].name,emp->name,sizeof(char)*(strlen(emp->name)+1));
         off->department_head->n_subordinates = 1;
         off->department_head->subordinates[0].n_subordinates = 0;
         off->department_head->subordinates[0].supervisor = off->department_head;



         }

         else{

            int counter = 0 ;
            int cursor = 0;



              struct queue* que = malloc(sizeof(struct queue));

              que->wait[cursor] = off->department_head;

              counter++;
              cursor++;
              counter  = addQueue(que,off->department_head, counter);




              while(1){

                 if(que->wait[cursor]->n_subordinates > 0 ){


                   counter  = addQueue(que,que->wait[cursor],counter);

                   cursor++;
                 }
                 else{

                   que->wait[cursor]->n_subordinates +=1;



                   que->wait[cursor]->subordinates = malloc(sizeof(struct employee)*que->wait[cursor]->n_subordinates );
                   que->wait[cursor]->subordinates[0].name = malloc(sizeof(char)*(strlen(emp->name)+1));
                   memcpy( que->wait[cursor]->subordinates[0].name , emp->name,sizeof(char)*(strlen(emp->name)+1));
                   que->wait[cursor]->subordinates[0].supervisor = que->wait[cursor];
                     que->wait[cursor]->subordinates[0].n_subordinates = 0;






                   free(que);


                       break;
                 }
             }
             // off->department_head->subordinates[0].n_subordinates += 1;
             // off->department_head->subordinates[0].subordinates = malloc(sizeof(struct employee)*off->department_head->subordinates[0].n_subordinates);
             // off->department_head->subordinates[0].subordinates[0].name = malloc(sizeof(char)*(strlen(emp->name)+1));
             // memcpy(  off->department_head->subordinates[0].subordinates[0].name, emp->name,sizeof(char)*(strlen(emp->name)+1));

         }
     }
 }

 else {

     int counter = 0 ;
     int cursor = 0;

     struct queue* que = malloc(sizeof(struct queue));

     que->wait[cursor] = off->department_head;
     counter++;
     cursor++;
     counter  = addQueue(que,off->department_head, counter);



     while(1){
       if(memcmp(off->department_head,supervisor,sizeof(struct employee))==0){

         off->department_head->n_subordinates +=1;

         if(off->department_head->n_subordinates ==1){
             off->department_head->subordinates = malloc(sizeof(struct employee));
         }
         else{
                   off->department_head->subordinates = realloc( off->department_head->subordinates ,sizeof(struct employee)*off->department_head->n_subordinates );
         }



         off->department_head->subordinates[off->department_head->n_subordinates-1].name = malloc(sizeof(char)*(strlen(emp->name)+1));
         memcpy( off->department_head->subordinates[off->department_head->n_subordinates-1].name , emp->name,sizeof(char)*(strlen(emp->name)+1));
         off->department_head->subordinates[off->department_head->n_subordinates-1].supervisor = off->department_head;
         off->department_head->subordinates[off->department_head->n_subordinates-1].n_subordinates = 0;
         setSupervisor(off->department_head);
           free(que);
         break;
       }

      else if(memcmp(que->wait[cursor],supervisor,sizeof(struct employee)) == 0){

        que->wait[cursor]->n_subordinates +=1;

        if(que->wait[cursor]->n_subordinates == 1){
          que->wait[cursor]->subordinates = malloc(sizeof(struct employee));
        }
        else{
          que->wait[cursor]->subordinates = realloc( que->wait[cursor]->subordinates ,sizeof(struct employee)*que->wait[cursor]->n_subordinates );
        }

        que->wait[cursor]->subordinates[que->wait[cursor]->n_subordinates-1].name = malloc(sizeof(char)*(strlen(emp->name)+1));
        memcpy( que->wait[cursor]->subordinates[que->wait[cursor]->n_subordinates-1].name , emp->name,sizeof(char)*(strlen(emp->name)+1));
        que->wait[cursor]->subordinates[que->wait[cursor]->n_subordinates-1].supervisor = que->wait[cursor];
        que->wait[cursor]->subordinates[que->wait[cursor]->n_subordinates-1].n_subordinates = 0;

       setSupervisor(off->department_head);


          free(que);
       break;
     }

     else{

       counter  = addQueue(que,que->wait[cursor],counter);
       cursor++;


     }
    }


 }
 }
/**
 * Fires an employee, removing from the office
 * If employee is null, nothing should occur
 * If the employee does not supervise anyone, they will just be removed
 * If the employee is supervising other employees, the first member of that
 *  team will replace him.
 */
 void office_fire_employee(struct employee* employee) {
   if(employee == NULL){
     return;
   }

   int flag = 0;
   if(employee->n_subordinates == 0 ) {
     size_t count = 0;

     for(size_t i = 0 ; i < employee->supervisor->n_subordinates; i ++){
       if(memcmp(&employee->supervisor->subordinates[i],employee,sizeof(struct employee))==0){
         if(i ==employee->supervisor->n_subordinates - 1){
           flag = 50;
         }
         else{
           flag= i;
         }
       }
     }

     if(flag==50){

       employee->supervisor->n_subordinates --;
       free(employee->name);
       employee->supervisor->subordinates = realloc(employee->supervisor->subordinates,sizeof(struct employee)*employee->supervisor->n_subordinates);


       return;

     }
     struct employee * emplys = malloc(sizeof(struct employee)*(employee->supervisor->n_subordinates -1 ));

     for(size_t i =0 ; i<(employee->supervisor->n_subordinates-1-flag) ; i++){     //get the employees
         emplys[i] = employee->supervisor->subordinates[i+1+flag];
     }

     employee->supervisor->n_subordinates --;

     employee->supervisor->subordinates = realloc(employee->supervisor->subordinates,sizeof(struct employee)*employee->supervisor->n_subordinates);

     for(size_t i =0 ; i<employee->supervisor->n_subordinates;i++){
       employee->supervisor->subordinates[i].name = realloc(employee->supervisor->subordinates[i].name,sizeof(char)*(strlen(emplys[i].name) +1 ));
       memcpy(employee->supervisor->subordinates[i].name,emplys[i].name,sizeof(char)*(strlen(emplys[i].name) +1 ));
       employee->supervisor->subordinates[i].n_subordinates = emplys[i].n_subordinates;
     }


     free(emplys[employee->supervisor->n_subordinates-1].name);
     free(emplys);
   }
   else{

    int counter = 0 ;
    struct employee * temp = employee;

    while(1){
      counter++;

      temp->name = realloc(temp->name,sizeof(char)*(strlen(temp->name) +1 ));

      memcpy(temp->name,temp->subordinates[0].name,sizeof(char)*(strlen(temp->name) +1 )); // change the name;

    if(temp->subordinates[0].n_subordinates ==0 ){
      size_t count = 0;
      struct employee * emplys = malloc(sizeof(struct employee)*(temp->n_subordinates -1 ));



      for(size_t i =0 ; i<(temp->n_subordinates-1) ; i++){     //get the employees
          emplys[i] = temp->subordinates[i+1];
      }


      temp->n_subordinates --;

      if(temp->n_subordinates == 0){
        free(emplys);
        free(temp->subordinates[0].name);
        temp->subordinates = realloc(temp->subordinates,sizeof(struct employee)*temp->n_subordinates);
      }

      else{
          temp->subordinates = realloc(temp->subordinates,sizeof(struct employee)*temp->n_subordinates);
          for(size_t i =0; i < temp->n_subordinates ; i++){

            temp->subordinates[i].name = realloc(temp->subordinates[i].name,sizeof(char)*(strlen(emplys[i].name) +1 ));

            memcpy(temp->subordinates[i].name,emplys[i].name,sizeof(char)*(strlen(emplys[i].name) +1 ));
            temp->subordinates[i].n_subordinates = emplys[i].n_subordinates;
          }

            free(emplys[temp->n_subordinates-1].name);
            free(emplys);
      }


      break;
    }
    else {
        temp = &temp->subordinates[0];
    }
  }




  }

 }





/**
 * Retrieves the first encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */
struct employee* office_get_first_employee_with_name(struct office* office,
  const char* name) {
    if(office ==NULL || name ==NULL){
      return NULL;
    }

    int counter = 0 ;
    int cursor = 0;
    size_t count  = 0;
    size_t checker = 0 ;
    struct queue* queue = malloc(sizeof(struct queue));


    queue->wait[cursor] = office->department_head;
    counter++;
    cursor++;
    counter  = addQueue(queue,office->department_head, counter);


    while(1){
      if(strcmp(queue->wait[cursor]->name,name)==0 ){
        struct employee* answer = queue->wait[cursor];
        free(queue);
        return answer;
      }
      else{
        counter  = addQueue(queue,queue->wait[cursor],counter);
        cursor++;
         if(cursor == counter){
           free(queue);
           return NULL;
         }
      }
    }

}

/**
 * Retrieves the last encounter where the employee's name is matched to one in the office
 * If the employee does not exist, it must return NULL
 * if office or name are NULL, your function must do nothing
 */
struct employee* office_get_last_employee_with_name(struct office* office,
  const char* name) {

    if(office ==NULL || name ==NULL){
      return NULL;
    }

    int counter = 0 ;
    int cursor = 0;
    size_t count  = 0;
    size_t checker = 0 ;
    struct queue* queue = malloc(sizeof(struct queue));


    queue->wait[cursor] = office->department_head;
    counter++;
    cursor++;
    counter  = addQueue(queue,office->department_head, counter);

    struct employee* answer = NULL;

    while(1){
      if(strcmp(queue->wait[0]->name,name)==0 ){
        answer = queue->wait[0];
        cursor++;
        if(cursor == counter){
          break;
        }
      }
      else if(strcmp(queue->wait[cursor]->name,name)==0 ){
        answer = queue->wait[cursor];
        cursor++;
        if(cursor == counter){
          break;
        }
      }
      else{
        counter  = addQueue(queue,queue->wait[cursor],counter);
        cursor++;
         if(cursor == counter){
           break;
         }
      }
    }
   free(queue);
	return answer;
}


/**
 * This function will need to retrieve all employees at a level.
 * A level is defined as distance away from the boss. For example, all
 * subordinates of the boss are 1 level away, subordinates of the boss's subordinates
 * are 2 levels away.
 *
 * if office, n_employees or emplys are NULL, your function must do nothing
 * You will need to provide an allocation for emplys and specify the
 * correct number of employees found in your query.
 */

 size_t findLevel(struct office* off, struct employee* e){
   size_t level = 0;
   if(strcmp(e->supervisor->name,off->department_head->name) ==0 ){
     return 1;
   }
   else{
     level = 1 + findLevel(off,e->supervisor);
     return level;
   }
 }


 void office_get_employees_at_level(struct office* office, size_t level,
   struct employee** emplys, size_t* n_employees) {
     if(n_employees ==NULL || emplys == NULL){

       return;
     }

     if(level ==0){
       *emplys = malloc(sizeof(struct employee));
       (*emplys)[0].name = malloc(sizeof(char) *( strlen(office->department_head->name)+1));
       memcpy(((*emplys)[0].name),office->department_head->name,sizeof(char)*(strlen(office->department_head->name)+1));
       size_t c = 1;
       memcpy(n_employees,&c,sizeof(size_t));


       return;
     }


     int counter = 0 ;
     int cursor = 0;
     size_t count  = 0;
     size_t checker = 0 ;
     struct queue* queue = malloc(sizeof(struct queue));


     queue->wait[cursor] = office->department_head;
     counter++;
     cursor++;
     counter  = addQueue(queue,office->department_head, counter);



     while(1){

       size_t lvl = findLevel(office,queue->wait[cursor]);

       if(lvl == level){

         count++;

         if(count == 1){
           *emplys = malloc(sizeof(struct employee));
           (*emplys)[0].name = malloc(sizeof(char) *( strlen(queue->wait[cursor]->name)+1));
         }
         else{
           *emplys = realloc(*emplys,sizeof(struct employee)*count);
           (*emplys)[count-1].name = malloc(sizeof(char) *( strlen(queue->wait[cursor]->name)+1));
         }


         memcpy(((*emplys)[count-1].name),queue->wait[cursor]->name,sizeof(char)*(strlen(queue->wait[cursor]->name)+1));


         memcpy(n_employees,&count,sizeof(size_t));

         cursor++;
         if(cursor == counter){
           free(queue);
           return;
         }
       }
       else{
         counter  = addQueue(queue,queue->wait[cursor],counter);
          cursor++;
          if(cursor == counter){
            free(queue);
            return;
          }
       }


     }
 }


/**
 * Will retrieve a list of employees that match the name given
 * If office, name, emplys or n_employees is NULL, this function should do
 * nothing
 * if office, n_employees, name or emplys are NULL, your function must do
 * nothing.
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_by_name(struct office* office, const char* name,
  struct employee** emplys, size_t* n_employees) {

    if(office ==NULL || name ==NULL || emplys == NULL || n_employees == NULL){
      return ;
    }

    int counter = 0 ;
    int cursor = 0;
    size_t count  = 0;
    size_t checker = 0 ;
    struct queue* queue = malloc(sizeof(struct queue));


    queue->wait[cursor] = office->department_head;
    counter++;
    cursor++;
    counter  = addQueue(queue,office->department_head, counter);




    while(1){
      if(strcmp(queue->wait[cursor]->name,name)==0 ){
        count++;

        if(count == 1){
          *emplys = malloc(sizeof(struct employee));
          (*emplys)[0].name = malloc(sizeof(char) *( strlen(queue->wait[cursor]->name)+1));
        }
        else{
          *emplys = realloc(*emplys,sizeof(struct employee)*count);
          (*emplys)[count-1].name = malloc(sizeof(char) *( strlen(queue->wait[cursor]->name)+1));
        }

        memcpy(((*emplys)[count-1].name),queue->wait[cursor]->name,sizeof(char)*(strlen(queue->wait[cursor]->name)+1));
        memcpy(n_employees,&count,sizeof(size_t));

        cursor++;
        if(cursor == counter){
          free(queue);
          return;
        }

      }
      else{

          counter  = addQueue(queue,queue->wait[cursor],counter);
           cursor++;
           if(cursor == counter){
             free(queue);
             return;
           }

      }
    }

}

size_t postOrder(struct queue* queue,struct employee* emp,size_t counter){
  if(emp->n_subordinates == 0){

    queue->wait[counter]= emp;

    counter++;
  }
  else{
    for(size_t i = 0 ; i<emp->n_subordinates; i ++){
      counter  = postOrder(queue,&emp->subordinates[i],counter);
    }
    queue->wait[counter]= emp;

    counter++;
  }
  return counter;
}

/**
 * You will traverse the office and retrieve employees using a postorder traversal
 * If off, emplys or n_employees is NULL, this function should do nothing
 *
 * You will need to provide an allocation to emplys and specify the
 * correct number of employees found in your query.
 */
void office_get_employees_postorder(struct office* off,
  struct employee** emplys,
  size_t* n_employees) {

    if(off==NULL || emplys== NULL || n_employees == NULL){
      return;
    }

    size_t counter = 0 ;
    int cursor = 0;
    size_t count  = 0;
    size_t checker = 0 ;
    struct queue* queue = malloc(sizeof(struct queue));

    counter  = postOrder(queue,off->department_head, counter);

    memcpy(n_employees,&counter,sizeof(size_t));

    *emplys = malloc(sizeof(struct employee)*counter);

    for(size_t i =0 ; i<counter ;i++){
      (*emplys)[i].name = malloc(sizeof(char) *( strlen(queue->wait[i]->name)+1));
      memcpy(((*emplys)[i].name),queue->wait[i]->name,sizeof(char)*(strlen(queue->wait[i]->name)+1));
    }

    free(queue);

}
/**
 * The employee will be promoted to the same level as their supervisor and will
 *  join their supervisor's team.
 * If the employee has members on their team, the first employee from that team
 *   will be promoted to manage that team.
 * if emp is NULL, this function will do nothing
 * if the employee is at level 0 or level 1, they cannot be promoted
 */
void office_promote_employee(struct employee* emp) {

}

/**
 * Demotes an employee, placing them under the supervision of another employee.
 * If supervisor or emp is null, nothing should occur
 * If the employee does not supervise anyone, they will not be demoted as they
 *  are already at the lowest position
 * If an employee is to be demoted but their new distance from the boss is less
 *  than the previous position, nothing will happen.
 * Otherwise, the employee should be assigned at the end the supervisor's team
 *  and the first employee from the previously managed team will be promoted.
 *
 * Edge case:
 * if the supervisor use to be an subordinate to the demoted employee
 *   (they will get promoted)
 * the demoted employee will be attached to subordinate's new subordinate's
 *   list not their previous list.
 */
void office_demote_employee(struct employee* supervisor, struct employee* emp){

}


void freeEmp(struct employee* emp){

  free(emp->name);

  if(emp->n_subordinates != 0){
    free(emp->subordinates);
  }

}

/**
 * The office disbands
 * (You will need to free all memory associated with employees attached to
 *   the office and the office itself)
 */
void office_disband(struct office* office) {


  if(office->department_head == NULL){
    free(office);
    return;
  }

  int counter = 0 ;
  int cursor = 0;

  struct queue* que = malloc(sizeof(struct queue));
  que->wait[cursor] = office->department_head;
  counter++;
  cursor++;

  counter  = addQueue(que,office->department_head, counter);

  while(1){
    if(que->wait[cursor]->n_subordinates == 0){
      cursor++;
      if(cursor == counter){
        break;
      }
    }
    else{
      counter  = addQueue(que,que->wait[cursor],counter);
      cursor++;
      if(cursor == counter){
        break;
      }
    }
  }

  for(int i = counter-1 ; i>=0; i--){

    freeEmp(que->wait[i]);
  }


  free(office->department_head);
  free(office);
  free(que);

}
