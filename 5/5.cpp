//
// Created by Shivam Singh on 02/12/17.
//

#include <iostream>
#include<fstream>

using namespace std;

class student {
    public:
        string usn, name , sem;
        void getData();
        void pack();
        void unpack(int);
        void disp();
}temp;

struct{
    int p;
    string usn;
}i1[100];
int cnt = 0;

fstream fp;

void search();
int searchIndex(string);
void getIndex();
void del(int);

void getIndex(){
    //cout << "getting index.." <<endl;
    fp.open("5.txt", ios::in);
    if(!fp)
        cout << "fp err !" <<endl;

    cnt = 0;
    while(fp){
        int p = fp.tellg();
        //cout << p ;
        temp.unpack(p);
        //cout << temp.usn.length() <<endl;
        if(temp.usn.length() < 3 || temp.usn[0] == '*')
            continue;
        i1[cnt].p = p;
        i1[cnt].usn = temp.usn;
        cout << i1[cnt].p << " => " << i1[cnt].usn << endl;
        cnt++;
    }

    fp.close();
}

void student :: getData(){
    cout << "usn: " ;
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

void student :: pack(){
    string b = usn + "|" + name + "|" + sem + "|";
    int p = fp.tellg();
    fp << b << endl;
    i1[cnt].p = p;
    //cout << "p==> " << p;
    i1[cnt].usn = usn;
    cnt++;
}

void search(int ch){
    cout << "usn: " ;
    string usn_s;
    cin >> usn_s;

    int r = searchIndex(usn_s);
    if(r == -1)
        cout << "not found !" << endl;
    else{
        int p = i1[r].p;

        fp.open("5.txt",ios::in);
        if(!fp)
            cout << "fp error";

        temp.unpack(p);

        fp.close();
        temp.disp();

        //del
        if(ch == 1)
            del(p);
    }
}

void del(int p){
    cout << "deleting...";
    fp.open("5.txt", ios::out | ios::in); //permission

    fp.seekg(p, ios::beg);
    fp << "*" ;

    fp.close();
}

void student :: disp(){
    cout << usn << "|" << name << "|" << sem << endl;
}

void student ::unpack(int p){
    //cout << "p: " << p <<endl;
    string r;
    fp.seekg(p, ios::beg);
    getline(fp, usn , '|');
    getline(fp, name, '|');
    getline(fp, sem, '|');
    getline(fp,r);
}

int searchIndex(string usn_s){
    for(int i=0; i<cnt; i++){
        //cout << i << endl;
        if(usn_s == i1[i].usn){
            //cout << "index: " << i << endl;
            return i;
        }
    }
    return -1;
}

int main(){
    getIndex();
    while(1){
        cout << "1.insert | 2.search | 3.del | 4.exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1:
                temp.getData();

                fp.open("5.txt", ios::out | ios::app );
                if(!fp)
                    cout << "fp error !";

                temp.pack();

                fp.close();
                break;

            case 2: search(0);
                break;
            case 3: search(1);
                break;
            default:
                exit(0);
        }
    }
    return 0;
}
