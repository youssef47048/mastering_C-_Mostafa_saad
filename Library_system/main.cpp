#include <bits/stdc++.h>
#define line "\n"
#define Max 1000
using namespace std;
struct Book
{
    string  book_name;
    int book_id;
    int total_borrowed;
    int total_quantity;

    Book(int _book_id, string _book_name,int _quantity)
    {
        book_id = _book_id;
        book_name = _book_name;
        total_quantity = _quantity;

    }
    bool search_prefix(string prefix){
        if((int)book_name.size()<prefix.size())return false;
        for(int i = 0 ; i < (int)prefix.size(); i++){
            if(prefix[i]!= book_name[i])return false;
        }return true;

    }
   bool borrow() {
		if (total_quantity - total_borrowed == 0)
			return false;
		++total_borrowed;
		return true;
	}
	void return_copy() {
		assert(total_borrowed > 0);
		--total_borrowed;
	}

};
struct User
{
    string user_name;
    int user_id , len  ;
    int borrowed_books_ids[Max] ;

    User()
    {
        user_name  = "no user name";
        user_id = -1;
        len = 0;
    }
    User(string _user_name, int _user_id)
    {
        user_name = _user_name;
        user_id = _user_id;
    }
    bool is_borrowed(int book_id) {
		for (int i = 0; i < len; ++i) {
			if (book_id == borrowed_books_ids[i])
				return true;
		}
		return false;
	}
	void borrow(int book_id) {
		borrowed_books_ids[len++] = book_id;
	}


	void return_copy(int book_id) {
		bool removed = false;
		for (int i = 0; i < len; ++i) {
			if (borrowed_books_ids[i] == book_id) {
				// Let's shift the array to the right to remove this entry
				for (int j = i + 1; j < len; ++j)
					borrowed_books_ids[j - 1] = borrowed_books_ids[j];
				removed = true;
				--len;
				break;
			}
		}
		if (!removed)
			cout << "User " << user_name << " never borrowed book id " << book_id
					<< "\n";
	}




};
bool cmp_id(Book &a , Book &b){

return a.book_id < b.book_id;
}
bool cmp_name(Book &a , Book &b){

return a.book_name<b.book_name;
}
struct Admin
{
    vector<Book>books;

    vector<User> user;
int total_books;
    int run()
    {
        cout<<"Library Menu:\n";
        cout<<" 1) add book\n 2) search books by prefix\n 3) print who borrowed book by name\n 4) print library by id\n 5) print library by name\n 6) add user\n 7) user borrow book\n 8) user return book\n 9) print users \n 10) exit\n";
        cout<<"Enter your menu choice [1 - 10]:\n";

        int choice = -1;
        while(choice == -1)
        {
            cin>> choice;
            if(!(choice>=1&&choice <= 10))
        {
            cout<<"Invalid Input: try again\n";
            choice = -1;
        }
    }
    return choice;
}
void menu()
    {
        while (true)
        {
            int choice = run();

            switch(choice)
            {
            case 1:
                add_book();
                break;
            case 2: search_book();
                    break;
            case 3: who_borrowed_book_name();
                    break;
           case 4: print_lib_name();
                    break;
            case 5:print_lib_id();
                    break;

            case 6: add_user();
                    break;
            case 7: user_borrow_book();
                    break;
            case 8: user_return_book();
                    break;
            case 9: print_users();
                    break;
          case 10: return;

            }
        }
    }
    bool valid_book_id(int book_id,string book_name){
        vector<Book>::iterator itr1,itr2;
        for(int i = 0 ; i < (int)books.size(); i++){
            if(books[i].book_id == book_id)return false;
            if(books[i].book_name == book_name)return false ;

        }
        return true;
    }
    void add_book()
    {
        string  book_name;
        int quantity , book_id;
        cout<<"Enter book info: ID [0-999] & NAME & QUANTITY: \n";
        cin >> book_id>>book_name>>quantity;
        if(valid_book_id(book_id,book_name)){
        Book add = Book(book_id, book_name,quantity );
        books.push_back(add);
        }else{
            cout<<"Already exist!"<<line;
        }
    }
    void search_book()
    {
        string prefix;
        cout<<"Enter Book name prefix:\n";
        cin>>prefix;
        bool state;
        int cnt = 0;
        for(int i = 0 ; i < books.size() ; i++){
            state = books[i].search_prefix(prefix);
            if(state){
                cout<<books[i].book_name<<line;
                ++cnt;
            }

        }
        if(!cnt)cout<<"Not found"<<line;

    }
    void print_lib_id(){
        sort(books.begin(),books.end(),cmp_id);
        for(int i = 0 ; i < books.size(); i++){
            cout<<"name: "<<books[i].book_name<<"   id: "<<books[i].book_id<<"  quantity: "<<books[i].total_quantity<<"   total_borrowed: "<<books[i].total_borrowed<<line;
        }
    }
    void print_lib_name(){
        sort(books.begin(),books.end(),cmp_name);
        for(int i = 0 ; i < books.size(); i++){
            cout<<"name: "<<books[i].book_name<<"   id: "<<books[i].book_id<<"  quantity: "<<books[i].total_quantity<<"   total_borrowed: "<<books[i].total_borrowed<<line;
        }
    }
    void add_user(){
        cout<<"Enter user name and NATIONAL ID"<<line;
        string user_name;
        int user_id;
        cin>>user_name>>user_id;
        User add = User(user_name , user_id);
        if(valid_user(add))user.push_back(add);
        else cout<<"User ALREADY exist"<<line;
    }
    bool valid_user(User &a){
        for(int i = 0 ; i < user.size() ; i++){
            if(a.user_id == user[i].user_id)return false;
        }
        return true;
    }


