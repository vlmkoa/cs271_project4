//
//  test_bst.cpp
//  CS 271 BST Project
//
//  Created by Sunho, Ava, Ryan
//

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "usecase.cpp"
#include "bst.h"
#include <chrono>

using namespace std;

void test_empty()
{
    try
    {
        BST<string, int> bst;
        if (!bst.empty())
        {
            cout << "Incorrect empty result when bst empty." << endl;
        }
        bst.insert("one", 1);
        if (bst.empty())
        {
            cout << "Incorrect empty result when bst has one item." << endl;
        }
        bst.insert("dos", 2);
        if (bst.empty())
        {
            cout << "Incorrect empty result when bst has multiple items." << endl;
        }
        bst.remove(1);
        if (bst.empty())
        {
            cout << "Incorrect empty result when an item was removed from bst." << endl;
        }
        bst.remove(2);
        string bst_str = bst.to_string();
        if (!bst.empty())
        {
            cout << "Incorrect empty result when all items were removed from bst. Result: " << bst_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining if BST is empty : " << e.what() << endl;
    }
}

void test_insert()
{
    try
    {
        // normal insert
        BST<string, int> bst;
        bst.insert("one", 1);
        string bst_str = bst.to_string();
        if (bst_str != "1")
        {
            cout << "Incorrect result of inserting (\"one\", 1). Expected 1 but got : " << bst_str << endl;
        }
        for (int i = 2; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        bst_str = bst.to_string();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect result of inserting keys 1-10 in order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        // insert same keys again
        for (int i = 1; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        bst_str = bst.to_string();
        if (bst_str != "1 2 1 3 2 4 3 5 4 6 5 7 6 8 7 9 8 10 9 10")
        {
            cout << "Incorrect result of inserting keys 1-10 in order when already in BST. Expected 1 2 1 3 2 4 3 5 4 6 5 7 6 8 7 9 8 10 9 10 but got : " << bst_str << endl;
        }

        // insert balanced tree
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 7 1 3 6 9 4 8 10")
        {
            cout << "Incorrect result of inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10}. Expected 5 2 7 1 3 6 9 4 8 10 but got : " << bst_str << endl;
        }

        // insert balanced keys again
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 7 1 3 6 9 1 2 4 5 6 8 10 3 4 7 8 9 10")
        {
            cout << "Incorrect result of inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10} twice. Expected 5 2 7 1 3 6 9 1 2 4 5 6 8 10 3 4 7 8 9 10 but got : " << bst_str << endl;
        }

        // insert left unbalanced, nonstring data, string key
        string lets[10] = {"j", "i", "h", "g", "f", "e", "d", "c", "b", "a"};
        BST<int, string> diff_bst;
        for (int i = 0; i < 10; i++)
        {
            diff_bst.insert(i, lets[i]);
        }
        string diff_str = diff_bst.to_string();
        if (diff_str != "j i h g f e d c b a")
        {
            cout << "Incorrect result of inserting letters a-j in reverse order. Expected j i h g f e d c b a but got : " << diff_str << endl;
        }

        // insert balanced, float data, float key
        float flts[10] = {5.0, 6.0, 5.5, 0.6, 2.8, 7.6, 4.99, 0.3, 7.7, 9.8};
        BST<float, float> float_bst;
        for (int i = 0; i < 10; i++)
        {
            float_bst.insert((float)i + 0.1, flts[i]);
        }
        string float_str = float_bst.to_string();
        if (float_str != "5 0.6 6 0.3 2.8 5.5 7.6 4.99 7.7 9.8")
        {
            cout << "Incorrect result of inserting floats. Expected 5 0.6 6 0.3 2.8 5.5 7.6 4.99 7.7 9.8 but got : " << float_str << endl;
        }

        // insert balanced, string data, char key
        char chrs[10] = {'e', 'c', 'g', 'a', 'd', 'f', 'i', 'b', 'h', 'j'};
        BST<string, char> char_bst;
        for (int i = 0; i < 10; i++)
        {
            char_bst.insert("dataaaa", chrs[i]);
        }
        string char_str = char_bst.to_string();
        if (char_str != "e c g a d f i b h j")
        {
            cout << "Incorrect result of inserting chars. Expected e c g a d f i b h j but got : " << char_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error inserting into bst : " << e.what() << endl;
    }
}

void test_get()
{
    try
    {
        BST<string, int> bst;
        string val = bst.get(0);
        if (val != "")
        {
            cout << "Incorrect get result from empty bst. Expected 0 but got " << val << endl;
        }
        // get root
        bst.insert("five", 5);
        val = bst.get(5);
        if (val != "five")
        {
            cout << "Incorrect get result. Expected \"five\" but got : " << val << endl;
        }
        // get right leaf
        bst.insert("seven", 7);
        val = bst.get(7);
        if (val != "seven")
        {
            cout << "Incorrect get result. Expected \"seven\" but got : " << val << endl;
        }
        // get left leaf
        bst.insert("three", 3);
        val = bst.get(3);
        if (val != "three")
        {
            cout << "Incorrect get result. Expected \"three\" but got : " << val << endl;
        }
        // get middle leaf
        bst.insert("one", 1);
        bst.insert("two", 2);
        val = bst.get(3);
        if (val != "three")
        {
            cout << "Incorrect get result. Expected \"three\" but got : " << val << endl;
        }
        // get val not in tree
        val = bst.get(8);
        if (val != "")
        {
            cout << "Incorrect get result. Expected empty string but got : " << val << endl;
        }
        // get removed val
        bst.remove(3);
        val = bst.get(3);
        if (val != "")
        {
            cout << "Incorrect get result. Expected empty string but got : " << val << endl;
        }

        // different types
        BST<int, char> char_bst;
        int cval = char_bst.get('a');
        if (cval != 0)
        {
            cout << "Incorrect get result from empty bst. Expected 0 but got " << cval << endl;
        }
        // get root
        char_bst.insert(1, 'a');
        cval = char_bst.get('a');
        if (cval != 1)
        {
            cout << "Incorrect get result. Expected 1 but got : " << cval << endl;
        }
        // get right leaf
        char_bst.insert(2, 'b');
        cval = char_bst.get('b');
        if (cval != 2)
        {
            cout << "Incorrect get result. Expected 2 but got : " << cval << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in getting data from bst : " << e.what() << endl;
    }
}

void test_remove()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;

        // test empty
        balanced_bst.remove(7);
        string bst_str = balanced_bst.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect result of removing key from empty tree. Expected empty but got : " << bst_str << endl;
        }

        // test nonempty
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        balanced_bst.remove(7);
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 8 1 3 6 9 4 10")
        {
            cout << "Incorrect result of removing 7. Expected 5 2 8 1 3 6 9 4 10 but got : " << bst_str << endl;
        }
        // remove leaf
        balanced_bst.remove(4);
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 8 1 3 6 9 10")
        {
            cout << "Incorrect result of removing 4. Expected 5 2 8 1 3 6 9 10 but got : " << bst_str << endl;
        }
        // remove root
        balanced_bst.remove(5);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 2 8 1 3 9 10")
        {
            cout << "Incorrect result of removing 5. Expected 6 2 8 1 3 9 10 but got : " << bst_str << endl;
        }
        // no left sub tree for removed key
        balanced_bst.remove(8);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 2 9 1 3 10")
        {
            cout << "Incorrect result of removing 8. Expected 6 2 9 1 3 10 but got : " << bst_str << endl;
        }
        // no right sub tree for removed key
        balanced_bst.remove(3);
        balanced_bst.remove(2);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 1 9 10")
        {
            cout << "Incorrect result of removing 2 and 3. Expected 6 1 9 10 but got : " << bst_str << endl;
        }
        // remove rest
        balanced_bst.remove(6);
        balanced_bst.remove(9);
        balanced_bst.remove(1);
        balanced_bst.remove(10);
        bst_str = balanced_bst.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect result of removing all values. Expected empty but got : " << bst_str << endl;
        }

        // remove when duplicate keys
        for (int i = 0; i < 20; i++)
        {
            balanced_bst.insert("some data", vals[i % 10]);
        }
        // remove root
        balanced_bst.remove(5);
        bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 7 1 3 6 9 1 2 4 6 8 10 3 4 7 8 9 10")
        {
            cout << "Incorrect result of removing 5 once. Expected 5 2 7 1 3 6 9 1 2 4 6 8 10 3 4 7 8 9 10 but got : " << bst_str << endl;
        }
        balanced_bst.remove(5);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 10")
        {
            cout << "Incorrect result of removing 5 twice. Expected 6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 10 but got : " << bst_str << endl;
        }
        // remove when successor is not leaf
        balanced_bst.insert("some data", 11);
        balanced_bst.insert("some data", 7);
        balanced_bst.remove(10);
        balanced_bst.remove(7);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 11")
        {
            cout << "Incorrect result of inserting and then removing 11 and 7. Expected 6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 11 but got : " << bst_str << endl;
        }

        // remove when key is not in tree
        balanced_bst.remove(12);
        bst_str = balanced_bst.to_string();
        if (bst_str != "6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 11")
        {
            cout << "Incorrect result of removing 12. Expected 6 2 7 1 3 6 9 1 2 4 8 10 3 4 7 8 9 11 but got : " << bst_str << endl;
        }

        // different types
        BST<int, int> int_bst;

        // test nonempty
        for (int i = 0; i < 10; i++)
        {
            int_bst.insert(i, vals[i]);
        }
        int_bst.remove(7);
        string int_str = int_bst.to_string();
        if (int_str != "5 2 8 1 3 6 9 4 10")
        {
            cout << "Incorrect result of removing 7. Expected 5 2 8 1 3 6 9 4 10 but got : " << int_str << endl;
        }
        // remove leaf
        int_bst.remove(4);
        int_str = int_bst.to_string();
        if (int_str != "5 2 8 1 3 6 9 10")
        {
            cout << "Incorrect result of removing 4. Expected 5 2 8 1 3 6 9 10 but got : " << int_str << endl;
        }
        // remove root
        int_bst.remove(5);
        int_str = int_bst.to_string();
        if (int_str != "6 2 8 1 3 9 10")
        {
            cout << "Incorrect result of removing 5. Expected 6 2 8 1 3 9 10 but got : " << int_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in removing node from bst : " << e.what() << endl;
    }
}

void test_max_data()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;

        // empty bst
        string max_str = balanced_bst.max_data();
        if (max_str != "")
        {
            cout << "Incorrect result of max_data. Expected empty but got : " << max_str << endl;
        }

        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }

        // max is leaf
        max_str = balanced_bst.max_data();
        if (max_str != "10 data")
        {
            cout << "Incorrect result of max_data. Expected \"10 data\" but got : " << max_str << endl;
        }
        // max has left child
        balanced_bst.remove(10);
        max_str = balanced_bst.max_data();
        if (max_str != "9 data")
        {
            cout << "Incorrect result of max_data. Expected \"9 data\" but got : " << max_str << endl;
        }
        // two maxes
        balanced_bst.remove(8);
        balanced_bst.remove(9);
        balanced_bst.insert("7 data", 7);
        max_str = balanced_bst.max_data();
        if (max_str != "7 data")
        {
            cout << "Incorrect result of max_data. Expected \"7 data\" but got : " << max_str << endl;
        }
        // max is root
        balanced_bst.remove(6);
        balanced_bst.remove(7);
        balanced_bst.remove(7);
        max_str = balanced_bst.max_data();
        if (max_str != "5 data")
        {
            cout << "Incorrect result of max_data. Expected \"5 data\" but got : " << max_str << endl;
        }
        // max is alone
        balanced_bst.remove(1);
        balanced_bst.remove(2);
        balanced_bst.remove(3);
        balanced_bst.remove(4);
        max_str = balanced_bst.max_data();
        if (max_str != "5 data")
        {
            cout << "Incorrect result of max_data. Expected \"5 data\" but got : " << max_str << endl;
        }
        // all removed
        balanced_bst.remove(5);
        max_str = balanced_bst.max_data();
        if (max_str != "")
        {
            cout << "Incorrect result of max_data. Expected empty but got : " << max_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining data of max node in bst : " << e.what() << endl;
    }
}

