/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseRAI.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:41:31 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/27 18:40:30 by ineumann         ###   ########.fr       */
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
    ReverseBI(const ReverseBI& x) : current(x.current) { }
    template<typename Iter>
    ReverseBI(const ReverseBI<Iter>& x) : current(x.base()) { } //.base() returns the underlying iterator
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
        ++(*this);
        return out;
    }

    ReverseBI& operator--() {
        ++current;
        return *this;
    }

    ReverseBI operator--(int) {
        ReverseBI   out(*this);
        --(*this);
        return out;
    }

    inline bool operator==(const ReverseBI& x) const    {
        return (x.base == this->base);
    }

    inline bool operator !=(const ReverseBI& x) const    {
        return !(x.base == this->base);
    }

    inline bool operator<(const ReverseBI& x) const    {
        return (x.base > this->base);
    }

    inline bool operator>(const ReverseBI& x) const    {
        return (x.base < this->base);
    }

    inline bool operator<=(const ReverseBI& x) const    {
        return !(x.base < this->base);
    }

    inline bool operator>=(const ReverseBI& x) const    {
        return !(x.base > this->base);
    }
};

template <class Iterator>
class ReverseRAI : public ReverseBI<Iterator> {
    public:
        typedef ReverseBI<Iterator> Base;
        typedef Iterator iterator_type;
        using typename Base::pointer;
        using typename Base::reference;
        using typename Base::size_type;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        ReverseRAI() : Base() { }
        ReverseRAI(const iterator_type& x) : Base(x) { }
        ReverseRAI(const ReverseRAI& x) : Base(x.current) { }
        template<typename Iter>
        ReverseRAI(const ReverseBI<Iter>& x) : Base(x.base()) { } //.base() returns the underlying iterator
        ~ReverseRAI() { }

        ReverseRAI operator=(const ReverseRAI& x) {
            Iterator::operator=(x);
            return *this;
        }
        ReverseRAI operator+(difference_type n) const {
            return ReverseRAI(this->current - n);
        }
        ReverseRAI& operator+=(difference_type n) {
            this->current -= n;
            return *this;
        }
        ReverseRAI operator-(difference_type n) const {
            return ReverseRAI(this->current + n);
        }
        ReverseRAI operator-=(difference_type n) {
            this->currennt += n;
            return *this;
        }
        reference   operator[](difference_type n) {
            return *(*this + n);
        }
};

template <class Iterator>
inline typename ReverseRAI<Iterator>::difference_type operator-(const ReverseRAI<Iterator>& lhs, const ReverseRAI<Iterator>& rhs) {
    return (lhs.base() - rhs.base());
}

template <class IteratorL, class IteratorR>
inline typename ReverseRAI<IteratorL>::difference_type operator-(const ReverseRAI<IteratorL>& lhs, const ReverseRAI<IteratorR>& rhs) {
    return (lhs.base() - rhs.base());
}

template <class Iterator>
inline ReverseRAI<Iterator> operator+(typename ReverseRAI<Iterator>::difference_type n, const ReverseRAI<Iterator>& x) {
    return ReverseRAI<Iterator>(x.base() - n);
}

#endif