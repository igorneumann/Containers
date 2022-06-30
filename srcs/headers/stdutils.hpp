/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdutils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:51:16 by ineumann          #+#    #+#             */
/*   Updated: 2022/06/30 19:25:15 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDUTILS_HPP
#define STTDUUTILS_hpp

namespace ft {
    //----------------------------------- PAIR --------------------------------
    template <typename T1, typename T2>
    class pair {
        public:

            // Default constructor
            pair() : first(), second() {};

            //copy constructor using member variables
            pair(const T1& a, const T2& b) : first(a), second(b) {};

            //copy constructor using a pair
            template <typename U, typename V>
            pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

            ~pair() {};

            pair& operator=(const pair& assign) {
                if (this != &assign) {
                    first = assign.first;
                    second = assign.second;
                }
                return (*this);
            }

            //---------------------- variables -----------------------------

            T1 first;
            T2 second;
    };

    //---------------------- FT::ALLOCATOR ------------------------ //
    /* - Member functions:
    * Address           Obtains the address of an object
    * Allocate          Allocates uninitialized storage
    * Deallocate        Deallocates storage
    * Construct         Constructs an object in allocated storage
    * Destroy           Destroys an object in allocated storage*/
   template <class T>
   class allocator 
   {
       public:
        typedef T                   value_type;
        typedef T*                  pointer;
        typedef T&                  reference;
        typedef const T*            const_pointer;
        typedef const T&            const_reference;
        typedef size_t              size_type;
        typedef long int            difference_type;

        allocator() throw() {};

        allocator(const allocator&) throw() {};

        template <class U>
        allocator(const allocator<U>&) throw() {};

        ~allocator() throw() {};

        pointer address(reference x) const {
            return &x;
        }

        const_pointer address(const_reference x) const {
            return &x;
        }

        pointer allocate(size_type n)
        {
            pointer ret;
            size_t size = n * sizeof(value_type);

            try {
                ret = reinterpret_cast<pointer>(::operator new(size))
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            return ret;
        }

        void deallocate (pointer p, size_type n) {
            (void)n;
            ::operator delete(p);
        }

        void construct(pointer p, const T& v) {
            new((void*)p)T(v);
        }

        void destroy(pointer p) {
            p->~T();
        }
   };

   template <class T>
   struct less {
       typedef T        first_argument_type;
       typedef T        second_argument_type;
       typpedef bool    result_type;

       bool operator() (const T& x, const T) const {
           return x<y;
       }
   };
}

#endif