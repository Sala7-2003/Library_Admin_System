#include <bits/stdc++.h>
#define ll long long
using namespace std;


static int counter_user = 0;
static int counter_book = 0;
static int auto_book_id = 200200;

const int Max_books = 20;
const int Max_users = 20;

struct user
{
    string name ="";
    ll id = 0;
    // Max 5 books to borrow for each user
    string borrowed[5] = {""};
    int No_of_borrowed = 0;

};


struct book
{

    user borrower;
    string name ="";
    ll id = auto_book_id ++;
    int quantity = 0,borrowed = 0;


    bool has_prefix(string prefix) {
		if (name.size() < prefix.size())
			return false;

		for (int i = 0; i < (int) prefix.size(); ++i) {
			if (prefix[i] != name[i])
				return false;
		}
		return true;
	}

};

bool sort_id (book &first, book &next)
{
    return first.id < next.id;
}


bool sort_name (book &first, book &next)
{
    return first.name < next.name;
}

user users[Max_users];
book books[Max_books];

struct Library_system
{

    void system_run()
    {

        int choice ;
        cout << "Enter a choice from 1 to 10 :\n";
        cout <<"1- Add book\n2- Search books\n3- Print the people who borrowed a certain book\n4- Print books sorted by id\n";
        cout <<"5- Print books sorted by name\n6- Add user\n7- Borrow a book for a user\n8- Return a book for a user\n";
        cout << "9- Print Usres\n10- Exit\n";
        cin >> choice ;
        if (choice <0 || choice > 10)
            cout << "Please enter a valid choice ( 0 - 10 )\n";
        else if (choice == 1)
            AddBook();
        else if (choice == 2)
            SearchBooks();
        else if (choice == 3)
            Print_people_who_borrowed();
        else if (choice == 4)
            Print_by_Id();
        else if (choice ==5)
            Print_by_name();
        else if (choice ==6)
            AddUser();
        else if (choice ==7)
            Borrow_book();
        else if (choice ==8)
            Return_book();
        else if (choice ==9)
            PrintUsers();
        else exit(0);
    }

    void AddBook()
    {
        cout << "Enter book name:\n";
        cin >> books[counter_book].name;
        cout << "Enter book quantity:\n";
        cin >> books[counter_book].quantity;
        counter_book++;
    }

    void SearchBooks()
    {
        string prefix;
        int flag = 0;
        cout << "Enter the prefix of the book you are searching for :\n";
        cin >> prefix;
        for (int i = 0 ; i < counter_book; i++)
        {
            if (books[i].has_prefix(prefix))
            {
                cout << books[i].name << " and its id : " <<books[i].id <<"\n";
                flag = 10000 ;
            }
        }
        if (flag == 0)
            cout << "Sorry , no book is found with that prefix !\n";
    }

    void Print_people_who_borrowed()
    {
        if (counter_user==0){
            cout << "No users added yet !\n";
            return ;
        }

        string book_;
        int flag = 0 ;
        cout << "Enter the book name :\n";
        cin >> book_;

        for (int i = 0 ; i < counter_user ; i++)
        {
            for (int j = 0 ; j < users[i].No_of_borrowed; j++)
            {
                if (users[i].borrowed[j] == book_)
                {
                    cout << users[i].name << "\n";
                    flag = 10000;
                    break;
                }
            }
        }

        if (flag == 0)
            cout << "No user borrowed this book yet !\n" ;
    }

    void AddUser()
    {
        string n;
        ll i_d;
        cout << "Enter name:\n";
        string s = " ";
        getline(cin, s);
        getline(cin, n);
        users[counter_user].name = n;
        cout << "Enter your national id:\n";
        cin >> i_d;
        users[counter_user].id = i_d;
        users [counter_user++];

    }

    void Print_by_Id()
    {
        sort(books,books+counter_book,sort_id);

        for (int i = 0; i < counter_book ; i++)
        {
            cout << "id = " << books[i].id << " name = " <<books[i].name << " total_quantity "
                 << books[i].quantity<< " total_borrowed " << books[i].borrowed
                 << "\n";
        }
    }

    void Print_by_name()
    {
        sort(books,books+counter_book,sort_name);

        for (int i = 0; i < counter_book ; i++)
        {
            cout << "id = " << books[i].id << " name = " <<books[i].name << " total_quantity "
                 << books[i].quantity<< " total_borrowed " << books[i].borrowed
                 << "\n";
        }
    }


    void Borrow_book()
    {
        string user_, book_ ;
        int flag1=0, flag2=0,flag3 = 0;
        cout << "Enter the user you want to borrow for :\n";
        string s = " ";
        getline(cin, s);
        getline (cin, user_);
        for (int i =0 ; i < counter_user; i++)
        {
            if (users[i].name==user_)
            {
                cout << "The user is found with national id : " << users[i].id << "\n";
                flag1 = 1000;
                flag3 = i ;
                break;
            }
        }
        if (flag1 == 0){
            cout << "sorry , there is no user found with that name !\n";
            return ;
        }
        if (users[flag3].No_of_borrowed==4){
            cout << "Sorry , you reached the maximum number of borrowed books\n ";
            return ;
        }
        else
        {
            flag1 = 0;
            cout << "Enter the book you want to borrow \n";
            cin >> book_;
            for (int i =0 ; i < counter_user; i++)
            {
                if (books[i].name==book_)
                {
                    if (books[i].quantity==0)
                    {
                        cout << "Sorry , no available copies of that book ritght now !\n";
                        break;
                    }

                    books[i].quantity-=1;
                    books[i].borrowed +=1;
                    flag2 = users[i].No_of_borrowed;
                    users[i].borrowed[flag2] = book_;
                    users[i].No_of_borrowed+=1;

                }

            }
        }
    }

    void PrintUsers()
    {
        if (counter_user == 0)
        {
            cout << "No users added yet !\n";
            return ;
        }
        for (int i = 0 ; i < counter_user ; i++)
        {
            cout << users[i].name << " and he/she borrowed " << users[i].No_of_borrowed << "  book(s)\n";
        }
    }


    void Return_book()
    {

        string user_, book_ ;
        int flag1=0, flag2=0,flag3 = 0;
        cout << "Enter the user you want to return the book from :\n";
        string s = " ";
        getline(cin, s);
        getline (cin, user_);
        for (int i =0 ; i < counter_user; i++)
        {
            if (users[i].name==user_)
            {
                cout << "The user is found with national id : " << users[i].id << "\n";
                flag1 = 1000;
                flag3 = i ;
                break;
            }
        }

        if (flag1 == 0){
            cout << "sorry , there is no user found with that name !\n";
            return ;
        }

        else
        {

            cout << "Enter the book you want to return \n";
            cin >> book_;
            for (int i =0 ; i < counter_user; i++)
            {
                if (books[i].name==book_)
                {

                    books[i].quantity++;
                    books[i].borrowed--;
                    flag2 = users[i].No_of_borrowed;
                    for (int j = i ; j <  flag2 ; j++)
                    {
                        users[flag3].borrowed[j]= users[flag3].borrowed[j+1];
                    }
                    users[i].No_of_borrowed--;
                }
            }
        }
    }
};


int main ()
{
    cout << "Welcome to our library !\nHow can I help u :) ?\n";
    while (true)
    {
        Library_system a;
        a.system_run();

    }
    return 0 ;
}