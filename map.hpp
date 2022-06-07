/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorneumann <igorneumann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:53:42 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/07 12:40:41 by igorneumann      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <functional>
#include <cmath>

namespace ft 
{
/*  @param key      Type of keys mapped to elements.
*   @param T        Type of elements mapped to keys.
*   @param Compare  Comparison object used to sort the binary tree.
*   @param Alloc    Object used to manage the vector' storage.
*/

template < class key, class T, class Compare = ft::less<key>, 
    class Alloc = ft::allocatos<ft::pair<cont key, T>>>
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
            typedef Key                                     key_type;
            typedef Compare                                 key_compare;
            typedef Alloc                                   allocator_type;
            typedef T                                       mapped_type;

            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef long int                                difference_type;
            typedef syze_t                                  size_type;

            typedef T&                                     reference;
            typedef const T&                               const_reference;
            typedef T*                                     pointer;
            typedef const T*                               const_pointer;

            typedef typename ft::map_iterator<Key, T, Compare, Node, false> iterator;
            typedef typename ft::map_iterator<Key, T, Compare, Note, true>  const_iterator;

            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, false> reverse_iterator;
            typedef typename ft::rev_map_iterator<Key, T, Compare, Node, true>  const_rev_iterator;
            /**
            *   Comparison object using map's key_compare. It can be return with the value_comp method.
            */
        
        class value_compare;
        {
            friend class map;

            protected:
                key compare comp;
                value_compare(Compare c) : comp(c) {}

            public:
                typedef bool        result_type;
                typedef value_type  first_argument_type;
                typedef value_type  second_argument_type;

                bool operator()(const value_type&, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
        };

        private:
            Node*                       _root; //1st element of a tree
            Node*                       _lastElem; //last element
            size_type                   _size; // # of values inside
            allocator_type              _allocPair;     //copy of allocator type object
            key_compare                 _comp;  // Copy of comp key compare predicate
            ft::alocator<Node>          _allocNode;  //Nodde's allocator

        public:

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
            _lastElem = createNode(FT:pair<const key_type, mapped_type>());
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
            _lastElem = createNode(FT:pair<const key_type, mapped_type>());
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
        map& operator=(cont map & x)
        {
            map tmp(x);
            this->swap(tmp);
            return *this;
        }
        /*----------------------ITERATORS--------------------*/

        iterator begin() {
            return iterator(_lastElem->right, _lastElem, _comp);
        }
        const_iterator begin() {
            return const_iterator(_lastElem->right, _lastElem, _comp);
        }
        iterator end()  {
            return iterator(_lastElem, _lastElem, _comp);
        }
        const_iterator end()  {
            return const_iterator(_lastElem, _LastElem, _comp);
        }
        reverse_iterator rbegin()   {
            return reverse_iterator(_lastElem->left, _lastelem, _comp);
        }
        const_reverse_iterator rbegin()   {
            return const_reverse_iterator(_lastElem->left, _lastelem, _comp);
        }
        reverse_iterator rend() {
            return reverse_iterator(_lastElem, _lastElem, _comp);
        }
        const_reverse_iterator rend()   {
            return const_reverse_iterator(__lastElem, _lastElem, _comp);
        }
        
        /*-----------------------CAPACITY----------------------*/
        bool    empty() const  {
            return _size == 0; //return true if equal to 0
        }
        size_type   size() const    {
            return _size;
        }
        size_type   max_size() const    {
            return this->_alloc.max_size()
        }

        /*----------------------ELEMENT ACCESS-------------------*/
        mapped_type& operator(const key_type& k)
        {
            Node* tmp = searchNode(_root, k);

            if (tmp)
                return tmp->content.second;
            
            value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
            return insertNode(_root, val)->content.second;
        }

        /*----------------------MODIFIERS-------------------*/

        
    };
}

#endif