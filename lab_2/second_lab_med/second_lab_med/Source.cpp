#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* newNode(int data, struct Node* nextNode)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = nextNode;
    return node;
}

struct Node* constList(const int* keys, int n)
{
    struct Node *head = NULL, *node = NULL;
    for (int i = n - 1; i >= 0; --i)
    {
        node = newNode(keys[i], node);
    }
    head = node;
    return head;
}

//я не понимаю как это работает, но оно работает
void insertNode(struct Node* head, int new_data, int after)
{
    struct Node* new_node = NULL;
    struct Node* tmp = head;

    while (tmp) {
        if (tmp->data == after) {  
            new_node = (struct Node*)malloc(sizeof(struct Node));

            if (new_node == NULL) {
                printf("Failed to insert element");
            }

            new_node->data = new_data;
            new_node->next = tmp->next;
            tmp->next = new_node;
            return;
        }
        tmp = tmp->next;
    }
}

//это тоже непонятно как работает
void deleteNode(struct Node* head, int value)
{
    struct Node* new_node = NULL;
    struct Node* tmp = head;

    while (tmp) {
        if (tmp->data == value) {  
            new_node = (struct Node*)malloc(sizeof(struct Node));

            if (new_node == NULL) {
                printf("Failed to delete element");
            }

            new_node = tmp->next->next;
            tmp->next = new_node;
            return;
        }
        tmp = tmp->next;
    }
}

void printList(struct Node* head)
{
    struct Node* ptr = head;
    while (ptr)
    {
        printf("%d -> ", ptr->data);
        ptr = ptr->next;
    }

    if (!ptr) {
        ptr = head;
        printf("%d <- first node of list\n", ptr->data);
    }
}

int main(void)
{
    const int keys[5] = { 1, 2, 3, 4, 5 };
    int n = sizeof(keys) / sizeof(keys[0]);

    struct Node* head = constList(keys, n);
    struct Node* sub;
    printList(head);
    insertNode(head, 2, 2);
    printList(head);
    deleteNode(head, 4);
    printList(head);
    return 0;
}