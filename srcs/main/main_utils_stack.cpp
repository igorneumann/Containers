/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_stack.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:56:08 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 19:04:35 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main_stack.hpp" 

typedef ft::stack<int>     ftst;
typedef std::stack<int>    stdst;

template < typename T>
void print_destroy_content(T &stk) {
    std::cout << "Container contents: ";
    if (!stk.empty())  {
        std::cout << stk.top();
        stk.pop();
        while (!stk.empty()) {
            std::cout << ", " << stk.top();
            stk.pop();
        }
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty!" << std::endl;
}

template < typename T, typename T2>
bool compare_destroy_content(T &stk, T2 &cpy) {
    while(!stk.empty()) {
        if (stk.top() != cpy.top())
            return 1;
        stk.pop();
        cpy.pop();
    }
    if (stk.empty())
        return 0;
    else
        return 1;
}

template < typename T, typename T2>
bool is_equal(T &cnt, T2 &cpy, std::string str) {
    if (compare_destroy_content(cnt, cpy))  {
        std::cout << str << std::endl;
        std::cout << "ERROR: CONTAINERS ARE DIFFERENT" << std::endl;
        print_destroy_content(cnt);
        print_destroy_content(cpy);
        return 0;
    }
    else {
        std::cout << str << std::endl;
        std::cout << "CONTAINERS HAD THE SAME CONTENT" << std::endl;
    }
    return 1;
}