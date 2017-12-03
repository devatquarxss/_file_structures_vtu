//
// Created by Shivam Singh on 02/12/17.
//

#include <iostream>
#include<fstream>

using namespace std;

class student{
    public:
        string usn, name, sem;
        void getData();
        void pack();
        void unpack();
        void mod();
        void disp();
}s[100],temp;

fstream fp;

void getFileData();
void error(int);
void display(int);
void search(int);

void student :: getData(){
    cout << "usn: " ;
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

void error(int errNo){
    switch(errNo){
        case 1: cout << "fp error !" << endl;
                break;
    }
}

void student :: pack(){
    string buf = usn + "|" + name + "|" + sem + "|";
    fp << buf << endl;
}

void getFileData(int ch){
    fp.open("3.txt",ios::in);

    int i = 0;
    while(fp){
        s[i].unpack();
        i++;
    }

    fp.close();

    switch (ch){
        case 2: search(i-1);
                break;
        case 3: display(i-1);
                break;
    }
}

void search(int c){
    cout << "usn: " ;
    string usn_s;
    cin >> usn_s;

    int sf = -1;
    for(int i=0; i<c; i++){
        if(s[i].usn == usn_s){
            sf = i;
            break;
        }
    }

    if(sf==-1)
        cout <<"not found !" <<endl;
    else{
        cout <<"1.Mod 2.not mod : ";
        int modCh;
        cin >> modCh;

        if(modCh == 1){
            s[sf].mod();
            fp.open("3.txt",ios::out);

            for(int i=0; i<c; i++){
                s[i].pack();
            }

            fp.close();
        }else
            return;

    }

}

void student :: mod(){
    while(1){
        cout << "1.usn | 2.name | 3.sem | 4.exit : ";
        int ch;
        cin >> ch;
        switch (ch){
            case 1: cout << "usn: ";
                    cin >> usn;
                break;
            case 2: cout << "name: ";
                    cin >> name;
                break;
            case 3: cout << "sem : ";
                    cin >> sem;
                break;
            default:return;
        }
    }
}

void display(int c){
    for(int i=0; i<c ; i++){
        s[i].disp();
    }
}

void student :: disp(){
    cout << usn << "|" << name << "|" << sem << endl;
}

void student :: unpack(){
    string r;
    getline(fp, usn, '|');
    getline(fp, name, '|');
    getline(fp, sem, '|');
    getline(fp, r);
}

int main(){

    while(1){
        cout <<"1.insert | 2.search | 3.display | 4.exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1: temp.getData();

                    fp.open("3.txt", ios::out | ios::app );
                    if(!fp)
                        error(1);

                    temp.pack();

                    fp.close();
                    break;

            case 2: getFileData(2);
                    break;

            case 3: getFileData(3);
                    break;

            default: exit(0);
        }
    }

    return 0;
}