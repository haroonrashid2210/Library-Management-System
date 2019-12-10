//Developed By:
//
//Name: Haroon Rashid
//Reg No: FA17-BCS-030
//
//Name: Abdul Muizz
//Reg No: FA17-BCS-003
//Submitted to : Dr. Inayat-ur-Rehman

//Project Name : Library Management System
//Data Structures Used: Hashing, Linked List, BST, Queues

#include <iostream>
#include <array>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>

using namespace std;
int quantity = 0;

int generateBookID(string basicString);

int generateAlphabetID(char c);

int queue_array[20];

struct BST *rack[10][5];

struct User *start = nullptr;

class Queue {
public:
    int top;

    Queue() {
        top = -1;
    }

    bool isFull() {
        return top == 19;
    }

    bool isEmpty() {
        return top == -1;
    }

    void enQueue(int value) {
        if (!isFull()) {
            top++;
            queue_array[top] = value;
        } else {
            cout << "Queue is full!";
        }
    }

    int deQueue() {
        int value = queue_array[0];
        // Push left
        for (int i = 0; i < top; ++i) {
            queue_array[i] = queue_array[i + 1];
        }
        top--;
        return value;
    }

    void reset() {
        top = -1;
    }

    int get_top() {
        return top;
    }
};

struct Book {
    string name;
    string author;
    int id, amount;
    int rack;
    struct Book *next;
public:
    Book(string new_name, string new_author, int new_id, int new_rack) {
        name = new_name;
        author = new_author;
        id = new_id;
        rack = new_rack;
        next = nullptr;
        amount = 1;
    }
};

struct BST {
    int id;
    struct BST *left, *right;
    struct Book *next;
public:
    BST(int new_id) {
        id = new_id;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }
};

struct User {
    string name;
    struct Book *book;
    struct User *next;
public:
    User(string new_name) {
        name = new_name;
        next = nullptr;
        book = nullptr;
    }
};


BST *searchBST(struct BST *root, int id);

void displayIssuedBooks();

bool returnBook(string user_name, string book_name);

Book *searchBook(int rack_no, int shelve, string name, string author_name);

Book *searchPreviousBook(struct BST *root, string name, string author_name);

bool searchBookcheck(struct BST *root, string name, string author_name);

bool issueBook(string username, string bookname, string author_name);

bool deleteBook(string name, string author_name);

Book *searchBook(struct BST *bst, string name, string author_name);

bool SearchingsearchBook(struct BST *bst, string name, int rack, int shelve);

void generateLibraryData();

Book *searchBookmain(struct BST *root, string name, string author_name);

void addBook(int shelve, string book_name, string author_name);

BST *createBST(int id, struct BST *root);

void displayLibrary(struct BST *root);

Queue queue;

