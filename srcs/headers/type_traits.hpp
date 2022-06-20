/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igorneumann <igorneumann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:48:35 by igorneumann       #+#    #+#             */
/*   Updated: 2022/06/02 12:33:28 by igorneumann      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_H
# define TYPE_TRAITS_H

#include <clocale>

namespace ft
{
    template <bool C, typename T = void>
    struct enable_if
    {
    };

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
        int tonti;
    };

    template<typename T, T val>
    struct integral_constant
    {
            typedef integral_constant<T, val>   type;
            typedef T                           value_type;
            static const T                      value = val;
            operator                            value_type(void) {
                return (this->value);
            }
    };

    struct true_type : public ft::integral_constant<bool, true>
    {
            typedef true_type                  type;
    };

    struct false_type : public ft::integral_constant<bool, false>
    {
            typedef false_type                 type;
    };

    //Is_integral implemantation

    //Generic answer for unrecognized types
    template<typename T>
    struct is_integral : public false_type {};

    //recognized types
    template<>
    struct is_integral<bool> :public true_type {};
    template<>
    struct is_integral<char> :public true_type {};
    template<>
    struct is_integral<wchar_t> :public true_type {};
    template<>
    struct is_integral<signed char> :public true_type {};
    template<>
    struct is_integral<short int> :public true_type {};
    template<>
    struct is_integral<int> :public true_type {};
    template<>
    struct is_integral<long int> :public true_type {};
    template<>
    struct is_integral<long long int> :public true_type {};
    template<>
    struct is_integral<unsigned char> :public true_type {};
    template<>
    struct is_integral<unsigned short int> :public true_type {};
    template<>
    struct is_integral<unsigned int> :public true_type {};
    template<>
    struct is_integral<unsigned long int> :public true_type {};
    template<>
    struct is_integral<unsigned long long int> :public true_type {};
    
    //Has_iterator_category check

    template<typename T>
    struct has_iterator_category {
        typedef char yes[1];
        typedef char no[2];

        template<typename C>
        static yes & test(typename C::iterator_category *);

        template<typename C>
        static no & test(...);

        static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
    };

    template<typename T>
    struct has_iterator {
        typedef char yes[1];
        typedef char no[2];

        template<typename C>
        static yes & test(typename C::iterator *);

        template<typename C>
        static no & test (...);

        static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
    };

    template<typename T>
    typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i)
    {
        return (bool (i%2));
    };

    template<typename T>
    struct st_remove_reference
    {
        typedef T type;
    };

    template<typename T>
    struct st_remove_reference<T&>
    {
        typedef T type;
    };

    template <typename T>
    typename st_remove_reference<T>::type & move(T & arg)
    {
        return (static_cast<typename st_remove_reference<T>::type & >(arg));
    };
};

#endif