/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:09 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/05 20:34:35 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp" 
#include <sys/time.h>
#include <string>
#include <vector>
#include <stdlib.h> // for system()

typedef ft::vector<int>     ftvec;
typedef std::vector<int>    stdvec;

template < typename T>
void print_content(ft::vector<T> &vec) {
    std::cout << "Container contains: ";
    if (vec.begin() != vec.end())  {
        std::cout << *vec.begin();
        for (ftvec::iterator it = (vec.begin() + 1); it != vec.end(); ++it)
            std::cout << ", " << *it;
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty!" << std::endl;
}

template < typename T>
void print_content(std::vector<T> &vec) {
    std::cout << "Container contains: ";
    if (vec.begin() != vec.end())  {
        std::cout << *vec.begin();
        for (stdvec::iterator it = (vec.begin() + 1); it != vec.end(); ++it)
            std::cout << ", " << *it ;
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty!" << std::endl;
}

template < typename T>
void rev_print_content(ft::vector<T> &vec) {
    std::cout << "Container contains (in reverse order):";
    if (vec.rbegin != vec.rend)  {
        std::cout << *vec.begin();
        for(ftvec:: iterator it = (vec.rbegin() + 1); it != vec.rend(); ++it)
            std::cout << ", " << *it ;
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty, even in reverse!" << std::endl;
}

template < typename T>
bool compare_content(ft::vector<T> &vec, std::vector<T> &cpy) {
    stdvec::iterator cpit = cpy.begin();
    ftvec::iterator it = vec.begin();
    while(it != vec.end() && cpit != cpy.end()) {
        if (*it != *cpit)
            return 1;
        ++cpit;
        ++it;
    }
    if (it == vec.end() && cpit == cpy.end())
        return 0;
    else
        return 1;
}

bool is_equal(ftvec &cnt, stdvec &cpy, std::string str) {
    if (compare_content(cnt, cpy))  {
        std::cout << str << std::endl;
        std::cout << "ERROR: CONTAINERS ARE DIFFERENT" << std::endl;
        print_content(cnt);
        print_content(cpy);
        return 0;
    }
    else {
        std::cout << str << std::endl;
        std::cout << "CONTAINERS HAVE THE SAME CONTENT" << std::endl;
        print_content(cnt);
    }
    return 1;
}

bool stl_test(void) {
    ftvec ftv;
    stdvec stdv;
    for (int i = 0; i < 20; i++)
        stdv.push_back(i * 7);
    ftv.assign(stdv.begin(), stdv.end());
    if (!is_equal(ftv, stdv, "Assigning items using STL iterators"))
        return 0;
    return 1;
}

bool constructor_test() {
    int i = 10;
    ftvec cnt;
    stdvec cpy;
    if (!is_equal(cnt, cpy, "DEFAULT CONSTRUCTOR:"))
        return 0;
    ftvec fill(i, 42);
    stdvec fillcpy(i, 42);
    for (int i = 0; i < 20; i++) {
        fill.push_back(i);
        fillcpy.push_back(i);
    }
    if (!is_equal(fill, fillcpy, "FILL CONSTRUCTOR:"))
        return 0;
    ftvec range((fill.begin() + 1), (fill.end() - 1 ));
    stdvec cpyrange((fillcpy.begin() + 1), (fillcpy.end() - 1));
    if (!is_equal(range, cpyrange, "RANGE CONSTRUCTOR"))
        return 0;
    ftvec copy(range);
    stdvec copycopy(cpyrange);
    if (!is_equal(copy, copycopy, "COPY CONSTRUCTOR"))
        return 0;
    copy = fill;
    copycopy = fillcpy;
    if (!is_equal(copy, copycopy, "ASSIGNATION OPERATOR"))
        return 0;
    return 1;
}

bool iterators_test() {
    int i = 20;
    ftvec ittest(i, 42);
    for (int i = 0; i < 20; i++) {
        ittest.push_back(i * 7);
    }
    ftvec::iterator it = ittest.begin();
    ftvec::iterator ite = ittest.end();
    ftvec::const_iterator cit = ittest.begin();
    ftvec::const_iterator cite = ittest.end();
    ftvec::iterator it5 = it + 5;
    ftvec::iterator it10 = it + 10;
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

bool reverse_iterators_test() {
    int i = 20;
    ftvec ittest(i, 42);
    for (int i = 0; i < 20; i++) {
        ittest.push_back(i * 7);
    }
    ftvec::reverse_iterator rit = ittest.rbegin();
    ftvec::reverse_iterator rite = ittest.rend();
    ftvec::const_reverse_iterator crit = ittest.rbegin();
    ftvec::const_reverse_iterator crite = ittest.rend();
    ftvec:: reverse_iterator rit5 = rit + 5;
    ftvec:: reverse_iterator rit10 = rit + 10;
    if (rit != crit || rite != crite || rit == rit5 || rit == rit10 || rit5 == rit10) {
        std::cout << "equality error" << std::endl;
       return 0;
    }
    return 1;
}

bool capacity_test() {
    ftvec test;
    
    if (!test.empty()){
        std::cout << "Capacity test error" << std::endl;
        return 0;
    }
    for (int i = 0; i < 20; i++)
        test.push_back(i * 7);
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

bool element_access_test() {
    ftvec elem;

    for (int i = 1; i <= 20; i++)
        elem.push_back(i * 7);
    const ftvec celem(elem);
    for (int i = 19; i > 0; i--) {
        if (elem[i] != celem[i]) {
            std::cout << "Constant element access error" << std::endl;      
            return 0;
        }
        else if (elem[i] != ((i + 1) * 7)) {
            std::cout << "Element access error " << elem.at(i) << "Should be:" << ((i + 1) * 7) << std::endl;      
            return 0;
        }
    }
    if (elem[0] != elem.front() || elem[19] != elem.back()) {
            std::cout << "Front/Back access error " << std::endl;      
            return 0;
        }
    for (int i = 19; i > 0; i--) {
        if (elem.at(i) != celem.at(i)) {
            std::cout << "Constant element access error" << std::endl;      
            return 0;
        }
        else if (elem.at(i) != ((i + 1) * 7)) {
            std::cout << "Element access error " << elem.at(i) << "Should be:" << ((i + 1) * 7) << std::endl;      
            return 0;
        }
        try{
                elem.at(i + 1);
        }
        catch (std::out_of_range& e) {
                std::cout << "Exception threw..." <<  (i + 1) << " is out of range." << std::endl;
        }
    }
    return 1;
}

bool modifiers_test() {
    ftvec modt;
    ftvec modcpy;
    int j = 50;

    modt.assign(j, 42);
    for (int i = 0; i < j; i++)
        if (modt[i] != 42)
            std::cout << "assign modifier error" << std::endl;
    for (int i = 0; i < 20; i++)
    {
        modt.push_back(i);
        if (modt.back() != i) {
            std::cout << "push_back error" << std::endl;
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

bool rel_operators_test() {
    ftvec rel;
    ftvec relcpy;

    rel.assign(10, 42);
    relcpy.assign(10, 42);
    if (rel != relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    relcpy.push_back(5);
    if (rel == relcpy || rel > relcpy || !(rel < relcpy) || rel >= relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    rel.push_back(10);
    if (rel == relcpy || rel < relcpy || !(rel > relcpy) || rel <= relcpy)
        std::cout << "Error on relational operator test" << std::endl;
    return 1;
}

int main(void) {
    srand(time(NULL));

    if (!constructor_test())
        std::cout << "failed on constructor tests" << std::endl;
    else
        std::cout << "constructor tests: OK" << std::endl;

    if (!stl_test())
        std::cout << "failed on STL tests" << std::endl;
    else
        std::cout << "STL tests: OK" << std::endl;

    if (!iterators_test())
        std::cout << "failed on iterators tests" << std::endl;
    else
        std::cout << "iterators tests: OK" << std::endl;

    if (!reverse_iterators_test())
        std::cout << "failed on reverse iterators tests" << std::endl;
    else
        std::cout << "reverse iterators tests: OK" << std::endl;

    if (!capacity_test())
        std::cout << "failed on capacity tests" << std::endl;
    else
        std::cout << "Capacity tests: OK" << std::endl;

    if (!element_access_test())
        std::cout << "failed on element access tests" << std::endl;
    else
        std::cout << "element access tests: OK" << std::endl;

    if (!modifiers_test())
        std::cout << "failed on modifiers tests" << std::endl;
    else
        std::cout << "modifiers tests: OK" << std::endl;

    if (!rel_operators_test())
        std::cout << "failed on relational operators tests" << std::endl;
    else
        std::cout << "Relational operators tests: OK" << std::endl;

    system("leaks a.out");
    return 0;
}