/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_vector.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:56:08 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/20 19:04:56 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main_vector.hpp" 

typedef ft::vector<int>     ftvec;
typedef std::vector<int>    stdvec;

template < typename T>
void print_content(T &vec) {
    std::cout << "Container contents: ";
    if (vec.begin() != vec.end())  {
        std::cout << *vec.begin();
        for (typename T::iterator it = (vec.begin() + 1); it != vec.end(); ++it)
            std::cout << ", " << *it ;
        std::cout << std::endl;
    }
    else
        std::cout << "NOTHING, like... really empty!" << std::endl;
}

template < typename T, typename T2>
bool compare_content(T &vec, T2 &cpy) {
    typename T2::iterator cpit = cpy.begin();
    typename T::iterator it = vec.begin();
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

template < typename T, typename T2>
bool is_equal(T &cnt, T2 &cpy, std::string str) {
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