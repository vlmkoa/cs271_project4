//
//  test_bst_example.cpp
//  CS 271 BST Project
//
//  Created by Ava, Sunho, Ryan
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
            cout << "Incorrect empty result when all items were removed from bst. Result: " << bst_str << " end result." << endl;
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
        bst.insert("one", 1);
        val = bst.get(1);
        if (val != "one")
        {
            cout << "Incorrect get result. Expected \"one\" but got : " << val << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        balanced_bst.remove(7);
        string bst_str = balanced_bst.to_string();
        if (bst_str != "5 2 8 1 3 6 9 4 10")
        {
            cout << "Incorrect result of removing 7. Expected 5 2 8 1 3 6 9 4 10 but got : " << bst_str << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        string max_str = balanced_bst.max_data();
        if (max_str != "10 data")
        {
            cout << "Incorrect result of max_data. Expected \"10 data\" but got : " << max_str << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        int max_k = balanced_bst.max_key();
        if (max_k != 10)
        {
            cout << "Incorrect result of max_key. Expected 10 but got : " << max_k << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        string min_str = balanced_bst.min_data();
        if (min_str != "1 data")
        {
            cout << "Incorrect result of min_data. Expected \"1 data\" but got : " << min_str << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        int min_k = balanced_bst.min_key();
        if (min_k != 1)
        {
            cout << "Incorrect result of min_key. Expected 10 but got : " << min_k << endl;
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
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        int succ = balanced_bst.successor(4);
        if (succ != 5)
        {
            cout << "Incorrect result of successor of 4. Expected 5 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(7);
        if (succ != 8)
        {
            cout << "Incorrect result of successor of 7. Expected 8 but got : " << succ << endl;
        }
        succ = balanced_bst.successor(10);
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
        BST<string, int> bst;
        for (int i = 1; i <= 10; i++)
        {
            bst.insert("some data", i);
        }
        string bst_str = bst.in_order();
        if (bst_str != "1 2 3 4 5 6 7 8 9 10")
        {
            cout << "Incorrect in_order result after inserting keys 1-10 in order. Expected 1 2 3 4 5 6 7 8 9 10 but got : " << bst_str << endl;
        }
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
        BST<string, int> bst;
        int vals[3] = {1, 0, 2};
        for (int i = 0; i < 3; i++)
        {
            bst.insert(to_string(vals[i]) + " data", vals[i]);
        }
        bst.trim(1, 2);
        string bst_str = bst.to_string();
        if (bst_str != "1 2")
        {
            cout << "Incorrect tree after trimming 1 0 2 with low=1, high=2. Expected 1 2 but got : " << bst_str << endl;
        }
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

    cout << "Testing completed" << endl;

    return 0;
}
