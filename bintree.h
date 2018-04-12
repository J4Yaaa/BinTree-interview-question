#pragma once
#include <stddef.h>

typedef int TreeType;

typedef struct TreeNode
{
    TreeType data;
    struct TreeNode* l_child;
    struct TreeNode* r_child;
}TreeNode;

void TreeInit(TreeNode** root);

TreeNode* CreateTree(TreeType arr[],size_t size,TreeType non_node);

void PreOrder(TreeNode* root);

void InOrder(TreeNode* root);

void PostOrder(TreeNode* root);

//根据树的先序遍历结果和中序遍历结果还原一棵树 7
TreeNode* RebuildTree(TreeType pre_arr[],size_t pre_size,TreeType in_arr[],size_t in_size);

//判断 tree2 是不是 tree1 的子树 26
int DoesTree1HaveTree2(TreeNode* root1,TreeNode* root2);

//二叉树的镜像 27
void MirrorTree(TreeNode* root);

//判断树是否对称 28
int IsSymmetrical(TreeNode* root);

//从上到下打印二叉树 32
void PrintFromTopToBottom(TreeNode* root);

//从上到下按层打印,每层打印成一行 32扩展
void PrintTreeWithLine(TreeNode* root);

//之字形打印二叉树
void PrintTreeWithZhi(TreeNode* root);

//输入一数组,判断该数组是不是二叉搜索树的后序遍历 33
int VerifyPostSquenceOfBST(TreeType arr[],int len);
//判断是不是先序遍历
int VerifyPreSquenceOfBST(TreeType arr[],int beg,int end);

//二叉树中和为某一值得路径 34
void FindSumIsKPath(TreeNode* root,int K);

//二叉搜索树转化为双向链表 36
TreeNode* TreeToLinkList(TreeNode* root);

//二叉搜索树中的第K大数字 54
TreeNode* KthNode(TreeNode* root,int K);

//求二叉树的深度 55
int Hight(TreeNode* root);
//判断二叉树是不是平衡二叉树
int IsBalancedTree(TreeNode* root);

