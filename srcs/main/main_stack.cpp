/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:43:44 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 18:00:40 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main_stack.hpp" 
#include "main_tests_stack.cpp" 
#include "main_utils_stack.cpp" 

typedef ft::stack<int>      ftst;
typedef std::stack<int>     stdst;

int main(void) {

    ftst    ftstk;
    ftst    ftstk2(ftstk);
    stdst   stdstk;
    stdst   stdstk2(stdstk);

    srand(time(NULL));

    if (!constructor_test(ftstk, stdstk, ftstk2, stdstk2))
        std::cout << "failed on constructor tests" << std::endl;
    else
        std::cout << "constructor tests: OK" << std::endl;\
    if (!capacity_test(ftstk))
        std::cout << "failed on capacity tests" << std::endl;
    else
        std::cout << "Capacity tests: OK" << std::endl;
    if (!element_access_test(ftstk))
        std::cout << "failed on element access tests" << std::endl;
    else
        std::cout << "element access tests: OK" << std::endl;
    if (!rel_operators_test(ftstk))
        std::cout << "failed on relational operators tests" << std::endl;
    else
        std::cout << "Relational operators tests: OK" << std::endl;
    if (!modifiers_test(ftstk))
        std::cout << "failed on modifiers tests" << std::endl;
    else
        std::cout << "modifiers tests: OK" << std::endl;
    system("leaks a.out");
    return 0;
}