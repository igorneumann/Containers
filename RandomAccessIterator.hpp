/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:15:12 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/03 19:50:55 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

# include <memory>
# include <cstddef>

namespace ft {
    template < typename T, typename Pointer, typename Reference, class Category = std::random_access_iterator_tag >
    class RandomAccessIterator {

        public:
            typedef RandomAccessIterator<T, Pointer, Reference> this_type;
            typedef RandomAccessIterator<T, T*, T&>             iterator;
            typedef RandomAccessIterator<T, const T*, const T&> const_iterator;
            typedef T                                           value_type;
            typedef Pointer                                     pointer;
            typedef Reference                                   reference;
            typedef size_t                                      size_type;
            typedef ptrdiff_t                                   difference_type;
            typedef Category                                    iterator_category;
            template <class T2, class A>                        friend class vector;
            pointer                                             array;

        public:
            RandomAccessIterator(): array(NULL) { }
            RandomAccessIterator(const pointer elem) : array(elem) { }
            RandomAccessIterator(const iterator& x) : array(const_cast<pointer>(x.array)) { }
            virtual ~RandomAccessIterator() {}

            this_type&  operator=(const iterator& x) {
                this->array = x.array;
                return *this;
            }

            this_type   operator++(int) {
                this_type   out(*this);
                this->array++;
                return out;
            }

            this_type&  operator++() {
                this->array++;
                return *this;
            }

            this_type   operator+(difference_type n) const {
                this_type out(*this);
                out.array += n;
                return out;
            }

            this_type&   operator+=(difference_type n) {
                this->array += n;
                return *this;
            }

            this_type   operator--(int) {
                this_type out(*this);
                this->array--;
                return out;
            }

            this_type&  operator--() {
                --this->array;
                return *this;
            }

            difference_type  operator-(RandomAccessIterator it) const {
                return this->array - it.array;
            }

            this_type   operator-(difference_type n) const {
                this_type out(*this);
                out -= n;
                return out;
            }

            this_type& operator -=(difference_type n) {
                this->array -= n;
                return *this;
            }

            reference operator*() {
                return *this->array;
            }

            pointer operator->() {
                return *(&(this->array));
            }

            template<typename T2, typename P, typename R, class C>
            inline bool operator==(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return(this->array == rhs.array);
            }

            template<typename T2, typename P, typename R, class C>
            inline bool operator!=(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return !(this->array == rhs.array);
            }

            template<typename T2, typename P, typename R, class C>
            inline bool operator<(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return (this->array < rhs.array);
            }

            template<typename T2, typename P, typename R, class C>
            inline bool operator>(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return (this->array > rhs.array);
            }

            template<typename T2, typename P, typename R, class C>
            inline bool  operator<=(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return !(this->array > rhs.array);
            }

            template<typename T2, typename P, typename R, class C>
            inline bool operator>=(const RandomAccessIterator<T2, P, R, C>& rhs) const {
                return !(this->array < rhs.array);
            }

            reference operator[](difference_type n) {
                return(*(this->array + n));
            }
    };
template <typename T, typename P, typename R, typename C>
inline RandomAccessIterator<T,P,R,C> operator+(typename RandomAccessIterator<T, P, R, C>::difference_type n, const RandomAccessIterator<T, P, R, C>& x) {
    return x + n;
}
}

#endif