void test_max_key()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;

        // empty bst
        int max_k = balanced_bst.max_key();
        if (max_k)
        {
            cout << "Incorrect result of max_key. Expected empty but got : " << max_k << endl;
        }

        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }

        // max is leaf
        max_k = balanced_bst.max_key();
        if (max_k != 10)
        {
            cout << "Incorrect result of max_key. Expected 10 but got : " << max_k << endl;
        }
        // max has left child
        balanced_bst.remove(10);
        max_k = balanced_bst.max_key();
        if (max_k != 9)
        {
            cout << "Incorrect result of max_key. Expected 9 but got : " << max_k << endl;
        }
        // two maxes
        balanced_bst.remove(8);
        balanced_bst.remove(9);
        balanced_bst.insert("7 data", 7);
        max_k = balanced_bst.max_key();
        if (max_k != 7)
        {
            cout << "Incorrect result of max_key. Expected 7 but got : " << max_k << endl;
        }
        // max is root
        balanced_bst.remove(6);
        balanced_bst.remove(7);
        balanced_bst.remove(7);
        max_k = balanced_bst.max_key();
        if (max_k != 5)
        {
            cout << "Incorrect result of max_key. Expected 5 but got : " << max_k << endl;
        }
        // max is alone
        balanced_bst.remove(1);
        balanced_bst.remove(2);
        balanced_bst.remove(3);
        balanced_bst.remove(4);
        max_k = balanced_bst.max_key();
        if (max_k != 5)
        {
            cout << "Incorrect result of max_key. Expected 5 but got : " << max_k << endl;
        }
        // all removed
        balanced_bst.remove(5);
        max_k = balanced_bst.max_key();
        if (max_k)
        {
            cout << "Incorrect result of max_key. Expected empty but got : " << max_k << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining key of max node in bst : " << e.what() << endl;
    }
}

