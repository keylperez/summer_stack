#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BST.h"

Product pList[] = {
	{"choco", 	25.25, 	1, 	{5, 27, 2024}},
	{"milk", 	13.50, 	5, 	{10-10-2024}},
	{"candy", 	1.25, 	10, {6-24-2023}},
	{"chicken", 30.00, 	5, 	{7-10-2024}},
	{"water", 	1.00, 	1, 	{00-00-0000}},
	{"hotdog", 	12.50, 	15, {7-12-2024}}
};

void init(NodePtr *head){
	*head = NULL;
}

Product createProduct(char name[], float price, int qty, int month, int day, int year){
	
	Product newProd;
	strcpy(newProd.prodName, name);
	newProd.prodPrice = price;
	newProd.prodQty = qty;
	newProd.expDate.day = day;
	newProd.expDate.month = month;
	newProd.expDate.year = year;
	
	return newProd;
}

bool insertNode(NodePtr *head, Product p){
	
	bool retVal = false;
	
	NodePtr newNode = (NodePtr) malloc(sizeof(NodeType));
		
	if(newNode != NULL){
	
		newNode->item = p;
		newNode->right = NULL;
		newNode->left = NULL;
		
		if(*head == NULL){
			*head = newNode;
			retVal = true;
		} else {
	
			if(strcmp((*head)->item.prodName, p.prodName) > 0) {
				retVal = insertNode(&(*head)->left, p);
			}
			if(strcmp((*head)->item.prodName, p.prodName) < 0) {
				
				retVal = insertNode(&(*head)->right, p);
			}		
		}
	}
	
	return retVal;
}

NodePtr searchNode(NodePtr head, char prodName[]){
	
	if(head != NULL){
		
		if(strcmp(head->item.prodName, prodName) > 0){
			head = searchNode((head)->left, prodName);
		}
		else if(strcmp(head->item.prodName, prodName) < 0){
			head = searchNode((head)->right, prodName);
		}
//		if(strcmp((*head)->item.prodName, prodName) == 0){
//			return *head;
//		}
	} else {
		printf("\nNOT FOUND!!...");
	}
	return head;
}

NodePtr *findSuccessor(NodePtr *head){
	
	if((*head)->right != NULL){
		findSuccessor(&(*head)->right);
	}
	
	return &(*head);
}

NodePtr deleteNode(NodePtr *head, char prodName[]){
	
	NodePtr *temp = &(*head);
	
	if(*head != NULL){
		
		if(strcmp((*head)->item.prodName, prodName) > 0){
			(*head)->left = deleteNode(&(*head)->left, prodName);
		}
		else if(strcmp((*head)->item.prodName, prodName) < 0){
			(*head)->right = deleteNode(&(*head)->right, prodName);
		}
		else {
			if((*head)->left != NULL && (*head)->right != NULL){
				temp = findSuccessor(&(*head)->left);
				(*head)->item = (*temp)->item;
				(*head)->left = deleteNode(&(*head)->left, (*temp)->item.prodName);
			}
			else if((*head)->left == NULL){
				temp = &(*head)->right;
				free(*head);
			} else if((*head)->right == NULL){
				temp = &(*head)->left;
				free(*head);
			}
		}	
	} 
	return *temp;
	
}

void BSF(NodePtr head);

void inOrderDFS(NodePtr head){

	if(head->left != NULL){
		inOrderDFS(head->left);
	}
	printf("%-10s", head->item);
	if(head->right != NULL){
		inOrderDFS(head->right);
	}
}

void postOrderDFS(NodePtr head){
	if(head->left != NULL){
		inOrderDFS(head->left);
	}
	if(head->right != NULL){
		inOrderDFS(head->right);
	}
	printf("%-10s", head->item);
}

void preOrderDFS(NodePtr head){
	printf("%-10s", head->item);
	if(head->left != NULL){
		inOrderDFS(head->left);
	}
	if(head->right != NULL){
		inOrderDFS(head->right);
	}
}
