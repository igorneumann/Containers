/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:43:44 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/24 19:55:10 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_stack.hpp" 
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
        std::cout << "constructor tests: OK" << std::endl;

    system("leaks a.out");
    return 0;
}