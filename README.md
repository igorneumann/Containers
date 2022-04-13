42 project to reimplement 3 C++ containers:

- Vector
- Map
- Stack


     ------------------------ FT::VECTOR ------------------------- 
    
     - Coplien form:
     (constructor):        Construct vector
     (destructor):         Destruct vector
     operator=:            Assign vector
    
     - Iterators:
     begin:                Return iterator to beginning
     end:                  Return iterator to end
     rbegin:               Return reverse iterator to reverse beginning
     rend:                 Return reverse iterator to reverse end
    
     - Capacity:
     size:                 Return size
     max_size:             Return maximum size
     resize:               Change size
     capacity:             Return size of allocated storage capacity
     empty:                Test whether vector is empty
     reserve:              Request a change in capacity
    
     - Element access:
     operator[]:           Access element
     at:                   Access element
     front:                Access first element
     back:                 Access last element
    
     - Modifiers:
     assign:               Assign vector content
     push_back:            Add element at the end
     pop_back:             Delete last element
     insert:               Insert elements
     erase:                Erase elements
     swap:                 Swap content
     clear:                Clear content
    
     - Non-member function overloads:
     relational operators: Relational operators for vector
     swap:                 Exchange contents of two vectors
     ------------------------------------------------------------- 
    
       @param T        Type of container's elements.
       @param Alloc    Object used to manage the vector' storage.


     ------------------------ FT::STACK -------------------------- 
    
     - Coplien form:
     (constructor):        Construct stack
     (destructor):         Destruct stack
     operator=:            Assign content
    
     - Member functions:
     empty:                Test whether container is empty
     size:                 Return size
     top:                  Access next element
     push:                 Insert element
     pop:                  Remove top element
    
     - Non-member function overloads:
     relational operators: Relational operators for stack
     ------------------------------------------------------------- 

       @param T            Type of container's elements.
       @param Container    Container object used internally to store T elements.


     ------------------------- FT::MAP --------------------------- 
    
     - Coplien form:           
     (constructor):    Construct map
     (destructor):     Map destructor
     operator=:        Assign map
    
     - Iterators:
     begin:            Return iterator to beginning
     end:              Return iterator to end
     rbegin:           Return reverse iterator to reverse beginning
     rend:             Return reverse iterator to reverse end
    
     - Capacity:
     empty:            Test whether container is empty
     size:             Return container size
     max_size:         Return maximum size
    
     - Element access:
     operator[]:       Access element
    
     - Modifiers:
     insert:           Insert elements
     erase:            Erase elements
     swap:             Swap content
     clear:            Clear content
    
     - Observers:
     key_comp:         Return key comparison object
     value_comp:       Return value comparison object
    
     - Operations:
     find:             Get iterator to element
     count:            Count elements with a specific key
     lower_bound:      Return iterator to lower bound
     upper_bound:      Return iterator to upper bound
     equal_range       Get range of equal elements
     ------------------------------------------------------------- 
    
       @param key      Type of keys mapped to elements.
       @param T        Type of elements mapped to keys.
       @param Compare  Comparison object used to sort the binary tree.
       @param Alloc    Object used to manage the vector' storage.
    
