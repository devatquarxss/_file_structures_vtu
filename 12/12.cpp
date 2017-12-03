#include <iostream>
#include<fstream>

using namespace std;

class student{
public:
    string usn, name, sem;
    void insert();
    void pack();
    void unpack();
    void disp();
}temp;

struct node{
    int data;
    node * next;
};

node * n; //new
node * h = nullptr; //head
node * t; //temp

fstream fp;

void del();
void del2(int);
void dispAllRec();
void createIndex();
void createLinkList(int);

void student :: insert(){
    cout << "usn: ";
    cin >> usn;
    cout << "name: ";
    cin >> name;
    cout << "sem: ";
    cin >> sem;
}

void student :: pack(){
    string b = usn + "|" + name + "|" + sem + "|" ;
    if(b.length() > 45){
        cout << "rec len err !" <<endl;
        return;
    }
    while(b.length() <= 45)
        b += '_';

    if(h==nullptr){
        fp.open("12.txt", ios::out | ios::app);
        if(!fp)
            cout << "fp err" <<endl;
        fp << b << endl;
        fp.close();
    }else{
        fp.open("12.txt", ios::out | ios::in);
        if(!fp)
            cout << "fp err" <<endl;

        //
        int p = h->data;
        h = h->next;

        //
        fp.seekg(p,ios::beg);

        //
        fp << b << endl;

        fp.close();
    }
}

void del(){
    cout << "usn : ";
    string usn_s;
    cin >> usn_s;

    fp.open("12.txt", ios::in);
    if(!fp)
        cout << "fp err" <<endl;

    int f=0;
    int p;
    while(fp){
        string r;
        p = fp.tellg(); //***** before unpacking => take pos
        temp.unpack();
        if(temp.usn == usn_s){
            f=1;
            temp.disp();
            break;
        }
    }

    fp.close();

    if(f==0)
        cout << "not found !" <<endl;
    else
        del2(p);
}

void del2(int p){
    fp.open("12.txt",ios::out | ios::in);
    if(!fp)
        cout << "fp err" <<endl;

    fp.seekg(p, ios::beg);
    fp.put('*');

    fp.close();

    //create linklist
    createLinkList(p);
}

void createLinkList(int p){
    //create linklist
    if(h == nullptr){
        n = new node;
        n->data = p;
        n->next = nullptr;
        h = n; //
        t = n;
    }else{
        n = new node;
        n->data = p;
        n->next = nullptr;
        t->next = n; //
        t = n;
    }
}

void createIndex(){
    fp.open("12.txt", ios::in);

    while(fp){
        int p = fp.tellg();

        temp.unpack();

        //create linklist
        if(temp.usn[0] == '*'){
            createLinkList(p);
        }
    }

    fp.close();
}

void dispAllRec(){
    fp.open("12.txt", ios::in);

    while(fp){
        temp.unpack();
        if(temp.usn.length() < 3 || temp.usn[0] == '*')
            continue;
        temp.disp();
    }

    fp.close();
}

void student :: disp(){
    cout << usn << "|" <<name << "|" <<sem << endl;
}

void student ::unpack() {
    string r;
    getline(fp, usn , '|');
    getline(fp, name, '|');
    getline(fp, sem , '|');
    getline(fp, r);
}

int main(){
    fp.open("12.txt", ios::out | ios::app);
    if(!fp)
        cout << "fp err" <<endl;
    fp.close();

    createIndex();

    while(1){
        cout << "1.insert | 2.del | 3.disp | 4.exit : ";
        int ch;
        cin >> ch;
        switch(ch){
            case 1:
                temp.insert();
                temp.pack();
                break;
            case 2:del();
                break;
            case 3:
                dispAllRec();
                break;
            default: exit(0);
        }
    }

    return 0;
}
