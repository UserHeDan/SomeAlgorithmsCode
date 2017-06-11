#include <stdio.h>
#include <stdlib.h>
#define NIL NULL

//定义树节点
typedef struct tree_node
{
	struct tree_node *parent;
	struct tree_node *left;
	struct tree_node *right;
	int key;
}tree_node;

/*********************声明部分******************************/
tree_node *Successor(tree_node *root, int value);
tree_node *Predecessor(tree_node *root, int value);
tree_node *Search_node(tree_node *root, int value);
tree_node *Maximum(tree_node *root);
tree_node *Minimum(tree_node *root);
tree_node *Transplant(tree_node *root, tree_node *root1, tree_node *root2);
tree_node *Delete(tree_node *root, int oldvalue);
tree_node *Insert(tree_node *root, int newvalue);


//二叉搜索树的插入
tree_node *Insert(tree_node *root, int newvalue)
{

	tree_node *newnode = (tree_node*) malloc (1*sizeof(tree_node));
	while (newnode == NIL)
	{
		newnode = (tree_node*) malloc (1*sizeof(tree_node));
	}
	newnode->left = NIL;
	newnode->right = NIL;
	newnode->parent = NIL;
	newnode->key = newvalue;

	tree_node *pfast =root;
	tree_node *pslow = NIL;
	while (pfast)
	{
		pslow = pfast;
		if (newnode->key < pfast->key)
		{ 
			pfast = pfast->left;
		}
		else
		{
			pfast = pfast->right;
		}
	}

	newnode->parent = pslow;
	if (pslow == NIL)			//根节点为空
	{
		root = newnode;
	}

	else if (pslow->key > newnode->key)
	{
		pslow->left = newnode;
	}
	else
	{
		pslow->right = newnode;
	}
	return root;
}


//用一棵子树替换另一棵子树
tree_node *Transplant(tree_node *root, tree_node *root1, tree_node *root2)
{
	if (root1->parent == NIL)		//root1是根节点
	{
		root = root2;
	}
	else if (root1->parent->left == root1)
	{
		root1->parent->left = root2;
	}
	else
	{
		root1->parent->right = root2;
	}
	if (root2 != NIL)				//考虑到root2子树可能为空
	{
		root2->parent = root1->parent;
	}
	return root;					//这个返回值可以很好得应用于根节点的删除,从而更新根节点
}
//二叉树的删除
tree_node *Delete(tree_node *root, int oldvalue)
{
	tree_node *oldnode = Search_node(root, oldvalue);
	if (oldnode->left == NIL)
	{
		root = Transplant(root, oldnode, oldnode->right);
	}
	else if (oldnode->right == NIL)
	{
		root = Transplant(root, oldnode, oldnode->left);
	}
	else
	{
		tree_node *successor = Minimum(oldnode->right);
		if (successor != oldnode->right)
		{
			Transplant(root, successor, successor->right);
			successor->right = oldnode->right;
			successor->right->parent = successor;

		}
		root = Transplant(root, oldnode, successor);		//successor没有左子树
		successor->left = oldnode->left;
		successor->left->parent = successor;
	}
	return root;
}

//查找二叉搜索树的节点
tree_node *Search_node(tree_node *root, int value)
{
	while (root != NIL && value != root->key)		//先要判断root是否为空
	{
		if (value < root->key)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}
	return root;
}

//得到一棵树的最小节点的值
tree_node *Minimum(tree_node *root)
{
	if (root == NIL)
	{
		return root;
	}
	while (root->left != NIL)
	{
		root = root->left;
	}
	return root;
}

//得到一棵树的最大节点的值
tree_node *Maximum(tree_node *root)
{
	if (root == NIL)
	{
		return root;
	}
	while (root->right != NIL)
	{
		root = root->right;
	}
	return root;
}

//得到二叉搜索树的前驱
tree_node *Predecessor(tree_node *root, int value)
{
	tree_node *p_cur = Search_node(root, value);
	while (p_cur->left != NIL)
	{
		return Maximum(p_cur->left);
	}

	tree_node *p_tmp = p_cur->parent;
	while (p_tmp != NIL && p_tmp->left == p_cur)
	{
		p_cur = p_tmp;
		p_tmp = p_tmp->parent;
	}
	return p_tmp;
}

//得到二叉搜索树的后继
tree_node *Successor(tree_node *root, int value)
{
	tree_node *p_cur = Search_node(root, value);
	while (p_cur->right != NIL)					//存在右子树
	{
		return Minimum(p_cur->right);
	}

	tree_node *p_tmp = p_cur->parent;
	while (p_tmp != NIL && p_tmp->right == p_cur)			//不存在右子树
	{
		p_cur = p_cur->parent;
		p_tmp = p_tmp->parent;
	}
	return p_tmp;
}

//前序遍历输出二叉树
void preorder_tree_walk(tree_node *root)
{
	if (root != NIL)
	{
		printf("%d ", root->key);
		preorder_tree_walk(root->left);
		preorder_tree_walk(root->right);
	}
}

//中序输出二叉树
void inorder_tree_walk(tree_node *root)
{
	if (root != NIL)
	{
		inorder_tree_walk(root->left);
		printf("%d ", root->key);
		inorder_tree_walk(root->right);
	}
}

//后序遍历输出二叉树
void postorder_tree_walk(tree_node *root)
{
	if (root != NIL)
	{
		postorder_tree_walk(root->left);
		postorder_tree_walk(root->right);
		printf("%d ", root->key);
	}
}

//前中后序输出搜索二叉树
void output_BST(tree_node *root)
{
	inorder_tree_walk(root);
	printf("\n");
	preorder_tree_walk(root);
	printf("\n");
	postorder_tree_walk(root);
	printf("\n");
}


//测试BST
int main(int argc, char const *argv[])
{
	tree_node *root = NIL;

	int N;
	int i, n;
	//输入N个数字
	printf("插入N个数字：\n");
	scanf("%d", &N);

	for (i = 0; i < N; i++)
	{
		scanf("%d", &n);
		root = Insert(root, n);				//返回值很重要
	}
	//输出排序好的BST树
	output_BST(root);

	int Min = Minimum(root)->key;
	int Max = Maximum(root)->key;
	printf("%d %d\n", Max, Min);

	printf("查找N个数字：\n");
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &n);
		tree_node *ret = Search_node(root, n);
		if (ret == NIL)
		{
			printf("%d is not found\n", n);
		}
		else
		{
			printf("%d is found\n", n);
			if (ret->key == Min)
			{
				printf("%d is the smallest key\n", ret->key);
			}
			if (ret->key == Max)
			{
				printf("%d is the largest key\n", ret->key);
			}
		}
	}
	printf("删除N个数字：\n");
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &n);
		root = Delete(root, n);
	}
	output_BST(root);
	return 0;
}
