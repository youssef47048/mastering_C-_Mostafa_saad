#include <bits/stdc++.h>

using namespace std;
map<int,deque<string> >m;
void add(){
    cout<<"Enter specialization, name, status:  ";
    bool status;
    int num;
    string name;
    cin >> num>>name>>status;
    if(status)
        m[num].push_front(name);
    else
        m[num].push_back(name);

}
void print(){
    map<int,deque<string> >::iterator itr;
    for(int i = 1 ;i<=20;i++){
        if((m[i].size())){
            cout<<"There are "<<m[i].size()<<" patients in specialization "<<i<<endl;
            for(int j = 0 ; j < m[i].size();j++ ){
                cout<<m[i][j]<<" \n";
            }
        }
    }
}
void get_next(){
    int num ;
    cout<<"Enter specialization \n";
    cin>>num;
    if(m[num].size()>5){
        cout<<"No patients at the moment, Have rest, Dr\n";
    }else {
        cout<<m[num].front()<<" go with the doctor\n";
        m[num].pop_front();
    }
}
int main()
{
    int n;
    do{
       cout<< "Enter your choice\n";
       cout<< "1) Add new patient\n";
       cout<<"2) Print all patients\n";
       cout<<"3) Get next patient\n";
        cout<<"4) Exit\n";
        m:cin >>n;
        switch(n){
        case 1:
            add();
            break;
        case 2:
           print();
            break;
        case 3:
            get_next();
            break;
         case 4:
             return 0;
      //i could not make it to reiterate.
            cout<<"unvalid number\n";

        }
    }while(n>=1&&n<=4);
    return 0;
}
