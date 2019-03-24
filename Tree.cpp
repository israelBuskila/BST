#include <iostream>
#include <math.h>
#include <algorithm>
#include "Tree.hpp"



using namespace std;
using namespace ariel;



  Node::Node(){
      this->value=0;
  }
   Node::Node(int val) {
        this->value = val;
    }

    Node::Node(int val, Node *left, Node *right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }

    bool containsNode(Node* top, int data) {
		if (top == NULL) return false;
		if (data == top->value) return true;
		if (data < top->value)  return containsNode(top->left, data);    
		return containsNode(top->right, data);
	}

	Node* getParent(Node *root, int key){
    if (root == NULL) return NULL;
    else if (root->right->value == key || root->left->value == key) return root;
	else if (root->value > key) getParent(root->left, key);
	else getParent(root->right, key);
	
	}
	
	Node* getNodeByIndex(Node* top, int data) {
		if (top == NULL) return NULL;
		if (data == top->value) return top;
		if (data < top->value)  return getNodeByIndex(top->left, data);    
		return getNodeByIndex(top->right, data);
	}
	
    Tree::Tree(){
        roo = NULL;
    }

	
void Tree::addHelper(Node *root, int val) {
	       if(contains(val) == true)
         throw std::invalid_argument( "Value already exists" );
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node(val);
            } else {
                addHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node(val);
            } else {
                addHelper(root->right, val);
            }
        }
    }
   
    
    void Tree::printHelper(Node *root) {
        //postOrder
        if (!root) return;
        printHelper(root->left);
        cout<<root->value<<' ';
        printHelper(root->right);
    }

    int Tree::nodesCountHelper(Node *root) {
        if (!root) return 0;
        else return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
    }

    int Tree::heightHelper(Node *root) {
        if (!root) return 0;
        else return 1 + std::max(heightHelper(root->left), heightHelper(root->right));
    }

    void Tree::printMaxPathHelper(Node *root) {
        if (!root) return;
        cout<<root->value<<' ';
        if (heightHelper(root->left) > heightHelper(root->right)) {
            printMaxPathHelper(root->left);
        } else {
            printMaxPathHelper(root->right);
        }
    }

    bool Tree::deleteValueHelper(Node *parent, Node *current, int value) {
       if(contains(value) == false)
         throw std::invalid_argument( "value not exist" );
        if (!current) return false;
        if (current->value == value) {
            if (current->left == NULL || current->right == NULL) {
                Node *temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->roo = temp;
                }
            } else {
                Node *validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                int temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) || deleteValueHelper(current, current->right, value);
    }

    void Tree::insert(int i){
        
          if (roo) {
            this->addHelper(roo, i);
        } else {
            roo = new Node(i);
        }
    }

    void Tree::remove(int i){
        bool flag= this->deleteValueHelper(NULL, this->roo, i);
    }

    int Tree::size(){
       return nodesCountHelper(roo);
    }

    bool Tree::contains(int i){
        bool con = containsNode(roo, i);
        return con;
		
		
    }

    int Tree::root(){
         return this->roo->value;
    }

    int Tree::parent(int i){
		Node* parent=getParent(this->roo, i);
      
        return parent->value;
    }

    int Tree::left(int i){
        Node* n=getNodeByIndex(this->roo, i);
		return n->left->value;
    }

    int Tree::right(int i){
		
        Node* n=getNodeByIndex(this->roo, i);
		return n->right->value;
    }

    void Tree::print(){
       printHelper(this->roo);
    }
// int main() {

// ariel::Tree e;
// e.size();
// // e->insert(5);
// // int s = e.size();
// // cout<<s<<endl;
//}

