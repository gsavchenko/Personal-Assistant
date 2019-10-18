/*
 * @file conversation.h
 * @author George Savchenko
 * @date Dec 2017
 * @brief A conversation interface
 */

/*
 * Stores basic conversation information.
 */
typedef struct Conversation
{
    char *keyword;
    char *response;
    double userRating;
    double systemRating;
    double learningRate;
    int keywordCount;

} Conversation;

Conversation *createNewRule(char *keyword, char *response, double userRating);

/* Print information associated with conversation
 * @param   item
 */
void printConversationData(void *item);

/* Compare 2 conversations' frequencies
 * @param    itemOne to compare
 * @param    itemTwo to compare
 */
int compareConversations(const void *itemOne, const void *itemTwo);

/* Delete a conversation object
 * @param   item to delete
 */
void deleteConversation(void *item);

/* Get the keyword for rule
 * @param Conversation
 * @return  Pointer to keyword
 */
char *getKeyword(Conversation *c);

/* Get the system's rating for the rule
 * @param Conversation
 * @return System rating
 */
double getSystemRating(Conversation *c);

/* Get the users's rating for the rule
 * @param   Conversation
 * @return  User Rating
 */
double getUserRating(Conversation *c);

/* Get the the amount of times a keyword was used
 * @param   Conversation
 * @return  Total keyword usage
 */
int getWordCount(Conversation *c);
