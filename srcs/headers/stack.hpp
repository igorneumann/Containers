/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:42:54 by ineumann          #+#    #+#             */
/*   Updated: 2022/05/24 19:15:08 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"

namespace ft {

    template<class T, class Container = vector<T> >
    class stack
    {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
        
        explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {
        }
        bool empty() const {
            return this->c.empty();
        }
        size_type size() const {
            return this->c.size();
        }
        const value_type& top() const {
            return this->c.back();
        }
        void push (const value_type& val) {
            this->c.push_back(val);
        }
        void pop() {
            this->c.pop_back();
        }
        friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c == rhs.c);
        }
        friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c != rhs.c);
        }
        friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c < rhs.c);
        }
        friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c > rhs.c);
        }
        friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c <= rhs.c);
        }
        friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
            return (lhs.c >= rhs.c);
        }
        protected:
            container_type c;
    };
}

#endif