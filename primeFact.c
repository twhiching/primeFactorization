#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* This program finds all Prime Factors (if there are any) of a given number and display them. */
struct node{

	int data;
	struct node *left;
	struct node *right;
};

/* newNode() allocates a new node with the given data and NULL left and right pointers. */
struct node* newNode(int data){
	// Allocate memory for new node
	struct node* node = (struct node*)malloc(sizeof(struct node));
	// Assign data to this node
	node->data = data;
	// Initialize left and right children as NULL
	node->left = NULL;
	node->right = NULL;
	return(node);
}

void printInorder(struct node* node){

	if (node == NULL)
        	return;
     	// first recur on left child
	printInorder(node->left);
     	// then print the data of node
	if(node -> left == NULL && node -> right == NULL)
		printf("%d x ", node->data);
     	// now recur on right child
	printInorder(node->right);
}

int isPrime(int number){

	int i;

	if(number == 2)
		return 1;
	for(i = 2; i < number; ++i){

		if((number % i) == 0)
			return 0;
	}
	return 1;
}

int main(int argc, char *argv[]){

	char userInput[10];
	int c,i,j,number,flag,temp;

	i = 0;
	printf("Please enter a number you would like to have prime factorized: ");
	while((c = getchar()) != EOF && c != '\n'){
		if(isdigit(c)){
			userInput[i] = c;
			++i;
		}else{
			fprintf(stderr, "Valid characters are numbers only. Please try again.\n");
			return -1;
		}
	}

	userInput[i] = '\0';
	//convert the input to an int
	number = atoi(userInput);

	//Check to see if number is 1
	if(number == 1){

		fprintf(stderr, "The number entered must be greater than 1. Please try again.\n");
		return -1;
	}
	//Check if the number is prime
	if(isPrime(number)){
		fprintf(stderr, "The number you entered is a prime number. Please try again.\n");
		return -1;
	}

	struct node *root = newNode(number);
	struct node *currentNode = root;
	flag = 1;
	while(flag){

		number = currentNode -> data;
		/* Check to see what is the lowest divsor for the number then creates left and right
	           nodes and continues the process untill all leaf nodes are prime numbers */
		for(i = 2; i < number; ++i){

			if(number % i == 0){

				temp = number/i;
				//left child
				struct node *leftNode = newNode(i);
				//right child
				struct node *rightNode = newNode(temp);
				currentNode -> left = leftNode;
				currentNode -> right = rightNode;
				//check to see if right child is prime
				if(isPrime(rightNode -> data)){
					flag = 0;
					break;
				}
				currentNode = rightNode;
				break;
			}
		}
	}
	printf("%d = ",root -> data);
	printInorder(root);
	printf("\b\b \n");
	return 0;
}
