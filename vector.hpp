/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:40:48 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/24 20:11:38 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <cmath>
#include "vector-utils.hpp"
#include "RandomAccessIterator.hpp"
#include "reverseRAI.hpp"

namespace ft {

    template<class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
    // -----------------------------typedefs-----------------------------
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef T&                                          reference;
        typedef const T&                                    const_reference;
        typedef T*                                          pointer;
        typedef const T*                                    const_pointer;
        typedef size_t                                      size_type;
        typedef long int                                    difference_type;
        typedef RandomAccessIterator<T, T*, T&>             iterator;
        typedef RandomAccessIterator<T, const T*, const T&> const_iterator; 
        typedef ReverseRAI<iterator>                        reverse_iterator;
        typedef ReverseRAI<const_iterator>                  const_reverse_iterator;

    // -----------------------------variables-----------------------------
        private:
            allocator_type	    _alloc;
            size_type           _size;
            size_type           _max_size;
            pointer             _array;

        public:
    // -----------------------------Constructors destructor & copy-----------------------------
            explicit vector( const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(0), _max_size(0) {
            }

            explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(n), _max_size(n) {
                this->_array = _alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(&this->_array[i], val);
            }
            
            template <typename InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename std::enable_if<!std::is_integral<InputIterator>::value >::type* = 0) : _alloc(alloc), _size(0){
                    
                    InputIterator tmp(first);
                    while (tmp++ != last)
                        this->_size++;
                    this->_max_size = this->_size;
                    this->_array = this->_alloc.allocate(this->_max_size);
                    for (int i = 0; first != last; ++first, ++i)
                        this->_array[i] = *first;
            }
            vector( const vector& x ) : _alloc(x._alloc), _size(0), _max_size(0), _array(0) {
                *this = x;
            }
            vector &operator=(const vector & x) {
                _alloc.deallocate(_array, _max_size);;
                this->_array = _alloc.allocate(x._max_size);
                this->_max_size = x._max_size;
                this->_size = 0;
                this->assign(x.begin(), x.end());
			    return *this;
            }
            ~vector( void )   { 
                if (this->_array && this->begin() != this->end())
                    _alloc.deallocate(this->_array, this->_max_size);
                this->_array = NULL;
            }
    // -----------------------------Iterators-----------------------------
			iterator	begin(void) {
				return iterator(this->_array);
			}
			iterator	end(void) {
				return iterator(this->_array + this->_size);
			}
			const_iterator	begin(void)	const {
				return const_iterator(this->_array);
			}
			const_iterator	end(void) const {
				return const_iterator(this->_array + this->_size);
			}
            reverse_iterator rbegin() {
                return reverse_iterator(this->_array + this->_size - 1);
            }
            reverse_iterator rend() {
                return reverse_iterator(this->_array - 1);
            }
            const_reverse_iterator rbegin() const {
                return const_reverse_iterator(this->_array + this->_size - 1);
            }
            const_reverse_iterator rend() const {
                return const_reverse_iterator(this->_array - 1);
            }
    // -----------------------------Capacity-----------------------------
            size_type  size() const {
                return this->_size;
            }
            size_type   max_size() const {
                return this->_alloc.max_size();
            }
            void        resize( size_type n, value_type val = value_type() ) {
                if (n > this->_max_size)
                    reserve(n);
                while (n > this->_size)
                    push_back(val);
                while (n < this->_size)
                    pop_back();
            }
            size_type   capacity() const    {
                return this->_max_size;
            }
            bool   empty() const   {
                return (!(this->_size));
            }
            void    reserve(size_type n) {
                if (n > this->_max_size) {
                    n = std::max(n, this->_max_size * 2);
                    pointer tmp = _alloc.allocate(n);
                    for (size_type i = 0; i < this->_size; i++)
                        _alloc.construct(&(tmp[i]), _array[i]);
                    this->~vector();
                    this->_array = tmp;
                    this->_max_size = n;
                }
            }
    // -----------------------------Element Access-----------------------------
            reference   operator[](size_type n) {
                return this->_array[n];
            }
            reference   operator[](size_type n) const {
                return this->_array[n];
            }
            reference   at(size_type n) {
                if (n >= this->_size)
                    throw std::out_of_range("out of range");
                return this->_array[n];
            }
            reference   at(size_type n) const {
                if (n >= this->_size)
                    throw std::out_of_range("out of range");
                return this->_array[n];
            }
            reference   front() {
                return this->_array[0];
            }
            reference   front() const {
                return this->_array[0];
            }
            reference   back()  {
                return this->_array[this->_size - 1];
            }
            reference   back() const    {
                return this->_array[this->_size - 1];
            }
    // -----------------------------Modifiers-----------------------------
            void clear() {
                while (this->_size)
                    pop_back();
            }
            template <class InputIterator>
            void    assign(InputIterator first, InputIterator last, 
                    typename std::enable_if<!std::is_integral<InputIterator>::value >::type* = 0) {
                clear();
                while (first != last)  {
                    push_back(*first);
                    ++first;
                }
            }
            void    assign(size_type n, const   T& val)    {
                clear();
                while (n)   {
                    push_back(val);
                    --n;
                }
            }
            
