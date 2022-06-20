/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:09 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 18:00:18 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main_vector.hpp" 
#include "main_tests_vector.cpp" 
#include "main_utils_vector.cpp" 

typedef ft::vector<int>     ftvec;
typedef std::vector<int>    stdvec;

int main(void) {
    
    int i = 10;
    ftvec ftv;
    ftvec ftv2;
    ftvec ftv42(i, 42);
    stdvec stdv;
    stdvec stdv42(i, 42);

    srand(time(NULL));

    if (!constructor_test(ftv, stdv, ftv42, stdv42))
        std::cout << "failed on constructor tests" << std::endl;
    else
        std::cout << "constructor tests: OK" << std::endl;

    if (!stl_test(ftv, stdv))
        std::cout << "failed on STL tests" << std::endl;
    else
        std::cout << "STL tests: OK" << std::endl;

    if (!iterators_test(ftv))
        std::cout << "failed on iterators tests" << std::endl;
    else
        std::cout << "iterators tests: OK" << std::endl;

    if (!reverse_iterators_test(ftv))
        std::cout << "failed on reverse iterators tests" << std::endl;
    else
        std::cout << "reverse iterators tests: OK" << std::endl;

    if (!capacity_test(ftv))
        std::cout << "failed on capacity tests" << std::endl;
    else
        std::cout << "Capacity tests: OK" << std::endl;

    if (!element_access_test(ftv))
        std::cout << "failed on element access tests" << std::endl;
    else
        std::cout << "element access tests: OK" << std::endl;

    if (!modifiers_test(ftv, ftv2))
        std::cout << "failed on modifiers tests" << std::endl;
    else
        std::cout << "modifiers tests: OK" << std::endl;

    if (!rel_operators_test(ftv, ftv2))
        std::cout << "failed on relational operators tests" << std::endl;
    else
        std::cout << "Relational operators tests: OK" << std::endl;

    system("leaks a.out");
    return 0;
}