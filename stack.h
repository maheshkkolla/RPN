typedef struct stack Stack;
typedef struct item Item;
typedef Item * ItemPtr;

struct stack {
	ItemPtr top;
	int count;
};
struct item {
	void *data;
	ItemPtr prev;
	ItemPtr next;

};

Stack createStack(void);
int push(Stack *, void *);
void * pop(Stack *);