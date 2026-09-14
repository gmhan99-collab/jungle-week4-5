//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

int isInt(char *s);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int j;
	char c[120];
	char i[120];
	int p = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");
	while (p != 0) // was c!= 0
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%119s", c);
		if(!isInt(c)) 
		{
			p = 4;
			int o;
			while((o = getchar()) != '\n' && o != EOF){}

			// printf("\nWrong input\n");
		}
		else p = atoi(c);

		switch (p)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			// 문자열 입력에 대한 처리를 위한 코드
			scanf("%119s", i);
			if(isInt(i)) // 1 when integer, 0 when not
			{
				j = insertSortedLL(&ll, atoi(i));
				printf("The resulting linked list is: ");
				printList(&ll);
				break;
			}
			else
			{
				int k;
				while((k = getchar()) != '\n' && k != EOF){}

				printf("\nWrong input\n");
				break;
			}
		case 2:
			printf("The value %d was added at index %d\n", atoi(i), j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	// use fuction inserNode() to insert
	ListNode *cur;
	int count = 0;
	// input into Empty List
	if(ll->head == NULL)
		return insertNode(ll, 0, item);
	cur = ll->head;
	while(1)
	{
		if(cur == NULL || cur->item >= item)
		{
			if(cur != NULL && cur->item == item) return -1;
			insertNode(ll,count,item);
			break;
		}
		cur = cur->next;
		count++;
	}
	return count;

	
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

int isInt(char *s) {
    if (s[0] == '\0')
        return 0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (!('0' <= s[i] && s[i] <= '9')) {

            if (s[i] == '-' && i == 0 && s[i + 1] != '\0') {
                continue;
            }

            return 0;
        }
    }

    return 1;
}