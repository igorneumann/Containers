/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests_stack.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:09:07 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 19:04:40 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main_stack.hpp" 

typedef ft::stack<int>      ftst;
typedef std::stack<int>     stdst;

template < typename T, typename T2 >
bool constructor_test(T &cnt, T2 &cpy, T &fill, T2 &fillcpy) {
    if (!is_equal(cnt, cpy, "DEFAULT CONSTRUCTOR:"))
        return 0;
    for (int i = 0; i < 20; i++) {
        fill.push(i);
        fillcpy.push(i);
    }
    if (!is_equal(fill, fillcpy, "FILL CONSTRUCTOR:"))
        return 0;
    for (int i = 0; i < 20; i++) {
        fill.push(i);
        fillcpy.push(i);
    }
    T copy(fill);
    T2 copycopy(fillcpy);
    if (!is_equal(copy, copycopy, "COPY CONSTRUCTOR:"))
        return 0;
    for (int i = 0; i < 20; i++) {
        fill.push(i);
        fillcpy.push(i);
    }
    copy = fill;
    copycopy = fillcpy;
    if (!is_equal(copy, copycopy, "ASSIGNATION OPERATOR:"))
        return 0;
    return 1;
}

template < typename T>
bool capacity_test(T &test) {
    
    if (!test.empty()){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    for (int i = 0; i < 20; i++)
        test.push(i * 7);
    if (test.empty()){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    if (test.size() != 20){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    return 1;
}

template < typename T>
bool element_access_test(T &elem) {

    for (int i = 1; i <= 20; i++)
        elem.push(i * 7);
    const ftst celem(elem);
    for (int i = 19; i > 0; i--) {
        if (i == 19 && elem.top() != celem.top()) {
            std::cout << "Constant element access error" << std::endl;      
            return 0;
        }
        else if (elem.top() != ((i + 1) * 7)) {
            std::cout << "Element access error " << elem.top() << "Should be:" << ((i + 1) * 7) << std::endl;      
            return 0;
        }
        elem.pop();
    }
    return 1;
}

template < typename T>
bool modifiers_test(T &modt) {
    int j = 20;

    while(modt.size())
        modt.pop();
    for (int i = 1; i <= 20; i++)
    {
        modt.push(i);
        if (modt.top() != i) {
            std::cout << "push error" << std::endl;
            return 0;
        }
        if ((modt.size()) != (unsigned long)i) {
            std::cout << "push_whatever error, J is: " << i << ", Size is: " << modt.size() << std::endl;
            return 0;
        }
    }
    for (int i = 0; i < 20; i++) {
        modt.pop();
        j--;
        if ((modt.size()) != (unsigned long)j) {
            std::cout << "pop error, J is: " << j << ", Size is: " << modt.size() << std::endl;
        return 0;
        }

    }
    return 1;
}

template < typename T>
bool rel_operators_test(T rel) {

    ftst    relcpy(rel);

    if (rel != relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    relcpy.push(5);
       if (rel == relcpy || rel > relcpy || !(rel < relcpy) || rel >= relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    rel.push(10);
    if (rel == relcpy || rel < relcpy || !(rel > relcpy) || rel <= relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    return 1;
}