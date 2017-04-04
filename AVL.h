
#include <sstream>
#include <string>
#include "AVLNode.h"

class AVL
{
private:
	void clear(AVLNode **WhyGodWhy);
	AVLNode *root;
	void insert(AVLNode **WhyGodWhy, int Value);
	void remove(AVLNode ***, AVLNode **WhyGodWhyParent, AVLNode **WhyGodWhy, int Value);
	void serialize(std::stringstream& s, AVLNode** NextValue);
	void updateHeight(AVLNode *);
	int checkBalance(AVLNode *);
	void rotateLeft(AVLNode **, AVLNode **);
	void rotateRight(AVLNode **, AVLNode **);
	void findInOrderSuccessor(AVLNode **, AVLNode **Parent);
	//void doubleRotateLeft(AVLNode **, AVLNode *);
	//	void doubleRotateRight(AVLNode **,AVLNode *);

public:
	AVL();
	~AVL();
	void insert(int aNewInt);
	void clear();
	void remove(int anIntToRemove);
	std::string serialize();
};