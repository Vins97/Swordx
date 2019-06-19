#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "sorting.h"
#include "wordList.h"

  
node_w* newNode(string word,int occ){
    node_w *temp = malloc(sizeof(node_w));
    if(occ==0)
		temp->occurrency =1;
	else 
		temp->occurrency=occ;
    strcpy(temp->word,word);
    temp->left = temp->right = NULL;
    return temp;
}

void inOrder(node_w *root){
    if (root != NULL) {
        inOrder(root->left);
        if(strlen(root->word)>0)
			printf("%s %d \n", root->word,root->occurrency);
        inOrder(root->right);
    }
}

void transferTreeToList(node_w * root,analisys_t * listOut){
    if (root != NULL) {
        transferTreeToList(root->left,listOut);
        if(strlen(root->word)>0)
			push(listOut,root->word,root->occurrency);
        transferTreeToList(root->right,listOut);
    }
}

analisys_t * sortByOccurrency(node_w* root){
	analisys_t* list=(analisys_t *)malloc(sizeof(analisys_t));
	transferTreeToList(root,list);
	bubbleSort(list);
	return list;
}
void _insert(node_w*n,string word){
	insert(n,1,word);
}
node_w* insert(node_w * n , int occ, string word){
    if (n == NULL) 	return newNode(word,0); 
    if (strcasecmp(word,n->word)<0)
		n->left = insert(n->left,occ,word);
    else if (strcasecmp(word,n->word)>0)
        n->right = insert(n->right,occ,word);   
    else if (strcasecmp(word,n->word)==0)
		n->occurrency++;		
    return n;
}

node_w* minValueNode(node_w* n){
    node_w* current = n; 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left; 
    return current;
}

node_w* deleteNode(node_w* root,string word){
    // base case
    if (root == NULL) return root; 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcasecmp(word,root->word)<0)
        root->left = deleteNode(root->left, word); 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcasecmp(word,root->word)>0)
        root->right = deleteNode(root->right, word); 
    // if key is same as root's key, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if (root->left == NULL){
            node_w *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            node_w *temp = root->left;
            free(root);
            return temp;
        } 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        node_w* temp = minValueNode(root->right); 
        // Copy the inorder successor's content to this node
        root->occurrency = temp->occurrency;
        strcpy(root->word,temp->word); 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}

void push(analisys_t *l,string w,int occ){	
	if(strlen(l->word)==0){
		strcpy(l->word,w);
		l->occurrency=occ;		
	}else{		
	while ((l->next != NULL)&&(strcasecmp(l->word,w)!=0)){
		l= l->next;
	}
	if((strcasecmp(l->word,w))==0)
		l->occurrency++;
	else{
	    l->next = malloc(sizeof(analisys_t));
		strcpy(l->next->word,w);
		l->next->occurrency = occ;		
	}
  }
}

/*void deleteWord(analisys_t * list,string word){
	analisys_t *del=list;
	analisys_t *ptr;
	while((del->next)!= NULL && (strcasecmp(del->next->word,word)!=0))
		del = del->next;
	if(strcasecmp(del->next->word,word)==0){
		ptr = del->next;
		del->next = del->next->next;
		free(ptr);
	}
	else 
		return;
}*/

void fileListPush(fileList_t * fList,string nFile){
	while(fList->next!=NULL)
		fList= fList->next;
	fList->next = malloc(sizeof(fileList_t));
	strcpy(fList->next->nameFile,nFile);
}

int fileListDelete(fileList_t * fList,string nFile){
	fileList_t *del = fList;
	fileList_t *ptr;
	while((del->next)!= NULL && (strcmp(del->next->nameFile,nFile)!=0))
		del = del->next;
	if(strcmp(del->next->nameFile,nFile)==0){
		ptr=del->next;
		del->next = del->next->next;
		free(ptr);
		return 1;		
		}
	else 	
		return 0;
}
