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

/* The Queue class is a basic implementation of a queue data structure in C++. */
class Queue
{
public:
    int top;

    /**
     * The Queue constructor initializes the top variable to -1.
     * top = -1 represents empty queue
     */
    Queue()
    {
        top = -1;
    }

    /**
     * The function checks if the queue is full by comparing the top index to the maximum index value.
     * Function is setting queue size of 20 items (0-19)
     * 
     * @return a boolean value, which indicates whether the queue is full or not.
     */
    bool isFull()
    {
        return top == 19;
    }

    /**
     * The function checks if the top of the stack is equal to -1 and returns true if it is, indicating
     * that the stack is empty.
     * 
     * @return a boolean value, which indicates whether the stack is empty or not.
     */
    bool isEmpty()
    {
        return top == -1;
    }

    /**
     * The enQueue function adds an element to the queue if it is not full, otherwise it displays a
     * message indicating that the queue is full.
     * 
     * @param value The parameter "value" is an integer that represents the value to be added to the
     * queue.
     */
    void enQueue(int value)
    {
        if (!isFull())
        {
            top++;
            queue_array[top] = value;
        }
        else
        {
            cout << "Queue is full!";
        }
    }

    /**
     * The deQueue function removes and returns the first element in the queue by shifting all elements
     * to the left.
     * 
     * @return The value being returned is the element that was removed from the front of the queue.
     */
    int deQueue()
    {
        int value = queue_array[0];
        // Push left
        for (int i = 0; i < top; ++i)
        {
            queue_array[i] = queue_array[i + 1];
        }
        top--;
        return value;
    }

    /**
     * The function clears the queue by setting the value of the variable "top" to -1.
     */
    void reset()
    {
        top = -1;
    }

    /**
     * The function returns the value of the top element in a stack.
     * 
     * @return The value of the variable "top" is being returned.
     */
    int getTop()
    {
        return top;
    }
};

/**
 * The above code defines a struct called Book with variables for name, author, id, amount, rack, and a
 * pointer to the next book.
 */
struct Book
{
    string name;
    string author;
    int id, amount;
    int rack;
    struct Book *next;

public:
    /**
     * The Book constructor initializes the name, author, id, rack, next, and amount variables.
     */
    Book(string new_name, string new_author, int new_id, int new_rack)
    {
        name = new_name;
        author = new_author;
        id = new_id;
        rack = new_rack;
        next = nullptr;
        amount = 1;
    }
};

/**
 * The above code defines a struct for a Binary Search Tree (BST) with an additional pointer to a Book
 * struct.
 */
struct BST
{
    int id;
    struct BST *left, *right;
    struct Book *next;

public:
    BST(int new_id)
    {
        id = new_id;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }
};

/**
 * The above code defines a struct called User with a name, a pointer to a Book, and a pointer to the
 * next User.
 */
