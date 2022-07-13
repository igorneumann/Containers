/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:53:42 by ineumann          #+#    #+#             */
/*   Updated: 2022/07/13 18:14:34 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <cmath>
#include "stdutils.hpp"
#include "chooseconst.hpp"
#include "type_traits.hpp"
#include "map_iterator.hpp"
#include "rev_map_iterator.hpp"

namespace ft 
{
/*  @param key      Type of keys mapped to elements.
*   @param T        Type of elements mapped to keys.
*   @param Compare  Comparison object used to sort the binary tree.
*   @param Alloc    Object used to manage the vector' storage.
*/

template < class key, class T, class Compare = ft::less<key>, class Alloc = ft::allocator<ft::pair<const key, T> > >
    class map
    {

        private:
                struct Node
            {
                ft::pair<const key, T>  content;
                Node*                   parent;
                Node*                   left;
                Node*                   right;
            };
        
        public:
            typedef key                                     key_type;
            typedef Compare                                 key_compare;
            typedef Alloc                                   allocator_type;
            typedef T                                       mapped_type;

            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef long int                                difference_type;
            typedef size_t                                  size_type;

            typedef T&                                     reference;
            typedef const T&                               const_reference;
            typedef T*                                     pointer;
            typedef const T*                               const_pointer;

            typedef typename ft::map_iterator<key, T, Compare, Node, false> iterator;
            typedef typename ft::map_iterator<key, T, Compare, Node, true>  const_iterator;

            typedef typename ft::rev_map_iterator<key, T, Compare, Node, false> reverse_iterator;
            typedef typename ft::rev_map_iterator<key, T, Compare, Node, true>  const_rev_iterator;

        private:
            
            Node*                       _root; //1st element of a tree
            Node*                       _lastElem; //last element
            size_type                   _size; // # of values inside
            allocator_type              _allocPair;     //copy of allocator type object
            key_compare                 _comp;  // Copy of comp key compare predicate
            ft::allocator<Node>          _allocNode;  //Nodde's allocator

            /**
            *   Comparison object using map's key_compare. It can be return with the value_comp method.
            */
           public:
        
            class value_compare
            {
                friend class map;

                protected:
                    key_compare comp;
                    value_compare(Compare c) : comp(c) {}

                public:
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;

                    bool operator()(const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };

        /*  Default (blank) constructor
            @param comp     The template param used for sorting the map.
            @param alloc    The template param used for the allocation.*/       
        explicit map(const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()) : _size(0), _allocPair(alloc), _comp(comp)
        {
            _lastElem = createNode(ft::pair<const key_type, mapped_type>());
            _root = _lastElem;
            _lastElem->left = _lastElem;
            _lastElem->right-> _lastElem;
        }

        /*  Range Constructor
            @param first    An iterator representing first element of the range.
            @param last     An iterator indicating end of the range (will be excluded and not copied).
            @param comp     The template param used for sorting the map.
            @param alloc    The template param used for the allocation. */
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : _size(0), _allocPair(alloc), _comp(comp)
        {
            _lastElem = createNode(ft::pair<const key_type, mapped_type>());
            _root = _lastElem;
            _lastElem->left = _lastElem;
            _lastElem->right = _lastElem;

            for (; first != last; ++first)
                insert(*first);
        }

        /*  Copy Constructor
             @param x        The map that will be copied. */
        map(const map& x) : _size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
        {
            _lastElem = createNode(ft::pair<const key_type, mapped_type>());
            _root = _lastElem;
            _lastElem->left = _lastElem;
            _lastElem->right = _lastElem;

            for(iterator it = x.begin(); it != x.end(); ++it)
                insert(*it);
        }

        /*  Destructor */
        ~map()
        {
            clear();
            deallocateNode(_lastElem);
        }

        /*  Copy operator = calls the copy constructor */
        map& operator=(const map & x)
        {
            map tmp(x);
            this->swap(tmp);
            return *this;
        }
        /*----------------------ITERATORS--------------------*/

        iterator begin() {
            return iterator(_lastElem->right, _lastElem, _comp);
        }
        const_iterator begin() const {
            return const_iterator(_lastElem->right, _lastElem, _comp);
        }
        iterator end()  {
            return iterator(_lastElem, _lastElem, _comp);
        }
        const_iterator end() const {
            return const_iterator(_lastElem, _lastElem, _comp);
        }
        reverse_iterator rbegin()   {
            return reverse_iterator(_lastElem->left, _lastElem, _comp);
        }
        const_rev_iterator rbegin() const {
            return const_reverse_iterator(_lastElem->left, _lastElem, _comp);
        }
        reverse_iterator rend() {
            return reverse_iterator(_lastElem, _lastElem, _comp);
        }
        const_rev_iterator rend() const {
            return const_reverse_iterator(_lastElem, _lastElem, _comp);
        }
        
        /*-----------------------CAPACITY----------------------*/
        bool    empty() const  {
            return _size == 0; //return true if equal to 0
        }
        size_type   size() const    {
            return _size;
        }
        size_type   max_size() const    {
            return this->_alloc.max_size();
        }

        /*----------------------ELEMENT ACCESS-------------------*/
        mapped_type& operator[](const key_type& k)
        {
            Node* tmp = searchNode(_root, k);

            if (tmp)
                return tmp->content.second;
            
            value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
            return insertNode(_root, val)->content.second;
        }

        /*----------------------MODIFIERS-------------------*/
        /* Inserts one element if the key didn't already exist in map. Increases 
           the size by one if the element was inserted.
        
           @param val  The pair<key, mapped value> to insert.
           @return     Return a pair with an iterator pointing to the newly element 
                       inserted if the key wasn't existing in map, otherwise an iterator 
                       to the key already present; and a boolean : true if the element 
                       was inserted, false if already  existing.*/

        ft::pair<iterator, bool> insert (const value_type& val)
        {
            // Searches if val's key is already present and returns an iterator to the key if it's the case
            Node* elemIsPresent = searchNode(_root, val.first);
            if (elemIsPresent)
                return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastElem, _comp), false);
            ++_size;
            return ft::pair<iterator, bool>(iterator(insertNode(_root, val), _lastElem, _comp), true);
        }

        /*  Inserts one element if the key didn't already exist in map, starting from a certain position*/
        iterator insert (iterator position, const value_type& val)
        {
            // If position key is higher than val, we need to decrease position 
            // until we find the closest highest key from val in the tree
            if (position->first > val.first)
            {
                iterator prev(position);
                --prev;
                while (prev != end() && prev->first >= val.first)
                {
                    --position;
                    --prev;
                }
            }

            //Opposite case
            else if (position->first < val.first)
            {
                iterator next(position);
                ++next;
                while (next != end() && next->first <= val.first)
                {
                    ++position;
                    ++next;
                }
            }

            // If the value already exist, and the tree isn't empty
            if (position != end() && val.first == position->first)
                return position;
            
            ++_size;
            return iterator(insertNode(position.getNode(), val), _lastElem, _comp);
        }
        /* Inserts all elements between first and last (if they're not already existing), 
           and increases the map' size.
        
           @param first    An iterator pointing to the range's beginning (will be include).
           @param last     An iterator pointing to the range's end (will not be include).*/
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last,
                    typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0)
        {
            while (first != last)
                insert(*first++);
        }

        // Remove element at the @param position

        size_type erase(iterator position)
        {
            deleteNode(position.getNode(), position->first);
            --_size;
        }

        //remove element that matches @param k and @return 1 (erased) or 0 (not erased)
        size_type erase (const key_type& k)
        {
            size_type ret = deleteNode(_root, k);
            _size -= ret;
            return ret;
        }

        //remove all elements from @param first iterator up to @param last iterator
        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                iterator tmp(first);
                ++first;
                erase(tmp);
            }
        }

        //swap @param map with the contents of this one
        void swap (map& x)
        {
            swap(_root, x._root);
            swap(_lastElem, x._lastelem);
            sweap(_size, x._size);
            swap(_comp, x._comp);
            swap(_allocPair, x._allocPair);
            swap(_allocNode, x._allocNode);
        }

        //nuke everything inside the container
        void clear()    {
            erase(begin(), end());
        }

        /*----------------------------OBSERVERS------------------------------------*/

        //  @returns A copy of the comparison object used by the container to compare keys.
        key_compare key_comp() const {
            return _comp;
        }

        // @returns A comparisson object that compare whenever the 1st came before the 2nd
        value_compare   value_comp() const {
            return value_compare(_comp);
        }

        /*----------------------------OPERATIONS------------------------------------*/
    

        //   Searches the container for an element with a specific key.

        iterator    find(const key_type& k) {
            Node* tmp = searchNode(_root, k);

            if (tmp)
                return iterator(tmp, _lastElem, _comp);
            return end();
        }

        const_iterator find(const key_type& k) const {
            Node* tmp = searchNode(_root, k);

            if (tmp)
                return iterator(tmp, _lastElem, _comp);
            return end();
        }

        //  Searches the container for elements with a specific key and returns the number of matches.

        size_type   count(const key_type& k) const {
            Node* tmp = searchNode(_root, k);

            return tmp ? true: false; // Since the key cant be twice, returns 0 or 1
        }

        //  Searches for the element whose key is not considered to go before k.

        iterator lower_bound(const key_type& k) {
            iterator it = begin();

            for (; it != end(); ++it)
                if (!_comp(it->first, k))
                    break;

            return it;
        }

        const_iterator lower_bound(const key_type& k) const {
            const_iterator it = begin();

            for (; it != end(); ++it)
                if (!_comp(k, it->first))
                    break;
            return it;
        }

        //    Searches for the element whose key is considered to go after k

        iterator upper_bound(const key_type& k) {
            iterator it = begin();

            for (; it != end(); ++it)
                if (_comp(k, it->first))
                    break;
            return it;
        }

        const_iterator upper_bound(const key_type& k) const {
            const_iterator it = begin();

            for (; it != end(); ++it)
                if (_comp(k, it->first))
                    break;
            
            return it;
        }

        // Returns the bounds of a range that includes all the elements in the container which have a specific key. - Unique keys = single element at most

        pair<iterator,iterator> equal_range(const key_type& k) {
            iterator it = upper_bound(k);

            if (it != begin()) {
                --it;

                if (_comp(it->first, k) || _comp(k, it->first))
                    ++it;
            }

            iterator next(it);
            if (it != end())
                ++next;
            
            return make_pair<iterator, iterator>(it, next);
        }

        pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
            const_iterator it = upper_bound(k);

            if (it != begin()) {
                --it;

                if (_comp(it->first, k) || _comp(k, it->first))
                    ++it;
            }

            const_iterator next(it);
            if (it != end())
                ++next;

            return make_pair<const_iterator, const_iterator>(it, next);
        }

        /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */

    private:
    
        // swaps 2 variables using reference
    
        template <class U>
        void swap(U& a, U& b) {
            U temp = a;
            a = b;
            b = temp;
        }

        //create a pair
        template <class T1,class T2>
        pair<T1, T1> make_pair(T1 x, T2 y) const {
            return pair<T1, T2>(x,y);
        }

        /* -------AVL BINARY SEARCH TREE ----- 
            inserting and deleting inside the tree */

        Node* createNode(const value_type& pair) {
            Node* newNode = _allocNode.allocate(1);

            _allocPair.construct(&newNode->content, pair);
            newNode->parent = 0;
            newNode->left = 0;
            newNode->right = 0;

            return newNode;
        }

        // Call destructor of node's content, and then deallocates the node.
        
        void    deallocateNode(Node* del) {
            _allocPair.destroy(&del->content);
            _allocNode.deallocate(del, 1);
        }

        // Calculates the tree's height.

        int heightTree(Node* root, int height) {
            if (!root || root == _lastElem)
                return height - 1;
            
            int leftHeight = heightTree(root->left, height +1);
            int rightHeight = heightTree(root->right, height + 1);

            return leftHeight > rightHeight ? leftHeight : rightHeight;
        }

        Node* searchNode (Node* root, key_type Key) const {
            if (!root || root == _lastElem)
                return 0;

            if (!_comp(root->content.first > Key) && !_comp(Key, root->content.first))
                return root;

            if (root->content.first > Key && root->left && root->left != _lastElem)
                return searchNode(root->left, Key);
            else if (root->content.first < Key && root->right && root->right != _lastElem)
                return searchNode(root->right, Key);
            return 0;
        }

        Node* searchMaxNode(Node *root) const {
            if (root->right && root->right != _lastElem)
                return searchMaxNodde(root->right);
            return root;
        }

        Node* searchMinNode(Node *root) const {
            if (root->left && root->left != _lastElem)
                return searchMinNode(root->left);
            return root;
        }

        /* Inserts a pair in the tree or a specific subtree by adding a new element
            equilibrates the AVL tree if necessary. */
    };
}

#endif