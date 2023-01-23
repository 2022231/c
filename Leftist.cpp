#include<iostream>
using namespace std;

typedef struct node{
  int data,s;
  node *left,*right;

  node(int data){
    this->data = data;
    this->left = this->right = NULL;
    this->s = 1;
  }
}node;

int height(node *root){
  if(!root)
    return 0;
  return 1 + min(height(root->left),height(root->right));
}

node *merge(node *root1, node *root2){
  if(!root1)
    return root2;
  if(!root2)
    return root1;


  node *finalroot, *left, *returnheap;

  if(root1->data < root2->data){
    returnheap = merge(root1->right, root2);
    finalroot = root1;
  } else {
    returnheap = merge(root1, root2->right);
    finalroot = root2;
  }

  if(!finalroot->left || returnheap->s > finalroot->left->s){
    node *temp = finalroot->left;
    finalroot->left = returnheap;
    finalroot->right = temp;
   // swap(finalroot->left, finalroot->right);
  } else {

    finalroot->right = returnheap;
  }

  finalroot->s = height(finalroot);
  return finalroot;
}

node *insert(node *root, int data){
  node *newnode = new node(data);
  if(!root){
    return newnode;
  }
  return  merge(root,newnode);
}


node *deletenode(node *root){
  node *temp = merge(root->left, root->right);
  delete root;
  return temp;
}


void print(node *root, string indent, bool last){
  if(root){
    cout<<indent;
    if(last){
      cout<<"L---- ";
      indent += "|   ";
    } else{
      cout<<"R---- ";
      indent += "   ";
    }
    cout<<root->data<<endl;
    print(root->left,indent,true);
    print(root->right,indent,false);
  } 
}

int main(){
  node *root = NULL;
 int nn,data;
 while(1){
  cout<<"1.Insert\n2.Delete\nEnter- ";
  cin>>nn;
  switch(nn){
    case 1:
      cout<<"Enter Insert...";
      cin>>data;
      root = insert(root, data);
      print(root,"", false);
      break;
    case 2:
      root = deletenode(root);
      print(root, "", false);
      break;
    default:
      cout<<"Wrong Input";
  }
 } 
}