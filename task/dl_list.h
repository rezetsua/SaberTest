#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <random>
#include <map>

using namespace std;

struct ListNode {
    ListNode *prev;
    ListNode *next;
    ListNode *rand;
    string data;
};

class DLList
{
public:
    DLList();

    void PushBack(string str);
    void FillRandMembers();
    void PrintList();

    void Serialize (FILE * file);
    void Deserialize (FILE * file);

private:
    ListNode *head;
    ListNode *tail;
    int count;
};

#endif // DLLIST_H