void test_min_data()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;

        // empty bst
        string min_str = balanced_bst.min_data();
        if (min_str != "")
        {
            cout << "Incorrect result of max_data. Expected empty but got : " << min_str << endl;
        }

        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }

        // min is leaf
        min_str = balanced_bst.min_data();
        if (min_str != "1 data")
        {
            cout << "Incorrect result of min_data. Expected \"1 data\" but got : " << min_str << endl;
        }
        // min has right child
        balanced_bst.remove(1);
        min_str = balanced_bst.min_data();
        if (min_str != "2 data")
        {
            cout << "Incorrect result of min_data. Expected \"2 data\" but got : " << min_str << endl;
        }
        // two mins
        balanced_bst.insert("2 data", 2);
        min_str = balanced_bst.min_data();
        if (min_str != "2 data")
        {
            cout << "Incorrect result of min_data. Expected \"2 data\" but got : " << min_str << endl;
        }
        // min is root
        balanced_bst.remove(3);
        balanced_bst.remove(4);
        balanced_bst.remove(2);
        balanced_bst.remove(2);
        min_str = balanced_bst.min_data();
        if (min_str != "5 data")
        {
            cout << "Incorrect result of min_data. Expected \"5 data\" but got : " << min_str << endl;
        }
        // min is negative
        balanced_bst.insert("-2 data", -2);
        min_str = balanced_bst.min_data();
        if (min_str != "-2 data")
        {
            cout << "Incorrect result of min_data. Expected \"-2 data\" but got : " << min_str << endl;
        }
        // min is alone
        balanced_bst.remove(-2);
        balanced_bst.remove(7);
        balanced_bst.remove(6);
        balanced_bst.remove(9);
        balanced_bst.remove(8);
        balanced_bst.remove(10);
        min_str = balanced_bst.min_data();
        if (min_str != "5 data")
        {
            cout << "Incorrect result of min_data. Expected \"5 data\" but got : " << min_str << endl;
        }
        // all removed
        balanced_bst.remove(5);
        min_str = balanced_bst.min_data();
        if (min_str != "")
        {
            cout << "Incorrect result of max_data. Expected empty but got : " << min_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining data of min node in bst : " << e.what() << endl;
    }
}

