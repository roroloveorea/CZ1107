#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////
//int ll2array(LinkedList *ll);
void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);

	//printing all possible sequences
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}
/*int ll2array(LinkedList *ll)
{
  int arrayl[ll->size];
  int x=0;
  ListNode *tempforarray;
  tempforarray=ll->head;
  while(temp!=NULL)
  {
      arrayl[x]=tempforarray->item;
      tempforarray=tempforarray->next;
      i++;
  }
  return arrayl[ll->size];
}*/
void sumToC(LinkedList* ll, int C, ArrayList* al)
{
   // Write your code here
   int x =0;
    int y =0;
    ListNode *temp;
    int counter;
    int array[C];
     ArrayNode *temp2 = (ArrayNode*)malloc(sizeof(ArrayNode));
    ArrayNode *temp3 = (ArrayNode*)malloc(sizeof(ArrayNode));
	if(C<=2)
    {
        return;
    }

    for(x=1;x<C;x++)
    {

        insertNode(ll,ll->size,x);

        for(y=x+1;y<C;y++)
        {

            insertNode(ll,ll->size,y);

            if(ll->sum>C)
            {
                removeNode(ll,ll->size-1);
                counter = findNode((*ll),ll->size-1)->item;
                removeNode(ll,ll->size-1);
                if(ll->head==NULL)
                    break;
                y = counter;

            }


            if(ll->sum == C)
                {
                    temp = ll->head;
                    int i=0;
                    //duplicate ll int oarray

                    if(al->head == NULL)
                    {

                    temp2->itemArray = (int*)malloc(sizeof(array));

                    while(temp!=NULL)
                    {
                        temp2->itemArray[i] =temp->item;
                        temp = temp->next;
                        i++;
                    }

                    temp2->sizeArray = i;
                    temp2->next = NULL;

                    al->head = (ArrayNode*)malloc(sizeof(ArrayNode));
                    al->head = temp2;
                    al->size++;
                    al->head->next = NULL;

                    }


                    else
                    {
                        temp3 = al->head;
                        while(temp3->next!=NULL)
                            temp3 = temp3->next;

                        temp3->next = (ArrayNode*)malloc(sizeof(ArrayNode));
                        temp3->next->itemArray = (int*)malloc(sizeof(array));

                        i=0;
                        while(temp!= NULL)
                        {
                            temp3->next->itemArray[i] =temp->item;
                            temp = temp->next;
                            i++;
                        }
                        temp3->next->sizeArray = i;

                        al->size++;
                        temp3->next->next = NULL;



                    }

                }
                //save ll
        }

        removeAllItems(ll);

        }

//save ll

        al->size++;
        temp2 = al->head;
        while(temp2->next!=NULL)
            temp2 = temp2->next;

        temp2->next = (ArrayNode*)malloc(sizeof(ArrayNode));
        temp2->next->itemArray = (int*)malloc(sizeof(array[1]));

        temp2->next->itemArray[0] = C;
        temp2->next->sizeArray = 1;
		temp2->next->next = NULL;




}
///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}





int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

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
	ll->sum =0;
}


