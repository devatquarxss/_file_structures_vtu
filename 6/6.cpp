//
// Created by Shivam Singh on 03/12/17.
//

#include <iostream>
#include <fstream>

using namespace std;

class student{
    public:
        string usn, name, sem;
        void getInput();
        void pack();
        void unpack(int);
        void disp();

}temp;

struct {
    int p ;
    string name;
    string usn;
}i1[100];
int cnt = 0;

fstream fp;

void search();
void getIndex();
void del(int);


void student :: pack(){
    string b = usn + "|" + name + "|" + sem + "|";
    int p = fp.tellg();
    fp << b <<endl;
    i1[cnt].p =  p;
    i1[cnt].usn = usn;
    i1[cnt].name = name;
}

void student :: disp(){
    cout << usn << "|" << name << "|" << sem << endl;
}

void search(int ch){
    cout << "name: ";
    string name;
    cin >> name;

    int sf = -1;

    //loop in index
    for(int i=0; i<cnt; i++){
        if(i1[i].name == name){
            sf = i;
            break;
        }
    }

    if(sf == -1)
        cout << "not found !" <<endl;
    else{
        fp.open("6.txt", ios::in);
        if(!fp)
            cout << "fp err !" <<endl;

        temp.unpack(i1[sf].p);

        fp.close();
        temp.disp();

        if(ch == 1)
            del(i1[sf].p);
    }
}

void student ::unpack(int p) {
    string r;
    fp.seekg(p,ios::beg);
    getline(fp, usn , '|');
    getline(fp, name, '|');
    getline(fp, sem , '|');
    getline(fp,r);
}

void getIndex(){
    fp.open("6.txt", ios::in);
    if(!fp)
        cout << "fp err!" <<endl;

    cnt = 0;
    while(fp){
        int p = fp.tellg();
        temp.unpack(p);
        if(temp.usn.length() < 3 || temp.usn[0] == '*')
            continue;
        i1[cnt].p = p;
        i1[cnt].usn = temp.usn;
        i1[cnt].name = temp.name;
        cout << i1[cnt].p << " => " << i1[cnt].usn << " => " << i1[cnt].name << endl;
        cnt++;
    }

    fp.close();
}

void del(int p){
    cout << "del..."<<endl;
    fp.open("6.txt", ios::out | ios::in);

    fp.seekg(p,ios::beg);
    fp << '*';

    fp.close();
}

void student ::getInput() {
    cout << "usn : ";
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

int main(){
    getIndex();
    while(1){
        cout << "1.insert | 2.search | 3.del | 4.exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1:temp.getInput();
                    fp.open("6.txt", ios::out | ios::app);
                    if(!fp)
                        cout << "fp err !" << endl;

                    temp.pack();

                    fp.close();
                    break;
            case 2: search(0);
                    break;
            case 3: search(1);
                    break;
            default : exit(0);
        }
    }

    return 0;
}