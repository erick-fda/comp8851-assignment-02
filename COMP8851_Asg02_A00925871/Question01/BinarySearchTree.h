/*========================================================================================
	BinarySearchTree
	
	A binary search tree that uses lazy deletion.

	Rather than deleting elements as soon as they are removed, the tree will only 
	delete elements once more than half of its total elements have been marked for deletion.
    
    Copyright 2018 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
		https://github.com/erick-fda
        https://bitbucket.org/erick-fda
	
========================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "stdafx.h"
#include "dsexceptions.h"
#include <algorithm>
using namespace std;

/*========================================================================================
	BinarySearchTree	
========================================================================================*/
template <typename Comparable>
class BinarySearchTree
{

	/*----------------------------------------------------------------------------------------
		Internal Types
    ----------------------------------------------------------------------------------------*/
	private:
		struct BinaryNode
		{
			Comparable element;
			BinaryNode *left;
			BinaryNode *right;
			bool _isDeleted = false;

			/* Pseudo-copy constructor */
			BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, bool d)
				: element{ theElement }, left{ lt }, right{ rt }, _isDeleted { d } { }

			/* Pseudo-move constructor */
			BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt, bool d)
				: element{ std::move(theElement) }, left{ lt }, right{ rt }, _isDeleted{ d } { }
		};

    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		BinaryNode* root;
		int _nodeCount = 0;
		int _deletedNodeCount = 0;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BinarySearchTree() :
			root{ nullptr }, 
			_nodeCount{ 0 }, 
			_deletedNodeCount{ 0 }
		{}

        /** Copy constructor. */
		BinarySearchTree(const BinarySearchTree& rhs) :
			root{ nullptr }, 
			_nodeCount{ rhs._nodeCount }, 
			_deletedNodeCount{ rhs._deletedNodeCount }
		{
			root = clone(rhs.root);
		}

        /** Move constructor. */
		BinarySearchTree(BinarySearchTree&& rhs) :
			root{ rhs.root }, 
			_nodeCount{ rhs._nodeCount }, 
			_deletedNodeCount{ rhs._deletedNodeCount }
		{
			rhs.root = nullptr;
			rhs._nodeCount = 0;
			rhs._deletedNodeCount = 0;
		}

        /** Destructor. */
		~BinarySearchTree()
		{
			makeEmpty();
		}

        /** Copy assignment. */
		BinarySearchTree & operator=(const BinarySearchTree & rhs)
		{
			BinarySearchTree copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

        /** Move assignment. */
		BinarySearchTree & operator=(BinarySearchTree && rhs)
		{
			std::swap(root, rhs.root);
			std::swap(_nodeCount, rhs._nodeCount);
			std::swap(_deletedNodeCount, rhs._deletedNodeCount);
			return *this;
		}

	/*----------------------------------------------------------------------------------------
		Instance Getter Methods
    ----------------------------------------------------------------------------------------*/
    public:
        
    
	/*----------------------------------------------------------------------------------------
		Instance Setter Methods
	----------------------------------------------------------------------------------------*/
    public:


	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    private:
		/**
			Mark the given node as deleted and adjust relevant member values.
		*/
		void LazyDeleteNode(BinaryNode*& node)
		{
			if (nullptr != node && 
				!(node->_isDeleted))
			{
				node->_isDeleted = true;
				++_deletedNodeCount;
			}
		}

		/**
			Actually (not lazily) deletes all the nodes marked for deletion in the given subtree.
		*/
		void ClearDeletedNodesInSubtree(BinaryNode*& t)
		{
			/* If this node is null, do nothing. */
			if (nullptr == t)
			{
				return;
			}

			/* If this node has a left subtree, clear it of deleted nodes. */
			ClearDeletedNodesInSubtree(t->left);

			/* If this node has a right subtree, clear it of deleted nodes. */
			ClearDeletedNodesInSubtree(t->right);

			/*
				If this node is marked for deletion, delete it.
				
				Note that by this point in the method, this node is guaranteed 
				to not have any children marked for deletion.
			*/
			if (t->_isDeleted)
			{
				/* If this node has two children... */
				if (t->left != nullptr && t->right != nullptr) // Two children
				{
					BinaryNode* minRightNode = findMin(t->right);
					t->element = minRightNode->element;
					t->_isDeleted = false;
					minRightNode->_isDeleted = true;

					ClearDeletedNodesInSubtree(t->right);
				}
				/* If this node has one or no children... */
				else
				{
					BinaryNode* oldNode = t;
					t = (t->left != nullptr) ? t->left : t->right;
					delete oldNode;
					--_nodeCount;
					--_deletedNodeCount;
				}
			}
		}

		/**
			If more than half the nodes in the tree have been marked for deletion, 
			deletes all such nodes.
		*/
		void TryLazyDelete()
		{
			if (_deletedNodeCount > (_nodeCount / 2))
			{
				ClearDeletedNodesInSubtree(root);
			}
		}

	public:
		/**
			Return whether the tree contains the given value.
		*/
		bool contains(const Comparable & x) const
		{
			return contains(x, root);
		}

		/**
			Return whether the tree is logically empty.
		*/
		bool isEmpty() const
		{
			return (root == nullptr || 
					_deletedNodeCount >= _nodeCount );
		}

		/**
			Prints the tree contents in sorted order.
		*/
		void printTree(ostream & out = cout) const
		{
			if (isEmpty())
				out << "Empty tree" << endl;
			else
				printTree(root, out);
		}

		/**
			Make the tree logically empty.
		*/
		void makeEmpty()
		{
			makeEmpty(root);
			TryLazyDelete();
		}

		/**
			Insert the given lvalue into the tree.
			
			Duplicates are ignored.
			
			If a value already exists in the tree but is currently marked for deletion, 
			the deletion flag will be removed.
		*/
		void insert(const Comparable & x)
		{
			insert(x, root);
		}
		
		/**
			Insert the given rvalue into the tree.
			
			Duplicates are ignored.
			
			If a value already exists in the tree but is currently marked for deletion, 
			the deletion flag will be removed.
		*/
		void insert(Comparable && x)
		{
			insert(std::move(x), root);
		}

		/**
			Removes the given value from the tree.
			
			Does nothing if the tree does not contain the given value.
			
			This method may trigger a lazy deletion if more than half of the tree's 
			nodes have been marked for deletion after removing the given value.
		*/
		void remove(const Comparable & x)
		{
			remove(x, root);
			TryLazyDelete();
		}

    private:
		/**
			Inserts the given lvalue into the given subtree.
		*/
		void insert(const Comparable & x, BinaryNode * & t)
		{
			/* If this node is null, insert the new element here. */
			if (t == nullptr)
			{
				t = new BinaryNode{ x, nullptr, nullptr, false };
				++_nodeCount;
			}
			/* If the value is lesser, insert into the left subtree. */
			else if (x < t->element)
			{
				insert(x, t->left);
			}
			/* If the value is greater, insert into the right subtree. */
			else if (t->element < x)
			{
				insert(x, t->right);
			}
			/* If the value is stored in this node and 
				the node has been marked for deletion, 
				unmark it as such. */
			else if (t->_isDeleted)
			{
				t->_isDeleted = false;
				--_deletedNodeCount;
			}
			else
			{
				;  // Duplicate; do nothing
			}
		}

		/**
			Inserts the given lvalue into the given subtree.
		*/
		void insert(Comparable && x, BinaryNode * & t)
		{
			/* If this node is null, insert the new element here. */
			if (t == nullptr)
			{
				t = new BinaryNode{ std::move(x), nullptr, nullptr, false };
				++_nodeCount;
			}
			/* If the value is lesser, insert into the left subtree. */
			else if (x < t->element)
			{
				insert(std::move(x), t->left);
			}
			/* If the value is greater, insert into the right subtree. */
			else if (t->element < x)
			{
				insert(std::move(x), t->right);
			}
			/* If the value is stored in this node and 
				the node has been marked for deletion, 
				unmark it as such. */
			else if (t->_isDeleted)
			{
				t->_isDeleted = false;
				--_deletedNodeCount;
			}
			else
			{
				;  // Duplicate; do nothing
			}
		}

		/**
			Removes the given value from the given subtree.
		*/
		void remove(const Comparable & x, BinaryNode * & t)
		{
			/*
				If this node is null, then do nothing.
			*/
			if (t == nullptr)
			{
				return;   // Item not found; do nothing
			}
			/*
				If the given value is lesser, remove from the left subtree.
			*/
			if (x < t->element)
			{
				remove(x, t->left);
			}
			/*
				If the given value is greater, remove from the right subtree.
			*/
			else if (t->element < x)
			{
				remove(x, t->right);
			}
			/* If the node is not null, and the given value is neither lesser nor greater, 
				then it is contained in this node. Mark this node for deletion. */
			else
			{
				LazyDeleteNode(t);
			}
		}

		/**
			Check if a given item exists in a given subtree.
		*/
		bool contains(const Comparable & x, BinaryNode *t) const
		{
			/* If the subtree is null, then it definitely doesn't contain the item. */
			if (t == nullptr)
			{
				return false;
			}
			/* If the item is lesser, check the left subtree. */
			else if (x < t->element)
			{
				return contains(x, t->left);
			}
			/* If the item is greater, check the right subtree. */
			else if (t->element < x)
			{
				return contains(x, t->right);
			}
			/*
				If the item is neither null, lesser, nor greater, then this node is it.
				
				Return FALSE if this node is marked for deletion and TRUE otherwise.
			*/
			else
			{
				return !(t->_isDeleted);
			}
		}

		/**
			Make the given subtree empty.
		*/
		void makeEmpty(BinaryNode*& t)
		{
			if (t != nullptr)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				LazyDeleteNode(t);
			}
		}

		/**
			Print the contents of the given subtree in sorted order.
		*/
		void printTree(BinaryNode *t, ostream & out) const
		{
			if (t != nullptr)
			{
				printTree(t->left, out);

				/* Print out the current node only if it is not marked for deletion. */
				if (!(t->_isDeleted))
				{
					out << t->element << endl;
				}

				printTree(t->right, out);
			}
		}

		/**
			Clone a subtree.
		*/
		BinaryNode* clone(BinaryNode *t) const
		{
			if (t == nullptr)
				return nullptr;
			else
				return new BinaryNode{ t->element, clone(t->left), clone(t->right), t->_isDeleted };
		}
};
