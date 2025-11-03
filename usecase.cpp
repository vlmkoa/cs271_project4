#include "bst.h"
#include <fstream>
#include <sstream>
#include <algorithm>

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
            // Insert with binary as KEY (for lookup) and hex as DATA
            bst->insert(hex_string, binary);
        }
    }

    file.close();
    return bst;
}

string convert(BST<string, string> *bst, string bin)
{
    string result = "";

    // Process binary string in chunks of 4 bits from RIGHT to LEFT
    int len = bin.length();
    for (int i = len; i > 0; i -= 4)
    {
        int start = max(0, i - 4);
        int chunk_len = i - start;
        string chunk = bin.substr(start, chunk_len);

        // Pad with zeros on the LEFT if less than 4 bits
        if (chunk.length() < 4)
        {
            chunk.insert(0, 4 - chunk.length(), '0');
        }

        // Look up the hex string for this 4-bit chunk
        string hex_string = bst->get(chunk);
        result = hex_string + result; // Prepend to maintain order
    }

    return result;
}
