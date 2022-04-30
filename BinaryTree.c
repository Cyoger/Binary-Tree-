// Binary Tree
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode_struct {
	struct treeNode_struct* leftPtr;
	int data;
	struct treeNode_struct* rightPtr;
} TreeNode;

// A pointers for the root of the binary tree.
TreeNode* rootPtr = NULL;

typedef struct queueNode_struct {
	TreeNode* node;
	struct queueNode_struct* nextPtr;
} QueueNode;

// Two pointers for the head and tail of the queue
QueueNode* headPtr = NULL;
QueueNode* tailPtr = NULL;

// Input/output file pointer declarations
FILE *inPtr;
FILE *outPtr;

// Insert a new element to the binary tree. 
void insert(TreeNode** treePtr, int value);

// Enqueue a new element into the queue. 
void enqueue(TreeNode* node);

// Dequeue an element from the queue. 
TreeNode* dequeue();

// Check if the queue is empty. 
int isQueueEmpty();

/*************
 * In-Order traversal and print out of the binary tree into the output file. (Increasing order)
 */
void inOrder(TreeNode* treePtr);

/*************
 * Reverse-Order traversal and print out of the binary tree. (Decreasing order)
 */
void reverseOrder(TreeNode* treePtr);

/*************
 * Level-Order traversal and print out of the binary tree.
 * It first prints the root, then the nodes in the next levels.
 * In each level, from left to right.
 */
void levelOrder();

/*************
 * Print out the binary tree with 90-degree counterclockwise rotated. 
 * (See the sample output in the problem description.)
 */
void printTree(TreeNode* treePtr, int totalSpaces);

/*************
 * Search the binary tree for a value and return the result node, NULL otherwise.
 */
TreeNode* searchTree(TreeNode* treePtr, int value);

// main function
int main(void)
{

	/*************
	 * Open the file "input.txt" as the input file.
	 * If the operation is not successful, print out a 
     * proper message to the screen and terminate the program.
	 */
	inPtr = fopen("input.txt", "r");
	if (inPtr == NULL)
	{
		printf("error! no file found.\n");
		return 0;
	}
	




	/*************
	 * Open the file "output.txt" as the output file.
	 * If the operation is not successful, print out a 
     * proper message to the screen and terminate the program.
	 */
	outPtr = fopen("output.txt", "w");
	if (outPtr == NULL)
	{
		printf("error! no file found.\n");
		return 0;
	}
	




	fprintf(outPtr,"The numbers being inserted into the binary tree are: \n");
	int temp;
	//fscanf(inPtr, "%d", &temp);
	while(!feof(inPtr))
    {
		fscanf(inPtr,"%d",&temp);
        fprintf(outPtr,"%d ",temp);
        insert(&rootPtr,temp);
        //fscanf(inPtr,"%d",&temp);
    }
    fprintf(outPtr,"\n");

	fclose(inPtr);








	fprintf(outPtr, "In-Order traversal and print out of the binary tree is: \n");
	inOrder(rootPtr);
	fprintf(outPtr, "\n");


	fprintf(outPtr, "The Binary Tree in reverse (decreasing) order is: \n");
	reverseOrder(rootPtr);
	fprintf(outPtr, "\n");

	fprintf(outPtr, "The Binary Tree in level-order is: \n");
	levelOrder(rootPtr);
	fprintf(outPtr, "\n");





	fprintf(outPtr, "Printing the binary tree with 90-degree counterclockwise rotated: \n");
	printTree(rootPtr, 0);



	fprintf(outPtr, "Searching the binary tree: \n");
	
	//f = searchTree(rootPtr, 6);
	if (searchTree(rootPtr, 6))
	{
		fprintf(outPtr, "6 found.\n");
	}else
	{
		fprintf(outPtr, "6 not found.\n");
	}
	
	if (searchTree(rootPtr, 25))
	{
		fprintf(outPtr, "25 found.\n");
	}else
	{
		fprintf(outPtr, "25 not found.\n");
	}
	
	if (searchTree(rootPtr, 18))
	{
		fprintf(outPtr, "18 found.\n");
	}else
	{
		fprintf(outPtr, "18 not found.\n");
	}


	fclose(outPtr);
}

