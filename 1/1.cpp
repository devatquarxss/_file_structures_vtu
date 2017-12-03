//
// Created by Shivam Singh on 01/12/17.
//

#include <iostream>
#include<algorithm>
#include <fstream>
using namespace std;

void stdInpOut(){
    cout << "stdInpOut" << endl;

    cout << "n: ";
    int n ;
    cin >> n;

    string a[n];
    for(int i=0; i<n; i++){
        cin >> a[i];
        reverse(a[i].begin(), a[i].end());
        cout << a[i] << endl;
    }
}

void file(){
    cout << "file" << endl;

    string inpFn, outFn ;
    cout<< "inp fn: ";
    cin >> inpFn;
    cout << "out fn: ";
    cin >> outFn;

    //
    fstream inpFp, outFp;
    inpFp.open(inpFn, ios::in);
    outFp.open(outFn, ios::out);

    //
    if(!inpFp || !outFp){
        cout << "fp error !" << endl;
    }

    //
    string name;
    while(inpFp){
        getline(inpFp, name);
        reverse(name.begin(), name.end());
        outFp << name << endl;
    }
}

int main(){
    cout << "Hello World !" << endl;

    while(1){
        cout << "1.stdInpOut | 2.file | 3.exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1: stdInpOut();
                    break;
            case 2: file();
                    break;
            case 3: exit(0);
        }
    }

    return 0;
}