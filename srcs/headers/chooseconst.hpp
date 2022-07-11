/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooseconst.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:02:48 by ineumann          #+#    #+#             */
/*   Updated: 2022/07/11 18:07:36 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHOOSECONST_HPP
#define CHOOSECONST_HPP

namespace ft {
// Use a boolean to typedef either type 1 or type 2.
template <bool isConst, typename isFalse, typename isTrue>
struct chooseConst {};

//Typedef: pointer, ref...
template <typename isFalse, typename isTrue>
struct chooseConst<false, isFalse, isTrue> {
    typedef isFalse type;
};

//Typedef: const pointer, const ref...
template <typename isFalse, typename isTrue>
struct chooseConst<true, isFalse, isTrue> {
    typedef isTrue type;
};
}

#endif