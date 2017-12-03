//
// Created by Shivam Singh on 03/12/17.
//

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

fstream fp;

string arr[100];
int arrCnt = 0;


void getData(string, int, int);

void getData(string fName){
    fp.open(fName, ios::in);

    while(fp){
        string r;
        getline(fp, r);
        if(r.length() == 0)
            continue;
        arr[arrCnt] = r;
        arrCnt++;
    }

    fp.close();
}

int main(){

    getData("7a.txt");
    getData("7b.txt");

    sort(arr, arr + arrCnt);

    string r = "someRandomStr";
    for(int i=0; i<arrCnt; i++) {
        if (arr[i] == arr[i + 1]) {
            if (r != arr[i]) {
                cout << arr[i] << endl;
                r = arr[i];
            }
        }
    }

    return 0;
}
