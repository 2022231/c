#include <iostream>
using namespace std;

typedef struct node{
	int data;
	node *left,*right,*parent;

	node(int data, node* parent){
		this->data = data;
		this->left = this->right = NULL;
		this->parent = parent;
	}
}node;
	

node *leftRotate(node *x){
	node *y = x->right;
	node *t2 = y->left;
	
	if(x->parent){
			if(x->parent->left == x)
				x->parent->left = y;
			else
				x->parent->right = y;
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
	
	
	if(t2)
		t2->parent = x;
	y->parent = x->parent;
	x->parent = y;

	y->right = x;
	x->left = t2;
}


node *splay(node *root){
	while(root->parent){
		if(root->parent->parent == NULL){
			if(root == root->parent->left)
				rightRotate(root->parent);
			else 
				leftRotate(root->parent);
		} else if (root == root->parent->left && root->parent == root->parent->parent->left) {
		        // zig-zig rotation
		        rightRotate(root->parent->parent);
		        rightRotate(root->parent);
		} else if (root == root->parent->right && root->parent == root->parent->parent->right) {
		        // zag-zag rotation
		        leftRotate(root->parent->parent);
		        leftRotate(root->parent);
		} else if (root == root->parent->right && root->parent == root->parent->parent->left) {
		        // zig-zag rotation
		        leftRotate(root->parent);
		        rightRotate(root->parent);
		} else {
		        // zag-zig rotation
		        rightRotate(root->parent);
		        leftRotate(root->parent);
		}
	}
	return root;
}

node *search(node *root,node *parent,int data){
  if(!root)
    return parent;
  if(data == root->data)
    return root;
  else if(data < root->data)
    return search(root->left,root,data);
  else if(data > root->data)
    return search(root->right,root,data);
}

node *insertNodehelper(node *root,int data,node *parent){
	if(!root)
		return new node(data,parent);
	if(data < root->data){
		root->left  = insertNodehelper(root->left, data, root);
	}
	else if(data > root->data){
		root->right  = insertNodehelper(root->right, data, root);
	}
	return root;
} 
node *insertNode(node *root,int data,node *parent){
	root = insertNodehelper(root,data,parent);
	//root = splay(search(root,NULL,data));
//return search(root,NULL,data);
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
	node *temp = splay(search(root,NULL,data));
	if(temp->data != data)
		return temp;
	else{
		node *templeft = temp->left;
		node *tempright = temp->right;
		

		if(templeft ==  NULL)
			return tempright;
		else if(tempright == NULL)
			return splay(predessor(templeft));
		else{
			root = splay(predessor(temp));
			root->right = tempright;
		}
		delete temp;
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
		//if(root->parent)
		//	cout<<root->parent->data;
		cout<<" "<<root->data<<endl;
		preorder(root->left,indent,true);
		preorder(root->right,indent,false);
	}	
}

int main(){
	node *root = NULL;

	root = insertNode(root,12,NULL);
	root = insertNode(root,10,NULL);
	root = insertNode(root,7,NULL);
	root = insertNode(root,13,NULL);
	root = insertNode(root,14,NULL);


//	root = deleteNode(root, 9);
	preorder(root,"",false);
	root = deleteNode(root, 16);
	root = deleteNode(root, 7);
	//root = splay(search(root,NULL,11));
	//rightrotate(search(root,NULL,8));
	//rightrotate(search(root,NULL,6));	
	preorder(root,"",false);
	
}