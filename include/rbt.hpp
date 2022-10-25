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
	
		const this_type *leftmost () const
		{
			const this_type *node = this;
			while (node && node->left)
				node = node->left;

			return node;
		}

		this_type *leftmost ()
		{
			return const_cast<this_type *> (const_cast<const this_type *> (this)->leftmost ());
		}

		const this_type *rightmost () const
		{
			const this_type *node = this;
			while (node && node->right)
				node = node->right;

			return node;
		}

		this_type *rightmost ()
		{
			return const_cast<this_type *> (const_cast<const this_type *> (this)->rightmost ());
		}

		// First rule: The first node in the tree is the leftmost node in the tree.
		// Next rule: The successor of a node is:
		//   * Next-R rule: If it has a right subtree, the leftmost node in the right subtree.
		//   * Next-U rule: Otherwise, traverse up the tree
		//      - If you make a right turn (i.e. this node was a left child), then that parent node is the successor
		//      - If you make a left turn (i.e. this node was a right child), continue going up.
		//      - If you can't go up anymore, then there's no successor
		const this_type *successor () const
		{
			if (right)
				return right->leftmost ();

			const this_type *node = this;
			while (node && node->parent && node->is_right_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}

		this_type *successor ()
		{
			return const_cast<this_type *> (const_cast<const this_type *> (this)->successor ());
		}

		const this_type *predecessor () const
		{
			if (left)
				return left->rightmost ();
			
			const this_type *node = this;
			while (node && node->parent && node->is_left_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}

		this_type *predecessor ()
		{
			return const_cast<this_type *> (const_cast<const this_type *> (this)->predecessor ());
		}
	};

	template<typename T>
	struct traits
	{
		typedef typename T::value_type value_type;
	};

	template<typename T>
	struct traits<const T>
	{
		typedef const typename T::value_type value_type;
	};

	template<typename Container, typename Node>
	class bst_iterator
	{
	public:
		typedef Container container_type;
		typedef Node node_type;
		typedef typename traits<node_type>::value_type value_type;

	private:
		container_type *_tree;
		node_type *_node;

	public:
		bst_iterator () : _tree (NULL), _node ((node_type *)RBT_NODE_END) {}
		bst_iterator (const bst_iterator &other) : _tree (other._tree), _node (other._node) {}
		bst_iterator (container_type *tree, node_type *node) : _tree (tree), _node (node) {}

		bst_iterator &operator= (const bst_iterator &other)
		{
			_tree = other._tree;
			_node = other._node;
			
			return *this;
		}

		bool operator== (const bst_iterator &other)
		{
			return _tree == other._tree && _node == other._node;
		}

		bool operator!= (const bst_iterator &other)
		{
			return !(*this == other);
		}

		value_type &operator* () { return _node->value; }
		value_type *operator-> () { return *_node->value; }

		bst_iterator &operator++ ()
		{
			*this = next ();
			return *this;
		}

		bst_iterator operator++ (int)
		{
			bst_iterator tmp = *this;
			*this = next ();
			return tmp;
		}

		bst_iterator &operator-- ()
		{
			*this = prev ();
			return *this;
		}

		bst_iterator operator-- (int)
		{
			bst_iterator tmp = *this;
			*this = prev ();
			return tmp;
		}

		node_type *node ()
		{
			return _node;
		}

	private:

		bst_iterator next ()
		{
			if (_node == (node_type *)RBT_NODE_BEGIN)
			{
				node_type *node = _tree->root ()->leftmost ();
				if (!node)
					node = (node_type *)RBT_NODE_END;

				return bst_iterator (_tree, node);
			}
			else if (_node == (node_type *)RBT_NODE_END)
				return bst_iterator (*this);

			node_type *node = _node->successor ();
			if (!node)
				node = (node_type *)RBT_NODE_END;

			return bst_iterator (_tree, node);
		}

		bst_iterator prev ()
		{
			if (_node == (node_type *)RBT_NODE_END)
			{
				node_type *node = _tree->root ()->rightmost ();
				if (!node)
					node = (node_type *)RBT_NODE_BEGIN;

				return bst_iterator (_tree, node);
			}
			else if (_node == (node_type *)RBT_NODE_BEGIN)
				return bst_iterator (*this);

			node_type *node = _node->predecessor ();
			if (!node)
				return bst_iterator (_tree, (node_type *)RBT_NODE_BEGIN);

			return bst_iterator (_tree, node);
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
		typedef rbt<T, Compare, Allocator> this_type;
		typedef T value_type;
		typedef size_t size_type;
		typedef rbt_node<T> node_type;
		typedef Compare value_compare;
		typedef Allocator allocator_type;

		typedef bst_iterator<this_type, node_type> iterator;
		typedef bst_iterator<const this_type, const node_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		node_type *_root;
		size_type _size;
		value_compare _less_than;
		allocator_type _alloc;

	public:
		explicit rbt (const allocator_type &alloc = allocator_type ()) :
			_root (NULL), _less_than (), _alloc (alloc) {}

		~rbt ()
		{
			// @Todo
		}

		node_type *root ()
		{
			return _root;
		}

		const node_type *root () const
		{
			return _root;
		}

		void insert (const value_type &val)
		{
			node_type *node = _alloc.allocate (sizeof (node_type));
			_alloc.construct (node, val);
			insert (node);
			_size += 1;
		}

		iterator erase(iterator it)
		{
			// @Todo
			return it;
		}

		iterator search (const value_type &value)
		{
			node_type *node = _root;
			while (node)
			{
				if (node->value == value)
					break;
				else if (_less_than (value, node->value))
					node = node->left;
				else
					node = node->right;
			}

			return iterator (this, node);
		}

		allocator_type get_allocator () const
		{
			return _alloc;
		}

		bool empty () const
		{
			return !_root;
		}

		size_type size () const
		{
			return _size;
		}

		size_type max_size () const
		{
			return std::numeric_limits<size_type>::max ();
		}

		iterator begin ()
		{
			iterator it = iterator (this, (node_type *)RBT_NODE_BEGIN);

			return ++it;
		}

		const_iterator begin () const
		{
			const_iterator it = const_iterator (this, (node_type *)RBT_NODE_BEGIN);

			return ++it;
		}

		iterator end ()
		{
			return iterator (this, (node_type *)RBT_NODE_END);
		}

		const_iterator end () const
		{
			return const_iterator (this, (node_type *)RBT_NODE_END);
		}

		reverse_iterator rbegin ()
		{
			return reverse_iterator (end ());
		}

		const_reverse_iterator rbegin () const
		{
			return const_reverse_iterator (end ());
		}

		reverse_iterator rend ()
		{
			return reverse_iterator (begin ());
		}

		const_reverse_iterator rend () const
		{
			return const_reverse_iterator (begin ());
		}

	private:

		void insert (node_type *node)
		{
			bst_insert (node);
			node->is_black = false;
			insert_fixup (node);
		}

		void erase(node_type *node)
		{
			// @Todo
			bst_erase (node);
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
			if (_root == x)
				_root = y;
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
			if (_root == x)
				_root = y;
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
			if (!_root)
			{
				_root = node;
				node->parent = NULL;
				node->left = NULL;
				node->right = NULL;
			
				return;
			}

			node_type *curr = _root;
			node_type *parent = NULL;
			
			while (curr)
			{
				parent = curr;
				if (_less_than (node->value, curr->value))
					curr = curr->left;
				else
					curr = curr->right;
			}

			
			if (_less_than (node->value, parent->value))
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
			while (node != _root && !node->is_black && !node->parent->is_black)
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

					// Case 1: uncle is red, recolor
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

			_root->is_black = true;
		}

		void bst_erase (node_type *node)
		{
			// Simple case: leaf node
			if (!node->left && !node->right)
			{
				if (!node->parent)
					_root = NULL;
				else if (node->parent->left == node)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
			}
			else if (!node->right || !node->left)	// Simple case: the node has only one child
			{
				node_type *child = node->right ? node->right : node->left;
			
				if (!node->parent)
					_root = child;
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

				// This recursion is only one level deep, since
				// the successor has at most one child
				if (successor != node->right)
					bst_erase (successor);

				if (!node->parent)
					_root = successor;
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
	};
}

#endif
