/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:13:09 by ineumann          #+#    #+#             */
/*   Updated: 2022/04/29 18:42:32 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp" 
#include <sys/time.h>
#include <string>
#include <vector>

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
    return 0;
}

bool capacity_test() {
    return 0;
}

bool element_access_test() {
    return 0;
}

bool modifiers_test() {
    return 0;
}

bool rel_operators_test() {
    return 0;
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
    if (!capacity_test())
        std::cout << "failed on capacity tests" << std::endl;
    else
        std::cout << "Scapacity tests: OK" << std::endl;
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
    return 0;
}