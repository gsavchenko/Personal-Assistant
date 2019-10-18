/*
* @file testMain.c
* @author George Savchenko
* @date 24 Sep 2017
* @brief test main with unit tests for ADT
*/
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTreeAPI.h"
#include "integer.h"

char *testPassed(void *item)
{
    if (item != NULL)
        return "PASSED";
    else
        return "FAIL";
}

char *checkValue(void *item, char *type)
{
    char *msgOne = " is not NULL";
    char *msgTwo = " is NULL";

    char *resultOne = malloc(strlen(type) + strlen(msgOne) + 2);
    char resultTwo[500];

    strcpy(resultOne, type);
    strcat(resultOne, msgOne);
    strcpy(resultTwo, type);
    strcat(resultTwo, msgTwo);

    if (item != NULL)
        return resultOne;
    else
        return resultOne;
}

void runTest(int testNum, char *testName, char *expected, char *output, char *result)
{
    printf("%i %s \n", testNum, testName);
    printf("EXPECTED: %s \n", expected);
    printf("OUTPUT: %s \n", output);
    printf("RESULT: %s \n\n", result);
}

int main(int argc, char **argv)
{
    int two = 2;
    int one = 1;
    int three = 3;

    // 1. Test Create
    Tree *test = createBinTree(&compareData, &destroyData);
    runTest(1, "Create Tree", "Empty Tree", checkValue(test, "Tree"), testPassed(test));

    //2. Testing createNode
    addToTree(test, &two);
    runTest(2, "Create TreeNode", "Node with Data", checkValue(test->root, "Node"), testPassed(test->root));

    //3. Testing addToTree
    addToTree(test, &three);
    runTest(3, "addToTree", "New node inserted", checkValue(test->root->right, "Node"), testPassed(test->root->right));

    //4. Testing findInTree
    addToTree(test, &one);
    int toSearch = *(int *)findInTree(test, &one);
    runTest(4, "findInTree", "Found data", checkValue(&toSearch, "Lookup Node"), testPassed(&toSearch));

    //5. Testing getRootData
    char sRootData[10];
    sprintf(sRootData, "%d", *(int *)getRootData(test));
    runTest(5, "getRootData", "Root should be 2", sRootData, testPassed(test->root));

    //6. Testing removeFromTree
    removeFromTree(test, &two);
    sprintf(sRootData, "%d", *(int *)getRootData(test));
    runTest(6, "removeInTree", "Root should be 3", sRootData, testPassed(test->root));

    //7. Testing printFunctions
    addToTree(test, &two);
    printf("7 printInOrder, printPreOrder, printPostOrder \n");
    printf("EXPECTED: Ordered output of elements 3 times \n");
    printInOrder(test, &printData);
    printf("\n");
    printPreOrder(test, &printData);
    printf("\n");
    printPostOrder(test, &printData);
    printf("RESULT: PASSED \n\n");

    //8. Testing isTreeEmpty
    runTest(8, "isTreeEmpty", "Tree should not be NULL", checkValue(test, "Tree"), testPassed(test));

    //9. Testing isLeaf
    char sIsLeaf[10];
    sprintf(sIsLeaf, "%d", isLeaf(test->root->left->right));
    runTest(9, "isLeaf", "Value should be 1 (true)", sIsLeaf, testPassed(test->root->left->right));

    //10. Testing hasTwoChildren
    char sHasChildren[10];
    sprintf(sHasChildren, "%d", hasTwoChildren(test->root->left->right));
    runTest(10, "hasChildren", "Value should be 0 (false)", sHasChildren, testPassed(test->root->left->right));

    //11. Testing getHeight
    char sGetHeight[10];
    sprintf(sGetHeight, "%d", getHeight(test->root));
    runTest(11, "getHeight", "Value should be 3", sGetHeight, testPassed(test->root));

    //12. Testing destroyBinTree
    destroyBinTree(test);
    runTest(12, "destroyBinTree", "Value should be NULL", checkValue(test, "Tree"), "FAIL");

    //13. Testing isTree Empty
    char sIsTreeEmpty[10];
    sprintf(sIsTreeEmpty, "%d", isTreeEmpty(test));
    runTest(12, "isTreeEmpty", "Value should be NULL", checkValue(test, "Root"), "FAIL");

    return 0;
}