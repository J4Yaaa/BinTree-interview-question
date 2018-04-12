#include "bintree.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "StackQueue.h"

void TreeInit(TreeNode** root)
{
    assert(root == NULL);
    if(*root == NULL)
    {
        return;
    }
    *root = NULL;
}

TreeNode* CreateTreeNode(TreeType value)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = value;
    node->l_child = NULL;
    node->r_child = NULL;
    return node;
}

TreeNode* _CreateTree(TreeType arr[],size_t* index,size_t size,TreeType non_node)
{
    if(index == NULL)
    {
        return NULL;
    }
    if(*index >= size)
    {
        return NULL;
    }
    if(arr[*index] == non_node)
    {
        return NULL;
    }
    TreeNode* root = CreateTreeNode(arr[*index]);
    ++(*index);
    root->l_child = _CreateTree(arr,index,size,non_node);
    ++(*index);
    root->r_child = _CreateTree(arr,index,size,non_node);
    return root;
}

TreeNode* CreateTree(TreeType arr[],size_t size,TreeType non_node)
{
    if(arr == NULL)
    {
        return NULL;
    }
    size_t index = 0;
    return _CreateTree(arr,&index,size,non_node);
}

void PreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ",root->data);
    PreOrder(root->l_child);
    PreOrder(root->r_child);
}

void InOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    InOrder(root->l_child);
    printf("%d ",root->data);
    InOrder(root->r_child);
}

void PostOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    PostOrder(root->l_child);
    PostOrder(root->r_child);
    printf("%d ",root->data);
}

size_t Get_Root_Pos_In_In_arr(TreeType value,TreeType in_arr[],size_t beg,size_t end)
{
    size_t i = beg;
    for(; i < end; ++i)
    {
        if(in_arr[i] == value)
        {
            return i;
        }
    }
    return (size_t)-1;
}

TreeNode* _RebuildTree(TreeType pre_arr[],TreeType in_arr[],size_t beg,size_t end,size_t* index,size_t size)
{
    if(*index >= size)
    {
        return NULL;
    }
    if(end - beg <= 0)
    {
        return NULL;
    }
    size_t offset = Get_Root_Pos_In_In_arr(pre_arr[*index],in_arr,beg,end);
    if(offset == (size_t)-1)
    {
        return NULL;
    }
    TreeNode* root = CreateTreeNode(pre_arr[*index]);
    ++(*index);
    //这里 ++(*index)以后的元素要么是root的左孩子,要么是root的右孩子
    //如果左孩子赋值失败,就会return回来,index就给右孩子用
    //所以,在赋值失败以后不需要 ++index
    //如果左孩子赋值成功,就会继续寻找下一个元素(++(*index)),直到赋值失败以后,index就是右孩子的元素
    root->l_child = _RebuildTree(pre_arr,in_arr,0,offset,index,size);
    root->r_child = _RebuildTree(pre_arr,in_arr,offset+1,end,index,size);
    return root;
}

TreeNode* RebuildTree(TreeType pre_arr[],size_t pre_size,TreeType in_arr[],size_t in_size)
{
    if(pre_arr == NULL || in_arr == NULL)
    {
        return NULL;
    }
    if(pre_size != in_size)
    {
        return NULL;
    }
    size_t index = 0;
    return _RebuildTree(pre_arr,in_arr,0,in_size,&index,in_size);
}

int _DoesTree1HaveTree2(TreeNode* root1,TreeNode* root2)
{
    if(root2 == NULL)
    {
        return 1;
    }
    if(root1 == NULL)
    {
        return 0;
    }
    if(root1->data != root2->data)
    {
        return 0;
    }
    return _DoesTree1HaveTree2(root1->l_child,root2->l_child) && _DoesTree1HaveTree2(root1->r_child,root2->r_child);
}

int DoesTree1HaveTree2(TreeNode* root1,TreeNode* root2)
{
    if(root1 == NULL || root2 == NULL)
    {
        return 0;
    }
    //1.再 tree1 中找到和 tree2 根节点值相同的元素
    //2.判断这个元素的左右子树 和 tree2 的左右子树是否相同
    int result = 0;
    //从根节点开始找和root2根节点值相同的元素
    //如果根节点不匹配,就递归的从左子树和右子树中找
    result = _DoesTree1HaveTree2(root1,root2);
    if(!result)
    {
        result = _DoesTree1HaveTree2(root1->l_child,root2);
    }
    if(!result)
    {
        result = _DoesTree1HaveTree2(root1->r_child,root2);
    }
    return result;
}

