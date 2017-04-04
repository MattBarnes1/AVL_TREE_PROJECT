#include "AVL.h"
#include "AVLNode.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>



AVL::AVL()
{
	root = 0;
}


AVL::~AVL()
{
	clear(&root);
}





void AVL::insert(int aNewInt)
{
	insert(&root, aNewInt);
}


void AVL::clear()
{
	clear(&root);
}

void AVL::clear(AVLNode **WhyGodWhy)
{
	if (!(*WhyGodWhy)) return;
	if ((*WhyGodWhy)->left)
	{
		clear(&(*WhyGodWhy)->left);
	}
	if ((*WhyGodWhy)->right)
	{
		clear(&(*WhyGodWhy)->right);
	}
	delete *WhyGodWhy;
	*WhyGodWhy = 0;
}

void AVL::remove(int anIntToRemove)
{
	AVLNode*** Right = 0;
	bool end = false;
	remove(Right, &root, &root, anIntToRemove);
}


void AVL::insert(AVLNode **WhyGodWhy, int aValue)//WhyGodWhy is always the prior thing pointed to.
{
	AVLNode *Parent = 0;
	AVLNode *Child = 0;
	if (!(*WhyGodWhy))
	{
		Parent = (*WhyGodWhy);
		*WhyGodWhy = new AVLNode(aValue);
		updateHeight(*WhyGodWhy);
		Child = (*WhyGodWhy);
		return;
	}
	else if ((*WhyGodWhy)->Value < aValue)
	{ //Parent of our node so 02 in example when inserting 3
		Parent = (*WhyGodWhy);
		insert(&(*WhyGodWhy)->right, aValue);
		Child = (*WhyGodWhy)->right;
	}
	else if ((*WhyGodWhy)->Value > aValue)
	{
		Parent = (*WhyGodWhy);
		insert(&(*WhyGodWhy)->left, aValue);
		Child = (*WhyGodWhy)->left;
	}
	updateHeight(*WhyGodWhy);
	if (Child == 0) return;
	updateHeight(Child);
	int Balance = checkBalance(*WhyGodWhy);
	if (Balance < -1)
	{
		if (checkBalance((*WhyGodWhy)->right) > 0)
		{
			//std::cout << "Before Rotations: " << serialize() << std::endl;
			rotateRight(&(*WhyGodWhy)->right, &(*WhyGodWhy)->right->left);
			//std::cout << "After Right Rotation" << serialize() << std::endl;
			rotateLeft(WhyGodWhy, &(*WhyGodWhy)->right);
			//std::cout << "After Left Rotation" << serialize() << std::endl;
		}
		else {
			rotateLeft(WhyGodWhy, &(*WhyGodWhy)->right);
		}

	}
	else if (Balance > 1)
	{
		if (checkBalance((*WhyGodWhy)->left) < 0)
		{
			rotateLeft(&(*WhyGodWhy)->left, &((*WhyGodWhy)->left)->right);
		
			rotateRight(WhyGodWhy, &(*WhyGodWhy)->left);
		}
		else {
			rotateRight(WhyGodWhy, &(*WhyGodWhy)->left);
		}
	}
	return;
}




void AVL::rotateLeft(AVLNode **newParent, AVLNode **anImbalancedNode)
{
	AVLNode *oldParentSwap = (*newParent);
	*newParent = *anImbalancedNode;
	oldParentSwap->right = (*newParent)->left;
	(*newParent)->left = oldParentSwap;
	



	updateHeight(*newParent);
	updateHeight(oldParentSwap);
}

void AVL::rotateRight(AVLNode **newParent, AVLNode **anImbalancedNode)
{
	AVLNode *oldParentSwap = (*newParent);
	*newParent = *anImbalancedNode;
	//std::cout << "*newParent = *anImbalancedNode: " << serialize() << std::endl;
	oldParentSwap->left = (*newParent)->right;
	//std::cout << "oldParentSwap->left = (*newParent)->right; " << serialize() << std::endl;
	(*newParent)->right = oldParentSwap;
	//std::cout << "(*newParent)->right = oldParentSwap; " << serialize() << std::endl;
	updateHeight(*newParent);
	updateHeight(oldParentSwap);

}


