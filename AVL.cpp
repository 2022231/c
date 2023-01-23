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
	

int height(node *root){
	if(!root)
		return 0;
	return 1 + max(height(root->left)  ,height(root->right));
}

int getbalancefactor(node *root){
	return height(root->left)-height(root->right);
}

node *leftrotate(node *x){
	node *y = x->right;
	node *t2 = y->left;

	y->left = x;
	x->right = t2;

	return y;
}


node *rightrotate(node *x){
	node *y = x->left;
	node *t2 = y->right;

	y->right = x;
	x->left = t2;

	return y;
}


node *insertNode(node *root,int data){
	if(!root)
		return new node(data);
	if(data < root->data)
		root->left  = insertNode(root->left, data);
	else if(data > root->data)
		root->right  = insertNode(root->right, data);

	int balancefactor = getbalancefactor(root);

	if(balancefactor > 1){ //left-left or left-right case
		if(data < root->left->data){ //left-left case
			return rightrotate(root);
		}else{   //left-right case
			root->left = leftrotate(root->left);
			return rightrotate(root);
		} 
	}else if(balancefactor < -1){ //right-right or right-left case
		if(data > root->right->data){ //right-right case
			return leftrotate(root);
		}else{   //right-left case
			root->right = rightrotate(root->right);
			return leftrotate(root);
		} 
	}
	return root;

} 

node *sucessor(node *root){
	if(!root)
		return NULL;
	node *temp = root->right;
	while(temp->left){
		temp = temp->left;
	}
	return temp;
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
	
	int balancefactor = getbalancefactor(root);

	if(balancefactor > 1){ //left-left or left-right case
		if(getbalancefactor(root->left) >= 0){ //left-left case
			return rightrotate(root);
		}else{   //left-right case
			root->left = leftrotate(root->left);
			return rightrotate(root);
		} 
	}else if(balancefactor < -1){ //right-right or right-left case
		if(getbalancefactor(root->right) <= 0){ //right-right case
			return leftrotate(root);
		}else{   //right-left case
			root->right = rightrotate(root->right);
			return leftrotate(root);
		} 
	}

	return root;

}
void inorder(node *root){
	if(!root) return;
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}

void preorder(node *root, string indent, bool last){
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
		preorder(root->left,indent,true);
		preorder(root->right,indent,false);
	}	
}

int main(){
	node *root = NULL;

	root = insertNode(root,8);
	root = insertNode(root,6);
	root = insertNode(root,9);
	root = insertNode(root,1);
	root = insertNode(root,7);
	root = insertNode(root, 10);

	//root = deleteNode(root,-1);
	
	root = insertNode(root,5);
	root = insertNode(root,56);
	root = insertNode(root,12);
	root = insertNode(root, 11);

	root = deleteNode(root, 9);
	preorder(root,"",false);
	cout<<"\n"<<height(root);
}