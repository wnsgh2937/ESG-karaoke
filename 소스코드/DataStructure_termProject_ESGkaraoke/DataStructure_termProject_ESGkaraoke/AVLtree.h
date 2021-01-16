#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int key;
	char singer[100];
	char title[100];
}song;

typedef struct {
	int val;
	song data;
	struct node* parent;
	struct node* left;
	struct node* right;
}node;

void rotate(node* p);
void reConstruct(node* childNode);
void LL_rotate(node* p);
void RR_rotate(node* p);
void LR_rotate(node* p);
void RL_rotate(node* p);
void add_(node* parentNode, node* childNode);
void cut(node* p, node* c);
int get_bf(node* p);
int get_height(node* p);


typedef struct {
	node* head;
}tree;

tree* createNewTree() {
	tree* tmp = (tree*)malloc(sizeof(tree));
	tmp->head = NULL;
	return tmp;
}

node* createNewNode(int val) {
	node* tmp = (node*)malloc(sizeof(node));
	tmp->val = val;
	tmp->parent = NULL;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


void add_node(tree* t, node* parentNode, node* childNode) {
	childNode->parent = parentNode;
	if (childNode->val < parentNode->val) parentNode->left = childNode;
	else parentNode->right = childNode;
	reConstruct(t, childNode);
}

void rotate(tree* t, node* p) {
	int bf = get_bf(p);
	if (1 < bf) {
		if (get_bf(p->left) > 0) {
			LL_rotate(t, p);
		}
		else {
			LR_rotate(t, p);
		}
	}
	else if (bf < -1) {
		if (get_bf(p->right) < 0) {
			RR_rotate(t, p);
		}
		else {
			RL_rotate(t, p);
		}
	}
}

void reConstruct(tree* t, node* childNode) {
	node* iter = childNode;
	int isUnbalance = 0;
	while (iter != NULL) {
		int bf = get_bf(iter);
		if (bf < -1 || 1 < bf) {
			isUnbalance = 1;
			break;
		}
		iter = iter->parent;
	}
	if (isUnbalance) {
		rotate(t, iter);
	}
}


void LL_rotate(tree* t, node* p) {
	node* L1 = p;
	node* L2 = p->left;
	node* pp = p->parent;
	int isRoot = 0;
	int dir = -1;
	if (pp == NULL) {
		isRoot = 1;
		t->head = NULL;
	}
	else {
		if (pp->left == L1) {
			dir = 0;
			pp->left = NULL;
			L1->parent = NULL;
		}
		else {
			dir = 1;
			pp->right = NULL;
			L1->parent = NULL;
		}
	}

	if (L2->right == NULL) {
		L1->left = NULL;
		L2->parent = NULL;

		L1->parent = L2;
		L2->right = L1;
	}
	else {
		node* sub = L2->right;

		sub->parent = NULL;
		L2->right = NULL;

		L2->parent = NULL;
		L1->left = sub;
		sub->parent = L1;

		L2->right = L1;
		L1->parent = L2;
	}

	if (isRoot) {
		t->head = L2;
	}
	else {
		if (dir == 0) {
			pp->left = L2;
		}
		else if (dir == 1) {
			pp->right = L2;
		}
		L2->parent = pp;
	}


}
void RR_rotate(tree* t, node* p) {
	node* L1 = p;
	node* L2 = p->right;
	node* pp = p->parent;
	int isRoot = 0;
	int dir = -1;
	if (pp == NULL) {
		isRoot = 1;
		t->head = NULL;
	}
	else {
		if (pp->left == L1) {
			dir = 0;
			pp->left = NULL;
			L1->parent = NULL;
		}
		else {
			dir = 1;
			pp->right = NULL;
			L1->parent = NULL;
		}
	}

	if (L2->left == NULL) {
		L1->right = NULL;
		L2->parent = NULL;

		L1->parent = L2;
		L2->left = L1;
	}
	else {
		node* sub = L2->left;

		sub->parent = NULL;
		L2->left = NULL;

		L2->parent = NULL;
		L1->right = sub;

		L2->left = L1;
		L1->parent = L2;
	}

	if (isRoot) {
		t->head = L2;
	}
	else {
		if (dir == 0) {
			pp->left = L2;
		}
		else if (dir == 1) {
			pp->right = L2;
		}
		L2->parent = pp;
	}


}
void LR_rotate(tree* t, node* p) {
	RR_rotate(t, p->left);
	LL_rotate(t, p);
}

void RL_rotate(tree* t, node* p) {
	LL_rotate(t, p->right);
	RR_rotate(t, p);
}


int get_height(node* p) {
	if (p == NULL) return -1;
	int height = 0;
	height = max(get_height(p->left), get_height(p->right)) + 1;
	return height;
}

int get_bf(node* p) {
	if (p == NULL) return;
	return get_height(p->left) - get_height(p->right);
}


int isEmpty(tree* t) {
	if (t->head == NULL) return 1;
	else return 0;
}

int find(node* iter, int val, node** findNode) {
	if (val == iter->val) {
		*findNode = iter;
		return 1;
	}
	else if (val < iter->val) {
		if (iter->left == NULL) {
			*findNode = iter;
			return 0;
		}
		else find(iter->left, val, findNode);
	}
	else if (iter->val < val) {
		if (iter->right == NULL) {
			*findNode = iter;
			return 0;
		}
		else find(iter->right, val, findNode);
	}
}


//childNum==1,2 
//d=0 ¿Þ d=1 ¿À
void print_DFS(node* iter, int childNum, int d) {
	if (childNum == 1 && d == 0) printf("%d,", iter->val);
	else if (childNum == 1 && d == 1) printf(",%d", iter->val);
	else if (childNum == 2 && d == 0) printf("%d", iter->val);
	else if (childNum == 2 && d == 1) printf(",%d", iter->val);
	if (!(iter->left == NULL && iter->right == NULL)) {
		printf("(");
		if (iter->left == NULL && iter->right != NULL) print_DFS(iter->right, 1, 1);
		else if (iter->left != NULL && iter->right == NULL) print_DFS(iter->left, 1, 0);
		else if (iter->left != NULL && iter->right != NULL) { print_DFS(iter->left, 2, 0); print_DFS(iter->right, 2, 1); }
		printf(")");
	}
}

void print(tree* t) {
	if (t->head == NULL) return;
	printf("%d", t->head->val);
	print_DFS(t->head, -1, -1);
}

node* get_min(node* iter) {
	while (iter->left != NULL) iter = iter->left;
	return iter;
}

node* get_max(node* iter) {
	while (iter->right != NULL) iter = iter->right;
	return iter;
}

node* deleteNode(tree* t, node* delNode) {
	if (delNode->left == NULL && delNode->right == NULL) {
		if (delNode->parent == NULL) {
			t->head = NULL;
			return delNode;
		}
		node* parentNode = delNode->parent;
		if (parentNode->left == delNode) parentNode->left = NULL;
		else parentNode->right = NULL;
		delNode->parent = NULL;
		return delNode;
	}
	else if (delNode->left != NULL && delNode->right == NULL) {
		if (delNode->parent == NULL) {
			node* leftNode = delNode->left;
			t->head = leftNode;
			leftNode->parent = NULL;
			delNode->left = NULL;
			return delNode;
		}
		node* parentNode = delNode->parent;
		node* leftNode = delNode->left;
		if (parentNode->left == delNode) parentNode->left = leftNode;
		else parentNode->right = leftNode;
		leftNode->parent = parentNode;
		delNode->parent = NULL;
		delNode->left = NULL;
		return delNode;
	}
	else if (delNode->left == NULL && delNode->right != NULL) {
		if (delNode->parent == NULL) {
			node* rightNode = delNode->right;
			t->head = rightNode;
			rightNode->parent = NULL;
			delNode->right = NULL;
			return delNode;
		}
		node* parentNode = delNode->parent;
		node* rightNode = delNode->right;
		if (parentNode->left == delNode) parentNode->left = rightNode;
		else parentNode->right = rightNode;
		rightNode->parent = parentNode;
		delNode->parent = NULL;
		delNode->right = NULL;
		return delNode;
	}
	else if (delNode->left != NULL && delNode->right != NULL) {
		node* addNode = deleteNode(t, get_min(delNode->right));
		node* delL = delNode->left;
		node* delR = delNode->right;
		node* delP = delNode->parent;
		delNode->left = NULL;
		delNode->right = NULL;
		delNode->parent = NULL;

		addNode->left = delL;
		addNode->right = delR;
		addNode->parent = delP;

		if (delL != NULL) delL->parent = addNode;
		if (delR != NULL) delR->parent = addNode;
		if (delP == NULL) t->head = addNode;
		else {
			if (delP->left == delNode) delP->left = addNode;
			else delP->right = addNode;
		}
		return delNode;
	}
}


void clear_DFS(node* iter) {
	if (iter->left == NULL && iter->right == NULL) free(iter);
	else {
		if (iter->left != NULL) clear_DFS(iter->left);
		if (iter->right != NULL) clear_DFS(iter->right);
	}
}
void clear(tree* t) {
	clear_DFS(t->head);
	t->head = NULL;
}