#include "LinkedList.h"

typedef struct status Status;

struct status {
  int error;
  int result;
};

Status evaluate(char *expression);
char * infixToPostfix(char * expression);
LinkedList splitExpression(char *);
void stringCopy(char *source, char **destination, int from, int sizeOfDestination);
