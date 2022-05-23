/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:10:00 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/23 19:45:52 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

#include "vector.hpp" 
#include "stack.hpp" 
#include <string>
#include <vector>
#include <stack>
#include <sys/time.h>
#include <stdlib.h> 

template < typename T>
void print_content(T &vec);

template < typename T, typename T2 >
bool compare_content(T &vec, T2 &cpy);

template < typename T, typename T2 >
bool is_equal(T &cnt, T2 &cpy, std::string str);

template < typename T, typename T2 >
bool stl_test(T &ftv, T2 &stdv);

template < typename T, typename T2 >
bool constructor_test(T &cnt, T2 &cpy, T &fill, T2 &fillcpy);

#endif