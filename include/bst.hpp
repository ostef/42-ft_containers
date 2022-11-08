#ifndef FT_BST_HPP
#define FT_BST_HPP

#include "utility.hpp"

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

	template<typename Node>
	class bst_iterator
	{
	public:
		typedef Node node_type;
		typedef typename keep_const<node_type>::value_type value_type;

	private:
		node_type *_node;
		node_type *_before_begin;
		node_type *_past_end;
	
	private:
		bst_iterator () : _node (NULL), _before_begin (NULL), _past_end (NULL) {}

	public:
		
		template<typename Other_Node>
		bst_iterator (const bst_iterator<Other_Node> &other) :
			_node (other.node ()), _before_begin (other.before_begin ()), _past_end (other.past_end ()) {}

		template<typename Tree>
		bst_iterator (Tree &tree, node_type *node) :
			_node (node), _before_begin (tree.before_begin ()), _past_end (tree.past_end ()) {}

		template<typename Tree>
		bst_iterator (const Tree &tree, node_type *node) :
			_node (node), _before_begin (tree.before_begin ()), _past_end (tree.past_end ()) {}

		bst_iterator (node_type *node, node_type *before_begin, node_type *past_end) :
			_node (node), _before_begin (before_begin), _past_end (past_end) {}

		template<typename Other_Node>
		bst_iterator &operator= (const bst_iterator<Other_Node> &other)
		{
			_node = other._node;
			_before_begin = other._before_begin;
			_past_end = other._past_end;
			
			return *this;
		}

		template<typename Other_Node>
		bool operator== (const bst_iterator<Other_Node> &other)
		{
			return _node == other.node () && _before_begin == other.before_begin () && _past_end == other.past_end ();
		}

		template<typename Other_Node>
		bool operator!= (const bst_iterator<Other_Node> &other)
		{
			return !(*this == other);
		}

		value_type &operator* () const
		{
			if (_node == _before_begin || _node == _past_end)
				throw std::runtime_error ("invalid iterator");
			
			return _node->value;
		}

		value_type *operator-> () const
		{
			if (_node == _before_begin || _node == _past_end)
				throw std::runtime_error ("invalid iterator");
			
			return &_node->value;
		}

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

		node_type *node () const
		{
			return _node;
		}

		node_type *before_begin () const
		{
			return _before_begin;
		}

		node_type *past_end () const
		{
			return _past_end;
		}

	private:

		bst_iterator next ()
		{
			if (_node == _before_begin)
			{
				node_type *node = _node->right->leftmost ();
				if (!node)
					node = _past_end;

				return bst_iterator (node, _before_begin, _past_end);
			}
			else if (_node == _past_end)
				return bst_iterator (*this);

			node_type *node = _node->successor ();
			if (!node)
				node = _past_end;

			return bst_iterator (node, _before_begin, _past_end);
		}

		bst_iterator prev ()
		{
			if (_node == _past_end)
			{
				node_type *node = _node->left->rightmost ();
				if (!node)
					node = _before_begin;

				return bst_iterator (node, _before_begin, _past_end);
			}
			else if (_node == _before_begin)
				return bst_iterator (*this);

			node_type *node = _node->predecessor ();
			if (!node)
				node = _before_begin;

			return bst_iterator (node, _before_begin, _past_end);
		}
	};
}

#endif