int main() {
    // generating auto library data from file
    generateLibraryData();

    int choise;

    cout <<endl<<"Developed By\n"<<endl<<"Name: Haroon Rashid"<<endl<<"Reg No: FA17-BCS-030"<<"\n\n"<<"Name: Abdul Muizz"<<endl<<"Reg No: FA17-BCS-003"<<"\n\n";

    while (true) {
        cout << "\n\n\n++++++++++     M E N U     ++++++++++\n";
        cout << "0. Exit\n";
        cout << "1. Display All Books\n";
        cout << "2. Insert a Book\n";
        cout << "3. Delete a Book\n";
        cout << "4. Search Book By Name\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Display Issues\n";
        cout << "\nSelect an option : ";

        cin >> choise;
        switch (choise) {
            case 0: {
                exit(0);
            }
            case 1: {
                cout << "\n\n\n++++++++++     D I S P L A Y     ++++++++++\n";
                // For each rack
                for (int c = 0; c < 5; ++c) {
                    cout << "\n+++++   R A C K - " << c + 1 << "   +++++\n";

                    // For each shelve
                    for (int r = 0; r < 10; ++r) {
                        cout << "\n+++ S H E L V E - " << r + 1 << " +++\n";
                        displayLibrary(rack[r][c]);
                    }
                }
                break;
            }
            case 2: {
                string book_name;
                string author_name;

                cout << "\n\n\n++++++++++     I N S E R T     ++++++++++\n";
                cout << "0. Back\n";
                cout << "1. Mathematics\n";
                cout << "2. Computer\n";
                cout << "3. Physics\n";
                cout << "4. Islamiat\n";
                cout << "5. Others\n";
                cout << "\nSelect an option : ";
                cin >> choise;
                if (choise == 0) break;
                else {
                    cout << "\nBook Name : ";

                    cin.ignore();
                    getline(cin, book_name);

                    cout << "\nAuthor Name : ";
                    getline(cin, author_name);

                    addBook(choise - 1, book_name, author_name);
                }
                break;

            }
            case 3: {
                string name, author_name;
                cout << "\n\n\n++++++++++     D E L E T E     ++++++++++\n";
                cout << "\nEnter Book Name : ";
                cin.ignore();
                getline(cin, name);
                cout << "\nEnter Author Name : ";
                getline(cin, author_name);
                bool deleted = deleteBook(name, author_name);
                if (deleted) cout << "\n\nSuccessfully Deleted";
                else cout << "\n\nBook not found";
                break;
            }
            case 4: {
                string name;
                bool found = false;
                cout << "\n\n\n++++++++++     S E A R C H     ++++++++++\n";
                cout << "\nEnter Book Name : ";
                cin.ignore();
                getline(cin, name);

                int id = generateBookID(name);
                // For each rack
                for (int c = 0; c < 5; ++c) {
                    // For shelve
                    int shelve = id % 10;

                    // search BST
                    struct BST *bst = searchBST(rack[shelve][c], id);

                    // If BST found
                    if (bst != nullptr) {
                        found = SearchingsearchBook(bst, name, c, shelve);
                        break;
                    }
                }
                if (!found) {
                    cout << "\n\nBook not found";
                }
                break;
            }
            case 5: {
                string book_name;
                string author_name;
                string username;
                cout << "\n\n\n++++++++++     I S S U E     ++++++++++\n";
                cout << "\nEnter User Name : ";
                cin.ignore();
                getline(cin, username);
                cout << "\nEnter Book Name : ";
                getline(cin, book_name);
                cout << "\nEnter Author Name : ";
                getline(cin, author_name);

                bool issue = issueBook(username, book_name, author_name);
                if (issue) cout << "\n\nBook issued successfully!\n";
                break;
            }
            case 6: {
                string book_name;
                string username;
                cout << "\n\n\n++++++++++     R E T U R N     ++++++++++\n";
                cout << "\nEnter User Name : ";
                cin.ignore();
                getline(cin, username);
                cout << "\nEnter Book Name : ";
                getline(cin, book_name);


                bool issue = returnBook(username, book_name);
                if (issue) cout << "\n\nBook returned successfully!\n";
                break;
            }
            case 7: {
                cout << "\n\n\n++++++++++     I S S U E D   B O O K S     ++++++++++\n";
                displayIssuedBooks();
                break;
            }
            default: {
                cout << "\nInvalid input!";
            }
        }
    }
}

int generateBookID(string str) {
    queue.reset();
    int value = 0;
    // Check for each character in str
    for (int i = 0; i < str.length(); ++i) {
        // If str[i] is a space
        if (str[i] == ' ') {
            queue.enQueue(value);
            value = 0;
        } else {
            value += generateAlphabetID(str[i]);
        }
    }
    queue.enQueue(value);
    value = 0;

    stringstream string_stream;

    while (!queue.isEmpty()) {
        // Adding whole que values to string_stream
        string_stream << queue.deQueue();
    }

    // Combining different parts
    string combining_values = string_stream.str();

    istringstream integer_string_stream(combining_values);

    // Converting combining_values to int
    integer_string_stream >> value;
    return value;
}

int generateAlphabetID(char c) {

    char alphabets[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                        't', 'u', 'v', 'w', 'x', 'y', 'z'};
    c = tolower(c);

    for (int i = 0; i < 26; ++i) {
        if (c == alphabets[i])
            return ++i;
    }

    return -1;
}

BST *searchBST(struct BST *root, int id) {

    if (root == nullptr) {
        return nullptr;
    } else {
        while (root != nullptr) {
            if (root->id > id) root = root->left;
            else if (root->id < id) root = root->right;
            else return root;
        }
        return nullptr;
    }
}