int AVL::checkBalance(AVLNode* n) {

	return (n->left ? n->left->height : -1) - (n->right ? n->right->height : -1);

}

void AVL::remove(AVLNode ***LastToTakeALeft, AVLNode **WhyGodWhyParent, AVLNode **WhyGodWhy, int Value)
{
	AVLNode ***LocalLast = 0;

	if ((*WhyGodWhy)->Value > Value)
	{
		LocalLast = LastToTakeALeft; //Saves the pointer by passing this one
 		LastToTakeALeft = &WhyGodWhy;
		bool areturn = false;
		if(!(&(*WhyGodWhy)->left))
		{
			**LastToTakeALeft = 0;
			LocalLast = 0;

		} else {
		remove(LocalLast, &(*WhyGodWhy), &(*WhyGodWhy)->left, Value);
		if (LocalLast)
		{
			if ((*WhyGodWhy) == (**LastToTakeALeft)) //We've returned to a working return; Have deleted the proper value (otherwise returns null);
						{
							AVLNode ** Parent = *LastToTakeALeft;
							LastToTakeALeft = LocalLast;


							bool areturn = false;
							remove(LocalLast, Parent, &(*Parent), ((*Parent)->left)->Value);		
							
							
							if (LocalLast != 0)
							{
								LastToTakeALeft = LocalLast; //reorders and returns
							}
						}
					
				} else {
				**LastToTakeALeft = 0;
			}
		
		}
	}
	else if ((*WhyGodWhy)->Value < Value)
	{
		LocalLast = LastToTakeALeft;
		if(!(&(*WhyGodWhy)->right))
		{
			**LastToTakeALeft = 0;
			LocalLast = 0;

		} else {
		remove(LocalLast, &(*WhyGodWhy), &(*WhyGodWhy)->right, Value);
		if (LocalLast)
		{
				AVLNode *** Parent = LastToTakeALeft;
				if (*WhyGodWhy == **LastToTakeALeft) //We've returned to a working return; Have deleted the proper value (otherwise returns null);
				{
					remove(LocalLast, Parent, &(**Parent)->left, (&(**Parent)->left)->Value);
					if (LocalLast != 0)
					{
						LastToTakeALeft = LocalLast;
					}
				}
			
		}
	}
	}
	else //Values Match
	{
		if ((*WhyGodWhy)->left == 0 || (*WhyGodWhy)->right == 0) //one node is null or both are null
		{
			if ((*WhyGodWhy)->left != 0)
			{
				AVLNode *Temp = (*WhyGodWhy)->left;
				(*WhyGodWhy)->left = 0;//prolly unecessary
				delete *WhyGodWhy;
				*WhyGodWhy = Temp;
				if(LastToTakeALeft != 0) *LastToTakeALeft = 0;
			}
			else if ((*WhyGodWhy)->right != 0) {
				AVLNode *Temp = (*WhyGodWhy)->right;
				(*WhyGodWhy)->right = 0;
				delete  *WhyGodWhy;
				*WhyGodWhy = Temp;
				if (LastToTakeALeft != 0)  *LastToTakeALeft = 0;
			}
			else {
				delete  *WhyGodWhy;
				*WhyGodWhy = 0;
				if (LastToTakeALeft != 0)  *LastToTakeALeft = 0;
				int i = 0;
			}
		}
		else {
			if ((*WhyGodWhy)->right) //Easy case
			{
				AVLNode * myRight = (*WhyGodWhy)->right;
				AVLNode * myLeft = (*WhyGodWhy)->left;
				AVLNode * retVal;
				findInOrderSuccessor(&retVal, &(*WhyGodWhy)->right);

				delete  *WhyGodWhy;
				*WhyGodWhy = retVal;
				if (myRight != *WhyGodWhy)
				{
					(*WhyGodWhy)->right = myRight;
				}
				if (myRight != *WhyGodWhy)
				{
					updateHeight((*WhyGodWhy)->right);
				}
				(*WhyGodWhy)->left = myLeft;
				if (((*WhyGodWhy)->left))
				{
					updateHeight((*WhyGodWhy)->left);
				}
				if (LastToTakeALeft != 0)  *LastToTakeALeft = 0;
			}
			else { //Jesus, no!
				AVLNode * myRight = (*WhyGodWhy)->right;
				AVLNode * myLeft = (*WhyGodWhy)->left;
				delete  *WhyGodWhy;

				*WhyGodWhy = new AVLNode((**LastToTakeALeft)->Value);
				(*WhyGodWhy)->left = myLeft;
				(*WhyGodWhy)->right = myRight;
			}
		}
	}
	

	if (WhyGodWhy)
	{
		updateHeight(*WhyGodWhy); 
	}
	updateHeight(*WhyGodWhyParent); 
	int Balance = checkBalance(*WhyGodWhyParent);
	if (Balance < -1)
	{
		if (checkBalance((*WhyGodWhyParent)->right) > 0)
		{
			rotateRight(&(*WhyGodWhyParent)->right, &(*WhyGodWhyParent)->right->left);
			rotateLeft(WhyGodWhyParent, &(*WhyGodWhyParent)->right);
		}
		else {
			rotateLeft(WhyGodWhyParent, &(*WhyGodWhyParent)->right);
		}

	}
	else if (Balance > 1)
	{
		if (checkBalance((*WhyGodWhyParent)->left) < 0)
		{
			rotateLeft(&(*WhyGodWhyParent)->left, &((*WhyGodWhyParent)->left)->right);
			rotateRight(WhyGodWhyParent, &(*WhyGodWhyParent)->left);
		}
		else {
			rotateRight(WhyGodWhyParent, &(*WhyGodWhyParent)->left);
		}
	}
}

