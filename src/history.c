#define _HISTORY_A
#include "history.h"
#include<stdio.h>
#include<stdlib.h>

/* Initialize the linked list to keep the history. */
List* init_history(){
  List *list = malloc(sizeof(List));//first allocate memory to handle the size of the list.
 if (list == NULL){
   return NULL;
  }
 list->root = NULL;//set the root to point to null. First instance of list creation.
 return list;
}
char *copyStr(char *str){//helper function copys string and recives the length of string.
  int len = 0;
  char *copy = str;
  while(*copy != '\0'){
    len++;
    copy++;
  }
  char *copyStr = (char *)malloc(len+1);
  if (copyStr == NULL){
    return NULL;
  }
  for(int i = 0; i<len; i++){
    copyStr[i] = str[i];
  }
  copyStr[len] = '\0';
    return copyStr;
}
void add_history(List *list, char *str){
  Item *item = malloc(sizeof(Item));//allocate memory for a new item.
  if(item ==NULL){//break case.
    return;
  }
  item->str = copyStr(str);// allocates memory for str and copys string.
  if(item->str == NULL){//handle duplicates.
    free(item);
    return;
  }
  if(list->root == NULL){//if list is empty.
    list->root = item;//intialize item to root
    item->id = 1;// this asignes a unique id to the first instance of a item.
  }else{//else find the last item and assign id +1.
    Item *curr = list->root;
    while(curr->next != NULL){
      curr = curr->next;
    }
    item->id = curr->id +1;
    curr->next = item;// links the new item to the end.
  }
  item->next =NULL;//set new item to point to NULL.
}

/* Retrieve the string stored in the node where Item->id == id.                                       
   List* list - the linked list                                                                       
   int id - the id of the Item to find */
char *get_history(List *list, int id){
  if(list == NULL || list->root == NULL){//checks if no content present.  
    return NULL;
  }
  Item *curr = list->root;
  while(curr != NULL){
    if(curr->id == id){//if the id that is being searched for is found return.
      return curr->str;
    }
    curr = curr->next;//if not continue to iterate.
  }
  return NULL;
}
/*Print the entire contents of the list. */
void print_history(List *list){
  if(list == NULL || list->root == NULL){//checks if no content present.
    return;
  }
  Item *curr = list->root ;
  while(curr != NULL){
    printf("Item[%d], String:%s\n", curr->id, curr->str);
    curr = curr->next;
  }
}

/*Free the history list and the strings it references. */
void free_history(List *list){
 if(list == NULL || list->root == NULL){
    return;
  }
  Item *curr = list->root ;
  Item *next;//temp
  while(curr != NULL){
    next =curr->next;//save the next item before freeing the current to continue.
    free(curr->str);//free the str in curr item.
    free(curr);//free the curr list.
    curr = next;//move to next item
  }
  free(list);//finaly free the list structure.
}
