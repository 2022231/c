#include<iostream>
using namespace std;
typedef struct node{
	int data;
	string color;
	node *left,*right,*parent;
	node(int data){
		this->color = "R";
		this->data = data;
		this->left = this->right = this->parent = NULL;
	}

}node;

node *root;


void leftRotate(node *x){
	node *y = x->right;
	node *t2 = y->left;

	if(x->parent){
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else{
		root = y;
	}

	if(t2) 
		t2->parent = x;
	y->parent = x->parent;
	x->parent = y;

	y->left = x;
	x->right = t2;
}

void rightRotate(node *x){
	node *y = x->left;
	node *t2 = y->right;
	if(x->parent){
			if(x->parent->left == x)
				x->parent->left = y;
			else
				x->parent->right = y;
			
		}
		else {
			root = y;
		}
	if(t2)
		t2->parent = x;
	y->parent = x->parent;
	x->parent = y;

	y->right = x;
	x->left = t2;
}

void insertfix(node *x){
	if(root == x){
		x->color == "B";
		return;
	}
	while(x->parent != NULL && x->parent->color == "R"){
		node *g = x->parent->parent;
		if(g->left == x->parent){
			if(g->right != NULL && g->right->color == "R"){
				node *u = g->right;
				if(u->color == "R"){
					g->color = "R";
					x->parent->color = "B";
					u->color = "B";
					x = g;
				}
			}
			else {
				if(x->parent->right == x){
					x = x->parent;
					leftRotate(x);
				}
				g->color = "R";
				x->parent->color = "B";
				rightRotate(g);
			}
		} else {
			if(g->left != NULL && g->left->color == "R"){
				node *u = g->left;
				if(u->color == "R"){
					g->color = "R";
					x->parent->color = "B";
					u->color = "B";
					x = g;
				}
			}
			else {
				if(x->parent->left == x){
					x = x->parent;
					rightRotate(x);
				}
				g->color = "R";
				x->parent->color = "B";
				leftRotate(g);
			}
		}
	
	root->color = "B";	
	}
}

void insert(int data){
	node *newnode = new node(data);
	if(root == NULL){
		root = newnode;
		newnode->color = "B";
		return;
	}
	else{
		node *temp = root;
		while(temp){
			if(data < temp->data){
				if(temp->left == NULL){
					temp->left = newnode;
					newnode->parent = temp;
					break;
				} 
				else temp = temp->left;
			}
			else if(data > temp->data){
				if(temp->right == NULL){
					temp->right = newnode;
					newnode->parent = temp;
					break;
				} 
				else temp = temp->right;
			}
		}
	}
	insertfix(newnode);

}


void preorder(node *root, string indent, bool last){
	if(root){
		cout<<indent;
		if(last){
			cout<<"L----";
			indent += "|    ";
		} else {
			cout<<"R----";
			indent += "    ";
		}
		cout<<root->data<<" "<<root->color<<endl;
		preorder(root->left,indent,true);
		preorder(root->right,indent,false);
	}
}
int main(){
	root = NULL;
	insert(12);
	insert(91);
	insert(23);
	insert(43);
	insert(54);
	
	
	preorder(root,"",false);
}