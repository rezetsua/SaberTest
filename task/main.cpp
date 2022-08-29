#include "dl_list.h"
#include <bitset>

using namespace std;

template <typename T>
void PrintNumberBinaryForm(T num) {
    char digits = sizeof (num) * 8 - 2; // Skip signed bit and -1 for shift
    T mask = static_cast<T>(1) << digits; // Mask for getting the next bit after the sign bit

    num < 0 ? printf("1") : printf("0"); // Print signed bit
    for (; mask; mask >>= 1)
        printf("%c", (num & mask) ? '1' : '0');
    printf("\n");
}

void RemoveDups(char* str) {
    char *cur = &str[1];
    char *nonDup = &str[1]; // Next non dublicate element
    char unqElem = str[0]; // Last unique element
    bool strChanged = false;

    while (*nonDup != '\0') {
        while (*nonDup != '\0' && *nonDup == unqElem)
            ++nonDup;

        if (strChanged || *cur == unqElem) {
            *cur = *nonDup;
            strChanged = true;
        }

        unqElem = *cur;
        ++cur;
    }
}

void TestTask3(const char* filePath) {
    DLList list;

    list.PushBack("0dsf");
    list.PushBack("1qgg");
    list.PushBack("2fahg");
    list.PushBack("3gqv");
    list.PushBack("4sava");
    list.FillRandMembers();

    list.PrintList();

    FILE* file = fopen(filePath, "wb");
    list.Serialize(file);
    fclose(file);

    DLList listClone;
    file = fopen(filePath, "rb");
    listClone.Deserialize(file);

    printf("\n");
    listClone.PrintList();
}

int main()
{
    // Task 1
//    int num = 1245;
//    PrintNumberBinaryForm(num);
//    // For check accuracy
//    bitset<sizeof (num)*8> b(num);
//    cout << b << endl;

    // Task 2
//    char data[] = "abb  CCc ddd";
//    RemoveDups(data);
//    printf("%s\n", data);

    // Task 3
//    TestTask3("/home/urii/Документы/list.dat");
    return 0;
}
