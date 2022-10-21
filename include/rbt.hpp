/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:20:27 by soumanso          #+#    #+#             */
/*   Updated: 2022/07/21 16:20:27 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#include "utility.hpp"

#define RBT_NODE_BEGIN ((void *)0x01)
#define RBT_NODE_END ((void *)0x02)

namespace ft
{
	template<class T>
	struct rbt_node
	{
		typedef rbt_node<T> this_type;
		typedef T value_type;

		bool is_black;
		this_type *parent;
		this_type *left;
		this_type *right;
		value_type value;

		rbt_node () :
			is_black (false), parent (NULL), left (NULL), right (NULL), value () {}
		rbt_node (const value_type &val) :
			is_black (false), parent (NULL), left (NULL), right (NULL), value (val) {}
		rbt_node (const this_type &other) :
			is_black (other.is_black), parent (other.parent), left (other.left), right (other.right), value (other.value) {}
		~rbt_node () {}

		this_type &operator= (const this_type &other)
		{
			is_black = other.is_black;
			parent = other.parent;
			left = other.left;
			right = other.right;
			value = other.value;
			return *this;
		}

		bool is_left_child () const
		{
			return parent && parent->left == this;
		}

		bool is_right_child () const
		{
			return parent && parent->right == this;
		}
	
		this_type *leftmost ()
		{
			this_type *node = this;
			while (node && node->left)
				node = node->left;

			return node;
		}

		this_type *rightmost ()
		{
			this_type *node = this;
			while (node && node->right)
				node = node->right;

			return node;
		}

		// First rule: The first node in the tree is the leftmost node in the tree.
		// Next rule: The successor of a node is:
		//   * Next-R rule: If it has a right subtree, the leftmost node in the right subtree.
		//   * Next-U rule: Otherwise, traverse up the tree
		//      - If you make a right turn (i.e. this node was a left child), then that parent node is the successor
		//      - If you make a left turn (i.e. this node was a right child), continue going up.
		//      - If you can't go up anymore, then there's no successor
		this_type *successor ()
		{
			if (right)
				return right->leftmost ();

			this_type *node = this;
			while (node && node->parent && node->is_right_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}

		this_type *predecessor ()
		{
			if (left)
				return left->rightmost ();
			
			this_type *node = this;
			while (node && node->parent && node->is_left_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}
	};

	template<
		class T,
		class Compare = std::less<T>,
		class Allocator = std::allocator<rbt_node<T> >
	>
	class rbt
	{
	public:
		typedef rbt<T, Allocator> this_type;
		typedef T                 value_type;
		typedef rbt_node<T>       node_type;
		typedef Compare           value_compare;
		typedef Allocator         allocator_type;

		class iterator
		{
		public:
			typedef rbt<T, Compare, Allocator> container_type;

		public:
			iterator () : m_tree (NULL), m_node ((node_type *)RBT_NODE_END) {}
			iterator (const iterator &other) : m_tree (other.m_tree), m_node (other.m_node) {}
			iterator (container_type *tree, node_type *node) : m_tree (tree), m_node (node) {}

			iterator &operator= (const iterator &other)
			{
				m_tree = other.m_tree;
				m_node = other.m_node;
				return *this;
			}

			bool operator== (const iterator &other)
			{
				return m_tree == other.m_tree && m_node == other.m_node;
			}

			bool operator!= (const iterator &other)
			{
				return !(*this == other);
			}

			value_type &operator* () { return m_node->value; }
			value_type *operator-> () { return *m_node->value; }

			iterator &operator++ ()
			{
				*this = next ();
				return *this;
			}

			iterator operator++ (int)
			{
				iterator tmp = *this;
				*this = next ();
				return tmp;
			}

			iterator &operator-- ()
			{
				*this = prev ();
				return *this;
			}

			iterator operator-- (int)
			{
				iterator tmp = *this;
				*this = prev ();
				return tmp;
			}

			node_type *node ()
			{
				return m_node;
			}

		private:

			iterator next ()
			{
				if (m_node == (node_type *)RBT_NODE_BEGIN)
				{
					node_type *node = m_tree->m_root->leftmost ();
					if (!node)
						node = (node_type *)RBT_NODE_END;

					return iterator (m_tree, node);
				}
				else if (m_node == (node_type *)RBT_NODE_END)
					return iterator (*this);

				node_type *node = m_node->successor ();
				if (!node)
					node = (node_type *)RBT_NODE_END;

				return iterator (m_tree, node);
			}

			iterator prev ()
			{
				if (m_node == (node_type *)RBT_NODE_END)
				{
					node_type *node = m_tree->m_root->rightmost ();
					if (!node)
						node = (node_type *)RBT_NODE_BEGIN;

					return iterator (m_tree, node);
				}
				else if (m_node == (node_type *)RBT_NODE_BEGIN)
					return iterator (*this);

				node_type *node = m_node->predecessor ();
				if (!node)
					return iterator (m_tree, (node_type *)RBT_NODE_BEGIN);

				return iterator (m_tree, node);
			}

		private:
			container_type *m_tree;
			node_type *m_node;
		};

		friend class iterator;

	public:
		explicit rbt (const allocator_type &alloc = allocator_type ()) :
			m_root (NULL), m_less_than (), m_alloc (alloc) {}

		~rbt ()
		{
			// @Todo
		}

		void insert (const value_type &val)
		{
			node_type *node = m_alloc.allocate (sizeof (node_type));
			m_alloc.construct (node, val);
			insert (node);
		}

		iterator begin ()
		{
			// @Todo: Make this O(1)
			node_type *node = m_root;
			while (node && node->left)
				node = node->left;
	
			return iterator (this, node);
		}

		iterator end ()
		{
			return iterator (this, (node_type *)RBT_NODE_END);
		}

	private:

		void insert (node_type *node)
		{
			bst_insert (node);
			node->is_black = false;
			insert_fixup (node);
		}

		void left_rotate (node_type *x)
		{
			node_type *y = x->right;

			// Turn y's left sub-tree into x's right sub-tree
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			
			// Update the parents: y's new parent was x's parent
			y->parent = x->parent;
			
			// Update the root
			if (m_root == x)
				m_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			
			// Update y's left sub-tree and x's parent
			y->left = x;
			x->parent = y;
		}

		void right_rotate (node_type *x)
		{
			node_type *y = x->left;
			
			// Turn x's right sub-tree into y's left sub-tree
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			
			// Update the parents: y's new parent was x's parent
			y->parent = x->parent;
			
			// Update the root
			if (m_root == x)
				m_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			
			// Update y's right sub-tree and x's parent
			y->right = x;
			x->parent = y;
		}

		void bst_insert (node_type *node)
		{
			if (!m_root)
			{
				m_root = node;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
			
				return;
			}

			node_type *curr = m_root;
			node_type *parent = NULL;
			
			while (curr)
			{
				parent = curr;
				if (m_less_than (node->value, curr->value))
					curr = curr->left;
				else
					curr = curr->right;
			}

			
			if (m_less_than (node->value, parent->value))
			{
				ASSERT (parent->left == NULL);
				parent->left = node;
			}
			else
			{
				ASSERT (parent->right == NULL);
				parent->right = node;
			}

			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
		}

		void insert_fixup (node_type *node)
		{
			while (node != m_root && !node->is_black && !node->parent->is_black)
			{
				node_type *parent = node->parent;
				node_type *grand_parent = parent->parent;
				// Case A: the parent is the left child of the grand parent
				if (parent == grand_parent->left)
				{
					node_type *uncle = grand_parent->right;
					
					// Case 1: the uncle is red, recolor
					if (uncle && !uncle->is_black)
					{
						grand_parent->is_black = false;
						parent->is_black = true;
						uncle->is_black = true;
						node = grand_parent;
					}
					else
					{
						// Case 2: node is the right child of its parent, left-rotate
						if (node == parent->right)
						{
							left_rotate (parent);
							node = parent;
							parent = node->parent;
						}

						// Case 3: node is the left child of its parent, right-rotate
						right_rotate (grand_parent);
						bool tmp = parent->is_black;
						parent->is_black = grand_parent->is_black;
						grand_parent->is_black = tmp;
						node = parent;
					}
				}
				else	// Case B: parent is right child of grand parent
				{
					node_type *uncle = grand_parent->left;

					// Case 1" uncle is red, recolor
					if (uncle && !uncle->is_black)
					{
						grand_parent->is_black = false;
						parent->is_black = true;
						uncle->is_black = true;
						node = grand_parent;
					}
					else
					{
						// Case 2: node is the left child of its parent, right-rotate
						if (node == parent->left)
						{
							right_rotate (parent);
							node = parent;
							parent = node->parent;
						}

						// Case 3: node is right child of its parent, left-rotate
						left_rotate (grand_parent);
						bool tmp = parent->is_black;
						parent->is_black = grand_parent->is_black;
						grand_parent->is_black = tmp;
						node = parent;
					}
				}
			}

			m_root->is_black = true;
		}

		void bst_remove (node_type *node)
		{
			// Simple case: leaf node
			if (!node->left && !node->right)
			{
				if (!node->parent)
					m_root = NULL;
				else if (node->parent->left == node)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
			}
			else if (!node->right || !node->left)	// Simple case: the node has only one child
			{
				node_type *child = node->right ? node->right : node->left;
			
				if (!node->parent)
					m_root = child;
				else if (node->parent->left == node)
					node->parent->left = child;
				else
					node->parent->right = child;
			
				child->parent = node->parent;
			}
			else	// The node has two children
			{
				node_type *successor = node->right;
			
				while (successor->left)
					successor = successor->left;

				// @Note: this isn't recursive, since the successor only has at most one child
				if (successor != node->right)
					bst_remove (successor);

				if (!node->parent)
					m_root = successor;
				else if (node->parent->left == node)
					node->parent->left = successor;
				else
					node->parent->right = successor;

				successor->parent = node->parent;
	
				successor->left = node->left;
				if (successor->left)
					successor->left->parent = successor;
				
				successor->right = node->right;
				if (successor->right)
					successor->right->parent = successor;
			}
		}

		node_type *search (const value_type &value)
		{
			node_type *node = m_root;
			while (node)
			{
				if (node->value == value)
					break;
				else if (m_less_than (value, node->value))
					node = node->left;
				else
					node = node->right;
			}

			return node;
		}

	private:
		node_type *m_root;
		value_compare m_less_than;
		allocator_type m_alloc;
	};
}

#endif
