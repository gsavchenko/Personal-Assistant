/*
* @file main.c
* @author George Savchenko
* @date 24 Nov 2017
* @brief main program with object usages
*/
// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "BinaryTreeAPI.h"
#include "Conversation.h"

// Char array to store menu options
char *menuOptions[6] = {
    "1) Add a new rule",
    "2) Remove a rule",
    "3) Display rules",
    "4) Modify rule rating",
    "5) Discuss",
    "9) Quit",
};

void printMenu()
{
    printf("Main Menu \n");
    printf("--------- \n");
    printf("%s \n", menuOptions[0]);
    printf("%s \n", menuOptions[1]);
    printf("%s \n", menuOptions[2]);
    printf("%s \n", menuOptions[3]);
    printf("%s \n", menuOptions[4]);
    printf("%s \n", menuOptions[5]);
}

void resetScreen(char *lastAction)
{
    system("clear");
    printf("%s \n\n", lastAction);
    printMenu();
}

int main(int argc, char **argv)
{
    Tree *conversationTree = createBinTree(&compareConversations, &deleteConversation);
    int run_program = 1;
    int game_state = 1;

    // File IO
    char const *const fileName = argv[1];
    char line[256];
    char keyword[50];
    char response[250];
    char strUserRating[25];
    FILE *file = fopen(fileName, "r");

    if (file != NULL)
    {
        int alternateLines = 0;

        while (fgets(line, sizeof(line), file) != NULL)
        {
            if (alternateLines == 0)
            {
                strtok(line, "\n");
                strcpy(keyword, line);
                alternateLines = 1;
            }
            else
            {
                strcpy(response, line);
                alternateLines = 0;
                Conversation *c = createNewRule(keyword, response, 0.5);
                addToTree(conversationTree, c);
            }
        }

        fclose(file);
    }
    else
    {
        printf("Error, something went wrong with the file: %s", strerror(errno));
        exit(1);
    }

    printf("Read from file: \n");
    printInOrder(conversationTree, &printConversationData);
    printf("------------------------------------------------------\n");
    printMenu();

    while (run_program)
    {
        printf("Please enter an option: ");
        scanf("%d", &game_state);

        switch (game_state)
        {
        case 1: // add a new rule
            printf("%s \n", menuOptions[0]);
            double userRating = 0;

            printf("Enter a keyword [string]: ");
            getchar();
            fgets(keyword, 100, stdin);
            sscanf(keyword, "%s", keyword);

            printf("Enter a response [multiple strings]: ");
            fgets(response, sizeof(response), stdin);

            printf("Enter the new rule importance [0-1]: ");
            fgets(strUserRating, sizeof(strUserRating), stdin);
            sscanf(strUserRating, "%lf", &userRating);

            if (strlen(keyword) && strlen(response) && userRating > 0)
            {
                Conversation *c = createNewRule(keyword, response, userRating);
                addToTree(conversationTree, c);
                resetScreen("New rule succesfully added!");
            }
            else
            {
                resetScreen("Invalid input - Please enter conversation info! \n");
            }
            break;
        case 2: // remove a rule
            printf("%s \n", menuOptions[1]);

            printf("Enter the keyword of the rule to remove [string]: ");
            getchar();
            fgets(keyword, sizeof(keyword), stdin);
            sscanf(keyword, "%s", keyword);
            if (strlen(keyword) > 0)
            {
                Conversation *c = createNewRule(keyword, "", 0.0);

                if (findInTree(conversationTree, c) != NULL)
                {
                    removeFromTree(conversationTree, c);
                    resetScreen("Rule removed successfully! \n");
                }
                else
                {
                    resetScreen("Invalid rule - Not found! \n");
                }
            }
            else
                printf("Invalid input - Please enter a keyword!\n");
            break;
        case 3: // display rules
            printf("%s \n", menuOptions[2]);
            printInOrder(conversationTree, &printConversationData);
            printf("\n");
            break;
        case 4: // modify rule rating
            printf("%s \n", menuOptions[3]);
            double newUserRating = 0;

            printf("Enter the keyword of the rule to modify [string]: ");
            getchar();
            fgets(keyword, sizeof(keyword), stdin);
            sscanf(keyword, "%s", keyword);

            Conversation *toSearch = createNewRule(keyword, "", 0.0);
            Conversation *toModify = (Conversation *)findInTree(conversationTree, toSearch);

            free(toSearch);
            if (toModify != NULL)
            {
                printf("Current user rating: %.2f \n", toModify->userRating);
                printf("Enter a new User Rating: ");
                getchar();
                fgets(strUserRating, sizeof(strUserRating), stdin);
                sscanf(strUserRating, "%lf", &newUserRating);
                toModify->userRating = newUserRating;
                resetScreen("Value successfully modified! \n");
            }
            else
                resetScreen("Invalid input - Not found!");
            break;
        case 5: // have a discussion
            printf("%s \n", menuOptions[4]);
            char userInput[2];
            char userQuestion[250];
            char *words;
            Conversation *bestMatch = NULL;
            double currentImportance = 0;
            double highestImportance = 0;

            printf("Personal Assistant: What's up? \n");

            getchar();
            fgets(userQuestion, sizeof(userQuestion), stdin);
            strncpy(userQuestion, userQuestion, strlen(userQuestion));

            words = strtok(userQuestion, " ");
            while (words != NULL)
            {
                // Remove trailing new line escape character
                size_t newLine = strlen(words) - 1;
                if (words[newLine] == '\n')
                    words[newLine] = '\0';

                Conversation *toSearch = createNewRule(words, "", 0);
                Conversation *foundConvo = (Conversation *)findInTree(conversationTree, toSearch);

                free(toSearch);
                if (foundConvo != NULL)
                {
                    if (bestMatch == NULL)
                        bestMatch = foundConvo;
                    else
                    {
                        currentImportance = foundConvo->userRating + foundConvo->systemRating;
                        highestImportance = bestMatch->userRating + bestMatch->systemRating;
                        if (currentImportance > highestImportance)
                            bestMatch = foundConvo;
                    }
                }

                words = strtok(NULL, " ");
            }

            if (bestMatch != NULL)
            {
                printf("Personal Assistant: %s", bestMatch->response);
                printf("Was this response helpful? [Y/N] ");

                fgets(userInput, sizeof(userInput), stdin);
                sscanf(userInput, "%s", userInput);

                bestMatch->keywordCount++;
                if (strcmp(userInput, "y") == 0 || strcmp(userInput, "Y") == 0)
                {
                    bestMatch->systemRating = bestMatch->systemRating + (bestMatch->systemRating * bestMatch->learningRate / bestMatch->keywordCount);
                    resetScreen("Great! It was fun :) \n");
                }
                else if (strcmp(userInput, "n") == 0 || strcmp(userInput, "N") == 0)
                {
                    bestMatch->systemRating = bestMatch->systemRating - (bestMatch->systemRating * bestMatch->learningRate / bestMatch->keywordCount);
                    if (bestMatch->systemRating < 0)
                        bestMatch->systemRating = 0;

                    resetScreen("That's too bad! I'll try better next time :(");
                }
            }
            else
                resetScreen("Personal Assistant: Huh? I didn't get that :( \n");
            break;
        case 9: // exit program
            printf("%s \n", menuOptions[5]);
            run_program = 0;
            break;
        default:
            printf("Not an option \n");
            break;
        }
    }

    printf("Thanks for talking to me! See you again soon.\n");
    destroyBinTree(conversationTree);

    return 0;
}