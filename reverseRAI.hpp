/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseRAI.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:41:31 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/22 20:00:01 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSERAI_HPP
# define REVERSERAI_HPP

template <class Iterator>
class ReverseBI
{
protected:
    Iterator    current;
public:
    typedef Iterator                                iterator_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
    typedef typename Iterator::size_type            size_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::iterator_category    iterator_category;

    ReverseBI() : current() { }
    ReverseBI(const iterator_type& x) : current(x) { }
    ReverseBI(const ReverseBI& x) : current.(x.current) { }
    template<typename Iter>
    ReverseBI(const ReverseBI<iter>& x) : current(x.base()) { } //.base() returns the underlying iterator
    ~ReverseBI() { }

    ReverseBI& operator=(const ReverseBI& x) {
        Iterator::operator=(x);
        return *this;
    }

    iterator_type base() const {
        return this->current;
    }

    reference operator*() {
        return *current;
    }

    pointer operator->() {
        return &operator*();
    }

    ReverseBI& operator++() {
        --current;
        return *this;
    }

    ReverseBI operator++(int) {
        ReverseBI   out(*this);
        --current;
        return out;
    }
};

#endif