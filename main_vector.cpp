/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:09 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/27 19:44:12 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp" 

template <typename T>
void print_content(ft::vector<T> &vec) {
    std::cout << "Container contains:";
    if (vec.begin() != vec.end())  {
        std::cout << *it;
        for (ft::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it)
            std::cout << *it << ", ";
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty!" << std::endl;
}

template <typename T>
void rev_print_content(ft::vector<T> &vec) {
    std::cout << "Container contains (in reverse order):";
    if (vec.rbegin != vec.rend)  {
        std::cout << *it;
        for(ft::vector<T>:: iterator it = vec.rbegin(); it != vec.rend(); ++it)
            std::cout << *it << ", ";
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty, even in reverse!" << std::endl;
}

int main(int argc, char **argv) {
    if !(stl_test())
        std::cout << "failed on STL tests"
    if !(constructor_test())
        std::cout << "failed on constructor tests"
    if !(iterators_test())
        std::cout << "failed on iterators tests"
    if !(capacity_test())
        std::cout << "failed on capacity tests"
    if !(element_access_test())
        std::cout << "failed on element access tests"
    if !(modifiers_test())
        std::cout << "failed on modifiers tests"
    if !(rel_operators_test())
        std::cout << "failed on relational operators tests"
    return 0;
}