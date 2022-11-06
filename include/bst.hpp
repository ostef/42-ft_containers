#ifndef FT_BST_HPP
#define FT_BST_HPP

#include "utility.hpp"

#define BST_NODE_BEGIN ((void *)0x01)
#define BST_NODE_END ((void *)0x02)

namespace ft
{
	template<typename T>
	struct keep_const
	{
		typedef typename T::value_type value_type;
	};

	template<typename T>
	struct keep_const<const T>
	{
		typedef const typename T::value_type value_type;
	};

	template<typename Container, typename Node>
	class bst_iterator
	{
	public:
		typedef Container container_type;
		typedef Node node_type;
		typedef typename keep_const<node_type>::value_type value_type;

	private:
		container_type *_tree;
		node_type *_node;

	public:
		bst_iterator () : _tree (NULL), _node ((node_type *)BST_NODE_END) {}
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
		value_type *operator-> () { return &_node->value; }

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

		container_type *tree ()
		{
			return _tree;
		}

		node_type *node ()
		{
			return _node;
		}

	private:

		bst_iterator next ()
		{
			if (_node == (node_type *)BST_NODE_BEGIN)
			{
				node_type *node = _tree->root ()->leftmost ();
				if (!node)
					node = (node_type *)BST_NODE_END;

				return bst_iterator (_tree, node);
			}
			else if (_node == (node_type *)BST_NODE_END)
				return bst_iterator (*this);

			node_type *node = _node->successor ();
			if (!node)
				node = (node_type *)BST_NODE_END;

			return bst_iterator (_tree, node);
		}

		bst_iterator prev ()
		{
			if (_node == (node_type *)BST_NODE_END)
			{
				node_type *node = _tree->root ()->rightmost ();
				if (!node)
					node = (node_type *)BST_NODE_BEGIN;

				return bst_iterator (_tree, node);
			}
			else if (_node == (node_type *)BST_NODE_BEGIN)
				return bst_iterator (*this);

			node_type *node = _node->predecessor ();
			if (!node)
				return bst_iterator (_tree, (node_type *)BST_NODE_BEGIN);

			return bst_iterator (_tree, node);
		}
	};
}

#endif
