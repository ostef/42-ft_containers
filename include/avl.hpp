#ifndef FT_AVL_HPP
#define FT_AVL_HPP

#include "bst.hpp"

namespace ft
{
	template<typename T>
	struct avl_node
	{
		typedef T value_type;

		avl_node *parent;
		avl_node *left;
		avl_node *right;
		char balance_factor;
		value_type value;

		avl_node () :
			parent (NULL), left (NULL), right (NULL), balance_factor (0), value () {}
		avl_node (const value_type &val) :
			parent (NULL), left (NULL), right (NULL), balance_factor (0), value (val) {}
		avl_node (const avl_node &other) :
			parent (other.parent), left (other.left), right (other.right), balance_factor (other.balance_factor), value (other.value) {}
		~avl_node () {}

		avl_node &operator= (const avl_node &other)
		{
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
	
		const avl_node *leftmost () const
		{
			const avl_node *node = this;
			while (node && node->left)
				node = node->left;

			return node;
		}

		avl_node *leftmost ()
		{
			return const_cast<avl_node *> (const_cast<const avl_node *> (this)->leftmost ());
		}

		const avl_node *rightmost () const
		{
			const avl_node *node = this;
			while (node && node->right)
				node = node->right;

			return node;
		}

		avl_node *rightmost ()
		{
			return const_cast<avl_node *> (const_cast<const avl_node *> (this)->rightmost ());
		}

		// First rule: The first node in the tree is the leftmost node in the tree.
		// Next rule: The successor of a node is:
		//   * Next-R rule: If it has a right subtree, the leftmost node in the right subtree.
		//   * Next-U rule: Otherwise, traverse up the tree
		//      - If you make a right turn (i.e. this node was a left child), then that parent node is the successor
		//      - If you make a left turn (i.e. this node was a right child), continue going up.
		//      - If you can't go up anymore, then there's no successor
		const avl_node *successor () const
		{
			if (right)
				return right->leftmost ();

			const avl_node *node = this;
			while (node && node->parent && node->is_right_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}

		avl_node *successor ()
		{
			return const_cast<avl_node *> (const_cast<const avl_node *> (this)->successor ());
		}

		const avl_node *predecessor () const
		{
			if (left)
				return left->rightmost ();
			
			const avl_node *node = this;
			while (node && node->parent && node->is_left_child ())
				node = node->parent;

			if (!node)
				return NULL;
			
			return node->parent;
		}

		avl_node *predecessor ()
		{
			return const_cast<avl_node *> (const_cast<const avl_node *> (this)->predecessor ());
		}
	};

	template<
		typename T,
		typename Compare = std::less<T>,
		typename Allocator = std::allocator<avl_node<T> >
	>
	class avl_tree
	{
	public:
		typedef avl_tree<T, Compare, Allocator> this_type;
		typedef T value_type;
		typedef size_t size_type;
		typedef avl_node<T> node_type;
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
		avl_tree () : _root (NULL), _less_than (Compare ()), _alloc (allocator_type ()) {}

		explicit avl_tree (const Compare &comp, const allocator_type &alloc = allocator_type ()) :
			_root (NULL), _less_than (comp), _alloc (alloc) {}

		template<typename InputIt>
		avl_tree (InputIt first, InputIt last, const Compare &comp = Compare (), const allocator_type &alloc = allocator_type ()) :
			_root (NULL), _less_than (comp), _alloc (alloc)
		{
			for (InputIt it = first; it != last; it++)
				insert (*it);
		}

		avl_tree (const avl_tree &other) :
			_root (NULL), _less_than (other._less_than), _alloc (other._alloc)
		{
			for (const_iterator it = other.begin (); it != other.end (); it++)
				insert (*it);
		}

		~avl_tree ()
		{
			clear ();
		}

		avl_tree &operator= (const avl_tree &other)
		{
			clear ();
			for (const_iterator it = other.begin (); it != other.end (); it++)
				insert (*it);
		}

		node_type *root ()
		{
			return _root;
		}

		const node_type *root () const
		{
			return _root;
		}

		pair<node_type *, bool> insert (const value_type &value)
		{
			node_type *curr = _root;
			node_type *parent =  NULL;
			bool less;

			while (curr)
			{
				parent = curr;

				if (_less_than (value, curr->value))
				{
					curr = curr->left;
					less = true;
				}
				else if (_less_than (curr->value, value))
				{
					curr = curr->right;
					less = false;
				}
				else
				{
					return make_pair (curr, false);
				}
			}

			node_type *node = _alloc.allocate (sizeof (node_type));
			_alloc.construct (node);
			node->parent = parent;

			if (!parent)
				_root = node;
			else if (less)
				parent->left = node;
			else
				parent->right = node;
			
			_size += 1;

			while (parent)
			{
				if (node->is_left_child ())
				{
					if (parent->balance_factor == 1)
					{
						parent->balance_factor = 0;

						break;
					}
					else if (parent->balance_factor == 0)
					{
						parent->balance_factor = -1;
					}
					else if (parent->balance_factor == -1)
					{
						fix_insert_left_imbalance (parent);

						break;
					}
				}
				else
				{
					if (parent->balance_factor == -1)
					{
						parent->balance_factor = 0;

						break;
					}
					else if (parent->balance_factor == 0)
					{
						parent->balance_factor = 1;
					}
					else if (parent->balance_factor == 1)
					{
						fix_insert_right_imbalance (parent);

						break;
					}

				}
			
				node = parent;
				parent = node->parent;
			}

			return make_pair (node, true);
		}

		iterator erase (iterator it)
		{
			ASSERT (it.tree () == this);

			node_type *next = it.node ()->successor ();
			erase (it.node ());

			return iterator (this, next);
		}

		iterator erase (iterator first, iterator last)
		{
			ASSERT (first.tree () == this);
			ASSERT (last.tree () == this);

			iterator it = first;
			iterator result = first;
			while (it != last)
			{
				iterator next = it;
				++next;
				result = erase (it);
				it = next;
			}

			return result;
		}

		void clear ()
		{
			node_type *node = _root->leftmost ();
			while (node)
			{
				node_type *next = node->successor ();
				erase (node);
				node = next;
			}
		}

		void swap (const avl_tree &other)
		{
			node_type *tmp_root = _root;
			size_type tmp_size = _size;
			value_compare tmp_less_than = _less_than;
			
			_root = other._root;
			_size = other._size;
			_less_than = other._less_than;

			other._root = tmp_root;
			other._size = tmp_size;
			other._less_than = tmp_less_than;

			std::swap (_alloc, other._alloc);
		}

		template<typename Comp, typename Key>
		iterator find (const Key &key, Comp less_than)
		{
			node_type *node = _root;
			while (node)
			{
				if (less_than (key, node->value))
					node = node->left;
				else if (less_than (node->value, key))
					node = node->right;
				else
					break;
			}
			if (!node)
				return iterator (this, (node_type *)BST_NODE_END);

			return iterator (this, node);
		}

		template<typename Comp, typename Key>
		const_iterator find (const Key &key, Comp less_than) const
		{
			const node_type *node = _root;
			while (node)
			{
				if (less_than (key, node->value))
					node = node->left;
				else if (less_than (node->value, key))
					node = node->right;
				else
					break;
			}
			if (!node)
				return const_iterator (this, (const node_type *)BST_NODE_END);

			return const_iterator (this, node);
		}

		iterator find (const value_type &value)
		{
			return find (value, _less_than);
		}

		const_iterator find (const value_type &value) const
		{
			return find (value, _less_than);
		}

		value_compare value_comp () const { return _less_than; }
		allocator_type get_allocator () const { return _alloc; }
		bool empty () const { return !_root; }
		size_type size () const { return _size; }
		size_type max_size () const { return std::numeric_limits<size_type>::max (); }

		iterator begin ()
		{
			iterator it = iterator (this, (node_type *)BST_NODE_BEGIN);

			return ++it;
		}

		const_iterator begin () const
		{
			const_iterator it = const_iterator (this, (node_type *)BST_NODE_BEGIN);

			return ++it;
		}

		iterator end ()
		{
			return iterator (this, (node_type *)BST_NODE_END);
		}

		const_iterator end () const
		{
			return const_iterator (this, (node_type *)BST_NODE_END);
		}

		reverse_iterator rbegin () { return reverse_iterator (end ()); }
		const_reverse_iterator rbegin () const { return const_reverse_iterator (end ()); }

		reverse_iterator rend () { return reverse_iterator (begin ()); }
		const_reverse_iterator rend () const { return const_reverse_iterator (begin ()); }

	private:

		node_type *rotate_left (node_type *parent)
		{
			node_type *node = parent->right;

			parent->right = node->left;
			if (parent->right)
				parent->right->parent = parent;
			
			node->parent = parent->parent;
			if (!parent->parent)
				_root = node;
			else if (parent->is_left_child ())
				parent->parent->left = node;
			else
				parent->parent->right = node;
			
			node->left = parent;
			node->left->parent = node;

			return node;
		}

		node_type *rotate_right (node_type *parent)
		{
			node_type *node = parent->left;

			parent->left = node->right;
			if (parent->left)
				parent->left->parent = parent;
			
			node->parent = parent->parent;
			if (!parent->parent)
				_root = node;
			else if (parent->is_left_child ())
				parent->parent->left = node;
			else
				parent->parent->right = node;
			
			node->right = parent;
			node->right->parent = node;

			return node;
		}

		node_type *fix_insert_left_imbalance (node_type *parent)
		{
			if (parent->left->balance_factor == parent->balance_factor)
			{
				parent = rotate_right (parent);
				parent->balance_factor = 0;
				parent->right->balance_factor = 0;
			}
			else
			{
				char old_bf = parent->left->right->balance_factor;
				rotate_left (parent->left);
				parent = rotate_right (parent);

				parent->balance_factor = 0;
				if (old_bf == -1)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 1;
				}
				else if (old_bf == 1)
				{
					parent->left->balance_factor = -1;
					parent->right->balance_factor = 0;
				}
				else if (old_bf == 0)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 0;
				}
			}

			return parent;
		}

