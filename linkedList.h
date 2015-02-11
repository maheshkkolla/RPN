
typedef struct node Node;
typedef struct linkedList LinkedList;
typedef Node * NodePtr; 
typedef void traverseOperation(void * data);
struct node {
	void *data;
	Node *next;
};

struct linkedList {
	NodePtr head;
	NodePtr tail;
	int count;
};

LinkedList createList(void);
NodePtr create_node(void *data);
int add_to_list(LinkedList *,Node *);
void traverse(LinkedList,traverseOperation);
void *get_first_element(LinkedList list);
void *get_last_element(LinkedList list);
void *getElementAt(LinkedList, int );
int indexOf(LinkedList, void *);
void * deleteElementAt(LinkedList *, int);
int asArray(LinkedList, void **);
