/*
  this file holds the prototypes and variables for node.cpp
  author: Dieter Voegels
  Date: 03/15/2018
*/
#include <iostream>

using namespace std;

class node{
 public:
  node();
  node* getRight();
  node* getLeft();
  node* getParent();
  int getNum();
  void setRight(node* newRight);
  void setLeft(node* newLeft);
  void setNum(int newNumber);
  void setParent(node* newParent);
 private:
  int number = -1;
  node* left = NULL;
  node* right = NULL;
  node* parent;
};
