struct avl_node {
	int val;
	struct avl_node * right;
	struct avl_node * left;
	int height;
};

typedef struct avl_node node;

node * insert(node* root, int val);
node * delete_node(node* root, int val);
node * inorder_successor(node* root);
node * search_node(node* root, int val);
void display_tree(node* root);
void display(node* root);
int height(node* root);
node* joinRight(node* T1, node* T2);
node* joinLeft(node* T1, node* T2);
node* join(node* t1, node* t2);
node *joinAVL(node* TL, int m, node*TR);
node *joinLeftAVL(node* TL, int m, node*TR);
node *joinRightAVL(node* TL, int m, node*TR);
node* split(node* t1, int val);
node* split_tree(node* t, int k);

node* new_node(int val);
int balance_factor(node* root);

node* left_rotate(node* root);
node* right_rotate(node* root);

void print_elapsed(clock_t start, clock_t stop);

long long int NUM_VALS;