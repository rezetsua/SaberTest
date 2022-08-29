#include "dl_list.h"

DLList::DLList() : head(nullptr), tail(nullptr), count(0)
{

}

void DLList::PushBack(string str)
{
    ListNode *temp = new ListNode;
    temp->prev = tail;
    temp->next = nullptr;
    temp->rand = nullptr;
    temp->data = str;

    if (head == nullptr)
        head = temp;
    else
        tail->next = temp;

    tail = temp;
    ++count;
}

void DLList::FillRandMembers()
{
    // Create vector for get ListNode* by index
    vector<ListNode*> listVec;
    listVec.reserve(count);
    for (ListNode *cur = head; cur != nullptr; cur = cur->next)
        listVec.push_back(cur);

    // In each ListNode's rand member put listVec[random index]
    random_device rd;
    mt19937 mersenne(rd());
    uniform_int_distribution<> distribution(0, count - 1);
    for (ListNode *cur = head; cur != nullptr; cur = cur->next)
        cur->rand = listVec[distribution(mersenne)];
}

void DLList::PrintList()
{
    int lcount = 0;
    for (ListNode *cur = head; cur != nullptr; cur = cur->next, ++lcount)
        printf("%d\t current: %s\t random: %s\n", lcount, cur->data.c_str(), cur->rand->data.c_str());
}

void DLList::Serialize(FILE *file)
{
    // File structure:
    // count
    // dataSize0 + data0 .. dataSizeN + dataN
    // randIndex0 .. randIndexN

    fwrite(&count, sizeof(int), 1, file); // count

    map<ListNode*, int> m; // Allow to get node's index by address
    int index = 0;
    for (ListNode *cur = head; cur != nullptr; cur = cur->next, ++index) {
        int len = cur->data.size();
        fwrite(&len, sizeof(int), 1, file); // dataSizeI
        fwrite(cur->data.c_str(), sizeof(char), cur->data.size(), file); // dataI

        m.insert(make_pair(cur, index));
    }

    for (ListNode *cur = head; cur != nullptr; cur = cur->next)
        fwrite(&m[cur->rand], sizeof(int), 1, file); // randIndexI
}

void DLList::Deserialize(FILE *file)
{
    int listCount = 0;
    fread(&listCount, sizeof(int), 1, file);

    // Create vector for get ListNode* by index
    vector<ListNode*> listVec;
    listVec.reserve(count);

    // Fill node's data and listVec
    for (int i = 0; i < listCount; ++i) {
        int len = 0;
        fread(&len, sizeof(int), 1, file);

        string temp;
        temp.resize(len);
        fread(&temp[0], sizeof(char), len, file);

        PushBack(temp);
        listVec.push_back(tail);
    }

    // Fill node's rand member
    for (ListNode *cur = head; cur != nullptr; cur = cur->next) {
        int index = 0;
        fread(&index, sizeof(int), 1, file);
        cur->rand = listVec[index];
    }
}
