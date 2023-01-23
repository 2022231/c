#include <iostream>
using namespace std;

typedef struct node{
	int data;
	node *left,*right;

	node(int data){
		this->data = data;
		this->left = this->right = NULL;
	}
}node;

node *root=NULL;

void insertNode(int data){
	node *newnode = new node(data);
	if(!root)
	{
		root = newnode;
		return ;
	}
	
	node *temp = root;
	while(temp){
		if(data < temp->data){
			if( !temp->left ) {
				temp->left = newnode;
				return;
			}else{
				temp = temp->left;
			} 
		} else if (data > temp->data){
			if(	!temp->right ){
				temp->right = newnode;
				return;
			}else{
				temp = temp->right;
				}
		}
	}
} 

node *predessor(node *root){
	if(!root)
		return NULL;
	node *temp = root->left;
	while(temp->right){
		temp = temp->right;
	}
	return temp;
}
node *insertNode(node *root,int data){
	if(!root)
		return new node(data);
	if(data < root->data)
		root->left  = insertNode(root->left, data);
	else if(data > root->data)
		root->right  = insertNode(root->right, data);

	
	return root;

} 

node *deleteNode(node *root, int data){
	if(!root){
		return root;
	}
	if(data < root->data)
		root->left  = deleteNode(root->left, data);
	else if(data > root->data)
		root->right  = deleteNode(root->right, data);
	else{
		if(root->left == NULL && root->right == NULL){
			delete root;
			return NULL;
		} else if(root->left == NULL && root->right  != NULL){
			node *temp = root->right;
			delete root;
			return temp;
		} else if(root->left != NULL && root->right == NULL){
			node *temp = root->left;
			delete root;
			return temp;
		} else{
			node *temp = predessor(root);
			root->data = temp->data;
			root->left = deleteNode(root->left, temp->data);
		}
	}
	return root;
}
	

void inorder(node *tree){
	if(!tree) return;
	inorder(tree->left);
	cout<<tree->data<<" ";
	inorder(tree->right);
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
		cout<<root->data<<endl;
		preorder(root->left,indent,true);
		preorder(root->right,indent,false);
	}
}


int main(){
	node *root = NULL;

	root = insertNode(root, 5);
	root = insertNode(root, 10);
	root = insertNode(root, 1);
	root = insertNode(root, 3);
	root = insertNode(root, 20);
	preorder(root,"",false);
	root = deleteNode(root, 5);
	preorder(root,"",false);

}