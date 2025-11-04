#include <iostream>
#include <string>
#include "bst.h"
#include "usecase.cpp"

using namespace std;

/*
Main function demonstrating the binary to hexadecimal conversion use case
Preconditions: binhex.txt file exists with hex,binary pairs
Postconditions: Demonstrates conversion accuracy with example test cases and allows user input
*/
int main()
{
    // Create BST from CSV file
    string filename = "binhex.txt";

    cout << "Creating Binary Search Tree from " << filename << "..." << endl;
    BST<string, string> *bst = create_bst(filename);
    cout << "Binary Search Tree Created" << endl;
    cout << endl;

    // Example test cases demonstrating accuracy
    cout << "=== Example Test Cases ===" << endl;

    string test1 = "1010";
    string result1 = convert(bst, test1);
    cout << "Binary: " << test1 << " -> Hexadecimal: " << result1 << endl;

    string test2 = "11111111";
    string result2 = convert(bst, test2);
    cout << "Binary: " << test2 << " -> Hexadecimal: " << result2 << endl;

    string test3 = "10110101";
    string result3 = convert(bst, test3);
    cout << "Binary: " << test3 << " -> Hexadecimal: " << result3 << endl;

    cout << endl;

    // User interaction loop
    cout << "=== Welcome to CS271 Binary Conversion System ===" << endl;
    cout << "Enter binary representation for conversion:" << endl;
    cout << "Type 'q' to exit." << endl;
    cout << endl;

    while (true)
    {
        string binary;

        // Get binary input
        cout << "Binary: ";
        getline(cin, binary);

        // Check for exit condition
        if (binary == "q")
        {
            cout << "Exiting Binary Conversion system." << endl;
            break;
        }

        // Attempt conversion
        string result = convert(bst, binary);

        if (!result.empty())
        {
            cout << "Hexadecimal representation of " << binary << " is " << result << endl;
        }
        else
        {
            cout << "Hexadecimal conversion failed. Make sure you entered valid binary (0s and 1s only)." << endl;
        }

        cout << endl;
    }

    // Clean up
    delete bst;

    return 0;
}
