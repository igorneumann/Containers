/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:40:48 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/08 18:32:23 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <string>
#include <iterator>

namespace ft
{
    class vector
    {
        public:
            vector();
            ~vector(void);
            vector & operator = (const vector &vector);

        private:
            size_type           size;
            size_type           max_size;
            pointer             value;
    }
}

#endif