void test_min_key()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;

        // empty bst
        int min_k = balanced_bst.min_key();
        if (min_k)
        {
            cout << "Incorrect result of min_key. Expected empty but got : " << min_k << endl;
        }

        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }

        // min is leaf
        min_k = balanced_bst.min_key();
        if (min_k != 1)
        {
            cout << "Incorrect result of min_key. Expected 1 but got : " << min_k << endl;
        }
        // min has right child
        balanced_bst.remove(1);
        min_k = balanced_bst.min_key();
        if (min_k != 2)
        {
            cout << "Incorrect result of min_key. Expected 2 but got : " << min_k << endl;
        }
        // two mins
        balanced_bst.insert("2 data", 2);
        min_k = balanced_bst.min_key();
        if (min_k != 2)
        {
            cout << "Incorrect result of max_key. Expected 2 but got : " << min_k << endl;
        }
        // min is root
        balanced_bst.remove(2);
        balanced_bst.remove(2);
        balanced_bst.remove(3);
        balanced_bst.remove(4);
        min_k = balanced_bst.min_key();
        if (min_k != 5)
        {
            cout << "Incorrect result of min_key. Expected 5 but got : " << min_k << endl;
        }
        // min is negative
        balanced_bst.insert("-2 data", -2);
        min_k = balanced_bst.min_key();
        if (min_k != -2)
        {
            cout << "Incorrect result of min_data. Expected -2 but got : " << min_k << endl;
        }
        // min is alone
        balanced_bst.remove(-2);
        balanced_bst.remove(10);
        balanced_bst.remove(8);
        balanced_bst.remove(9);
        balanced_bst.remove(6);
        balanced_bst.remove(7);
        min_k = balanced_bst.min_key();
        if (min_k != 5)
        {
            cout << "Incorrect result of min_key. Expected 5 but got : " << min_k << endl;
        }
        // all removed
        balanced_bst.remove(5);
        min_k = balanced_bst.min_key();
        if (min_k)
        {
            cout << "Incorrect result of min_key. Expected empty but got : " << min_k << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining key of min node in bst : " << e.what() << endl;
    }
}