		node_type *fix_insert_right_imbalance (node_type *parent)
		{
			if (parent->right->balance_factor == parent->balance_factor)
			{
				parent = rotate_left (parent);
				parent->balance_factor = 0;
				parent->left->balance_factor = 0;
			}
			else
			{
				char old_bf = parent->right->left->balance_factor;
				rotate_right (parent->right);
				parent = rotate_left (parent);

				parent->balance_factor = 0;
				if (old_bf == -1)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 1;
				}
				else if (old_bf == 1)
				{
					parent->left->balance_factor = -1;
					parent->right->balance_factor = 0;
				}
				else if (old_bf == 0)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 0;
				}
			}

			return parent;
		}

		node_type *fix_erase_left_imbalance (node_type *parent)
		{
			if (parent->left->balance_factor == -1)
			{
				parent = rotate_right (parent);
				parent->balance_factor = 0;
				parent->right->balance_factor = 0;
			}
			else if (parent->left->balance_factor == 0)
			{
				parent = rotate_right (parent);
				parent->balance_factor = 1;
				parent->right->balance_factor = -1;
			}
			else if (parent->left->balance_factor == 1)
			{
				char old_bf = parent->left->right->balance_factor;
				rotate_left (parent->left);
				parent = rotate_right (parent);

				parent->balance_factor = 0;
				if (old_bf == -1)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 1;
				}
				else if (old_bf == 1)
				{
					parent->left->balance_factor = -1;
					parent->right->balance_factor = 0;
				}
				else if (old_bf == 0)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 0;
				}
			}

			return parent;
		}

		node_type *fix_erase_right_imbalance (node_type *parent)
		{
			if (parent->right->balance_factor == 1)
			{
				parent = rotate_left (parent);
				parent->balance_factor = 0;
				parent->left->balance_factor = 0;
			}
			else if (parent->right->balance_factor == 0)
			{
				parent = rotate_left (parent);
				parent->balance_factor = -1;
				parent->left->balance_factor = 1;
			}
			else if (parent->right->balance_factor == -1)
			{
				char old_bf = parent->right->left->balance_factor;
				rotate_right (parent->right);
				parent = rotate_left (parent);

				parent->balance_factor = 0;
				if (old_bf == -1)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 1;
				}
				else if (old_bf == 1)
				{
					parent->left->balance_factor = -1;
					parent->right->balance_factor = 0;
				}
				else if (old_bf == 0)
				{
					parent->left->balance_factor = 0;
					parent->right->balance_factor = 0;
				}
			}

			return parent;
		}

		void erase (node_type *node)
		{
			node_type *target;
			if (!node->left || !node->right)
			{
				target = node;
			}
			else
			{
				target = node->successor ();
				node->value = target->value;
			}

			node = target;
			node_type *parent = node->parent;
			while (parent)
			{
				if (node->is_left_child ())
				{
					if (parent->balance_factor == -1)
					{
						parent->balance_factor = 0;
					}
					else if (parent->balance_factor == 0)
					{
						parent->balance_factor = 1;

						break;
					}
					else if (parent->balance_factor == 1)
					{
						parent = fix_erase_right_imbalance (parent);
						if (parent->balance_factor == -1)
							break;
					}
				}
				else
				{
					if (parent->balance_factor == 1)
					{
						parent->balance_factor = 0;
					}
					else if (parent->balance_factor == 0)
					{
						parent->balance_factor = -1;

						break;
					}
					else if (parent->balance_factor == -1)
					{
						parent = fix_erase_left_imbalance (parent);
						if (parent->balance_factor == 1)
							break;
					}
				}

				node = parent;
				parent = node->parent;
			}

			node_type *child = target->right ? target->right : target->left;

			if (child)
				child->parent = target->parent;

			if (!target->parent)
				_root = child;
			else if (target->is_left_child ())
				target->parent->left = child;
			else
				target->parent->right = child;

			_size -= 1;
			_alloc.destroy (target);
			_alloc.deallocate (target, sizeof (node_type));
		}
	};
}

#endif
