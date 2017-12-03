//
// Created by Shivam Singh on 03/12/17.
//

#include <iostream>
#include <fstream>

using namespace std;

class student{
    public:
        string usn, name, sem;
        void insert();
        void pack();
        void unpack();
        void disp();
}temp;

fstream fp;
int hashing(string);
void getRec();

void student :: insert() {
    cout << "usn: ";
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

void student :: pack(){
    string b = usn + "|" + name + "|" + sem + "|";
    if(b.length() > 45){
        cout << "rec len err !" << endl;
        return;
    }
    while(b.length()<=45)
        b+='_';

    int p = hashing(usn);
    fp.open("11.txt",ios::in);
    fp.seekg(p,ios::beg);
    string r;
    getline(fp,r);
    fp.close();

    int c = r[0] - 48;
    fp.open("11.txt",ios::out| ios::in);
    fp.seekg(p,ios::beg);
    if(c<0){
        fp.put('1');
        p=p+1;
    }else if(c==1){
        fp.put('2');
        p=p+48;
    }else if(c==2){
        cout << "hash err !";
        fp.close();
        return;
    }
    fp.seekg(p,ios::beg);
    fp << b << endl;
    fp.close();

    cout << "p => " << p << endl;
}

int hashing(string usn){
    int t = ( (usn[0]-48)*100 + (usn[1]*10) + usn[2] )%9;
    return t*142;
}

void student ::unpack() {
    string r;
    getline(fp, usn, '|');
    getline(fp, name , '|');
    getline(fp, sem , '|');
    getline(fp,r);
}

void student :: disp(){
    cout << usn << "|" << name << "|" << sem << endl;
}

void getRec(){
    cout << "usn: ";
    string usn_s;
    cin >> usn_s ;

    int p = hashing(usn_s);
    fp.open("11.txt", ios::in);
    fp.seekg(p, ios::beg);
    string r;
    getline(fp, r);
    int c = r[0] - 48;
    fp.seekg(p+1, ios::beg);
    int f =0;
    for(int i=0; i<c; i++){
        temp.unpack();
        if(temp.usn == usn_s) {
            temp.disp();
            f=1;
        }
    }
    if(f==0)
        cout << "not found !" <<endl;
    fp.close();
}

int main(){
    //
    fp.open("11.txt", ios::out | ios::app);
    fp.close();

    while(1){
        cout << "1.Insert | 2.Retriev | 3. Exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1:
                temp.insert();

                //fp.open("11.txt", ios::out | ios::in);
                if(!fp)
                    cout << "fp err !" << endl;

                temp.pack();

                //fp.close();
                break;
            case 2:getRec();
                break;
            default:exit(0);
        }
    }
    return 0;
}