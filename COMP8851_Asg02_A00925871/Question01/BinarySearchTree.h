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
			BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
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
    public:
		/**
			Make the tree logically empty.
		*/
		void makeEmpty()
		{
			makeEmpty(root);
			TryLazyDelete();
		}

		/**
			Return whether the tree contains the given value.
		*/
		bool contains(const Comparable & x) const
		{
			return contains(x, root);
		}

    private:
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
				DeleteNode(t);
			}
		}

		/**
			Mark the given node as deleted and adjust relevant member values.
		*/
		void DeleteNode(BinaryNode*& node)
		{
			if (nullptr != node)
			{
				node->_isDeleted = true;
				++_deletedNodeCount;
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
				// TODO delete
			}
		}
};
