#include <iostream>
#include <string>
#include "bst.cpp"
#include "usecase.cpp"

using namespace std;

/*
Main function demonstrating the login use case
Preconditions: logins.csv file exists with username,password pairs
Postconditions: User can test login functionality with username/password input
*/
int main()
{
    // Create hash table from CSV file
    string filename = "binhex.txt";

    cout << "Creating Binary Search Tree" << filename << "..." << endl;
    BST<char, string> *bst = create_bst(filename);
    cout << "Binary Search Tree Created" << endl;
    cout << endl;

    // User interaction loop
    cout << "=== Welcome to CS271 Binary Conversion System ===" << endl;
    cout << "Enter binary representation for conversion:" << endl;
    cout << "Type 'q' to exit." << endl;
    cout << endl;

    while (true)
    {
        string binary;

        // Get username
        getline(cin, binary);

        // Check for exit condition
        if (binary == "q")
        {
            cout << "Exiting Binary Conversion system." << endl;
            break;
        }
        // Attempt login
        string result = convert(bst, binary);

        if (!result.empty())
        {
            cout << "Hexidecimal representation of " << binary << " is" << result << endl;
        }
        else
        {
            cout << "Hexidecimal conversion failed. Make sure you entered the correct binary" << endl;
        }

        cout << endl;
    }

    // Clean up
    delete bst;

    return 0;
}
