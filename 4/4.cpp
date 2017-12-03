//
// Created by Shivam Singh on 02/12/17.
// 17120267896

#include <iostream>
#include <fstream>

using namespace std;

fstream fp;

class student{
    public:
        string usn, name, sem;
        void getData();
        void pack();
        void unpack(int);
        void display();
}temp;

int rrn[100], cnt = 0;

void search();

void student :: getData() {
    cout << "usn: ";
    cin >> usn;
    cout << "name : ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

void student :: pack(){
    string b = usn + "|" + name + "|" + sem;
    int p = fp.tellg();
    fp << b <<endl;
    rrn[cnt++] = p;
    cout << p;
}

void student :: unpack(int p){
    fp.seekg(p, ios::beg);
    getline(fp, usn, '|');
    getline(fp, name, '|');
    getline(fp, sem, '|');
}

void search(){
    cout << "rrn: ";
    int rrn_s;
    cin >> rrn_s;

    if(rrn_s >= cnt || rrn_s < 0){
        cout << "No !";
        return;
    }

    int p = rrn[rrn_s];

    //
    fp.open("0.txt",ios::in);
    if(!fp)
        cout << "fp err !" << endl;

    temp.unpack(p);

    fp.close();
    temp.display();
}

void student :: display(){
    cout << usn << "|" << name << "|" << sem;
}

void createIndex(){
    fp.open("0.txt", ios::in);

    cnt = 0;
    while(fp){
        string r;
        int p = fp.tellg();
        getline(fp, r);
        if(r.length() == 0){
            break;
        }
        rrn[cnt] = p;
        cout << r << " " << rrn[cnt] << " " << cnt << endl;
        cnt++;
    }

    fp.close();
}

int main(){
    createIndex();
    while(1){
        cout << "1.insert | 2.search | 3.exit : ";
        int ch ;
        cin >> ch;
        switch (ch){
            case 1:
                temp.getData();
                fp.open("0.txt", ios::out | ios::app);
                if(!fp)
                    cout << "fp err !" <<endl;

                temp.pack();

                fp.close();
                break;
            case 2:
                search();
                break;
            default: exit(0);
        }
    }
    return 0;
}
