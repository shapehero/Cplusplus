#include <iostream>

using namespace std;

typedef struct list_node {
    int data;
    list_node *next;
}list_node_t;

void print_list(list_node *pHead)
{
    if (pHead == NULL)
        return;
    list_node *pNode = pHead;
    while (pNode != NULL)
    {
        cout << pNode->data << "  ";
        pNode = pNode->next;
    }
    cout << endl;
}

bool is_loop(list_node *pHead)
{
    if (pHead == NULL)
        return false;
    list_node *pSlow = pHead;
    list_node *pFast = pHead;
    while (pFast->next != NULL)
    {
        pSlow = pSlow->next;
        pFast = pFast->next->next;
        if (pSlow == pFast)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    //1,create list
    int arr[] = {1, 3, 5, 7, 8, 9, 2, 4, 6};
    int len = sizeof(arr)/sizeof(int);
    list_node *pHead = NULL;
    list_node *pNode;
    for (int i = 0; i < len; i++)
    {
        list_node *pNew = new list_node;
        pNew->data = arr[i];
        pNew->next = NULL;

        if (pHead == NULL)
        {
            pHead = pNew;
        }
        else
        {
            pNode->next = pNew;
        }
        pNode = pNew;
    }
    print_list(pHead);
    //is_loop false
    bool loop_exist = false;
    loop_exist = is_loop(pHead);
    if (loop_exist == true)
    {
        cout << "Loop exist in the list." << endl;
    }
    else
    {
        cout << "Loop not exist in the list." << endl;
    }
    
    // make a loop
    cout << "Make a loop in the list." << endl;
    list_node *pTmpNode = pHead;
    while (pTmpNode->next != NULL)
    {
        pTmpNode = pTmpNode->next;
    }
    pTmpNode->next = pHead;

    //is_loop true
    
    loop_exist = is_loop(pHead);
    if (loop_exist == true)
    {
        cout << "Loop exist in the list." << endl;
    }
    else
    {
        cout << "Loop not exist in the list." << endl;
    }

    //destroy list
    pTmpNode->next = NULL;
    list_node *pDelNode;
    while (pHead != NULL)
    {
        pDelNode = pHead->next;
        delete pHead;
        pHead = pDelNode;
    }

    return 0;
}