/*
* @file conversation.c
* @author George Savchenko
* @date Dec 2017
* @brief Conversation implementation
*/
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Conversation.h"

Conversation *createNewRule(char *keyword, char *response, double userRating)
{
    Conversation *c = malloc(sizeof(Conversation));
    c->keyword = (char *)malloc(100);
    strcpy(c->keyword, keyword);
    c->response = (char *)malloc(100);
    strcpy(c->response, response);
    c->userRating = userRating;
    c->systemRating = userRating;
    c->learningRate = 0.05;
    c->keywordCount = 0;
    return c;
}

char *getKeyword(Conversation *c)
{
    return c->keyword;
}

double getSystemRating(Conversation *c)
{
    return c->systemRating;
}

double getUserRating(Conversation *c)
{
    return c->userRating;
}

int getWordCount(Conversation *c)
{
    return c->keywordCount;
}

void printConversationData(void *item)
{
    Conversation *c = (Conversation *)item;

    if (c != NULL)
    {
        printf("%s\t Rating:%.2f\t System:%.2f\t Occurrences:%d \n", getKeyword(c), getUserRating(c), getSystemRating(c), getWordCount(c));
    }
}

void deleteConversation(void *item)
{
    Conversation *toDelete = (Conversation *)item;
    free(toDelete);
}

int compareConversations(const void *itemOne, const void *itemTwo)
{
    Conversation *convoOne = (Conversation *)itemOne;
    Conversation *convoTwo = (Conversation *)itemTwo;

    if (strcmp(convoOne->keyword, convoTwo->keyword) > 0)
        return 1;
    else if (strcmp(convoOne->keyword, convoTwo->keyword) < 0)
        return -1;
    else
        return 0;
}