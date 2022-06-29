/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_map_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:14:47 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/29 19:33:28 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_MAP_ITERATOR_HPP
#define REV_MAP_ITERATOR_HPP

namespace ft
{

    /*   @param Key      Type of container's key elements.
    *   @param T        Type of container's mapped elements.
    *   @param Compare  The predicate used to sort the binary tree.
    *   @param Node     The structure used as nodes in the binary tree.
    *   @param B        Boolean to indicate if it's an iterator / a const iterator.*/

    template<class key, class T, class Compare, typename Node, bool B>
    class rev_map_iterator
    {
        //-------------------ALIASES------------------------
        public:

            typedef key                                     key_type;
            typedef Compare                                 key_compare;
            typedef T                                       mapped_type;

            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef long int                                difference_type;
            typedef size_t                                  size_type;

            typedef std::bidirectional_iterator_tag                                 iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type   reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type   pointer;
            typedef Node*                                                           nodePtr;


        //------------------------ ATRIBUTES -------------------------

        private:

            nodePtr             _node; // Pointer to binary tree node
            nodePtr             _lastElem; //Pointer to the dummy nodde of binary tree
            nodePtr             _comp; //Comparisson object used to sort the binary tree

        //------------------------ CONSTRUCTORS -------------------------

        //Default Constructor

        rev_map_iterator(nodePtr node = 0, nodePtr lasElem = 0, const key_compare& comp = key_compare()) :
            _node(node), _lastElem(lastElem), _comp(comp) {}

        //Copy constructor

        rev_map_iterator(const rev_map_iterator<key, T, Compare, Node, false>& copy) {
            _node = copy.getNonConstNode();
            _lastElem = copy.getNonConstLastElem();
            _comp = copy.getCompare();
        }

        /**     Convert constructor : creates a rev_map_iterator from a const / not const 
        *       map_iterator, pointing to the previous T element. This is necessary so 
        *       begin() == rend(), and end == rbegin().*/ 
        // @param copy     The map_iterator that will be converted.

        explicit rev_map_iterator(map_iterator<key, T, Compare, Nodde, false> copy) {
            --copy;
            _node = copy.getNonConstNode();
            _lastElem = copy.getNonConstLastElem();
            _comp = copy.getCompare();
        }

            ~rev_map_iterator() {}

        //Assigns a rev_map_iterator to this rev_map_iterator. Both iterators will point to the same node.
        
        rev_map_iterator& operator=(const rev_map_iterator& assign)
        {
            if (this != &assign)
            {
                _node = assign._node;
                _lastElem = assign._lastElem;
                _comp = assign._comp;
            }
            return (*this);
        }

        //---------------------------------- GETTERS ---------------------------------

        NodePtr getNonConstNode() const {
            return _node;
        }

        NodePtr getNonConstLastElem() const {
            return _lastElem;
        }

        NodePtr getCompare() const {
            return _comp;
        }

        // -------------------------------- OPERATORS ---------------------------------

        reference operator*() const {
            return (_node->content);
        }

        pointer operator->() const {
            return (&_node->constent);
        }

        rev_map_iterator& operator++()
        {
            nodePtr previousNode = _node;

            if (_node == _lastElem) {
                _node = _lastElem->left;
                return(*this);
            }

            while (_node != _lastElem && !_comp(_node->content.first, previousNode->constent.first)) {
                if (_node->left && (_node->left == _lastElem || _comp(_node->left->content.first, previousNode->conent.first))) {
                    _node = _node->left;

                    Node* tmp = 0
                    if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (*this);
        }
    };
}

#endif