void MirrorTree(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    TreeNode* tmp = root->l_child;
    root->l_child = root->r_child;
    root->r_child = tmp;
    MirrorTree(root->l_child);
    MirrorTree(root->r_child);
}

int _IsSymmetrical(TreeNode* root_left,TreeNode* root_right)
{
    //如果都为空就表示相同
    if(root_left == NULL && root_right == NULL)
    {
        return 1;
    }
    //如果不同时为空就代表不相同
    //注意:判断同时为空(&&)必须放在不同时为空(||)前面
    //     因为不同时为空为真时包含了同时为空的情况
    if(root_left == NULL || root_right == NULL)
    {
        return 0;
    }
    //这里进行 根 左 右 和 根 右 左的递归判断
    return _IsSymmetrical(root_left->l_child,root_right->r_child) && _IsSymmetrical(root_left->r_child,root_right->l_child);
}

int IsSymmetrical(TreeNode* root)
{
    //判断一个数是不是对称的可以观察他左子树是否和右子树相同
    //这个树的 根 左 右序列和 根 右 左序列是否相同
    return _IsSymmetrical(root,root);
}

void PrintFromTopToBottom(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    QueueType value;
    while(SeqQueueFront(&q,&value))
    {
        printf("%d ",value->data);
        if(value->l_child != NULL)
        {
            SeqQueuePush(&q,value->l_child);
        }
        if(value->r_child != NULL)
        {
            SeqQueuePush(&q,value->r_child);
        }
        SeqQueuePop(&q);
    }
    printf("\n");
}

void PrintTreeWithLine(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    int nextlevelnode = 0;
    int hasprintnode = 1;
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    QueueType value;
    while(SeqQueueFront(&q,&value))
    {
        printf("%d ",value->data);

        if(value->l_child != NULL)
        {
            ++nextlevelnode;
            SeqQueuePush(&q,value->l_child);
        }
        if(value->r_child != NULL)
        {
            ++nextlevelnode;
            SeqQueuePush(&q,value->r_child);
        }

        SeqQueuePop(&q);
        --hasprintnode;
        if(hasprintnode == 0)
        {
            hasprintnode = nextlevelnode;
            nextlevelnode = 0;
            printf("\n");
        }
    }
}

void PrintTreeWithZhi(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack_left_to_right;//入栈顺序是树的节点从左向右
    SeqStack stack_right_to_left;//入栈顺序是树的节点从右向左
    SeqStackInit(&stack_left_to_right);
    SeqStackInit(&stack_right_to_left);
    SeqStackPush(&stack_left_to_right,root);
    while(stack_left_to_right.size != 0 || stack_right_to_left.size != 0)
    {
        SeqStackType value;
        while(SeqStackTop(&stack_left_to_right,&value))
        {
            printf("%d ",value->data);
            SeqStackPop(&stack_left_to_right);
            if(value->r_child != NULL)
            {
                SeqStackPush(&stack_right_to_left,value->r_child);
            }
            if(value->l_child != NULL)
            {
                SeqStackPush(&stack_right_to_left,value->l_child);
            }
        }
        printf("\n");
        while(SeqStackTop(&stack_right_to_left,&value))
        {
            printf("%d ",value->data);
            SeqStackPop(&stack_right_to_left);
            if(value->l_child != NULL)
            {
                SeqStackPush(&stack_left_to_right,value->l_child);
            }
            if(value->r_child != NULL)
            {
                SeqStackPush(&stack_left_to_right,value->r_child);
            }
        }
        printf("\n");
    }
}