            void    push_back(const T& val) {
                if ((_size + 1) > _max_size)
                    reserve(_size + 1);
                _array[_size] = val;
                _size++;
            }

            void    pop_back()  {
                this->_size--;
                if (_size == 0) {
                    _alloc.deallocate(_array, _max_size);
                    this->_array =  _alloc.allocate(_max_size);
                }
            }

                iterator    insert(iterator position, const T& val)   {
                    difference_type index = position - begin();
                    insert (position, 1, val);
                    return iterator(&this->_array[index]);
            }

            void    insert (iterator position, size_type n, const T& val) {
                vector tmp(position, end());
                    this->_size -= tmp.size();
                while(n) {
                        push_back(val);
                        n--;
                }
                for (iterator it = tmp.begin(); it != tmp.end(); it++) {
                        push_back(*it);
                }
                tmp.~vector();
            }
            
            template <class InputIterator>
            void    insert (iterator position, InputIterator first, InputIterator last,
                typename std::enable_if<!std::is_integral<InputIterator>::value >::type* = 0) {
                vector tmp(position, end());
                this->_size -= tmp.size();
                while (first != last) {
                    push_back(*first);
                    ++first;
                }
                for (iterator it = tmp.begin(); it != tmp.end(); it++)
                    push_back(it);
                tmp->~vector();
                }
            iterator erase(iterator position) {
                iterator out(position);
                while (position != end()) 
                    *position = *(++position);
                --this->_size;
                return out;
            }
            iterator erase(iterator first, iterator last) {
                iterator out (last);
                int      minus = 0;
                while (last != end()) {
                    *first++ = *last++;
                    minus++;
                }
                this->_size -= minus;
                return out;
            }
            void swap (vector& x) {
                vector tmp(x);
                x = *this;
                *this = tmp;
            }
    }; // class vector
    // -----------------------------non-member function overloads-----------------------------
    template <class T, class Alloc>
        bool operator == (const vector<T, Alloc>& first, const vector<T,Alloc>& second) {
            return (first.size() == second.size() && ft::equal(first.begin(), first.end(), second.begin(), second.end()));
        }

    template <class T, class Alloc>
        bool operator != (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (!(first == second));
        }
    
    template <class T, class Alloc>
        bool operator < (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return ft::smallerthan(first.begin(), first.end(), second.begin(), second.end());
        }

    template <class T, class Alloc>
        bool operator<= (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (!(second < first));
        }
    template <class T, class Alloc>
        bool operator > (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (second < first);
        }
    template <class T, class Alloc>
        bool operator>= (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (!(first < second));
        }
    template <class T, class Alloc>
        void swap (vector<T, Alloc>& first, vector<T, Alloc>& second) {
            vector<T, Alloc> tmp(first);
            first = second;
            second = tmp;
        }
}

#endif