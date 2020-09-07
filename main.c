#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
struct tree 
{ 
	int val;
	struct tree *left;
	struct tree *right;
};

int is_number(char c)
{
	if(c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

// 11: +
// 12: -
// 14: *
// 15: /
// 中序遍历
int run_calc(struct tree *root)
{
	if(!root)
	{
		printf("root=null\n");
		exit(0);
	}
	if(root->val > 9)
	{
		// printf("left:%d, op:%d, right:%d\n", root->left->val, root->val, root->right->val);
		switch (root->val)
		{
			case 11:
				return run_calc(root->left) + run_calc(root->right);
			case 12:
				return run_calc(root->left) - run_calc(root->right);
			case 14:
				return run_calc(root->left) * run_calc(root->right);
			case 15:
				return run_calc(root->left) / run_calc(root->right);
			default:
				return 0;
		}
	} else {
		return root->val;
	}
}

struct tree *init_tree(char exp[])
{
	int len = strlen(exp);
	struct tree *root = NULL;
	struct tree *lastone = NULL;
	struct tree *lastroot = NULL;
	struct tree *node = NULL;

	for(int i = 0; i < len; ++i)
	{
		struct tree *p = (struct tree *)malloc(sizeof(struct tree));
		// 赋值
		if(is_number(exp[i]))
		{
			// 他是叶子节点
			p->val = exp[i] - '0';
		}
		else 
		{
			switch(exp[i])
			{
				case '+':
					p->val = 11;
					break;
				case '-':
					p->val = 12;
					break;
				case '*':
					p->val = 14;
					break;
				case '/':
					p->val = 15;
					break;
				default:
					break;	
			}
		}
		p->left = NULL;
		p->right = NULL;
		if(node == NULL)
		{
			node = p;
			continue;
		}
		if(p->val > 9 && lastone == NULL)
		{
			lastone = p;
			lastone->left = node;
			if(root == NULL)
			{
				lastroot = root = p;
			}
			continue;
		}
		if(p->val == 11 || p->val == 12)
		{
			root = p;
			root->left = lastroot;
			lastone = p;
			lastroot = p;
		}
		else if(p->val == 14 || p->val == 15)
		{
			p->left = lastone->right;
			lastone->right = p;
			lastone = p;
		}
		else
		{
			lastone->right = p;
		}
	}
	return root;
}

void jfree(struct tree *root)
{
	if(!root->left && !root->right)
		free(root);
	else
	{
		jfree(root->left);
		jfree(root->right);
	}
}

int calc(char exp[])
{
	struct tree *root = NULL;
	root = init_tree(exp);
	int ret = run_calc(root);
	
	jfree(root);
	return ret;
}

int main(int argc, char *argv[])
{
	printf("%s=%d\n", argv[1], calc(argv[1]));
	// 1+2*3
/*
 *      +
 *     / \
 *    1   *
 *       / \
 *      2   3
 */
	return 0;
}
