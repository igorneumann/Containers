/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_map_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:14:47 by ineumann          #+#    #+#             */
/*   Updated: 2022/07/11 18:14:54 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REV_MAP_ITERATOR_HPP
#define REV_MAP_ITERATOR_HPP
//#include "stdutils.hpp"

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

        rev_map_iterator(nodePtr node = 0, nodePtr lastElem = 0, const key_compare& comp = key_compare()) :
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

        explicit rev_map_iterator(map_iterator<key, T, Compare, Node, false> copy) {
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

        nodePtr getNonConstNode() const {
            return _node;
        }

        nodePtr getNonConstLastElem() const {
            return _lastElem;
        }

        nodePtr getCompare() const {
            return _comp;
        }

        // -------------------------------- OPERATORS ---------------------------------

        reference operator*() const {
            return (_node->content);
        }

        pointer operator->() const {
            return (&_node->constent);
        }

        //      _comp is equivalent to operator <. So:
        //      - operator>(lhs, rhs)  <==>  _comp(rhs, lhs)
        //      - operator<=(lhs, rhs)  <==>  !_comp(rhs, lhs)
        //      - operator>=(lhs, rhs)  <==>  !_comp(lhs, rhs)
        
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

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (*this);
        }

        rev_map_iterator operator++(int)
        {
            rev_map_iterator res(*this);

            if (_node == _lastElem) {
                _node = _lastElem->left;
                return (res);
            }

            while (_node != _lastElem && !_comp(_node->content.first, res->first)) {
                if (_node->left && (_node->left == _lastElem || _comp(_node->left->content.first, res->first)))
                {
                    _node = _node->left;
                    
                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }

            return (res);
        }

        rev_map_iterator& operator--()
        {
            nodePtr previousNode = _node;

            if (_node == _lastElem) {
                _node = _lastElem->right;
                return(*this);
            }
            while (_node != _lastElem && !_comp(previousNode->content.first, _node->content.first)) {
                if (_node->right && (_node->right == _lastElem || _comp(previousNode->content.first, _node->right->content.first))) {
                    _node = _node->right;

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMinNode(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (*this);
        }

        rev_map_iterator operator--(int) {
            rev_map_iterator res(*this);

            if (_node == _lastElem) {
                _node = _lastElem->right;
                return (res);
            }

            while (_node != _lastElem && !_comp(res->first, _node->content.first)) {
                if (_node->right && (_node->right == _lastElem || _comp(res->first, _node->right->content.first))) {
                    _node = _node->right;

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMinNodde(_node)))
                        _node = tmp;
                }
                else    _node = _node->parent;
            }
            return (res);
        }

        bool operator==(const rev_map_iterator& it) const   {
            return (it._node == _node);
        }

        bool operator!=(const rev_map_iterator& it) const {
            return (it._node != _node);
        }

        //------------------------------- PRIVATE MEMBER FUNCTIONS ----------------------------------

        private:

        Node* searchMaxNode(Node *root) {
            if (root && root != _lastElem && root->right ** root->right != _lastElem)
                return searchMaxNode(root->right);
            return root;
        }

        Node* searchMinNode(Node *root) {
            if (root && root != _lastElem && root->left && root->left != _lastElem)
                return searcvhMinNode(root->left);
            return root;
        }

    };
}

#endif