void test_successor()
{
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        // empty tree
        int succ = balanced_bst.successor(4);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of a key in an empty tree. Expected 0 but got : " << succ << endl;
        }

        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        // successor is root
        succ = balanced_bst.successor(4);
        if (succ != 5)
        {
            cout << "Incorrect result of successor of 4. Expected 5 but got : " << succ << endl;
        }
        // successor is in right child subtree
        succ = balanced_bst.successor(7);
        if (succ != 8)
        {
            cout << "Incorrect result of successor of 7. Expected 8 but got : " << succ << endl;
        }
        // no successor
        succ = balanced_bst.successor(10);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of 10. Expected 0 but got : " << succ << endl;
        }
        // successor is in ancestors and is not root
        succ = balanced_bst.successor(1);
        if (succ != 2)
        {
            cout << "Incorrect result of successor of 1. Expected 2 but got : " << succ << endl;
        }
        // key is not in tree
        succ = balanced_bst.successor(11);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of 11. Expected 0 but got : " << succ << endl;
        }
        // duplicate successor
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        succ = balanced_bst.successor(7);
        if (succ != 7)
        {
            cout << "Incorrect result of successor of 7. Expected 7 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(5);
        if (succ != 5)
        {
            cout << "Incorrect result of successor of 5. Expected 5 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(4);
        if (succ != 4)
        {
            cout << "Incorrect result of successor of 4. Expected 4 but got : " << succ << endl;
        }
        // low keys
        balanced_bst.insert("data", 0);
        succ = balanced_bst.successor(0);
        if (succ != 1)
        {
            cout << "Incorrect result of successor of 0. Expected 1 but got : " << succ << endl;
        }
        balanced_bst.insert("data", -1);
        succ = balanced_bst.successor(-1);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of -1. Expected 0 but got : " << succ << endl;
        }

        // right unbalanced
        int order[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        BST<string, int> right_bst;
        for (int i = 0; i < 10; i++)
        {
            right_bst.insert(to_string(order[i]) + " data", order[i]);
        }
        // root
        succ = right_bst.successor(1);
        if (succ != 2)
        {
            cout << "Incorrect result of successor of 1. Expected 2 but got : " << succ << endl;
        }
        // middle
        succ = right_bst.successor(5);
        if (succ != 6)
        {
            cout << "Incorrect result of successor of 5. Expected 6 but got : " << succ << endl;
        }
        // leaf
        succ = right_bst.successor(10);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of 10. Expected 0 but got : " << succ << endl;
        }

        // left unbalanced
        BST<string, int> left_bst;
        for (int i = 9; i >= 0; i--)
        {
            left_bst.insert(to_string(order[i]) + " data", order[i]);
        }
        // leaf
        succ = left_bst.successor(1);
        if (succ != 2)
        {
            cout << "Incorrect result of successor of 1. Expected 2 but got : " << succ << " and " << left_bst.to_string() << endl;
        }
        // middle
        succ = left_bst.successor(5);
        if (succ != 6)
        {
            cout << "Incorrect result of successor of 5. Expected 6 but got : " << succ << endl;
        }
        // root
        succ = left_bst.successor(10);
        if (succ != 0)
        {
            cout << "Incorrect result of successor of 10. Expected 0 but got : " << succ << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in determining successor in bst : " << e.what() << endl;
    }
}

void test_in_order()
{
    try
    {
        // bst is empty
        BST<string, int> bst;
        string bst_str = bst.in_order();
        if (bst_str != "")
        {
            cout << "Incorrect in_order result for empty bst. Got : " << bst_str << endl;
        }

        // insert keys in order
        for (int i = 1; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        bst_str = bst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys 1-10 in order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        // insert keys in reverse order
        BST<string, int> rbst;
        for (int i = 10; i >= 1; i--)
        {
            rbst.insert("some data", i);
        }
        bst_str = rbst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys 1-10 in reverse order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }

        // insert balanced keys
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10}. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }
        // in order duplicates
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        bst_str = balanced_bst.in_order();
        if (bst_str != "1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10")
        {
            cout << "Incorrect in_order result after inserting keys {5, 2, 7, 1, 3, 4, 6, 9, 8, 10} twice. Expected 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 10 10 but got : " << bst_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting keys in_order from bst : " << e.what() << endl;
    }
}

