#include<stdio.h>
#include<stdlib.h>
#include"tokenizer.h"

/* Return true (non-zero) if c is a whitespace characer                                              
   ('\t' or ' ').                                                                                    
   Zero terminators are not printable (therefore false) */
int space_char(char c){
  if (c == '\0' || c == ' ' || c == '\t' || c == '\n'){//if pointer at char is a whitespace.                      
    return 1;
 }

 return 0;
}

/* Return true (non-zero) if c is a non-whitespace                                                   
   character (not tab or space).                                                                     
   Zero terminators are not printable (therefore false) */
int non_space_char(char c){
  if (c != ' ' && c != '\t' && c != '\0' && c != '\n'){// if pointer at char is not a whitespace.                 
   return 1;
 }

 return 0;
}
/* Returns a pointer to the first character of the next                                              
   space-separated token in zero-terminated str.  Return a zero pointer if                           
   str does not contain any tokens. */
char *token_start(char *str){
  if(str == NULL){
    return NULL;
  }
  while(*str != '\0' && space_char(*str)){//iterating through string to get to the start of next.
    str++;
  }
  if (*str == '\0'){
    return NULL;
  }
  return str;
}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token) {
  if (token == NULL) {// first using a base case to check if null.
    return NULL;
  }
  // Iterate through the token while it is not the null character ('\0')
  // and the character is a non-space character
  while (*token != '\0' && non_space_char(*token)){
    token++;
      }
  return token;  // If no whitespace is found, return pointer to the null character ('\0')           
}
/* Counts the number of tokens in the string argument. */
int count_tokens(char *str){
  int count=0;
  for(char *ptr = str; ptr != NULL && *ptr != '\0'; ){
    // Set ptr to the start of the next token (skipping over any spaces)
    ptr = token_start(ptr);
    if (ptr != NULL){
      count++;
    // Move ptr to the end of the current token 
      ptr = token_terminator(ptr);
    }
  }
    return count;
}
/* Returns a fresly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){
  // Allocate memory for the string copy (+1 for the null terminator)
  char *ptrMem = (char *) malloc(len+1);
  if(ptrMem == NULL){ // Check if memory allocation failed
    return NULL;
  }
  // Save the start of the memory block for return after copying
  char *startPtr = ptrMem;
    // Copy each character from the input string to the newly allocated memory
  for (int i =0; i< len; i++){
    *ptrMem = *inStr;
    ptrMem++;
    inStr++;
  }
  *ptrMem = '\0';//set last postion to null terminator.
  return  startPtr;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated                           
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:                                      
     tokens[0] = "hello"                                                                             
     tokens[1] = "world"                                                                             
     tokens[2] = "string"                                                                            
     tokens[3] = 0                                                                                   
*/
char **tokenize(char *str){
  if(str == NULL){// Check if the input string is NULL
    return NULL;
  }
  // Count the number of tokens in the string
  int numTokens = count_tokens(str);
    // Allocate memory for the array of token pointers (+1 for NULL terminator)
  char **drefPtr = (char **) malloc (sizeof(char*) *(numTokens+1));
  if(drefPtr == NULL){
    return NULL;
  }
  // Initialize a pointer to iterate through the input string
  char *copyPtr = str;
  for(int i =0; *copyPtr != '\0';i++){
    // Find the start of the next token
    copyPtr = token_start(copyPtr);
    if(copyPtr ==NULL){
      break;
    }
    // Find the end of the current token
    char *end =token_terminator(copyPtr);
    // Calculate the length of the token
    short len = end - copyPtr;
    // Copy the token into a newly allocated string
    drefPtr[i] = copy_str(copyPtr, len);
    // Move the copy pointer to the end of the token (next part of the string)
    copyPtr = end;
}
  drefPtr[numTokens] = NULL;

  return drefPtr;
}
/* Prints all tokens. */
void print_tokens(char **tokens){
  if(tokens == NULL){
    return ;
  }
  for(int i = 0; tokens[i] != NULL; i++){
    printf("Tokens[%d] %s\n",i,tokens[i]);
  }
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens){
  if(tokens == NULL){
    return;
  }
  for(int i = 0; tokens[i] != NULL; i++){
    free(tokens[i]);
  }
      free(tokens);
}

