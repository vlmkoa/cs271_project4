#include "bst.h"
#include <fstream>
#include <sstream>

using namespace std;

BST<string, string> *create_bst(string fname);
string convert(BST<string, string> *bst, string bin);

BST<string, string> *create_bst(string fname)
{
    BST<string, string> *bst = new BST<string, string>();
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

        // Parse the line: "hexstring,binaryString"
        size_t comma_pos = line.find(',');
        if (comma_pos != string::npos)
        {
            string hex_string = line.substr(0, comma_pos);
            string binary = line.substr(comma_pos + 1);
            bst->insert(hex_string, binary);
        }
    }

    file.close();
    return bst;
}

string convert(BST<string, string> *bst, string bin)
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

        // Look up the hex stringacter for this 4-bit chunk
        string hex_string = bst->get(chunk);
        result = hex_string + result;
    }

    return result;
}