void test_trim()
{
    try
    {
        // trimming empty tree
        BST<string, int> bst;
        bst.trim(1, 2);
        string bst_str = bst.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect tree after trimming empty bst with low=1, high=2. Expected empty but got : " << bst_str << endl;
        }

        // trimming non-empty tree
        int vals[3] = {1, 0, 2};
        for (int i = 0; i < 3; i++)
        {
            bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        bst.trim(1, 2);
        bst_str = bst.to_string();
        if (bst_str != "1 2")
        {
            cout << "Incorrect tree after trimming 1 0 2 with low=1, high=2. Expected 1 2 but got : " << bst_str << endl;
        }
        // trimming more complex tree
        BST<string, int> bst2;
        int vals2[5] = {3, 0, 4, 2, 1};
        for (int i = 0; i < 5; i++)
        {
            bst2.insert(to_string(vals2[i]) + " data", vals2[i]);
        }
        bst2.trim(1, 3);
        bst_str = bst2.to_string();
        if (bst_str != "3 2 1")
        {
            cout << "Incorrect tree after trimming 3 0 4 2 1 with low=1, high=3. Expected 3 2 1 but got : " << bst_str << endl;
        }
        // trimming same bounds and tree twice
        bst2.trim(1, 3);
        bst_str = bst2.to_string();
        if (bst_str != "3 2 1")
        {
            cout << "Incorrect tree after trimming 3 0 4 2 1 twice with low=1, high=3. Expected 3 2 1 but got : " << bst_str << endl;
        }
        // trimming duplicates
        for (int i = 0; i < 10; i++)
        {
            bst2.insert(to_string(vals2[i]) + " data", vals2[i % 5]);
        }
        bst2.trim(1, 3);
        bst_str = bst2.to_string();
        if (bst_str != "3 2 3 1 2 3 1 2 1")
        {
            cout << "Incorrect tree after trimming 3 2 3 1 2 4 0 1 2 3 4 0 1 with low=1, high=3. Expected 3 2 3 1 2 3 1 2 1 but got : " << bst_str << endl;
        }
        bst2.remove(3);
        bst2.remove(3);
        bst2.remove(1);
        bst2.remove(1);
        bst2.remove(2);
        bst2.remove(2);
        // trimming out of bounds
        bst2.trim(4, 5);
        bst_str = bst2.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect tree after trimming 3 2 1 with low=4, high=5. Expected empty but got : " << bst_str << endl;
        }
        // trimming partially out of bounds, trimming root
        bst2.insert("some data", 3);
        bst2.insert("some data", 2);
        bst2.insert("some data", 1);
        bst2.trim(0, 2);
        bst_str = bst2.to_string();
        if (bst_str != "2 1")
        {
            cout << "Incorrect tree after trimming 3 2 1 with low=0, high=2. Expected 2 1 but got : " << bst_str << endl;
        }
        bst2.trim(2, 4);
        bst_str = bst2.to_string();
        if (bst_str != "2")
        {
            cout << "Incorrect tree after trimming 2 1 with low=2, high=4. Expected 2 but got : " << bst_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in trimming the bst : " << e.what() << endl;
    }
};

