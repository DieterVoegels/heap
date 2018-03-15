/*
  this file has the setters and getters for the variables in node.h
*/
#include  <iostream>
#include "node.h"

using namespace std;

node::node(){
  
}

node* node::getRight(){
  return right;
}

node* node::getLeft(){
  return left;
}

node* node::getParent(){
  return parent;
}

int node::getNum(){
  return number;
}

void node::setRight(node* newRight){
  right = newRight;
}

void node::setLeft(node* newLeft){
  left = newLeft;
}

void node::setNum(int newNumber){
  number = newNumber;
}

void node::setParent(node* newParent){
  parent = newParent;
}
