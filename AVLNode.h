#pragma once
#ifndef AVL_NODE_HPP

#define AVL_NODE_HPP
struct AVLNode
{
	int Value;
	int height;
	AVLNode *left, *right;
	AVLNode(int aValue)
	{
		left = 0;
		right = 0;
		Value = aValue;
	}
};
#endif
