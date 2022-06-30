/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:05:41 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/30 19:27:06 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR
#include "stdutils.hpp"

namespace ft
{
    template <class key, class T, class Compare, typename Node, bool B>
    class map_iterator
    {
        public:
            typedef key                                                             key_type;
            typedef Compare                                                         key_compare;
            typedef T                                                               mapped_type;
            typedef ft::pair<const key_type, mapped_type>                           value_type;
            typedef long int                                                        difference_type;
            typedef size_t                                                          size_type;
            typedef std::bidirectional_iterator_tag                                 iterator_category;
            typedef typename chooseConst<B, value_type&, const value_type&>::type   reference;
            typedef typename chooseConst<B, value_type*, const value_type*>::type   pointer;
            typedef Node*                                                           nodePtr;

        private:
            nodePtr         _node; //pointer to a binary tree's node;
            nodePtr         _lastElem; //pointer to the dummy node of a binary tree
            key_compare     _comp;  // comparison object used to sort the binary tree

        public:

            //Default constructor
            map_iterator(nodePtr node = 0, nodePtr lastElem = 0, const key_compare& comp = key_compare()) : 
                _node(node), _lastElem(lastElem), _comp(comp) {}

            //Copy Constructor
            map_iterator(const map_iterator<key, T, Compare, Node, false>& copy)
            {
                _node = copy.getNode();
                _lastElem = copy.getLastelem();
                _comp = copy.getCompare();
            }

            ~map_iterator() {}

            map_iterator& operator=(const map_iterator& assign) {
                if (this != &assign)
                {
                    _node = assign._node;
                    _lastElem = assign._lastElem;
                    _comp = assign._comp;
                }
                return (*this);
            }

        // ------------------------------ GETTERS ----------------------------
        
        nodePtr getNode() const {
            return _node;
        }

        nodePtr getLastelem() {
            return _lastElem;
        }

        key_compare getCompare() {
            return _comp;
        }

        // ------------------------------ OPERATORS ----------------------------

        reference operator*() const {
            return (_node->content);
        }

        pointer operator->() const {
            return (&_node->content);
        }

        map_iterator& operator++() {
            nodePtr previousNode = _node;

            if (_node == _lastElem)
            {
                _node = _lastElem->right;
                return(*this);
            }    

            //comp is equivalent to <.

            while (_node != _lastElem && !comp(previousNode->content.first, _node->content.first)) {
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

        map_iterator operator++(int) {
            map_iterator res(*this);

            if (_node == _lastElem) {
                _node = _lastElem->right;
                return (res);
            }

            while (_node != _lastElem && !_comp(res->first, _node->content.first))
            {
                if (_node->right && (_node->right == _lastElem || _comp(res->first, _node->right->content.first))) {
                    _node = _node->right;

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMinNodde(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (res);
        }

        map_iterator& operator--() {
            //inverse logic than ++
            nodePtr previousNode = _node;

            if (_node == _lastElem) {
                _node = _lastElem->left;
                return (*this);
            }
            while (_node != _lastElem && !_comp(_node->content.first, previousNode->content.first)) {
                if (_node->left && (_node->left == _lastElem || _comp(_node->left->content.first, previousNode->content.first)))
                {
                    _node - _node->left;

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMaxNode(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (*this);
        }

        map_iterator operator--(int)
        {
            map_iterator res(*this);

            if (_node == _lastElem)
            {
                _node = _lastElem->left;
                return (res);
            }

            while(_node->left && (_node->left == _lastElem || _comp(_node->left->content.first, res->first))) {
                if (_node->left && (_node->left == _lastElem || _comp(_node->left->content.first, res->first))) {
                    _node = _node->left;

                    Node* tmp = 0;
                    if (_node != _lastElem && (tmp = searchMaxNodde(_node)))
                        _node = tmp;
                }
                else
                    _node = _node->parent;
            }
            return (res);
        }

        bool operator==(const map_iterator& it) const {
            return (it._node == _node);
        }

        bool operator !=(const map_iterator& it) const {
            return (it._node != _node);
        }

        // ------------------------------ PRIVATE MEMBER FUNCTIONS ----------------------------

        Node* searchMaxNode(Node *root) {
            if (root && root != _lastElem && root->right && root->right != _lastElem)
                return searchMaxNode(root->right);
            return root;
        }

        Node* searchMinNode(Node *root) {
            if (root && root != _lastElem && root->left && root->left != _lastElem)
                return searchMinNode(root->left);
            return root;
        }
    };
}

#endif