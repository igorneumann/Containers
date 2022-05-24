/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests_stack.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:09:07 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/24 17:51:54 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_stack.hpp" 

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
bool iterators_test(T &ittest) {
    int i = 0;
    for (int i = 0; i < 20; i++) {
        ittest.push(i * 7);
    }
    typename T::iterator it = ittest.begin();
    typename T::iterator ite = ittest.end();
    typename T::const_iterator cit = ittest.begin();
    typename T::const_iterator cite = ittest.end();
    typename T::iterator it5 = it + 5;
    typename T::iterator it10 = it + 10;
	std::cout << "Regular iterators: ";
    if (it != cit || ite != cite || it == it5 || it == it10 || it5 == it10) {
        std::cout << "equality error" << std::endl;
        return 0;
    }
    else if (it < cit || ite > cite || it < cit || ite < cite || it >= it5 || it5 <= it || it >= it10 || it5 >= it10) {
        std::cout << "> / < error" << std::endl;
        return 0;
    }
    i = 0;
    while (it != it5) {
        i++;
        it++;
    }
    if (i != 5) {
        std::cout << "++ error: " << i << " should be 5" << std::endl;
        return 0;
    }
    while (it != it10) {
        i++;
        it++;
    }
    if (i != 10) {
        std::cout << "++ error: " << i << " should be 5" << std::endl;
        return 0;
    } 
    while (i-- > 0)
        it--;
    if (it != cit) {
        std::cout << "-- error: " << i << " should be equal to constant" << std::endl;
        return 0;
    } 
    else
	    std::cout << "OK" << std::endl;
    return 1;
}

template < typename T>
bool reverse_iterators_test(T &ittest) {
    for (int i = 0; i < 20; i++) {
        ittest.push(i * 7);
    }
    typename T::reverse_iterator rit = ittest.rbegin();
    typename T::reverse_iterator rite = ittest.rend();
    typename T::const_reverse_iterator crit = ittest.rbegin();
    typename T::const_reverse_iterator crite = ittest.rend();
    typename T::reverse_iterator rit5 = rit + 5;
    typename T::reverse_iterator rit10 = rit + 10;
    if (rit != crit || rite != crite || rit == rit5 || rit == rit10 || rit5 == rit10) {
        std::cout << "equality error" << std::endl;
       return 0;
    }
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
    if (test.max_size() <= 20){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    if (test.capacity() <= 20){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    if (test.size() != 20){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    test.resize(50);
    if (test.size() != 50){
        std::cout << "Resize capacity test error" << std::endl;
    return 0;
    }
    test.reserve(150);
    if (test.capacity() < 150){
        std::cout << "Reserve capacity test error" << std::endl;
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
        if (elem.top() != celem.top()) {
            std::cout << "Constant element access error" << std::endl;      
            return 0;
        }
        else if (elem.top() != ((i + 1) * 7)) {
            std::cout << "Element access error " << elem.at(i) << "Should be:" << ((i + 1) * 7) << std::endl;      
            return 0;
        }
    }
    return 1;
}

template < typename T>
bool modifiers_test(T &modt, T &modcpy) {
    int j = 50;

    modt.assign(j, 42);
    for (int i = 0; i < j; i++)
        if (modt[i] != 42)
            std::cout << "assign modifier error" << std::endl;
    for (int i = 0; i < 20; i++)
    {
        modt.push(i);
        if (modt.back() != i) {
            std::cout << "push error" << std::endl;
            return 0;
        }
        j++;
        if ((modt.size()) != (unsigned long)j) {
            std::cout << "push_whatever error, J is: " << j << ", Size is: " << modt.size() << std::endl;
            return 0;
        }
    }
    for (int i = 0; i < 20; i++) {
        modt.pop_back();
        j--;
        if ((modt.size()) != (unsigned long)j) {
            std::cout << "pop_back error, J is: " << j << ", Size is: " << modt.size() << std::endl;
        return 0;
        }

    }
    modt.insert((modt.begin() + 10), 20, 69);
    for (int i = 10; i < 20 ; i++)
        if (modt[i] != 69)
            std::cout << "Insert error" << std::endl;
    j += 20;
    if (modt.size() != (unsigned long)j)
        std::cout << "Insert size error" << std::endl;
    for (int i = 0; i < 20; i++, j--)
        modt.erase(modt.end());
    if (modt.size() != (unsigned long)j)
        std::cout << "Erase size error" << std::endl;
    modt.clear(); 
    if (!modt.empty())
        std::cout << "Clear error" << std::endl;
    modt.assign(2, 42);
    modcpy.assign(2, 69);
    modt.swap(modcpy);
    if (modt[0] != 69 || modcpy[0] != 42)
        std::cout << "Swap error" << std::endl;
    return 1;
}

template < typename T>
bool rel_operators_test(T rel, T relcpy) {

    rel.assign(10, 42);
    relcpy.assign(10, 42);
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