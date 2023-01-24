#include<iostream>
using namespace std;

void heapify(int a[],int n,int i){
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if(l < n && a[l] < a[largest])
		largest = l;
	if(r < n && a[r] <	 a[largest])
		largest = r;
	if(i != largest){
		swap(a[i],a[largest]);
		heapify(a,n,largest);
	}
}

void insert(int a[],int &n,int data){
	a[n++] = data;
	for(int i = n / 2 - 1; i >= 0;i--){
		heapify(a,n,i);
	}
}


void deletenode(int a[],int &n,int data){
	int i;
	for(i=0 ; i<=n ;i++){
		if(a[i] == data) break;
		if(i == n) return;
	}
	swap(a[i],a[--n]);
	for(int i = n / 2 - 1; i >= 0;i--){
		heapify(a,n,i);
	}
}

void print(int a[],int n,int i,string in,bool last){
	if(i<n){
		cout<<in;
		if(last){
			cout<<"L---- ";
			in+="|    ";
		}
		else{
			cout<<"R---- ";
			in+="    ";
		}
		cout<<a[i]<<endl;
		print(a,n,2 * i + 1,in,true);
		print(a,n,2 * i + 2,in,false);
		
	}
}
int main(){
	int a[1000];
	int n=0;
	insert(a,n,6);
	insert(a,n,7);
	insert(a,n,1);
	insert(a,n,8);
	insert(a,n,10);
	insert(a,n,0);
	print(a,n,0,"",false);
	deletenode(a,n,555);
	print(a,n,0,"",false);
}