void addBook(int shelve, string book_name, string author_name) {

    /*
     * shelve = 0       Maths
     * shelve = 1       Computer
     * shelve = 2       Physics
     * shelve = 3       Islamiat
     * shelve = 4       Others
     *
     * shelve are the columns
     */

    int id = generateBookID(book_name);
    int row = id % 10;
    struct Book *new_book = new Book(book_name, author_name, id, row);

    // Checking if BST already exists then work on it
    if (rack[row][shelve] != nullptr) {

        // Create it root and search if any BST already exists
        struct BST *root = rack[row][shelve];
        struct BST *searched = searchBST(root, id);

        // If no BST with such ID exists
        if (searched == nullptr) {
            struct BST *new_BST = createBST(id, root);

            // Adding new_book book to BST
            new_BST->next = new_book;
        }

            // If BST exists with same ID
        else {

            // Search if book with same name exists
            struct Book *searched_book = searchBook(searched, book_name, author_name);

            // If same book is alredy present
            if (searched_book != nullptr)
                searched_book->amount++;
            else {
                new_book->next = searched->next;
                searched->next = new_book;
            }
        }
    }

        // If BST does not exist at shelve array
    else {
        rack[row][shelve] = new BST(id);
        rack[row][shelve]->next = new_book;
    }
}

BST *createBST(int id, struct BST *root) {
    struct BST *current = new BST(id);

    struct BST *p = root;
    struct BST *k = p;

    if (p == nullptr) {
        root = current;
    } else {
        while (p != nullptr) {
            k = p;
            if (p->id > id) p = p->left;
            else p = p->right;
        }

        if (k->id > id) k->left = current;
        else k->right = current;
    }
    return current;
}

void displayLibrary(struct BST *root) {
    if (root != nullptr) {
        displayLibrary(root->left);

        // Displaying book linked list
        struct Book *book = root->next;
        while (book != nullptr) {

            printf("Book ID = %-10d Amount = %-10d Book Name = %-30s Author Name = %10s\n", book->id, book->amount,
                   book->name.c_str(),
                   book->author.c_str());
            book = book->next;

        }

        displayLibrary(root->right);
    }
}
//
//Book *searchBook(int rack_no, int shelve, string name) {
//    int id = generateBookID(name);
//
//    // BST that contains root
//    struct BST *bst = searchBST(rack[shelve][rack_no], id);
//    struct Book *book = bst->next;
//
//    while (book != nullptr) {
//        if (book->name == name)
//            return book;
//        book = book->next;
//    }
//
//    return nullptr;
//}

Book *searchBook(struct BST *bst, string name, string author_name) {
    int id = generateBookID(name);
    struct Book *book = bst->next;

    while (book != nullptr) {
        if (book->name == name && book->author == author_name)
            return book;
        book = book->next;
    }

    return nullptr;
}

bool SearchingsearchBook(struct BST *bst, string name, int rack, int shelve) {
    int id = generateBookID(name);
    struct Book *book = bst->next;
    bool found = false;

    while (book != nullptr) {
        if (book->name == name) {
            found = true;
            cout << "\nBook name : " << book->name << "       ID : " << book->id << "   Rack: " << rack + 1
                 << "  Shelve: "
                 << shelve + 1 << "  Author Name: " << book->author;
        }
        book = book->next;
    }

    return found;
}

bool deleteBook(string name, string author_name) {
    int id = generateBookID(name);
    // For each rack
    for (int c = 0; c < 5; ++c) {
        // For shelve
        int shelve = id % 10;

        // search BST
        struct BST *bst = searchBST(rack[shelve][c], id);

        // If BST found
        if (bst != nullptr) {
            // Searching book
            if (searchBookcheck(bst, name, author_name)) {
                struct Book *book = searchBookmain(bst, name, author_name);
                struct Book *prevbook = searchPreviousBook(bst, name, author_name);
                if (book->name == name && book->author == author_name) {
                    struct Book *del_book = book;
                    if (book->amount > 1) {
                        book->amount--;
                    } else {
                        if (book->next == nullptr) {
                            bst->next = nullptr;
                        } else {
                            bst->next = book->next;
                        }
                    }
                    return true;
                } else if (prevbook != nullptr) {
                    struct Book *del_book = book->next;
                    if (book->next->name == name && book->next->author == author_name) {
                        // If amount is greater than 1
                        if (book->next->amount > 1) {
                            book->next->amount--;
                            return true;
                        }
                        if (book->next->next != nullptr) {
                            book->next = book->next->next;
                        } else {
                            book->next = nullptr;
                        }
                        delete (del_book);
                        return true;
                    }

                    //Deleting book

                    // If amount is greater than 1

                }
            }

            // If book found

            // If book is the only book there

        }
    }

    return false;
}

