#include <iostream>
using namespace std;

void heapify(string a[], int n, int i){
  //int n = sizeof(a)/sizeof(a[0]);
  int largest = i;
  int l = 2 * i + 1 ;
  int r = 2 * i + 2;
  if (l < n && a[l] > a[largest])
    largest = l;
  if (r < n && a[r] > a[largest])
    largest = r;

  if (largest != i) {
    swap(a[i], a[largest]);
    heapify(a, n, largest);
  }
}
void insert(string a[],int &n, string data){
   if (n == 0){
    a[n] = data;
    n++;
  } else {
    a[n++] = data;
    for (int i = n / 2 - 1 ; i >= 0; i--) {
      heapify(a, n, i);
    }
  }
}
void deleteNode(string a[],int &n, string data) {
 int i;
 for ( i = 0; i < n; i++){
    if (data == a[i])
      break;
  }
  swap(a[i], a[n - 1]);

  n--;
  for (int i = n / 2 - 1; i >= 0; i--){
    heapify(a, n, i);
  }
}
void printArray(int a[], int n)
{
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << "\n";
}

void print(string a[],int n,int i, string indent, bool last){
  if(i < n){
    cout<<indent;
    if(last){
      indent += "|    ";
      cout<<"L----";
    }
    else{
      indent += "    ";
      cout<<"R----";
    }
  cout<<a[i]<<endl;
  print(a,n,i*2 +1,indent,true);
  print(a,n,i*2 +2,indent,false);
}

}

int main()
{
 int n = 0;
 string a[100] = {};
 int nn;
 string data;
 while(1){
  cout<<"1.Insert\n2.Delete\nEnter- ";
  cin>>nn;
  switch(nn){
    case 1:
      cout<<"Enter Insert...";
      cin>>data;
      insert(a, n, data);
      print(a, n, 0, "", false);
      break;
    case 2:
      cout<<"Enter Delete...";
      cin>>data;
      deleteNode(a, n, data);
      print(a, n, 0, "", false);
      break;
    default:
      cout<<"Wrong Input";
  }
 } 
}