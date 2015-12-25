// BuildTree.cpp : �������̨Ӧ�ó������ڵ㡣


#include "stdafx.h"
struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

/*
  *startPerorder--------------------������������ָ��
  *endPreorder---------------------����������յ�ָ��
  *	startInorder----------------------������������ָ��
  *	endInorder-----------------------����������յ�ָ��
  */
// �ݹ���ã�ÿ��ȷ����ǰ���  
BinaryTreeNode* ConstructCore(int* startPerorder, int* endPreorder, int* startInorder, int* endInorder)
{
	//�����һ��Ϊ���ڵ�  
	int rootValue = startPerorder[0];
	BinaryTreeNode* root = new BinaryTreeNode;
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;

	//�ݹ��˳�����  
	if (startPerorder == endPreorder)
	{
		if (startInorder == endInorder && *startPerorder == *endInorder)
			return root;
		else
			printf("Invalid input");
	}

	// ��������õ����ڵ㣬������������ҵ����ڵ��ֵ  
	int* rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;
  
	if (rootInorder == endInorder && *rootInorder != rootValue)
		printf("Invalid input.");

	int leftLength = rootInorder - startInorder;//��������Ԫ�ظ���
	int* leftPreorderEnd = startPerorder + leftLength;//��������������������Ľڵ�
	if (leftLength > 0)
	{
		//���Ӽ��й���������  
		root->m_pLeft = ConstructCore(startPerorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	}
	if (leftLength < endPreorder - startPerorder)//������Ӽ���Ϊ�յĻ�
	{
		//���Ӽ��й���������  
		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;
}

//������������򹹽�������  
BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

void TraverseTreePostorder(BinaryTreeNode* proot)
{
	if (proot == NULL)
		return;

	if (proot->m_pLeft != NULL)
		TraverseTreePostorder(proot->m_pLeft);
	if (proot->m_pRight != NULL)
		TraverseTreePostorder(proot->m_pRight);

	cout << proot->m_nValue << " ";
}
int isomorphic(const BinaryTreeNode *t1, const BinaryTreeNode *t2)
{
	if (t1 == NULL && t2 == NULL)
		return 1;
	else if (t1 == NULL || t2 == NULL)
		return 0;
	else
		return isomorphic(t1->m_pLeft, t2->m_pLeft) && isomorphic(t1->m_pRight, t2->m_pRight) ||
		isomorphic(t1->m_pLeft, t2->m_pRight) && isomorphic(t1->m_pRight, t2->m_pLeft);
}
int main()
{
	int preorder_1[] = {1,2,4,5,6,3,7,8};
	int inorder_1[] = {4,2,6,5,1,8,7,3};
	int preorder_2[] = {1,3,7,8,2,5,6,4};
	int inorder_2[] = {7,8,3,1,6,5,2,4};

	BinaryTreeNode* pRoot_1 = Construct(preorder_1, inorder_1, 8);
	BinaryTreeNode* pRoot_2 = Construct(preorder_2, inorder_2, 8);
	/*************************************/
	cout << "Tree 1:" << endl;
	cout << "preorder:";
	for (int i = 0; i < 7; i++)
		cout << *(preorder_1 + i) << " ";
	cout << endl;
	cout << "inorder:";
	for (int i = 0; i < 7; i++)
		cout << *(inorder_1 + i) << " ";
	cout << endl;
	cout << "postoder:";
	TraverseTreePostorder(pRoot_1);
	cout << endl;
	
	/************************************/
	cout << endl << "Tree 2:"<<endl;
	cout << "preorder:";
	for (int i = 0; i < 7; i++)
		cout << *(preorder_2 + i) << " ";
	cout << endl;
	cout << "inorder:";
	for (int i = 0; i < 7; i++)
		cout << *(inorder_2 + i) << " ";
	cout << endl;
	cout << "postoder:";
	TraverseTreePostorder(pRoot_2);
	cout << endl;
	
	int flag = isomorphic(pRoot_1, pRoot_2);
	if (1 == flag)
		cout << "ismorphic!" << endl;
	else
		cout << "not ismorphic" << endl;
	
	return 0;
}