void AVL::findInOrderSuccessor(AVLNode **retPointer, AVLNode **Parent )//Do last successor thing here as well.
{
	if ((*Parent)->left)
	{
		findInOrderSuccessor(retPointer, &(*Parent)->left);
		if ((*Parent)->left == *retPointer)
		{
			if ((*retPointer)->right)
			{
				(*Parent)->left = (*retPointer)->right;
				(*retPointer)->right = 0;
			}
			else {
				(*Parent)->left = 0;
			}
		}
		updateHeight(*retPointer);
		updateHeight(*Parent);
		int Balance = checkBalance(*Parent);
		if (Balance < -1)
		{
			if (checkBalance((*Parent)->right) > 0)
			{
				rotateRight(&(*Parent)->right, &(*Parent)->right->left);
				rotateLeft(Parent, &(*Parent)->right);
			}
			else {
				rotateLeft(Parent, &(*Parent)->right);
			}

		}
		else if (Balance > 1)
		{
			if (checkBalance((*Parent)->left) < 0)
			{
				rotateLeft(&(*Parent)->left, &((*Parent)->left)->right);
				rotateRight(Parent, &(*Parent)->left);
			}
			else {
				rotateRight(Parent, &(*Parent)->left);
			}
		}
	}
	else {
		*retPointer = *Parent;
	}
}








void AVL::updateHeight(AVLNode* ptr) {

	if (!ptr)
		return;

	ptr->height = 1 + std::max(ptr->left ? ptr->left->height : -1, ptr->right ? ptr->right->height : -1);
}

void AVL::serialize(std::stringstream& s, AVLNode** NextValue)
{


	if (!(*NextValue))
	{
		s << "[/]";
	}
	else {
		s << "[" << (*NextValue)->Value << "]";//  << " "<< "|" << (*NextValue)->height << 
		serialize(s, &(*NextValue)->left);
		serialize(s, &(*NextValue)->right);
	}


}

std::string AVL::serialize()
{
	std::stringstream aStream;

	serialize(aStream, &root);

	return aStream.str();
}