int VerifyPostSquenceOfBST(TreeType arr[],int len)
{
    if(arr == NULL || len <= 0)
    {
        return 0;
    }
    TreeType root = arr[len - 1];
    //找到第一个大于根节点值得元素下标
    int i = 0;
    for(; i < len - 1; ++i)
    {
        if(arr[i] > root)
        {
            break;
        }
    }
    //判断是不是下标 i 以后所有的值都比root大
    int j = i;
    for(; j < len - 1; ++j)
    {
        if(arr[j] < root)
        {
            return 0;
        }
    }
    //到这里证明当前根节点满足 i 以前所有元素小于根节点,以后所有元素大于根节点
    //再递归的判断 根节点左侧和根节点右侧是不是后序遍历
    int left = 1;
    //i 只可以大于0,等于0时代表没有元素
    if(i > 0)
    {
        left = VerifyPostSquenceOfBST(arr,i);
    }
    int right = 1;
    if(j < len - 1)
    {
        right = VerifyPostSquenceOfBST(arr+i,len - 1 - i);
    }
    return (left && right);
}

int VerifyPreSquenceOfBST(TreeType arr[],int beg,int end)
{
    if(arr == NULL || end <= 0)
    {
        return 0;
    }
    //这里是一个 [beg,end)的前闭后开区间,每次的根节点都是beg对应的元素
    TreeType root = arr[beg];
    //找到第一个大于根节点的值
    int i = 1;
    for(; i < end; ++i)
    {
        if(arr[i] > root)
        {
            break;
        }
    }
    int j = i;
    //判断i以后是不是都是大于根节点的值
    for(; j < end; ++j)
    {
        if(arr[j] < root)
        {
            return 0;
        }
    }
    int left = 1;
    //只有当 end - beg > 1 即最少有一个元素的时候才有必要继续判断下去
    if(end - beg > 1)
    {
        left = VerifyPreSquenceOfBST(arr,beg+1,i);
    }
    int right = 1;
    if(end - beg > 1)
    {
        right = VerifyPreSquenceOfBST(arr,i,end - 1);
    }
    return (left && right);
}

void PrintStack(SeqStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    size_t i = 0;
    for(; i < stack->size; ++i)
    {
        printf("%d ",stack->data[i]->data);
    }
    printf("\n");
}

void _FindSumIsKPath(TreeNode* root,int K,SeqStack* stack,int* sum)
{
    *sum += root->data;
    SeqStackPush(stack,root);
    if(root->l_child != NULL && *sum < K)
    {
        _FindSumIsKPath(root->l_child,K,stack,sum);
    }
    if(root->r_child != NULL && *sum < K)
    {
        _FindSumIsKPath(root->r_child,K,stack,sum);
    }
    if(*sum == K)
    {
       PrintStack(stack); 
    }
    SeqStackType value;
    SeqStackTop(stack,&value);
    *sum -= (value->data);
    SeqStackPop(stack);
}

void FindSumIsKPath(TreeNode* root,int K)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    int sum = 0;
    _FindSumIsKPath(root,K,&stack,&sum);
}

void _TreeToLinkList(TreeNode* root,TreeNode** lastnode)
{
    if(lastnode == NULL)
    {//非法输入
        return;
    }
    if(root == NULL)
    {//表示已经完成,链表走到了末尾
     //或者找到了开始元素,链表的头
        return;
    }
    //这里进行类似于中序遍历
    //先处理左子树
    TreeNode* cur = root;
    if(cur->l_child != NULL)
    {
        _TreeToLinkList(cur->l_child,lastnode);
    }
    //第一次循环退出我们就已经找到了链表的头结点
    //链表节点的左子树指向下一个节点

    //再处理根节点
    cur->l_child = *lastnode;
    if(*lastnode != NULL)
    {
        //如果当前lastnode节点不为空,就让lastnode的右子树指向cur
        (*lastnode)->r_child = cur;
    }
    *lastnode = cur;

    //最后处理右子树
    if(cur->r_child != NULL)
    {
        _TreeToLinkList(cur->r_child,lastnode);
    }
}

TreeNode* TreeToLinkList(TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    //需要转成一个排序的双向链表,可以考虑中序遍历
    //这里的lastnode代表每次指向当前已排序链表的结尾
    TreeNode* lastnode = NULL;
    _TreeToLinkList(root,&lastnode);
    TreeNode* head = lastnode;
    while(head != NULL && head->l_child != NULL)
    {
        head = head->l_child;
    }
    return head;
}

