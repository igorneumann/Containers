/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector-utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:18:38 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/05 20:30:14 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_HPP
# define VECTOR_UTILS_HPP

namespace ft {
	template <class Iterator1, class Iterator2>
    bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return (first2 == last2);
    }

	template <class Iterator1, class Iterator2>
    bool smallerthan(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
}

#endif