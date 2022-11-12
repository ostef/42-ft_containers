#ifndef FT_AVL_HPP
#define FT_AVL_HPP

#include "utility.hpp"
#include "iterator.hpp"
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

		explicit avl_node () :
			parent (NULL), left (NULL), right (NULL), balance_factor (0), value () {}
		explicit avl_node (const value_type &val) :
			parent (NULL), left (NULL), right (NULL), balance_factor (0), value (val) {}
		avl_node (const avl_node &other) :
			parent (other.parent), left (other.left), right (other.right), balance_factor (other.balance_factor), value (other.value) {}
		~avl_node () {}

		avl_node &operator= (const avl_node &other)
		{
			parent = other.parent;
			left = other.left;
			right = other.right;
			balance_factor = other.balance_factor;
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

		typedef bst_iterator<node_type> iterator;
		typedef bst_iterator<const node_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		// Do not assign the root directly unless you know what you're doing!
		// Use set_root instead, to update the before begin and past end nodes.
		node_type *_root;

		// These two are pointers, because we need to be able to swap
		// them so they belong to a different tree. Yeah that's fucked up,
		// but this is so iterators from the tree before a swap point to
		// the swapped tree after the swap. This seems like a shitty edge case,
		// but we need to handle it anyways. Fuck C++, fuck all this.
		node_type *_before_begin;
		node_type *_past_end;

		size_type _size;
		value_compare _less_than;
		allocator_type _alloc;
	
	public:

		avl_tree () : _root (NULL), _size (0), _less_than (Compare ()), _alloc (allocator_type ())
		{
			initialize_special_nodes ();
		}

		explicit avl_tree (const Compare &comp, const allocator_type &alloc = allocator_type ()) :
			_root (NULL), _size (0), _less_than (comp), _alloc (alloc)
		{
			initialize_special_nodes ();
		}

		template<typename InputIt>
		avl_tree (InputIt first, InputIt last, const Compare &comp = Compare (), const allocator_type &alloc = allocator_type ()) :
			_root (NULL), _size (0), _less_than (comp), _alloc (alloc)
		{
			initialize_special_nodes ();

			for (InputIt it = first; it != last; it++)
				insert (*it);
		}

		avl_tree (const avl_tree &other) :
			_root (NULL), _size (0), _less_than (other._less_than), _alloc (other._alloc)
		{
			initialize_special_nodes ();

			for (const_iterator it = other.begin (); it != other.end (); it++)
				insert (*it);
		}

		~avl_tree ()
		{
			_alloc.destroy (_before_begin);
			_alloc.destroy (_past_end);
			_alloc.deallocate (_before_begin, 2);

			clear ();
		}

		avl_tree &operator= (const avl_tree &other)
		{
			clear ();
			for (const_iterator it = other.begin (); it != other.end (); it++)
				insert (*it);

			return *this;
		}

		node_type *root ()
		{
			return _root;
		}

		const node_type *root () const
		{
			return _root;
		}

		node_type *before_begin ()
		{
			return _before_begin;
		}

		const node_type *before_begin () const
		{
			return _before_begin;
		}

		
		node_type *past_end ()
		{
			return _past_end;
		}

		const node_type *past_end () const
		{
			return _past_end;
		}


		pair<iterator, bool> insert (const value_type &value)
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
					return ft::make_pair (iterator (*this, curr), false);
				}
			}

			node_type *result = _alloc.allocate (1);
			_alloc.construct (result, node_type (value));
			result->parent = parent;

			if (!parent)
				set_root (result);
			else if (less)
				parent->left = result;
			else
				parent->right = result;
			
			_size += 1;

			node_type *node = result;
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

			return ft::make_pair (iterator (*this, result), true);
		}

		iterator erase (iterator it)
		{
			node_type *next = it.node ()->successor ();
			erase (it.node ());

			return iterator (*this, next);
		}

		iterator erase (iterator first, iterator last)
		{
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
			erase (begin (), end ());
		}

		void swap (avl_tree &other)
		{
			node_type *tmp_root = _root;
			node_type *tmp_before_begin = _before_begin;
			node_type *tmp_past_end = _past_end;
			size_type tmp_size = _size;
			value_compare tmp_less_than = _less_than;
			allocator_type tmp_alloc = _alloc;

			_root = other._root;
			_before_begin = other._before_begin;
			_past_end = other._past_end;
			_size = other._size;
			_less_than = other._less_than;
			_alloc = other._alloc;

			other._root = tmp_root;
			other._before_begin = tmp_before_begin;
			other._past_end = tmp_past_end;
			other._size = tmp_size;
			other._less_than = tmp_less_than;
			other._alloc = tmp_alloc;
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
				return iterator (*this, _past_end);

			return iterator (*this, node);
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
				return const_iterator (*this, _past_end);

			return const_iterator (*this, node);
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
			iterator it = iterator (*this, _before_begin);

			return ++it;
		}

		const_iterator begin () const
		{
			const_iterator it = const_iterator (*this, _before_begin);

			return ++it;
		}

		iterator end ()
		{
			return iterator (*this, _past_end);
		}

		const_iterator end () const
		{
			return const_iterator (*this, _past_end);
		}

		reverse_iterator rbegin () { return reverse_iterator (end ()); }
		const_reverse_iterator rbegin () const { return const_reverse_iterator (end ()); }

		reverse_iterator rend () { return reverse_iterator (begin ()); }
		const_reverse_iterator rend () const { return const_reverse_iterator (begin ()); }

	private:

		void initialize_special_nodes ()
		{
			_before_begin = _alloc.allocate (2);
			_past_end = _before_begin + 1;

			_alloc.construct (_before_begin, node_type ());
			_alloc.construct (_past_end, node_type ());
		}

		void set_root (node_type *new_root)
		{
			_root = new_root;
			_before_begin->right = new_root;
			_past_end->left = new_root;
		}

		void swap_nodes (node_type *a, node_type *b)
		{
			bool left_child = a->is_left_child ();
			bool right_child = a->is_right_child ();
			node_type *tmp_parent = a->parent;
			node_type *tmp_right = a->right;
			node_type *tmp_left = a->left;
			
			a->parent = b->parent;
			if (!a->parent)
				set_root (a);
			else if (b->is_left_child ())
				a->parent->left = a;
			else if (b->is_right_child ())
				a->parent->right = a;
			else
				ASSERT (false && "Invalid path");

			a->right = b->right;
			if (a->right)
				a->right->parent = a;
	
			a->left = b->left;
			if (a->left)
				a->left->parent = a;
	
			b->parent = tmp_parent;
			if (!b->parent)
				set_root (b);
			else if (left_child)
				b->parent->left = b;
			else if (right_child)
				b->parent->right = b;
			else
				ASSERT (false && "Invalid path");

			if (b == tmp_right)
				tmp_right = a;

			b->right = tmp_right;
			if (b->right)
				b->right->parent = b;

			if (b == tmp_left)
				tmp_left = a;

			b->left = tmp_left;
			if (b->left)
				b->left->parent = b;
		}

		node_type *rotate_left (node_type *parent)
		{
			node_type *node = parent->right;

			parent->right = node->left;
			if (parent->right)
				parent->right->parent = parent;
			
			node->parent = parent->parent;
			if (!parent->parent)
				set_root (node);
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
				set_root (node);
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
			if (node->left && node->right)
			{
				node_type *suc = node->successor ();

				swap_nodes (node, suc);

				if (node->parent)
					ASSERT (node->parent->left == node || node->parent->right == node);
				if (node->left)
					ASSERT (node->left->parent == node);
				if (node->right)
					ASSERT (node->right->parent == node);
				
				if (suc->parent)
					ASSERT (suc->parent->left == suc || suc->parent->right == suc);
				if (suc->left)
					ASSERT (suc->left->parent == suc);
				if (suc->right)
					ASSERT (suc->right->parent == suc);
			}

			node_type *target = node;

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
				set_root (child);
			else if (target->is_left_child ())
				target->parent->left = child;
			else
				target->parent->right = child;

			_size -= 1;
			_alloc.destroy (target);
			_alloc.deallocate (target, 1);
		}
	};

	template<class T, class Compare, class TAllocator>
	bool operator== (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		if (lhs.size () != rhs.size ())
			return false;
		
		return ft::equal (lhs.begin (), lhs.end (), rhs.begin ());
	}

	template<class T, class Compare, class TAllocator>
	bool operator!= (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Compare, class TAllocator>
	bool operator< (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		return ft::lexicographical_compare (lhs.begin (), lhs.end (), rhs.begin (), rhs.end ());
	}

	template<class T, class Compare, class TAllocator>
	bool operator> (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		return ft::lexicographical_compare (rhs.begin (), rhs.end (), lhs.begin (), lhs.end ());
	}

	template<class T, class Compare, class TAllocator>
	bool operator<= (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template<class T, class Compare, class TAllocator>
	bool operator>= (const avl_tree<T, Compare, TAllocator> &lhs, const avl_tree<T, Compare, TAllocator> &rhs)
	{
		return lhs > rhs || lhs == rhs;
	}
}

#endif
