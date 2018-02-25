/*========================================================================================
	Question 02
	
	A procedure to traverse a subtree of ChildSibNodes.
    
    Copyright 2018 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://github.com/erick-fda
        https://bitbucket.org/erick-fda
	
========================================================================================*/

#include <iostream>

/**
 *  Bare-bones ChildSibTree class, containing the given ChildSibNode definition and 
 *  the procedure for traversing the tree.
*/
template<typename Comparable>
class ChildSibTree
{
	private:
		template<typename Comparable>
		struct ChildSibNode
		{
			Comparable element;
			ChildSibNode<Comparable>	*	child;
			ChildSibNode<Comparable>	*	sib;
		};
		
		ChildSibNode<Comparable> * root;

	public:
		void Traverse()
		{
			TraverseChildSibTree(root);
		}

	private:
		/*
			Procedure to traverse a ChildSibNode subtree.

			I have assumed for the purposes of this question that ChildSibNode.child points to a 
			node's *first* child, if it exists, and that ChildSibNode.sib points to the *next* 
			sibling.

			Thus, to traverse a node's children, one would follow node.child.sib.sib... and so 
			on until sib is a nullptr, which means the end of node's children has been reached.
		*/
		void TraverseChildSibTree(ChildSibNode<Comparable>* node)
		{
			if (nullptr != node)
			{
				/* Traverse children if this node has any. */
				TraverseChildSibTree(node->child);

				/* Traverse this node's next sibling if there is one. */
				TraverseChildSibTree(node->sib);

				/* Do whatever you want to actually do at each node. 
					(e.g., print out contents, update some value, etc.) */
				//
				//
				//	std::cout << node->element;
				//
				//
			}
		}
};
