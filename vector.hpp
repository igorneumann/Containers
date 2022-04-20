/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:40:48 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/20 19:48:13 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <string>
#include <iterator>
#include <stdexcept>
#include <cmath>
#include "vector-utils.hpp"

namespace ft
{
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
        typedef syze_t                                      size_type;
        typedef long int                                    difference_type;
        typedef RandomAccessIterator<T, T*, T&>             iterator;
        typedef RandomAccessIterator<T, const T*, const T&> const_iterator; 
        typedef ReverseRAI<iterator>                        reverse_iterator;
        typedef ReverseRAI<const_iterator>                  const_reverse_iterator;

    // -----------------------------Constructors destructor & copy-----------------------------
            explicit vector( const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(0), _max_size(0) {
            }

            explicit vector( size_type n, const value_type& cal = value_type(), const allocator_type& alloc = allocator_type() ) : _alloc(alloc), _size(n), _max_size(n) {
                _array = new value_type[n]();
                for (size_type i = 0; i < n; i++)
                    _array[i] = val;
            }
            template <typename InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : size(0), _alloc(alloc){
                    
                    InputIterator tmp(first);
                    while (tmp++ != last)
                        _size++;
                    _max_size = _size;
                    _array = _alloc.allocate(_max_size);
                    for (int i = 0; first != last; ++first, ++i)
                        _array[i] = *first;
            }
            explicit vector( const vector& x ) : _alloc(x._alloc), _size(0), _max_size(0), _array(0) {
                *this = x;
            }
            vector &operator=(const vector & x) {
                delete[] _array;
                _array = new value_type[x._max_size];
                _max_size = x._max_size;
                _size = 0;
                assign(x.begin(), x.end());
			    return *this;
            }
            ~vector( void )   {
                delete[] _array;
            }
    // -----------------------------Iterators-----------------------------
			iterator	begin(void)	    {
				return iterator(_array);
			}
			iterator	end(void)       {
				return iterator(_array + _size);
			}
			const_iterator	begin(void)	{
				return const_iterator(_array);
			}
			const_iterator	end(void)	{
				return const_iterator(_array + _size);
			}
            reverse_iterator rbegin()   {
                return reverse_iterator(_array + _size - 1);
            }
            reverse_iterator rend()      {
                return reverse_iterator(_array - 1);
            }
            const_reverse_iterator rbegin()   {
                return const_reverse_iterator(_array + _size - 1);
            }
            const_reverse_iterator rend()       {
                return const_reverse_iterator(_array - 1);
            }
    // -----------------------------Capacity-----------------------------
            size_type  size() const {
                return _size;
            }
            size_type   max_size() const {
                return _alloc.max_size();
            }
            void        resize( size_type n, value_type val = value_type() ) {
                if (n > _max_size)
                    reserve(n);
                while (n > _size)
                    push_back(val);
                while (n < _size)
                    pop_back();
            }
            size_type   capacity() const    {
                return: _max_size;
            }
            size_type   empty() const   {
                return (!(_size))
            }
            void    reserve(size_type n) {
                if (n <= _max_size)
                    return ;
                n = ft::max(n, this->_max_size * 2);
                pointer tmp = new value_type[n];
                for (size_type i = 0; i < _size; i++)
                    tmp[i] = _array[i];
                this->~vector();
                _array = tmp;
                _max_size = n;
            }
    // -----------------------------Element Access-----------------------------
            reference   operator[](size_type n) {
                return _array[n];
            }
            reference   operator[](size_type n) const {
                return _array[n];
            }
            reference   at(size_type n) {
                if (n >= _size)
                    throw std::out_of_range("out of range");
                return _array[n];
            }
            reference   at(size_type n) const {
                if (n >= _size)
                    throw std::out_of_range("out of range");
                return _array[n];
            }
            reference   front() {
                return _array[0];
            }
            reference   front() const {
                return _array[0];
            }
            reference   back()  {
                return _array[_size - 1];
            }
            reference   back() const    {
                return _array[_size - 1];
            }
    // -----------------------------Modifiers-----------------------------
            template <class InputIterator>
            void    assign(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) {
                clear();
                if (first != last)  {
                    push_back(*first);
                    ++first;
                }
            }
            void    assign(size_type n, const   value_type& val)    {
                clear();
                while (n)   {
                    push_back(val);
                    --n;
                }
            }
            void    push_back(const value_type& val) {
                if (_size == 0)
                    reserve(1);
                else
                    reserve(_max_size * 2);
                _array[_size] = val;
                _size++;
            }
            void    pop_back()  {
                _size--;
            }
                iterator    insert(iterator position, const value_type& val)   {
                    difference_type index = position - begin();
                    insert (position, 1, val);
                    return iterator(&_array[index]);
            }
            void    insert (iterator position, size_type n, const value_type& val) {
                vector tmp(position, end());
                    _size -= tmp.size();
                while(n) {
                        push_back(val);
                        n--;
                }
                for (iterator it = tmp.begin(); it != tmp.end(); it++) {
                        push_back(*it);
                }
                tmp->~vector();
            }
            template <class InputIterator>
            void    insert (iterator position, InputIterator first, InputIterator last
                typename ft::check_type<typename ft::iterator_traits<InputIterator>::iterator_category>::type* = 0) {
                vector tmp(position, end());
                _size -= tmp.size();
                while (first != last) {
                    push_back(*first);
                    ++first;
                }
                for (iterator it = tmp.begin(); it != tmp.end(); it++)
                    push_back(*it);
                tmp->~vector();
                }
            }
            iterator erase(iterator position) {
                iterator out(position);
                while (position != end() - 1)
                    position = *(++position);
                --_size;
                return out;
            }
            iterator erase(iterator first, iterator last) {
                iterator out (last);
                int      minus = 0;
                while (last != end()) {
                    *first++ = *last++;
                    minus++;
                }
                _size -= minus;
                return out;
            }
            void swap (vector& x) {
                vector tmp(x);
                x = *this;
                *this = tmp;
            }
            void clear() {
                while (_size)
                    pop_back();
            }
    // -----------------------------variables-----------------------------
        private:
            allocator_type	    _alloc;
            size_type           _size;
            size_type           _max_size;
            pointer             _array;
   
    }; // class vector
    // -----------------------------non-member function overloads-----------------------------
    template <class T, class Alloc>
        bool operator == (const vector<T, Alloc>& first, const vector<T,Alloc>& second) {
            return (first.size() == second.size() && ft::equal(first.begin(), first.end(), second.end()));
        }

    template <class T, class Alloc>
        bool operator != (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (!(first == second));
        }
    
    template <class T, class Alloc>
        bool operator < (cont vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return ft:smallerthan(first.begin(), first.end(), second.begin(), rhx.end());
        }

    template <class T, class Alloc>
        bool operator<= (const vector<T, Alloc>& first, const vector<T, Alloc>& second) {
            return (!(second < first));
        }
    template <class T, class Alloc>
        bool operator > (cont vector<T, Alloc>& first, const vector<T, Alloc>& second) {
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