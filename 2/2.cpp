#include<iostream>
#include <fstream>
using namespace std;

//obj
class student{
    public :
        string usn, name, sem;
        void enterData();
        void pack();
        void unpack();
        void modRec();
}s[100],temp;

fstream fp;

void error(int);
void getRecords(int);
void searchForARecord(int);
void modOpt(int,int);
void modRec();
void displayRec(int);

void student :: enterData(){
    cout << "usn: ";
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem ;
}

void student :: pack(){
    string buf = usn + "|" + name + "|" + sem + "|";
    if(buf.length() > 45){
        error(2);
        return;
    }
    while(buf.length() < 45){
        buf += '_';
    }
    fp << buf << endl;
}

void error(int errNo){
    switch(errNo){
        case 1: cout << "fp error !";
                break;
        case 2: cout << "record buf lenght exceeded !";
                break;
    }
}

void getRecords(int opt){
    fp.open("2.txt",ios::in);
    if(!fp)
        error(1);
    int i = 0;
    while(fp){
        s[i].unpack();
        i++;
    }
    fp.close();
    switch(opt){
        case 0: searchForARecord(i);
                break;
        case 1: displayRec(i);
                break;
    }
}

void searchForARecord(int c){
    cout << "enter usn to search in record : ";
    string usn_s;
    cin >> usn_s;

    int search_f = -1;
    for(int i=0; i<c; i++){
        if(s[i].usn == usn_s){
            search_f = i;
            break;
        }
    }
    modOpt(search_f, c);
}

void modOpt(int search_f, int c){
    if(search_f == -1){
        cout << "Record Not Found !";
    }else{
        cout << "1. Modify 2. No : ";
        int modCh;
        cin >> modCh;
        switch(modCh){
            case 1: s[search_f].modRec();
                    fp.open("2.txt", ios::out);
                    if(!fp)
                        error(1);
                    for(int i=0;i<c-1;i++)
                        s[i].pack();
                    fp.close();
                    break;
            case 2:
                return;
        }
    }
}

void student :: modRec() {
    while(1){
        cout << "field to modify => 1.usn | 2.name | 3.sem | 4.exit : ";
        int modF ;
        cin >> modF;
        switch(modF){
            case 1: cout << "usn: " ;
                    cin >> usn;
                    break;
            case 2:
                    cout << "name: ";
                    cin >> name;
                    break;
            case 3:
                    cout << "sem: ";
                    cin >> sem;
                    break;
            case 4:
                    return;
        }
    }
}

void student :: unpack(){
    string seg;
    getline(fp, usn, '|');
    getline(fp, name, '|');
    getline(fp, sem, '|');
    getline(fp, seg);
}

void displayRec(int c){
    for(int i=0; i<c-1; i++){
        cout << s[i].usn << endl;
        cout << s[i].name << endl;
        cout << s[i].sem << endl;
    }
}

int main(){

    while(1){
        cout << "1.Insert | 2.Search | 3.Display | 4.Exit : " << endl;
        int ch;
        cin >> ch;
        switch (ch){
            case 1:
                temp.enterData();
                fp.open("2.txt", ios::out | ios::app);
                if(!fp)
                    error(1);
                temp.pack();
                fp.close();
                break;
            case 2:
                getRecords(0);
                break;
            case 3:
                getRecords(1);
                break;
            case 4:
                exit(0);
        }
    }

    return 0;
}