/*
  This program takes in numbers or a file and prints out a tree where the parent is bigger than its children. Then
  it prints out largest to smallest.
  author: Dieter Voegels
  date: 03/15/2018
*/
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include "node.h"

using namespace std;

//prototypes
void createMaxHeap(node* &head, node* heap[100], int size);
void heapify(node* parent, node* child);
void print(node* current, int number);
void printLargestToSmallest(node* head, node* heap[100], int counter);
void swap(node* current);

//constructor
int main(){
  char* input = new char[20];
  int numbers[100];
  for(int i = 1; i <= 99; i++){
    numbers[i] = -1;
  }
  node* heap[100];
  heap[0] = NULL;
  int i;
  bool quit = false;
  node* head = NULL;
  
  cout << "Input the numbers or file you wish to be created into a tree. Type in quit when you are done adding numbers or have entered in the file." << endl;
  
  //create heap
  while(quit == false){
    //get input from user
    cout << "Input a number or the word 'filename' or type quit to print the tree." << endl;
    cin.getline(input, 20);
    //when the user types in quit, create the max heap
    int size = 1;
    if(strcmp(input, "quit") == 0){
      quit = true;
      for(int i = 0; numbers[i] != -1; i++){
	node* Node = new node();
	Node->setNum(numbers[i]);
	heap[i+1] = Node;
	size++;
      }
      //add a node to the tree from row by row, left to right, heapifying as it hops node to node
      createMaxHeap(head, heap, size);
      
      //print out the tree
      int number = 0;
      print(head, number);
      printLargestToSmallest(head, heap, size);
    }
    //when the user types filename, get the filename and create the numbers array from that file
    if(strcmp(input, "filename") == 0){
      cout << "What is the file name?" << endl;
      char fileName[200];
      char input[200];
      cin.getline(fileName, 100);
      ifstream file(fileName);
      if(file.is_open()){
	file.getline(input, 200);
      }
      else{
	cout << "Could not find the file, try again." << endl;
      }
      int counter = 0;
      for(int i = 0; i < strlen(input); i++){
	//if it is a digit, then convert it into a single token
	if(isdigit(input[i]) == true){
	  //keep track of the start of the number and the length of the number
	  int start = i;
	  int length = 1;
	  while(input[i+1] != ' '){
	    length++;
	    i++;
	  }
	  //now convert the numbers into a single number
	  char* number = new char[length];
	  for(int j = 0; j != length; j++){
	    number[j] = input[start+j];
	  }
	  //change char to int
	  numbers[counter] = atoi(number);
	  counter++;
	}
      }
    }
    else{
      numbers[i] = atoi(input);
      i++;
    }
  }
}

//create the max heap tree
void createMaxHeap(node* &head, node* heap[100], int size){
  for(int i = 1; i < size; i++){
    if(head == NULL){
      head = heap[i];
    }
    else{
      node* parent = heap[i/2];
      if(parent->getLeft() == NULL){
	parent->setLeft(heap[i]);
      }
      else{
	parent->setRight(heap[i]);
      }
      heap[i]->setParent(parent);
      heapify(parent, heap[i]);
    }
  }
}

//swap numbers until parent is larger than its children
void heapify(node* parent, node* child){
  if(parent == NULL){
    return;
  }
  else if(parent->getNum() < child->getNum()){
    int temp = parent->getNum();
    parent->setNum(child->getNum());
    child->setNum(temp);
    heapify(parent->getParent(), parent);
  }
}

//print out the tree
void print(node* current, int number){
  if(current->getRight() != NULL){
    print(current->getRight(), ++number);
    number--;
  }
  
  for(int i = 1; i <= number; i++){
    cout << "\t";
  }
  cout << current->getNum() << endl;
  
  if(current->getLeft() != NULL){
    print(current->getLeft(), ++number);
    number--;
  }
}

//print out largest to smallest
void printLargestToSmallest(node* head, node* heap[100], int counter){
  for(int i = counter - 1; i > 0; i--){
    int temp = head->getNum();
    head->setNum(heap[i]->getNum());
    heap[i]->setNum(temp);
    cout << heap[i]->getNum() << " ";
    if(i != 1){
      if(heap[i]->getParent()->getLeft() == heap[i]){
	heap[i]->getParent()->setLeft(NULL);
      }
      else{
	heap[i]->getParent()->setRight(NULL);
      }
    }
    delete heap[i];
    swap(head);
  }
}

//swap the head with the largest child
void swap(node* current){
  if(current->getLeft() != NULL && current->getRight() != NULL){
    if(current->getLeft()->getNum() > current->getRight()->getNum()){
      if(current->getLeft()->getNum() > current->getNum()){
	int temp = current->getNum();
	current->setNum(current->getLeft()->getNum());
	current->getLeft()->setNum(temp);
	swap(current->getLeft());
      }
    }
    else{
      if(current->getRight()->getNum() > current->getNum()){
	int temp = current->getNum();
	current->setNum(current->getRight()->getNum());
	current->getRight()->setNum(temp);
	swap(current->getRight());
      }
    }
  }
  else if(current->getRight() != NULL){
    if(current->getRight()->getNum() > current->getNum()){
      int temp = current->getNum();
      current->setNum(current->getRight()->getNum());
      current->getRight()->setNum(temp);
      swap(current->getRight());
    }
  }
  else if(current->getLeft() != NULL){
    if(current->getLeft()->getNum() > current->getNum()){
      int temp = current->getNum();
      current->setNum(current->getLeft()->getNum());
      current->getLeft()->setNum(temp);
      swap(current->getLeft());
    }
  }
}