struct User
{
    string name;
    struct Book *book;
    struct User *next;

public:
    User(string new_name)
    {
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

bool searchBookCheck(struct BST *root, string name, string author_name);

bool issueBook(string username, string bookName, string author_name);

bool deleteBook(string name, string author_name);

Book *searchBook(struct BST *bst, string name, string author_name);

bool searchingSearchBook(struct BST *bst, string name, int rack, int shelve);

void generateLibraryData();

Book *searchBookMain(struct BST *root, string name, string author_name);

void addBook(int shelve, string book_name, string author_name);

BST *createBST(int id, struct BST *root);

void displayLibrary(struct BST *root);

Queue queue;

int main()
{
    // generating auto library data from file
    generateLibraryData();

    int choice;

    cout << endl
         << "Library Management System\n"
         << endl
         << "\n\n";

    while (true)
    {
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

        cin >> choice;
        switch (choice)
        {
        case 0:
        {
            exit(0);
        }
        case 1:
        {
            cout << "\n\n\n++++++++++     D I S P L A Y     ++++++++++\n";
            // For each rack
            for (int c = 0; c < 5; ++c)
            {
                cout << "\n+++++   R A C K - " << c + 1 << "   +++++\n";

                // For each shelve
                for (int r = 0; r < 10; ++r)
                {
                    cout << "\n+++ S H E L V E - " << r + 1 << " +++\n";
                    displayLibrary(rack[r][c]);
                }
            }
            break;
        }
        case 2:
        {
            string book_name;
            string author_name;

            cout << "\n\n\n++++++++++     I N S E R T     ++++++++++\n";
            cout << "0. Back\n";
            cout << "1. Mathematics\n";
            cout << "2. Computer\n";
            cout << "3. Physics\n";
            cout << "4. Others\n";
            cout << "\nSelect an option : ";
            cin >> choice;
            if (choice == 0)
                break;
            else
            {
                cout << "\nBook Name : ";

                cin.ignore();
                getline(cin, book_name);

                cout << "\nAuthor Name : ";
                getline(cin, author_name);

                addBook(choice - 1, book_name, author_name);
            }
            break;
        }
        case 3:
        {
            string name, author_name;
            cout << "\n\n\n++++++++++     D E L E T E     ++++++++++\n";
            cout << "\nEnter Book Name : ";
            cin.ignore();
            getline(cin, name);
            cout << "\nEnter Author Name : ";
            getline(cin, author_name);
            bool deleted = deleteBook(name, author_name);
            if (deleted)
                cout << "\n\nSuccessfully Deleted";
            else
                cout << "\n\nBook not found";
            break;
        }
        case 4:
        {
            string name;
            bool found = false;
            cout << "\n\n\n++++++++++     S E A R C H     ++++++++++\n";
            cout << "\nEnter Book Name : ";
            cin.ignore();
            getline(cin, name);

            int id = generateBookID(name);
            // For each rack
            for (int c = 0; c < 5; ++c)
            {
                // For shelve
                int shelve = id % 10;

                // search BST
                struct BST *bst = searchBST(rack[shelve][c], id);

                // If BST found
                if (bst != nullptr)
                {
                    found = searchingSearchBook(bst, name, c, shelve);
                    break;
                }
            }
            if (!found)
            {
                cout << "\n\nBook not found";
            }
            break;
        }
        case 5:
        {
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
            if (issue)
                cout << "\n\nBook issued successfully!\n";
            break;
        }
        case 6:
        {
            string book_name;
            string username;
            cout << "\n\n\n++++++++++     R E T U R N     ++++++++++\n";
            cout << "\nEnter User Name : ";
            cin.ignore();
            getline(cin, username);
            cout << "\nEnter Book Name : ";
            getline(cin, book_name);

            bool issue = returnBook(username, book_name);
            if (issue)
                cout << "\n\nBook returned successfully!\n";
            break;
        }
        case 7:
        {
            cout << "\n\n\n++++++++++     I S S U E D   B O O K S     ++++++++++\n";
            displayIssuedBooks();
            break;
        }
        default:
        {
            cout << "\nInvalid input!";
        }
        }
    }
}

/**
 * The function generates a book ID by converting a string into a numerical value based on the
 * alphabetical values of its characters.
 * 
 * @param str The parameter `str` is a string that represents the title of a book.
 * 
 * @return an integer value, which is the generated book ID based on the input string.
 */
int generateBookID(string str)
{
    queue.reset();
    int value = 0;
    // Check for each character in str
    for (int i = 0; i < str.length(); ++i)
    {
        // If str[i] is a space
        if (str[i] == ' ')
        {
            queue.enQueue(value);
            value = 0;
        }
        else
        {
            value += generateAlphabetID(str[i]);
        }
    }
    queue.enQueue(value);
    value = 0;

    stringstream string_stream;

    while (!queue.isEmpty())
    {
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

/**
 * The function "generateAlphabetID" takes a character as input and returns its corresponding position
 * in the alphabet, starting from 1, or -1 if the character is not a lowercase letter.
 * 
 * @param c The parameter `c` is a character that represents an alphabet.
 * 
 * @return the index position of the given character in the alphabet array. If the character is not
 * found in the array, it returns -1.
 */
int generateAlphabetID(char c)
{

    char alphabets[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                        't', 'u', 'v', 'w', 'x', 'y', 'z'};
    c = tolower(c);

    for (int i = 0; i < 26; ++i)
    {
        if (c == alphabets[i])
            return ++i;
    }

    return -1;
}

/**
 * The function searches for a node with a specific id in a binary search tree and returns a pointer to
 * that node if found, otherwise returns nullptr.
 * 
 * @param root The root node of the binary search tree (BST) that we want to search in.
 * @param id The "id" parameter is an integer value that represents the unique identifier of the node
 * we are searching for in the binary search tree (BST).
 * 
 * @return a pointer to the node in the binary search tree (BST) that has the specified id. If no node
 * with the specified id is found in the BST, the function returns nullptr.
 */
BST *searchBST(struct BST *root, int id)
{

    if (root == nullptr)
    {
        return nullptr;
    }
    else
    {
        while (root != nullptr)
        {
            if (root->id > id)
                root = root->left;
            else if (root->id < id)
                root = root->right;
            else
                return root;
        }
        return nullptr;
    }
}

/**
 * The function `addBook` adds a new book to a library system, organizing it based on the shelf and
 * row, and handling cases where the book or shelf already exists.
 * 
 * @param shelve The parameter "shelve" represents the shelf number where the book will be added. It is
 * an integer value that determines the column in the rack where the book will be placed. The possible
 * values for "shelve" are as follows:
 * @param book_name The name of the book that you want to add to the shelf.
 * @param author_name The author's name of the book.
 */
void addBook(int shelve, string book_name, string author_name)
{

    /*
     * shelve = 0       Maths
     * shelve = 1       Computer
     * shelve = 2       Physics
     * shelve = 3       Others
     *
     * shelve are the columns
     */

    int id = generateBookID(book_name);
    int row = id % 10;
    struct Book *new_book = new Book(book_name, author_name, id, row);

    // Checking if BST already exists then work on it
    if (rack[row][shelve] != nullptr)
    {

        // Create it root and search if any BST already exists
        struct BST *root = rack[row][shelve];
        struct BST *searched = searchBST(root, id);

        // If no BST with such ID exists
        if (searched == nullptr)
        {
            struct BST *new_BST = createBST(id, root);

            // Adding new_book book to BST
            new_BST->next = new_book;
        }

        // If BST exists with same ID
        else
        {

            // Search if book with same name exists
            struct Book *searched_book = searchBook(searched, book_name, author_name);

            // If same book is already present
            if (searched_book != nullptr)
                searched_book->amount++;
            else
            {
                new_book->next = searched->next;
                searched->next = new_book;
            }
        }
    }

    // If BST does not exist at shelve array
    else
    {
        rack[row][shelve] = new BST(id);
        rack[row][shelve]->next = new_book;
    }
}

/**
 * The function creates a new node with the given id and inserts it into a binary search tree.
 * 
 * @param id The `id` parameter represents the value of the node that we want to insert into the binary
 * search tree (BST).
 * @param root The `root` parameter is a pointer to the root node of the binary search tree (BST).
 * 
 * @return a pointer to the newly created BST node.
 */
BST *createBST(int id, struct BST *root)
{
    struct BST *current = new BST(id);

    struct BST *p = root;
    struct BST *k = p;

    if (p == nullptr)
    {
        root = current;
    }
    else
    {
        while (p != nullptr)
        {
            k = p;
            if (p->id > id)
                p = p->left;
            else
                p = p->right;
        }

        if (k->id > id)
            k->left = current;
        else
            k->right = current;
    }
    return current;
}

/**
 * The function displays the contents of a binary search tree, which represents a library, by
 * traversing the tree in an order manner and printing the details of each book in the linked list
 * associated with each node.
 * 
 * @param root The parameter "root" is a pointer to the root node of a binary search tree (BST).
 */
void displayLibrary(struct BST *root)
{
    if (root != nullptr)
    {
        displayLibrary(root->left);

        // Displaying book linked list
        struct Book *book = root->next;
        while (book != nullptr)
        {

            printf("Book ID = %-10d Amount = %-10d Book Name = %-30s Author Name = %10s\n", book->id, book->amount,
                   book->name.c_str(),
                   book->author.c_str());
            book = book->next;
        }

        displayLibrary(root->right);
    }
}

/**
 * The function searches for a book in a binary search tree based on its name and author name.
 * 
 * @param bst A pointer to a binary search tree (BST) structure.
 * @param name The name parameter is a string that represents the name of the book you are searching
 * for.
 * @param author_name The parameter "author_name" is a string that represents the name of the author of
 * the book.
 * 
 * @return a pointer to a Book structure.
 */
Book *searchBook(struct BST *bst, string name, string author_name)
{
    int id = generateBookID(name);
    struct Book *book = bst->next;

    while (book != nullptr)
    {
        if (book->name == name && book->author == author_name)
            return book;
        book = book->next;
    }

    return nullptr;
}

/**
 * The function searches for a book in a binary search tree based on its name, rack, and shelve, and
 * returns true if the book is found.
 * 
 * @param bst The parameter `bst` is a pointer to a binary search tree (BST) structure. This BST is
 * used to store and search for books.
 * @param name The name of the book you are searching for.
 * @param rack The parameter "rack" represents the rack number where the book is located.
 * @param shelve The parameter "shelve" represents the shelve number where the book is located.
 * 
 * @return a boolean value indicating whether the book with the given name, rack, and shelve was found
 * in the binary search tree (BST).
 */
bool searchingSearchBook(struct BST *bst, string name, int rack, int shelve)
{
    int id = generateBookID(name);
    struct Book *book = bst->next;
    bool found = false;

    while (book != nullptr)
    {
        if (book->name == name)
        {
            found = true;
            cout << "\nBook name : " << book->name << "       ID : " << book->id << "   Rack: " << rack + 1
                 << "  Shelve: "
                 << shelve + 1 << "  Author Name: " << book->author;
        }
        book = book->next;
    }

    return found;
}

/**
 * The function `deleteBook` is used to delete a book from a library system based on its name and
 * author name.
 * 
 * @param name The name parameter represents the name of the book that you want to delete.
 * @param author_name The author's name of the book you want to delete.
 * 
 * @return a boolean value. It returns true if the book with the given name and author name is
 * successfully deleted, and false otherwise.
 */
bool deleteBook(string name, string author_name)
{
    int id = generateBookID(name);
    // For each rack
    for (int c = 0; c < 5; ++c)
    {
        // For shelve
        int shelve = id % 10;

        // search BST
        struct BST *bst = searchBST(rack[shelve][c], id);

        // If BST found
        if (bst != nullptr)
        {
            // Searching book
            if (searchBookCheck(bst, name, author_name))
            {
                struct Book *book = searchBookMain(bst, name, author_name);
                struct Book *prevBook = searchPreviousBook(bst, name, author_name);
                if (book->name == name && book->author == author_name)
                {
                    struct Book *del_book = book;
                    if (book->amount > 1)
                    {
                        book->amount--;
                    }
                    else
                    {
                        if (book->next == nullptr)
                        {
                            bst->next = nullptr;
                        }
                        else
                        {
                            bst->next = book->next;
                        }
                    }
                    return true;
                }
                else if (prevBook != nullptr)
                {
                    struct Book *del_book = book->next;
                    if (book->next->name == name && book->next->author == author_name)
                    {
                        // If amount is greater than 1
                        if (book->next->amount > 1)
                        {
                            book->next->amount--;
                            return true;
                        }
                        if (book->next->next != nullptr)
                        {
                            book->next = book->next->next;
                        }
                        else
                        {
                            book->next = nullptr;
                        }
                        delete (del_book);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/**
 * The function searches for a previous book in a binary search tree based on the book's name and
 * author name.
 * 
 * @param root The "root" parameter is a pointer to the root node of a binary search tree (BST) data
 * structure.
 * @param name The parameter "name" is a string that represents the name of the book you are searching
 * for.
 * @param author_name The parameter "author_name" is a string that represents the name of the author of
 * the book.
 * 
 * @return a pointer to the previous book node in the binary search tree (BST) that matches the given
 * book name and author name.
 */
Book *searchPreviousBook(struct BST *root, string name, string author_name)
{
    int id = generateBookID(name);
    struct Book *book = root->next;
    struct Book *prev_book = book;

    while (book != nullptr)
    {
        if (book->name == name && book->author == author_name)
            return prev_book;
        prev_book = book;
        book = book->next;
    }
    return nullptr;
}

/**
 * The function searches for a book in a binary search tree based on its name and author name.
 * 
 * @param root The root parameter is a pointer to the root node of a binary search tree (BST).
 * @param name The name parameter is a string that represents the name of the book you are searching
 * for.
 * @param author_name The parameter "author_name" is a string that represents the name of the author of
 * the book.
 * 
 * @return a pointer to a Book structure.
 */
Book *searchBookMain(struct BST *root, string name, string author_name)
{
    int id = generateBookID(name);
    struct Book *book = root->next;

    while (book != nullptr)
    {
        if (book->name == name && book->author == author_name)
            return root->next;

        book = book->next;
    }
    return nullptr;
}

/**
 * The function searches for a book in a binary search tree based on its name and author name.
 * 
 * @param root A pointer to the root of a binary search tree (BST) structure.
 * @param name The name parameter is a string that represents the name of the book.
 * @param author_name The parameter "author_name" is a string that represents the name of the author of
 * the book.
 * 
 * @return a boolean value.
 */
bool searchBookCheck(struct BST *root, string name, string author_name)
{
    int id = generateBookID(name);
    struct Book *book = root->next;

    while (book != nullptr)
    {
        if (book->name == name && book->author == author_name)
            return true;

        book = book->next;
    }
    return false;
}

/**
 * The function `generateLibraryData()` reads data from a file, converts the shelf number to an
 * integer, and adds the book information (shelf number, book name, and author name) to a library.
 */
void generateLibraryData()
{
    ifstream inFile;

    /*
    How to add path

    Windows: "D:\\project\\...\\[filename].txt"
    */
    std::string filePath = "";

    if (!filePath.empty())
    {
        cerr << "Please provide file path to store and extract data";
    }

    inFile.open(filePath);
    if (!inFile)
    {
        cerr << "Unable to open the file";
        exit(1); // call system to stop
    }

    // Variables that will collect data
    int shelve;
    string shelve_str;
    string book_name;
    string author_name;
    while (getline(inFile, shelve_str))
    {
        // converting shelve_str to int
        shelve = stoi(shelve_str);

        getline(inFile, book_name);
        getline(inFile, author_name);
        addBook(shelve, book_name, author_name);
    }
    inFile.close();
}

/**
 * The function `issueBook` checks if a user exists, searches for a book in the library, and if found,
 * assigns the book to the user and removes it from the library.
 * 
 * @param user_name The name of the user who wants to issue the book.
 * @param book_name The name of the book that the user wants to issue.
 * @param author_name The author's name of the book that the user wants to issue.
 * 
 * @return a boolean value.
 */
bool issueBook(string user_name, string book_name, string author_name)
{

    bool user_exists = false;
    struct User *u = start;
    struct User *user1 = nullptr;
    struct User *user = nullptr;

    while (u != nullptr)
    {
        if (u->name == user_name)
        {
            user_exists = true;
        }
        user1 = u;
        u = u->next;
    }
    if (!user_exists)
    {
        user = new User(user_name);

        int id = generateBookID(book_name);
        int shelve = id % 10;
        struct Book *book = nullptr;
        struct Book *temp_book = nullptr;
        struct BST *bst = nullptr;

        for (int i = 0; i < 5; ++i)
        {
            bst = searchBST(rack[shelve][i], id);
            if (bst != nullptr)
            {
                book = searchBook(bst, book_name, author_name);
                if (book != nullptr)
                {
                    temp_book = new Book(book_name, author_name, id, i);
                    temp_book->author = book->author;

                    // deleting book now
                    deleteBook(book_name, author_name);

                    // Now looking if user linked list is null
                    user->book = temp_book;
                    if (start == nullptr)
                    {
                        start = user;
                    }
                    else
                    {
                        user1->next = user;
                    }

                    return true;
                }
            }
        }
        cout << "Book Not Found";
    }
    else
    {
        cout << "\n"
             << "One User can Issue Only One Book";
    }
    return false;
}

/**
 * The function `returnBook` takes a user name and a book name as input, searches for the user in a
 * linked list, checks if the user has the specified book, and if so, removes the book from the user's
 * possession and returns it to the library.
 * 
 * @param user_name The username of the user who wants to return the book.
 * @param book_name The book_name parameter is a string that represents the name of the book that the
 * user wants to return.
 * 
 * @return a boolean value. It returns true if the book is successfully returned by the user, and false
 * otherwise.
 */
bool returnBook(string user_name, string book_name)
{
    // searching username in list
    struct User *user = start;
    struct User *prev_user = start;
    while (user != nullptr)
    {
        prev_user = user;
        if (user->name == user_name)
            break;
        user = user->next;
    }

    // If user exists
    if (user != nullptr)
    {
        // Searching book
        struct Book *book = user->book;

        // If book exists
        if (book != nullptr && book->name == book_name)
        {

            // If there is only one book in user
            if (user->book == book)
            {
                addBook(book->rack, book_name, book->author);
                user->book = nullptr;
                delete book;

                // If the user is the root
                if (user == start)
                {
                    if (start->next != nullptr)
                    {
                        start = start->next;
                    }
                    else
                    {
                        start = nullptr;
                    }
                }
                else
                {
                    prev_user->next = user->next;
                    delete user;
                }
                return true;
            }
        }
        else
        {
            cout << "\nBook not Found";
        }
    }
    else
    {
        cout << "User Doesn't Exist";
    }
    return false;
}

/**
 * The function displays the details of all the books issued by each user.
 */
void displayIssuedBooks()
{
    struct User *user = start;
    while (user != nullptr)
    {
        struct Book *book = user->book;

        // Books
        while (book != nullptr)
        {
            printf("Username : %-15sBook name : %-15s Author Name : %-15s \n", user->name.c_str(), book->name.c_str(), book->author.c_str());
            book = book->next;
        }

        user = user->next;
    }
}