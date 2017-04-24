///////////////////////////////////////////////////////////////////////
// Student Name: Victor Barr
// Date: 11/3/2016
// Class: ECE 2035
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// Doubly Linked List
//
// This file should contain you implementation of the doubly-linked
// list data structure as described in the project documentation.
//
// Some functions are provided for you - use these as guides for the
// implementation of the remaining functions.
//
// This code can be tested using the testbench module. See
// testbench.h in the source, and LL_testbench_documentation.pdf in
// the project documentation for more information.
//
// GEORGIA INSTITUTE OF TECHNOLOGY, FALL 2016
///////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

/**
 * create_llnode
 *
 * Helper function that creates a node by allocating memory for it on the heap,
 * and initializing its previous and next pointers to NULL and its data pointer to the input
 * data pointer
 *
 * @param data A void pointer to data the user is adding to the doublely linked list.
 * @return A pointer to the linked list node
 */
static LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    newNode->data = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

/**
 * create_dlinkedlist
 *
 * Creates a doublely liked list by allocating memory for it on the heap. Initialize the size to zero,
 * as well as head, current, and tail pointer to NULL
 *
 * @return A pointer to an empty dlinkedlist
 */
DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;
    newList->size = 0;
    return newList;
}

void insertHead(DLinkedList* dll, void* data){
  LLNode* newNode = create_llnode(data);
  if(dll->head == NULL){
    dll->size++;
    dll->head = newNode;
    //dll->current = newNode;
    dll->tail = newNode;
  }else{
    dll->size++;
    newNode->next = dll->head;
    (dll->head)->previous = newNode;
    dll->head = newNode;
  }
}


void insertTail(DLinkedList* dll, void* data){
    LLNode* newNode = create_llnode(data);
    if(dll->tail == NULL) { //if tail doesnt exist
        dll->head = newNode; //this is the first node in the list
        dll->tail = newNode;
        //dll->current = newNode;
    } else { // if a tail does already exist
        newNode->previous = dll->tail; //set previous of new node to tail
        (dll->tail)->next = newNode; //set tail's next to newNode
        dll->tail = newNode; //set dll's  tail to newNode
    }
    dll->size++; //increase size
}

int insertAfter(DLinkedList* dll, void* newData){
    LLNode* newNode = create_llnode(newData);
    if (dll->current ==NULL) return 0;

    newNode->previous = dll->current; //sets newNode previous to current
    newNode->next = (dll->current)->next; //sets the next of newNode to current's next node
    (newNode->previous)->next = newNode; //sets newNode's previous's next to newNode
    (newNode->next)->previous = newNode; //sets newNode's next's previous to newnode

    dll->size++; //increases size
    return 1;
}

int insertBefore(DLinkedList* dll, void* newData){
    LLNode* newNode = create_llnode(newData);
    if (dll->current ==NULL) return 0;

    newNode->next = dll->current; //set newnodes next to current
    newNode->previous = (dll->current)->previous; //set newNode previous to the previous of current
    (newNode->previous)->next = newNode; //set newNode previous's next to new node
    (newNode->next)->previous = newNode; //set newNodes next's previous to newNode

    dll->size++; //increases size
    return 1;

}

void* deleteBackward(DLinkedList* dll, int shouldFree){
    if((dll->current) == dll->head || dll->current == NULL) {
         if(dll->current != NULL) {
            if(shouldFree) free((dll->current)->data);
            free(dll->current);  //if should free then frees
        }
        return NULL; //This sometimes shouldnt happen
    }
    LLNode * freeLater = dll->current; //sets a void pointer to equal the current void pointer
    dll -> current = (dll->current)->previous; //sets current to the previous
    (dll->current)->next = freeLater->next; //sets the new current's next to the next of the previous current
    if(dll->tail == freeLater) {dll->tail = dll->current; //if the previous current was the tail set new tail
        (dll->tail)->next = NULL; }
    //if it wasnt the tail set the previous of the one after the past current to the current current
    else (freeLater->next)->previous = dll->current;
    //if(dll->tail != freeLater)
    dll->size--;
    if(shouldFree) { free(freeLater->data);}free(freeLater);  //if should free then frees
    return getCurrent(dll); //returns the data of the current pointer
}

void* deleteForward(DLinkedList* dll, int shouldFree){
    if((dll->current) == dll->tail || dll->current == NULL) {
        if(dll->current != NULL) {
            if(shouldFree) free((dll->current)->data);
            free(dll->current);  //if should free then frees
        }
        return NULL; //if current is the tail or current is NULL
    }
    LLNode* freeLater = dll->current; //sets a pointer to the old current;
    dll->current = freeLater->next; //sets current to the next of current
    (dll->current)->previous = freeLater->previous; //sets the previous of the new current
    if(dll->head == freeLater) {dll->head = dll->current; //sets new head
        (dll->head)->previous = NULL; }
    else (freeLater->previous)->next = dll->current; //sets the pointer before old current to go to new current
    dll->size--;
    if(shouldFree) { free(freeLater->data);}free(freeLater);  //if should free then frees
    return getCurrent(dll); //returns the data of the current pointer

}

void destroyList(DLinkedList* dll, int shouldFree){
  if(dll->head != NULL){
    getHead(dll);
    while(deleteForward(dll,shouldFree)){};
  }
  free(dll);
}

void* getHead(DLinkedList* dll){
  if(dll->head != NULL){
    dll->current = dll->head;
    return (dll->head)->data;
}else{ //this isnt needed
    return NULL;
  }
}

void* getTail(DLinkedList* dll){
    //if dll tail doesnt equal null , set current to tail
    if(dll->tail!=NULL) dll->current = dll->tail;
    // return null if tail doesnt exist and data otherwise
    return ((dll->tail)==NULL)? NULL : (dll-> tail)->data;
}

void* getCurrent(DLinkedList* dll){
    // current already set so, if null return null, not: return data
    return (dll->current)==NULL? NULL : dll-> current->data;
}

void* getNext(DLinkedList* dll){
    // if current's next isnt null then set current to current's next
    if((dll->current)->next!=NULL) {
        dll->current = (dll->current)->next;
        return (dll->current)->data; //also return data
    } return NULL;//if not then return null
}

void* getPrevious(DLinkedList* dll){
    if((dll->current)->previous != NULL) { // if current has a previous
        dll->current = (dll->current)->previous; //set new current
        return (dll->current)->data; //return data at new current
    } return NULL; //if not true
}

int getSize(DLinkedList* dll){
    return dll->size; //I returned the size!
}