Book *searchPreviousBook(struct BST *root, string name, string author_name) {
    int id = generateBookID(name);
    struct Book *book = root->next;
    struct Book *prev_book = book;

    while (book != nullptr) {
        if (book->name == name && book->author == author_name)
            return prev_book;
        prev_book = book;
        book = book->next;
    }
    return nullptr;
}

Book *searchBookmain(struct BST *root, string name, string author_name) {
    int id = generateBookID(name);
    struct Book *book = root->next;

    while (book != nullptr) {
        if (book->name == name && book->author == author_name)
            return root->next;

        book = book->next;
    }
    return nullptr;
}

bool searchBookcheck(struct BST *root, string name, string author_name) {
    int id = generateBookID(name);
    struct Book *book = root->next;

    while (book != nullptr) {
        if (book->name == name && book->author == author_name)
            return true;

        book = book->next;
    }
    return false;
}

void generateLibraryData() {
    ifstream inFile;
    inFile.open("E:\\University\\Semester 4\\Data Structures and Algorithm\\Assignment no 3\\datafile.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    // Variables that will collect data
    int shelve;
    string shelve_str;
    string book_name;
    string author_name;
    while (getline(inFile, shelve_str)) {
        // converting shelve_str to int
        shelve = stoi(shelve_str);

        getline(inFile, book_name);
        getline(inFile, author_name);
        addBook(shelve, book_name, author_name);
    }
    inFile.close();
}

bool issueBook(string user_name, string book_name, string author_name) {

    bool user_exists = false;
    struct User *u = start;
    struct User *user1 = nullptr;
    struct User *user = nullptr;

    while (u != nullptr) {
        if (u->name == user_name) {
            user_exists = true;
        }
        user1 = u;
        u= u->next;
    }
    if(!user_exists) {
        user = new User(user_name);

        int id = generateBookID(book_name);
        int shelve = id % 10;
        struct Book *book = nullptr;
        struct Book *temp_book = nullptr;
        struct BST *bst = nullptr;

        for (int i = 0; i < 5; ++i) {
            bst = searchBST(rack[shelve][i], id);
            if (bst != nullptr) {
                book = searchBook(bst, book_name, author_name);
                if (book != nullptr) {
                    temp_book = new Book(book_name, author_name, id, i);
                    temp_book->author = book->author;

                    // deleteing book now
                    deleteBook(book_name, author_name);

                    // Now looking if user linked list is null
                        user->book = temp_book;
                    if(start== nullptr){
                        start = user;
                    }
                    else{
                        user1->next=user;
                    }

//                        // If not null
//                    else {
//                        // Arranging book in user
//                        book->next = user->book;
//                        user->book = book;
//
//                        // Now arranging user
//                        user->next = start;
//                        start = user;
//                    }
                    return true;
                }
            }
        }
        cout<<"Book Not Found";
    }
    else{
        cout<<"\n"<<"One User can Issue Only One Book";
    }
    return false;
}

bool returnBook(string user_name, string book_name) {
    // searching username in list
    struct User *user = start;
    struct User *prev_user = start;
    while (user != nullptr) {
        prev_user = user;
        if (user->name == user_name) break;
        user = user->next;
    }

    // If user exists
    if (user != nullptr) {
        // Searching book
        struct Book *book = user->book;

        // If book exists
        if (book != nullptr&&book->name==book_name) {

            // If there is only one book in user
            if (user->book == book) {
                addBook(book->rack, book_name, book->author);
                user->book= nullptr;
                delete book;

                // If the user is the root
                if (user == start) {
                    if(start->next!= nullptr){
                    start = start->next;
                    }
                    else{
                        start = nullptr;
                    }
                }
                else {
                    prev_user->next= user->next;
                    delete user;
                }
                return true;
            }
        }
        else{
            cout<<"\nBook not Found";
        }
    }
    else{
        cout<<"User Doesn't Exist";
    }
    return false;

}

void displayIssuedBooks() {
    struct User *user = start;
    while (user != nullptr) {
        struct Book *book = user->book;

        // Books
        while (book != nullptr) {
            printf("Username : %-15sBook name : %-15s Author Name : %-15s \n", user->name.c_str(), book->name.c_str(),book->author.c_str());
            book = book->next;
        }

        user = user->next;
    }
}