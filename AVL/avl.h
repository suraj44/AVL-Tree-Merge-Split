struct avl_node {
	int val;
	struct avl_node * right;
	struct avl_node * left;
	int height;
};

typedef struct avl_node node;

node * insert_node(node* root, int val);
int delete_node(node* root, int val);
int search_node(node* root, int val);

node* new_node(int val);