void test_binhex()
{
    try
    {
        BST<string, string> *bst1 = create_bst("binhex.txt");
        string bin1 = "111010100101";
        string expected_hex1 = "EA5";

        string hex1 = convert(bst1, bin1);
        delete bst1;

        if (hex1 != expected_hex1)
        {
            cout << "Incorrect result converting " << bin1 << " to hex. Expected : " << expected_hex1 << ", but got : " << hex1 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    try
    {
        BST<string, string> *bst2 = create_bst("binhex.txt");
        string bin2 = "110101";
        string expected_hex2 = "35";

        string hex2 = convert(bst2, bin2);
        delete bst2;

        if (hex2 != expected_hex2)
        {
            cout << "Incorrect result converting " << bin2 << " to hex. Expected : " << expected_hex2 << ", but got : " << hex2 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    try
    {
        BST<string, string> *bst3 = create_bst("binhex.txt");
        string bin3 = "11111010100101";
        string expected_hex3 = "3EA5";

        string hex3 = convert(bst3, bin3);
        delete bst3;

        if (hex3 != expected_hex3)
        {
            cout << "Incorrect result converting " << bin3 << " to hex. Expected : " << expected_hex3 << ", but got : " << hex3 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    try
    {
        BST<string, string> *bst3 = create_bst("binhex.txt");
        string bin3 = "0";
        string expected_hex3 = "0";

        string hex3 = convert(bst3, bin3);
        delete bst3;

        if (hex3 != expected_hex3)
        {
            cout << "Incorrect result converting " << bin3 << " to hex. Expected : " << expected_hex3 << ", but got : " << hex3 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }

    try
    {
        BST<string, string> *bst3 = create_bst("binhex.txt");
        string bin3 = "1";
        string expected_hex3 = "1";

        string hex3 = convert(bst3, bin3);
        delete bst3;

        if (hex3 != expected_hex3)
        {
            cout << "Incorrect result converting " << bin3 << " to hex. Expected : " << expected_hex3 << ", but got : " << hex3 << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error converting binary to hex : " << e.what() << endl;
    }
}

void test_trim_edge_cases()
{
    try
    {
        // Test 1: low > high (invalid range)
        BST<string, int> bst1;
        bst1.insert("data", 5);
        bst1.insert("data", 3);
        bst1.insert("data", 7);
        bst1.trim(10, 5);
        string bst_str = bst1.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect trim with low > high. Expected empty but got : " << bst_str << endl;
        }

        // Test 2: low == high (single value range)
        BST<string, int> bst2;
        bst2.insert("data", 5);
        bst2.insert("data", 5); // duplicate
        bst2.insert("data", 3);
        bst2.insert("data", 7);
        bst2.trim(5, 5);
        bst_str = bst2.to_string();
        if (bst_str != "5 5")
        {
            cout << "Incorrect trim with low == high. Expected 5 5 but got : " << bst_str << endl;
        }

        // Test 3: Single element, in range
        BST<string, int> bst3;
        bst3.insert("data", 5);
        bst3.trim(1, 10);
        bst_str = bst3.to_string();
        if (bst_str != "5")
        {
            cout << "Incorrect trim single element in range. Expected 5 but got : " << bst_str << endl;
        }

        // Test 4: Single element, out of range
        BST<string, int> bst4;
        bst4.insert("data", 5);
        bst4.trim(10, 20);
        bst_str = bst4.to_string();
        if (bst_str != "")
        {
            cout << "Incorrect trim single element out of range. Expected empty but got : " << bst_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in trim edge cases : " << e.what() << endl;
    }
}

void test_boundary_values()
{
    try
    {
        // Test with negative numbers
        BST<string, int> bst;
        bst.insert("neg", -100);
        bst.insert("zero", 0);
        bst.insert("pos", 100);

        int min_k = bst.min_key();
        if (min_k != -100)
        {
            cout << "Incorrect min_key with negative values. Expected -100 but got : " << min_k << endl;
        }

        int max_k = bst.max_key();
        if (max_k != 100)
        {
            cout << "Incorrect max_key with mixed values. Expected 100 but got : " << max_k << endl;
        }

        // Test with zero
        string zero_data = bst.get(0);
        if (zero_data != "zero")
        {
            cout << "Incorrect get for key 0. Expected \"zero\" but got : " << zero_data << endl;
        }

        // Test successor with negatives
        int succ = bst.successor(-100);
        if (succ != 0)
        {
            cout << "Incorrect successor of -100. Expected 0 but got : " << succ << endl;
        }

        // Test with large numbers
        BST<string, int> large_bst;
        large_bst.insert("large", 2147483647); // INT_MAX
        large_bst.insert("mid", 0);
        large_bst.insert("small", -2147483648); // INT_MIN

        int large_max = large_bst.max_key();
        if (large_max != 2147483647)
        {
            cout << "Incorrect max_key with INT_MAX. Expected 2147483647 but got : " << large_max << endl;
        }

        int large_min = large_bst.min_key();
        if (large_min != -2147483648)
        {
            cout << "Incorrect min_key with INT_MIN. Expected -2147483648 but got : " << large_min << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in boundary value tests : " << e.what() << endl;
    }
}

void test_empty_string_and_zeros()
{
    try
    {
        // Test with empty string as data
        BST<string, int> bst1;
        bst1.insert("", 5);
        bst1.insert("nonempty", 3);
        string result = bst1.get(5);
        if (result != "")
        {
            cout << "Incorrect get for empty string data. Expected empty string but got : \"" << result << "\"" << endl;
        }

        // Test with zero key
        BST<int, int> bst2;
        bst2.insert(100, 0);
        bst2.insert(200, 5);
        bst2.insert(50, -5);
        int zero_result = bst2.get(0);
        if (zero_result != 100)
        {
            cout << "Incorrect get for zero key. Expected 100 but got : " << zero_result << endl;
        }

        // Test with zero data
        bst2.insert(0, 10);
        int result2 = bst2.get(10);
        if (result2 != 0)
        {
            cout << "Incorrect get for zero data. Expected 0 but got : " << result2 << endl;
        }

        // Test min/max with zeros
        int min_k = bst2.min_key();
        if (min_k != -5)
        {
            cout << "Incorrect min_key with zeros. Expected -5 but got : " << min_k << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in empty string and zero tests : " << e.what() << endl;
    }
}

void test_operation_sequences()
{
    try
    {
        // Sequence 1: insert → trim → remove → get
        BST<string, int> bst1;
        bst1.insert("a", 5);
        bst1.insert("b", 3);
        bst1.insert("c", 7);
        bst1.insert("d", 1);
        bst1.insert("e", 9);

        bst1.trim(3, 7);
        string bst_str = bst1.to_string();
        if (bst_str != "5 3 7")
        {
            cout << "Incorrect result after trim in sequence. Expected 5 3 7 but got : " << bst_str << endl;
        }

        bst1.remove(3);
        string result = bst1.get(5);
        if (result != "a")
        {
            cout << "Incorrect get after remove in sequence. Expected \"a\" but got : " << result << endl;
        }

        // Sequence 2: Multiple removes then operations
        BST<string, int> bst2;
        for (int i = 1; i <= 10; i++)
        {
            bst2.insert("data", i);
        }

        bst2.remove(5);
        bst2.remove(3);
        bst2.remove(7);

        int succ = bst2.successor(4);
        if (succ != 6)
        {
            cout << "Incorrect successor after multiple removes. Expected 6 but got : " << succ << endl;
        }

        int min_k = bst2.min_key();
        if (min_k != 1)
        {
            cout << "Incorrect min_key after multiple removes. Expected 1 but got : " << min_k << endl;
        }

        int max_k = bst2.max_key();
        if (max_k != 10)
        {
            cout << "Incorrect max_key after multiple removes. Expected 10 but got : " << max_k << endl;
        }

        // Sequence 3: Alternating insert/remove
        BST<string, int> bst3;
        bst3.insert("x", 5);
        bst3.insert("y", 3);
        bst3.remove(5);
        bst3.insert("z", 7);
        bst3.insert("w", 5);
        bst3.remove(3);

        bst_str = bst3.to_string();
        if (bst_str != "7 5")
        {
            cout << "Incorrect result after alternating operations. Expected 7 5 but got : " << bst_str << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in operation sequence tests : " << e.what() << endl;
    }
}

void test_additional_template_types()
{
    try
    {
        // Test with double
        BST<double, double> double_bst;
        double_bst.insert(3.14, 1.5);
        double_bst.insert(2.71, 0.5);
        double_bst.insert(1.41, 2.5);

        double result = double_bst.get(1.5);
        if (abs(result - 3.14) > 0.001)
        {
            cout << "Incorrect get for double type. Expected 3.14 but got : " << result << endl;
        }

        // Test with string/string
        BST<string, string> str_bst;
        str_bst.insert("value1", "key1");
        str_bst.insert("value2", "key2");
        str_bst.insert("value3", "key3");

        string str_result = str_bst.get("key2");
        if (str_result != "value2")
        {
            cout << "Incorrect get for string/string type. Expected \"value2\" but got : " << str_result << endl;
        }

        string min_str = str_bst.min_key();
        if (min_str != "key1")
        {
            cout << "Incorrect min_key for string keys. Expected \"key1\" but got : " << min_str << endl;
        }

        // Test with long
        BST<long, long> long_bst;
        long_bst.insert(1000000L, 500000L);
        long_bst.insert(2000000L, 1500000L);
        long_bst.insert(500000L, 250000L);

        long long_result = long_bst.get(500000L);
        if (long_result != 1000000L)
        {
            cout << "Incorrect get for long type. Expected 1000000 but got : " << long_result << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in additional template type tests : " << e.what() << endl;
    }
}

void test_complex_successor()
{
    try
    {
        // Test with 3+ duplicate keys
        BST<string, int> bst;
        bst.insert("first", 5);
        bst.insert("second", 5);
        bst.insert("third", 5);
        bst.insert("fourth", 3);
        bst.insert("fifth", 7);

        int succ = bst.successor(5);
        if (succ != 5)
        {
            cout << "Incorrect successor with 3+ duplicates. Expected 5 but got : " << succ << endl;
        }

        // Remove one and test again
        bst.remove(5);
        succ = bst.successor(5);
        if (succ != 5)
        {
            cout << "Incorrect successor after removing one of 3 duplicates. Expected 5 but got : " << succ << endl;
        }

        // Remove all duplicates
        bst.remove(5);
        bst.remove(5);
        succ = bst.successor(3);
        if (succ != 7)
        {
            cout << "Incorrect successor after removing all duplicates. Expected 7 but got : " << succ << endl;
        }

        // Complex tree with multiple duplicate levels
        BST<string, int> bst2;
        int vals[] = {5, 3, 7, 3, 5, 7, 2, 4, 6, 8};
        for (int i = 0; i < 10; i++)
        {
            bst2.insert("data", vals[i]);
        }

        succ = bst2.successor(4);
        if (succ != 5)
        {
            cout << "Incorrect successor in complex duplicate tree. Expected 5 but got : " << succ << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error in complex successor tests : " << e.what() << endl;
    }
}

void time_test()
{
    BST<string, int> bst;
    // Insert many elements
    int vals[8] = {6, 1, 2, 7, 2, 8, 9, 10};
    for (int i = 0; i < 8; i++)
    {
        bst.insert("data", i);
    }
    BST<string, int> bst1;
    // Insert many elements
    int vals2[12] = {5, 1, 3, 7, 1, 8, 2, 10, 1, 2, 142, 12};
    for (int i = 0; i < 12; i++)
    {
        bst1.insert("data", i);
    }
    int total = 0;

    int val = rand() % 100;
    auto begin = std::chrono::high_resolution_clock::now();
    bst.insert("data", val);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "insert time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    bst.get(val);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "get time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    bst.successor(val);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "successor time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    bst.remove(val);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "remove time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    begin = std::chrono::high_resolution_clock::now();
    bst.trim(3, 9);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "trim time test took " << elapsed.count() << " nanoseconds" << endl;
    total += elapsed.count();

    cout << "Total time: " << total << endl;
}

int main()
{

    string file_name = "usecase.cpp";
    cout << endl
         << "Running tests for " << file_name << endl
         << endl;

    time_test();

    test_empty();
    test_insert();
    test_get();
    test_remove();
    test_max_data();
    test_max_key();
    test_min_data();
    test_min_key();
    test_successor();
    test_in_order();
    test_trim();
    test_binhex();
    test_trim_edge_cases();
    test_boundary_values();
    test_empty_string_and_zeros();
    test_operation_sequences();
    test_additional_template_types();
    test_complex_successor();

    cout << "Testing completed" << endl;

    return 0;
}
