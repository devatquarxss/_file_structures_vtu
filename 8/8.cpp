//
// Created by Shivam Singh on 03/12/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

fstream fp;

string newArr[100];
int newArrCnt=0;

void getData(string, int, int);

void getData(string fName){
    fp.open(fName, ios::in);

    while(fp){
        string r;
        getline(fp, r);
        if(r.length() == 0)
            continue;
        newArr[newArrCnt] = r;
        newArrCnt++;
    }

    fp.close();
}


int main(){

    for(int i=0; i<4 ; i++) { //8 for 8 files
        string fName = to_string(i) + ".txt";
        getData(fName);
    }

    sort(newArr, newArr + newArrCnt);

    //
    fp.open("res.txt", ios::out);

    string r = "junkStr";
    for(int i=0; i<newArrCnt ;i++){
        //common names
        if(newArr[i] == newArr[i+1]){
            if(r != newArr[i]) {
                cout << newArr[i] << endl;
                fp << newArr[i] << endl;
                //update r
                r = newArr[i];
            }
        }else{
            if(r != newArr[i]) {
                cout << newArr[i] << endl;
                fp << newArr[i] << endl;
            }
        }
    }

    fp.close();

    return 0;
}