// Insert a node into the binary tree. 
void insert(TreeNode** treePtr, int value) {
	// If the tree is empty
	if (*treePtr == NULL) {
		*treePtr = (TreeNode*) malloc(sizeof(TreeNode));
		// If memory allocation was successful
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		} else
			printf("%d No more memory is available.\n", value);
	} else { // The tree is not empty
		// The new data is less than the data in the current node
		if (value < (*treePtr)->data)
			insert(&(*treePtr)->leftPtr, value);
		// The new data is greater than the data in the current node
		else if (value > (*treePtr)->data)
			insert(&(*treePtr)->rightPtr, value);
		else  // Duplication will be ignored
			fprintf(outPtr, "%s", "duplicated ");
	}
}

// Insert a node at the queue tail. 
void enqueue(TreeNode* node) {
	QueueNode* newPtr = (QueueNode*) malloc(sizeof(QueueNode));
	if (newPtr != NULL) { // is space available
		newPtr->node = node;
		newPtr->nextPtr = NULL;
		// if queue is empty, insert the node at head
		if (isQueueEmpty(headPtr))
			headPtr = newPtr;
		else
			tailPtr->nextPtr = newPtr;
		tailPtr = newPtr;
	} else
		printf("Not inserted. No memory available.\n");
}

// Remove a node from the queue head. 
TreeNode* dequeue() {
	TreeNode* value = headPtr->node;
	QueueNode* tempPtr = headPtr;
	headPtr = headPtr->nextPtr;
	// if queue is empty
	if (headPtr == NULL)
		tailPtr = NULL;
	free(tempPtr);
	return value;
}

// Return 1 if the queue is empty, 0 otherwise. 
int isQueueEmpty(QueueNode* headPtr) {
	return headPtr == NULL;
}


void inOrder(TreeNode* treePtr){
	if (treePtr == NULL)
	{
		return;
	}
	inOrder(treePtr->leftPtr);
	fprintf(outPtr, "%d ", treePtr->data);
	inOrder(treePtr->rightPtr);
	

}



void reverseOrder(TreeNode* treePtr){
	if (treePtr == NULL)
	{
		return;
	}
	reverseOrder(treePtr->rightPtr);
	fprintf(outPtr, "%d ", treePtr->data);
	reverseOrder(treePtr->leftPtr);
	
}



void levelOrder(TreeNode* treePtr){
	enqueue(treePtr);
	while (!isQueueEmpty(headPtr))
	{
		TreeNode* temp = dequeue();
		fprintf(outPtr, "%d ", temp->data);
		if (temp->leftPtr != NULL)
			enqueue(temp->leftPtr);
		if (temp->rightPtr != NULL)
			enqueue(temp->rightPtr);
	}
	
}


void printTree(TreeNode* treePtr, int totalSpaces){
	if (treePtr != NULL)
	{	
		//totalSpaces += 5;
		printTree(treePtr->rightPtr, totalSpaces+5);
		
		fprintf(outPtr, "\n");
		for (int i = 0; i < totalSpaces; i++)
		{
			fprintf(outPtr, " ");
		}
		fprintf(outPtr, "%d\n", treePtr->data);
		printTree(treePtr->leftPtr, totalSpaces+5);
		
	}
	
	
}


TreeNode* searchTree(TreeNode* treePtr, int value){
	if(treePtr == NULL || treePtr->data == value){
		return treePtr;
	}
	if (treePtr->data < value)
	{
		return searchTree(treePtr->rightPtr, value);
	}
	return searchTree(treePtr->leftPtr, value);
	
}

