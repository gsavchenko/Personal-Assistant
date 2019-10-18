/*
* @file binaryTree.c
* @author George Savchenko
* @date Dec 2017
* @brief Binary Tree Implementation
*/
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTreeAPI.h"

TreeNode *createTreeNode(TreeDataPtr data)
{
    TreeNode *tn = malloc(sizeof(TreeNode));
    tn->data = data;
    tn->left = NULL;
    tn->right = NULL;
    return tn;
}

Tree *createBinTree(CompareFunc compare, DeleteFunc del)
{
    Tree *t = malloc(sizeof(Tree));
    t->compareFunc = compare;
    t->deleteFunc = del;
    t->root = NULL;
    return t;
}

void deleteTree(Tree *theTree, TreeNode *current)
{
    if (current != NULL)
    {
        deleteTree(theTree, current->left);
        deleteTree(theTree, current->right);

        theTree->deleteFunc(current->data);
        free(current);
        current = NULL;
    }
}

void destroyBinTree(Tree *toDestroy)
{
    deleteTree(toDestroy, toDestroy->root);
    free(toDestroy);
    toDestroy = NULL;
}

TreeNode *insert(TreeNode *currentNode, TreeDataPtr data, CompareFunc compare)
{
    if (currentNode == NULL)
        return createTreeNode(data);
    if (compare(currentNode->data, data) == 1)
        currentNode->right = insert(currentNode->right, data, compare);
    else if (compare(currentNode->data, data) == -1)
        currentNode->left = insert(currentNode->left, data, compare);
    return currentNode;
}

void addToTree(Tree *theTree, TreeDataPtr data)
{
    TreeNode *toInsert = insert(theTree->root, data, theTree->compareFunc);
    theTree->root = toInsert;
}

TreeNode *deleteNode(Tree *theTree, TreeNode *current, TreeDataPtr data, CompareFunc compare)
{
    if (current == NULL)
        return NULL;

    //printf("outside if \n");
    if (compare(current->data, data) == 1)
    {
        // printf("IN RIGHT SIDE \n");
        current->right = deleteNode(theTree, current->right, data, compare);
    }
    else if (compare(current->data, data) == -1)
    {
        //printf("IN LEFT SIDE \n");
        current->left = deleteNode(theTree, current->left, data, compare);
    }
    else
    {
        //printf("IN ROOT \n");
        if (isLeaf(current) == 1)
        {
            //printf("NO CHILDREN! \n");
            theTree->deleteFunc(current->data);
            free(current);
            current = NULL;
        }
        else if (current->right == NULL)
        {
            //printf("LEFT CHILD \n");
            TreeNode *temp = current;
            current = current->left;
            theTree->deleteFunc(temp->data);
            free(temp);
        }
        else if (current->left == NULL)
        {
            //printf("RIGHT CHILD \n");
            TreeNode *temp = current;
            current = current->right;
            theTree->deleteFunc(temp->data);
            free(temp);
        }
        else
        {
            //printf("TWO CHILDREN \n");
            TreeNode *temp = current->right;

            if (temp != NULL)
            {
                while (temp->left != NULL)
                {
                    temp = temp->left;
                }
            }

            current->data = temp->data;
            current->right = deleteNode(theTree, current->right, temp->data, compare);
        }
    }
    return current;
}

void removeFromTree(Tree *theTree, TreeDataPtr data)
{
    deleteNode(theTree, theTree->root, data, theTree->compareFunc);
}

TreeDataPtr findInTree(Tree *theTree, TreeDataPtr data)
{
    TreeNode *current = theTree->root;

    while (current != NULL && current->data != NULL)
    {
        if (theTree->compareFunc(current->data, data) == 1)
            current = current->right;
        else if (theTree->compareFunc(current->data, data) == -1)
            current = current->left;
        else
            return current->data;
    }

    if (current == NULL)
        return NULL;
    else
        return current->data;
}

TreeDataPtr getRootData(Tree *theTree)
{
    return theTree->root->data;
}

void traveseInOrder(TreeNode *current, PrintFunc printData)
{
    if (current != NULL)
    {
        traveseInOrder(current->left, printData);
        printData(current->data);
        traveseInOrder(current->right, printData);
    }
}

void printInOrder(Tree *theTree, PrintFunc printData)
{
    traveseInOrder(theTree->root, printData);
}

void traversePreOrder(TreeNode *current, PrintFunc printData)
{
    if (current != NULL)
    {
        printData(current->data);
        traversePreOrder(current->left, printData);
        traversePreOrder(current->right, printData);
    }
}

void printPreOrder(Tree *theTree, PrintFunc printData)
{
    traversePreOrder(theTree->root, printData);
}

void travesePostOrder(TreeNode *current, PrintFunc printData)
{
    if (current != NULL)
    {
        travesePostOrder(current->left, printData);
        travesePostOrder(current->right, printData);
        printData(current->data);
    }
}

void printPostOrder(Tree *theTree, PrintFunc printData)
{
    travesePostOrder(theTree->root, printData);
}

int isTreeEmpty(Tree *theTree)
{
    if (theTree->root == NULL)
        return 0;
    else
        return 1;
}

int isLeaf(TreeNode *treeNode)
{
    if (treeNode->left == NULL && treeNode->right == NULL)
        return 1;
    else
        return 0;
}

int hasTwoChildren(TreeNode *treeNode)
{
    if (treeNode->left != NULL && treeNode->right != NULL)
        return 1;
    else
        return 0;
}

int getHeight(TreeNode *treeNode)
{
    int leftHeight = 0;
    int rightHeight = 0;

    if (treeNode->left != NULL)
        leftHeight = getHeight(treeNode->left);
    if (treeNode->right != NULL)
        rightHeight = getHeight(treeNode->right);

    if (treeNode == NULL)
        return -1;

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}