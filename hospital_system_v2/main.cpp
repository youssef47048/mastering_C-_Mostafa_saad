#include <iostream>

using namespace std;
const int MAX_QU = 5;
const int MAX_SP = 20;
struct hospital_queue
{
    string names[MAX_QU];
    int status[MAX_QU];
    int len;
    int spec;

    hospital_queue()
    {
        len = 0;
        spec = -1;
    } hospital_queue(int _spec)
    {
        len = 0;
        spec = _spec;
    }
    bool add_end(string name, int st)
    {
        if(len >= MAX_QU)return false;
        names[len] = name ;
        status[len] = st;
        ++len;
        return true;
    } bool add_front(string name, int st)
    {
        if(len >= MAX_QU)return false;

        for(int i = len-1 ; i >= 0 ; i-- )
        {
            names[i+1] = names[i];
            status[i+1] = status[i];
        }
        names[0] = name ;
        status[0] = st ;
        len++;
        return true;

    } void remove_front()
    {
        if (len == 0)
        {
            cout << "No patients at the moment. Have rest, Dr\n";
            return;
        }
        cout << names[0] << " please go with the Dr\n";
        for(int i = 1 ; i<len ; i++ )
        {
            names[i-1] = names[i];
            status[i-1] = status[i];
        }
        len--;

    }
    void print()
    {
        if (len == 0)
            return;

        cout << "There are " << len << " patients in specialization " << spec << "\n";
        for (int i = 0; i < len; ++i)
        {
            cout << names[i] << " ";
            if (status[i])
                cout << "urgent\n";
            else
                cout << "regular\n";
        }
        cout << "\n";

    }

};
struct hospital_system
{
    hospital_queue queues[MAX_SP];
    hospital_system()
    {
        for(int i = 0 ; i < MAX_SP; i++)
        {
            queues[i] = hospital_queue(i);
        }
    }
    void run()
    {
        while(true)
        {
            int choise = menu();
            if(choise == 1 )add_patient();
            else if(choise == 2)print_patient();
            else if(choise == 3 )get_next();
            else break;
        }

    }
    bool add_patient(){
        string name;
        int spec, st;
        cout << "Enter specialization, name, status: ";
		cin >> spec >> name >> st;
		bool status;
		if(st == 0)
            status = queues[spec].add_end(name,st);
        else
             status = queues[spec].add_front(name,st);
        if(!status){
            cout<< "Sorry we can't add more patients for this specialization\n";
			return false;
        }
        return true;
    }
    void get_next(){
        int spec;
        cout << "Enter specialization: ";
		cin >> spec;
		queues[spec].remove_front();
    }
    void print_patient(){
        cout << "****************************\n";
		for (int i = 0; i < MAX_SP; ++i)
			queues[i].print();
    }
    int menu()
    {
        int choise = -1;
        while(choise == -1)
        {
            cout << "\nEnter your choice:\n";
            cout << "1) Add new patient\n";
            cout << "2) Print all patients\n";
            cout << "3) Get next patient\n";
            cout << "4) Exit\n";

            cin >> choise;
            if(!(choise>=1&&choise<=4))
            {
                cout << "Invalid choice. Try again\n";
                choise = -1;
            }

        }
        return choise;
    }

};
int main()
{
    hospital_system hospital = hospital_system();
    hospital.run();
    return 0;
}