    void  user_borrow_book(){
        cout<<"Enter user name and book name"<<line;
        string user_name , book_name;
        cin>>user_name>>book_name;
        int user_idx = find_user_idx_by_name(user_name);
        int book_idx = find_book_idx_by_name(book_name);
        if(user_idx == -1){
            cout<<"invalid user name"<<line;
            return;
        }
        if(book_idx == -1){
            cout<<"invalid book name"<<line;
            return;
        }
        if(books[book_idx].borrow()){
            user[user_idx].borrow(books[book_idx].book_id);
        }else{
            cout<<"there is no enough copies of that book"<<line;
            return;
        }

    }

    void user_return_book(){
        cout<<"Enter user name and book name"<<line;
        string user_name , book_name;
        cin>>user_name>>book_name;
        int user_idx = find_user_idx_by_name(user_name);
        int book_idx = find_book_idx_by_name(book_name);

        books[book_idx].return_copy();
        user[user_idx].return_copy(books[book_idx].book_id);
    }


     void who_borrowed_book_name(){
        string book_name;
        cout<<"ENTER THE BOOK NAME"<<line;
        cin>>book_name;
        int book_idx = find_book_idx_by_name(book_name);
        if(book_idx == -1){
            cout << "Invalid book name.\n";
			return;
        }
        int book_id = books[book_idx].book_id;

        if (books[book_idx].total_borrowed == 0) {
			cout << "No borrowed copies\n";
			return;
		}
		for(int i = 0 ; i < user.size();i++){
            if(user[i].is_borrowed(book_id))
                cout << user[i].user_name << "\n";
		}


     }
     int find_book_idx_by_name(string name){
        for(int i = 0 ; i < books.size() ; i++){
            if(name == books[i].book_name) return i;
        }
        return -1;
     }int find_user_idx_by_name(string name) {
		for (int i = 0; i < user.size(); ++i) {
			if (name == user[i].user_name)
				return i;
		}
		return -1;
	}
     void print_users(){
        for(int i =  0 ; i < user.size();i++){
            cout<<"User "<<user[i].user_name<<" id "<<user[i].user_id;
            cout<< " borrowed books ";
            for(int j = 0 ; j < user[i].len;j++)cout<<   user[i].borrowed_books_ids[j]<<" ";
            cout<<line;
        }
     }
};
int main(){
    Admin start;
    start.menu();
    return 0;
}
