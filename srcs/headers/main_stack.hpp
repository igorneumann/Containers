/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:10:00 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 17:59:10 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_STACK_HPP
# define MAIN_STACK_HPP

#include "stack.hpp" 
#include <string>
#include <stack>
#include <sys/time.h>
#include <stdlib.h> 

template < typename T>
void print_destroy_content(T &vec);

template < typename T, typename T2 >
bool compare_destroy_content(T &vec, T2 &cpy);

template < typename T, typename T2 >
bool is_equal(T &cnt, T2 &cpy, std::string str);

template < typename T, typename T2 >
bool constructor_test(T &cnt, T2 &cpy, T &fill, T2 &fillcpy);

template < typename T>
bool element_access_test(T &elem);

template < typename T>
bool rel_operators_test(T rel);

template < typename T>
bool modifiers_test(T &modt);

#endif