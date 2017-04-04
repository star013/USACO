/*
ID: thustar1
PROG: test utility
LANG: C++11
*/

void printInts(int* a,int n){
    for (int i = 0; i < n; i++)
		cout << a[i]<< " ";
    cout<<endl;
}

void printVec(vector<int> a){
    for (int i = 0; i < a.size(); i++)
		cout << a[i]<< " ";
    cout<<endl;
}