TreeNode* _KthNode(TreeNode* root,int K,int* index,TreeNode** knode)
{
    if(index == NULL)
    {
        return NULL;
    }
    //现在到最左侧,也就是第一个节点
    if(root->l_child != NULL)
    {
        _KthNode(root->l_child,K,index,knode);
    }
    //(如果有左孩子)只有在每一次跳出左孩子时在表示这个节点已经是前面的节点
    //(没有左孩子)表示当前节点是前面的节点
    ++(*index);
    if(*index == K)
    {
        *knode = root;
    }
    if(root->r_child != NULL)
    {
        _KthNode(root->r_child,K,index,knode);
    }
    return *knode;
}

TreeNode* KthNode(TreeNode* root,int K)
{
    if(root == NULL || K <= 0)
    {
        return NULL;
    }
    //index表示当前已经判断到第几个节点了
    int index = 0;
    //knode表示最后返回的值,找到就返回地址,没找到就返回null
    TreeNode* knode = NULL;
    return _KthNode(root,K,&index,&knode);
}

int Hight(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    int left = Hight(root->l_child);
    int right = Hight(root->r_child);
    return (left>right) ? left+1 : right+1;
}

int _IsBalancedTree(TreeNode* root,int* depth)
{
    if(root == NULL)
    {
        *depth = 0;
        return 1;
    }
    int left,right;
    //如果当前根节点有左孩子并且有右孩子,就一直递归找到最下面的子树
    if(_IsBalancedTree(root->l_child,&left)
       && _IsBalancedTree(root->r_child,&right))
    {
        int sub = left - right;
        if(sub <= 1 && sub >= -1)
        {//证明当前根节点是平衡的,那就求出当前的深度
         //当前节点的深度就是其父节点左孩子的深度或者右孩子的深度
         //根据这个深度了一判断当前树是否平衡
            *depth = 1 + (left > right ? left : right);
            return 1;
        }
    }
    return 0;
}

int IsBalancedTree(TreeNode* root)
{
    if(root == NULL)
    {
        return 1;
    }
    int depth = 0;
    return _IsBalancedTree(root,&depth);
}

/////////////////////////////////////////////
// 测试代码
/////////////////////////////////////////////

#if 1

#define TEST_HEADER printf("\n~~~~~~~~~~~%s~~~~~~~~~~~\n",__FUNCTION__)

void TestCreateTree()
{
    TEST_HEADER;
    TreeType arr[] = {1,2,4,'$','$','$',3,5,'$','$',6,'$','$'};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,'$');

    printf("先序: ");
    PreOrder(root);
    printf("\n");

    printf("中序: ");
    InOrder(root);
    printf("\n");

    printf("后序: ");
    PostOrder(root);
    printf("\n");
}

void TestRebulidTree()
{
    TEST_HEADER;
//测试代码1 完全二叉树
//    TreeType pre_arr[] = {1,2,4,5,3,6,7};
//    size_t pre_size = sizeof(pre_arr)/sizeof(pre_arr[0]);
//    TreeType in_arr[] = {4,2,5,1,6,3,7};
//    size_t in_size = sizeof(in_arr)/sizeof(in_arr[0]);
//    TreeNode* root = RebuildTree(pre_arr,pre_size,in_arr,in_size);

//测试代码2 普通二叉树
//    TreeType pre_arr[] = {1,2,4,7,3,5,6,8};
//    size_t pre_size = sizeof(pre_arr)/sizeof(pre_arr[0]);
//    TreeType in_arr[] = {4,7,2,1,5,3,8,6};
//    size_t in_size = sizeof(in_arr)/sizeof(in_arr[0]);
//    TreeNode* root = RebuildTree(pre_arr,pre_size,in_arr,in_size);

//测试代码3 所有节点只有左子树
//    TreeType pre_arr[] = {1,2,3,4};
//    size_t pre_size = sizeof(pre_arr)/sizeof(pre_arr[0]);
//    TreeType in_arr[] = {4,3,2,1};
//    size_t in_size = sizeof(in_arr)/sizeof(in_arr[0]);
//    TreeNode* root = RebuildTree(pre_arr,pre_size,in_arr,in_size);

//测试代码4 所有节点只有右子树
//    TreeType pre_arr[] = {1,2,3,4};
//    size_t pre_size = sizeof(pre_arr)/sizeof(pre_arr[0]);
//    TreeType in_arr[] = {1,2,3,4};
//    size_t in_size = sizeof(in_arr)/sizeof(in_arr[0]);
//    TreeNode* root = RebuildTree(pre_arr,pre_size,in_arr,in_size);

//测试代码5 只有一个节点的树
    TreeType pre_arr[] = {1};
    size_t pre_size = sizeof(pre_arr)/sizeof(pre_arr[0]);
    TreeType in_arr[] = {1};
    size_t in_size = sizeof(in_arr)/sizeof(in_arr[0]);
    TreeNode* root = RebuildTree(pre_arr,pre_size,in_arr,in_size);
    printf("先序: ");
    PreOrder(root);
    printf("\n");

    printf("中序: ");
    InOrder(root);
    printf("\n");

    printf("后序: ");
    PostOrder(root);
    printf("\n");
}

