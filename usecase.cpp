//
//  usecase.cpp
//  CS 271 BST Project
//
//  Created by Sunho, Ava, Ryan
//

#include "bst.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// function declarations
BST<string, string> *create_bst(string fname);
string convert(BST<string, string> *bst, string bin);

// function definitions

/**
 * create_bst: this function reads the file name
 * containing the hex data, and binary key pairs
 * and puts the elements from each line into BST
 * based on the key of each pair.
 *
 * Pre-condition: File must contains data that
 * conforms to "hex, binary" format.
 *
 * Post-condition: A BST created with nodes
 * made of data and key in the files.
 */

BST<string, string> *create_bst(string fname)
{
    BST<string, string> *bst = new BST<string, string>();
    ifstream file(fname);

    if (!file.is_open())
    {
        cerr << "Warning: Could not open file '" << fname << "'" << endl;
        return bst;
    }

    string line;
    int line_num = 0;
    while (getline(file, line))
    {
        line_num++;
        if (line.empty())
            continue;

        // Parse the line: "hex,binary" format
        size_t comma_pos = line.find(',');
        if (comma_pos == string::npos)
        {
            cerr << "Warning: Invalid format at line " << line_num << ": " << line << endl;
            continue;
        }

        string hex_string = line.substr(0, comma_pos);
        string binary = line.substr(comma_pos + 1);

        // Validate binary string contains only 0s and 1s
        bool valid = true;
        for (char c : binary)
        {
            if (c != '0' && c != '1')
            {
                cerr << "Warning: Invalid binary string at line " << line_num << ": " << binary << endl;
                valid = false;
                break;
            }
        }

        if (valid && !binary.empty() && !hex_string.empty())
        {
            // Insert with binary as KEY (for lookup) and hex as DATA
            bst->insert(hex_string, binary);
        }
    }

    file.close();
    return bst;
}

/**
 * convert: the function parses the input binary
 * value uses the BST to find equivalent hex
 * values return a string of equivalent final
 * hex
 *
 * Pre-condition: None
 *
 * Post-condition: a string of equivalent hex
 * value is returned
 */
string convert(BST<string, string> *bst, string bin)
{
    // Validate input
    if (!bst)
    {
        cerr << "Error: BST is null" << endl;
        return "";
    }

    if (bin.empty())
    {
        return "";
    }

    // Validate binary string
    for (char c : bin)
    {
        if (c != '0' && c != '1')
        {
            cerr << "Error: Invalid binary string (contains non-binary characters)" << endl;
            return "";
        }
    }

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

        // Check if lookup failed (empty string means not found)
        if (hex_string.empty())
        {
            cerr << "Error: No mapping found for binary chunk '" << chunk << "'" << endl;
            return "";
        }

        result = hex_string + result; // Prepend to maintain order
    }

    return result;
}
