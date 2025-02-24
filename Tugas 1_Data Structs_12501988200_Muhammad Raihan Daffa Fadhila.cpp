#include <stdio.h>
#include <stdlib.h>

struct tnode
{
    int x;
    struct tnode *next;
    struct tnode *prev;
} *head, *tail, *curr;

void push_front(int value)
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL)
    {
        head = tail = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
        head->prev = NULL;
    }
}

void push_back(int value)
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL)
    {
        head = tail = node;
        tail->next = NULL;
        tail->prev = NULL;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
        tail->next = NULL;
    }
}

void push_mid(int value, int searchKey)
{
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;

    if (head == NULL)
    {
        head = tail = node;
        node->next = NULL;
        node->prev = NULL;
    }
    else
    {
        struct tnode *curr = head;
        while (curr != NULL)
        {
            if (curr->x == searchKey)
            {
                if (curr == tail)
                {
                    push_back(value);
                }
                else
                {
                    node->next = curr->next;
                    node->prev = curr;
                    curr->next->prev = node;
                    curr->next = node;
                }
                return;
            }
            curr = curr->next;
        }
        printf("Data %d is not found\n", searchKey);
    }
}

void del_back()
{
    if (head == NULL)
    {
        printf("There is no data\n");
    }
    else
    {
        if (head == tail)
        {
            free(head);
            head = tail = NULL;
        }
        else
        {
            struct tnode *del = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(del);
        }
    }
}

void del_front()
{
    if (head == NULL)
    {
        printf("There is no data\n");
    }
    else
    {
        if (head == tail)
        {
            free(head);
            head = tail = NULL;
        }
        else
        {
            struct tnode *del = head;
            head = head->next;
            head->prev = NULL;
            free(del);
        }
    }
}

void del_mid(int searchKey)
{
    if (head == NULL)
    {
        printf("There is no data\n");
        return;
    }
    
    struct tnode *curr = head;
    while (curr != NULL)
    {
        if (curr->x == searchKey)
        {
            if (curr == head)
            {
                del_front();
            }
            else if (curr == tail)
            {
                del_back();
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d is not found\n", searchKey);
}

void printList()
{
    if (head == NULL)
    {
        printf("There is no data\n");
        return;
    }

    curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->x);
        curr = curr->next;
    }
    printf("\n");
}

int main()
{
    printf("Linked List Operations\n");

    push_front(76);
    push_front(90);
    push_front(45);
    push_back(100);
    push_mid(55, 90);
    del_back();
    del_front();
    del_mid(55);
    
    printList();

    return 0;
}