void TestHasSubtree()
{
    TEST_HEADER;
    TreeType arr1[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};
    size_t size1 = sizeof(arr1)/sizeof(arr1[0]);
    TreeNode* root1 = CreateTree(arr1,size1,-1);

    TreeType arr2[] = {8,9,-1,-1,2,-1,-1};
    size_t size2 = sizeof(arr2)/sizeof(arr2[0]);
    TreeNode* root2 = CreateTree(arr2,size2,-1);

    printf("ret = %d\n",DoesTree1HaveTree2(root1,root2));
}

void TestMirror()
{
    TEST_HEADER;
    TreeType arr[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    printf("原树: \n");
    printf("先序: ");
    PreOrder(root);
    printf("\n");

    printf("中序: ");
    InOrder(root);
    printf("\n");

    printf("后序: ");
    PostOrder(root);
    printf("\n");

    MirrorTree(root);
    printf("镜像以后的树: \n");
    printf("先序: ");
    PreOrder(root);
    printf("\n");

    printf("中序: ");
    InOrder(root);
    printf("\n");

    printf("后序: ");
    PostOrder(root);
    printf("\n");
}

void TestIsSymmetricalTree()
{
    TEST_HEADER;
//测试代码1 -> 不对称二叉树
//    TreeType arr[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};

//测试代码2 -> 对称二叉树
//    TreeType arr[] = {8,6,5,-1,-1,7,-1,-1,10,9,-1,-1,11,-1,-1};

//测试代码3 -> 所有节点只有左子树
//    TreeType arr[] = {8,6,5,-1,-1,-1,-1};

//测试代码4 -> 所有节点只有右子树
//    TreeType arr[] = {8,-1,6,-1,5,-1,-1};

//测试代码5 -> 只有一个节点
    TreeType arr[] = {8};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    printf("ret expect 1,actual %d\n",IsSymmetrical(root));
}

void TestPrintFromTopToBottom()
{
    TEST_HEADER;
//测试代码1 -> 不对称二叉树
//    TreeType arr[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};

//测试代码2 -> 对称二叉树
//    TreeType arr[] = {8,6,5,-1,-1,7,-1,-1,10,9,-1,-1,11,-1,-1};

//测试代码3 -> 所有节点只有左子树
//    TreeType arr[] = {8,6,5,-1,-1,-1,-1};

//测试代码4 -> 所有节点只有右子树
//    TreeType arr[] = {8,-1,6,-1,5,-1,-1};

//测试代码5 -> 只有一个节点
    TreeType arr[] = {8};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    PrintFromTopToBottom(root);
}

void TestPrintTreeWithLine()
{

    TEST_HEADER;
//测试代码1 -> 不对称二叉树
    TreeType arr[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};

//测试代码2 -> 对称二叉树
//    TreeType arr[] = {8,6,5,-1,-1,7,-1,-1,10,9,-1,-1,11,-1,-1};

//测试代码3 -> 所有节点只有左子树
//    TreeType arr[] = {8,6,5,-1,-1,-1,-1};

//测试代码4 -> 所有节点只有右子树
//    TreeType arr[] = {8,-1,6,-1,5,-1,-1};

//测试代码5 -> 只有一个节点
//    TreeType arr[] = {8};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    PrintTreeWithLine(root);
}

void TestPrintTreeWithZhi()
{

    TEST_HEADER;
//测试代码1 -> 不对称二叉树
//    TreeType arr[] = {8,8,9,-1,-1,2,4,-1,-1,7,-1,-1,7,-1,-1};

//测试代码2 -> 对称二叉树
    TreeType arr[] = {8,6,5,-1,-1,7,-1,-1,10,9,-1,-1,11,-1,-1};

//测试代码3 -> 所有节点只有左子树
//    TreeType arr[] = {8,6,5,-1,-1,-1,-1};

//测试代码4 -> 所有节点只有右子树
//    TreeType arr[] = {8,-1,6,-1,5,-1,-1};

//测试代码5 -> 只有一个节点
//    TreeType arr[] = {8};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    PrintTreeWithZhi(root);
}

void TestVerifyPostSquenceOfBST()
{
    TEST_HEADER;
//    TreeType arr[] = {5,7,6,9,11,10,8};
    TreeType arr[] = {7,4,6,5};
    int len = sizeof(arr)/sizeof(arr[0]);
    printf("ret = %d\n",VerifyPostSquenceOfBST(arr,len));
}

void TestVerifyPreSquenceOfBST()
{
    TEST_HEADER;
//    TreeType arr[] = {8,6,5,7,10,9,11};
    TreeType arr[] = {4,3,2,1};
    int len = sizeof(arr)/sizeof(arr[0]);
    printf("ret = %d\n",VerifyPreSquenceOfBST(arr,0,len));

}

void TestFindSumIsKPath()
{
    TEST_HEADER;
//    TreeType arr[] = {10,5,4,-1,-1,7,-1,-1,12,-1,-1};
    TreeType arr[] = {1,2,4,5,-1,-1,1,2,-1,-1,-1,2,-1,4,1,-1,-1,-1,3,-1,6,-1,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    FindSumIsKPath(root,10);
}

void PrintLinkList(TreeNode* head)
{
    if(head == NULL)
    {
        return;
    }
    TreeNode* cur = head;
    printf("正向打印: ");
    while(cur->r_child != NULL)
    {
        printf("%d ",cur->data);
        cur = cur->r_child;
    }
    printf("%d ",cur->data);
    printf("\n");

    printf("反向打印:");
    while(cur != NULL)
    {
        printf("%d ",cur->data);
        cur = cur->l_child;
    }
    printf("\n");
}

void TestTreeToLinkList()
{
    TEST_HEADER;
    TreeType arr[] = {10,6,4,-1,-1,8,-1,-1,14,12,-1,-1,16,-1,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    TreeNode* head = TreeToLinkList(root);
    PrintLinkList(head);
}

void TestKthNode()
{
    TEST_HEADER;
    TreeType arr[] = {5,3,2,-1,-1,4,-1,-1,7,6,-1,-1,8,-1,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    TreeNode* kthnode = KthNode(root,5);
    printf("kthnode is %d\n",kthnode->data);
}

void TestHight()
{
    TEST_HEADER;
    TreeType arr[] = {5,3,2,-1,-1,4,-1,4,-1,-1,7,6,-1,-1,8,-1,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    printf("hight = %d\n",Hight(root));
}

void TestIsBalancedTree()
{
    TEST_HEADER;
    TreeType arr[] = {1,2,4,-1,-1,5,7,-1,-1,-1,3,-1,6,-1,-1};
    int size = sizeof(arr)/sizeof(arr[0]);
    TreeNode* root = CreateTree(arr,size,-1);
    printf("ret = %d\n",IsBalancedTree(root));
}

int main()
{
    TestCreateTree();
    TestRebulidTree();
    TestHasSubtree();
    TestMirror();
    TestIsSymmetricalTree();
    TestPrintFromTopToBottom();
    TestPrintTreeWithLine();
    TestPrintTreeWithZhi();
    TestVerifyPostSquenceOfBST();
    TestVerifyPreSquenceOfBST();
    TestFindSumIsKPath();
    TestTreeToLinkList();
    TestKthNode();
    TestHight();
    TestIsBalancedTree();
    return 0;
}
 
#endif
