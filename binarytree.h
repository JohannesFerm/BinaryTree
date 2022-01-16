//Johannes Ferm & Molham Srour

typedef struct nod
{
	int val;
	struct nod *parent;
	struct nod *Lchild;
	struct nod *Rchild;
}nod;

typedef struct tree
{
	nod *root;
}tree;

tree *init(tree *t);

void insert(tree *t, int val);

nod *max(tree *t);

nod *min(tree *t);

nod *search(tree *t, int key);

nod *successor(tree *t, nod *x);

nod *predecessor(tree *t, nod *x);

void transplant(tree *t, nod *x, nod *y);

void delete(tree *t, nod *x);

void print_tree(tree *t);

int depth(nod *x);
