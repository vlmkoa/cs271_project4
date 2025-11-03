#include "bst.h"
#include <fstream>
#include <sstream>

using namespace std;

BST<char, string> *create_bst(string fname);
string convert(BST<char, string> *bst, string bin);

BST<char, string> *create_bst(string fname)
{
    BST<char, string> *bst = new BST<char, string>();
    ifstream file(fname);

    if (!file.is_open())
    {
        return bst;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        // Parse the line: "hexChar,binaryString"
        size_t comma_pos = line.find(',');
        if (comma_pos != string::npos)
        {
            char hex_char = line[0];
            string binary = line.substr(comma_pos + 1);
            bst->insert(hex_char, binary);
        }
    }

    file.close();
    return bst;
}

string convert(BST<char, string> *bst, string bin)
{
    string result = "";

    // Process binary string in chunks of 4 bits
    for (size_t i = 0; i < bin.length(); i += 4)
    {
        string chunk = bin.substr(i, 4);

        // Fill with zeros if less than 4 bits
        while (chunk.length() < 4)
        {
            chunk += "0";
        }

        // Look up the hex character for this 4-bit chunk
        char hex_char = bst->get(chunk);
        result += hex_char;
    }

    return result;
}
