#pragma once
#include <algorithm> // max
#include <stdexcept> // out_of_range and invalid_argument
#include <utility> // move

namespace dsac::array {
///Simplified version of std::vector
/// @tparam T the element type    
template <typename T>
class Vector {
    private:
        /// capacity of the array
        int cap{0};

        /// number of actual entries
        int sz{0};

        /// pointer to array of elements
        T* data{nullptr};

    public:
        /// TODO: Constructs an empty vector
        Vector() {
            cap = 0;
            sz = 0;
            data = nullptr;
        }

        /// TODO: Constructs a vector with the specified number of elements
        /// Each Element is Value Initialized
        /// @param n number of elements in the vector
        Vector(int n) {
             if (n < 0) {
                throw std::invalid_argument("Size can't be negative");
            }
            sz = n;
            cap = n;
            if (n == 0) {
                data = nullptr;
            }
            else {
                data = new T[n] {};
            }
        }

        /// TODO: Returns the current capacity of the underlying array
        /// @return the size of the underlying array
        int capacity() const {
            return cap;
        }

        /// TODO: Returns the number of elements stored
        /// @return the number of elements stored
        int size() const {
            return sz;
        }

        /// TODO: Tests whether the vector is empty.
        /// @return true if the vector is empty, false otherwise
        bool empty() const {
            return sz == 0;
        }

        /// TODO: Returns const reference to the element at index i
        /// behavior is undefined if i is out of bounds
        /// @param i index of desired element
        /// @return element at index i
        const T& operator[](int i) const {
            return data[i];
        }

        /// TODO: Returns reference to the element at index i
        /// behavior is undefined if i is out of bounds
        /// @param i index of desired element
        /// @return element at index i
        T& operator[](int i) {
            return data[i];
        }

        /// TODO: Returns const reference to the element at index i
        /// raises out_of_range exception with invalid index
        /// @param i index of desired element
        /// @return element at index i
        /// @throw out_of_range exception if index is invalid for current vector
        const T& at(int i) const {
            if (i < 0 || i >= sz) {
                throw std::out_of_range("Index out of range");
            }
            return data[i];
        }

        /// TODO: Returns reference to the element at index i
        /// raises out_of_range exception with invalid index
        /// @param i index of desired element
        /// @return element at index i
        /// @throw out_of_range exception if index is invalid for current vector
        T& at(int i) {
            if (i < 0 || i >= sz) {
                throw std::out_of_range("Index out of range");
            }
            return data[i];
        }

        /// TODO: Returns a const reference to the first element
        /// behavior is undefined if vector is empty
        /// @return reference to first element
        const T& front() const {
            return data[0];
        }

        /// TODO: Returns a live reference to the first element
        /// behavior is undefined if vector is empty
        /// @return reference to first element
        T& front() {
            return data[0];
        }

        /// TODO: Returns a const reference to the last element
        /// behavior is undefined if vector is empty
        /// @return reference to last element
        const T& back() const {
            return data [sz - 1];
        }

        /// TODO: Returns a live reference to the last element
        /// behavior is undefined if vector is empty
        /// @return reference to last element
        T& back() {
            return data[sz - 1];
        }

        /// TODO: Inserts an element at end of the vector
        /// @param elem   the new element
        void push_back(const T& elem) {
            if (sz == cap) {
                if (cap == 0) {
                    reallocate(1);
                }
                else {
                    reallocate(cap * 2);
                }
            }
            data[sz] = elem;
            sz++;
        }

        /// TODO: Removes the last element from the vector
        /// Calls shrink() after removing the element to reduce unused capacity when appropriate
        /// Behavior is undefined if the vector is empty
        void pop_back() {
            sz--;
            shrink();
        }

        /// TODO: Inserts an element at index i; 
        /// behavior is undefined if i is out of bounds
        /// @param i      index at which new element should be placed
        /// @param elem   the new element
        void insert(int i, const T& elem) {
            if (sz == cap) {
                if (cap == 0) {
                    reallocate(1);
                }
                else {
                    reallocate(cap * 2);
                }
            }
            for (int j = sz; j > i; j--) {
                data[j] = data[j - 1];
            }
            data[i] = elem;
            sz++;
        }

        /// TODO: Removes the element at index i and shifts subsequent elements left
        /// Calls shrink() after removing the element to reduce unused capacity when appropriate
        /// Behavior is undefined if i is out of bounds
        /// @param i index of element to be removed
        void erase(int i) {
            for (int j = i; j < sz - 1; j++) {
                data[j] = data[j + 1];
            }
            sz--;
            shrink();
        }

        /// TODO: Requests that the vector capacity be at least as large as the indicated capacity
        /// The function has no effect if the current capacity is already large enough
        /// @param minimum the minimum capacity after the operation
        void reserve(int minimum) {
            if (minimum > cap) {
                reallocate(minimum);
            }
        }
    
        /// TODO: Changes the capacity of the vector to new_cap
        /// Existing elements are preserved in their current order
        /// new_cap must be at least as large as the current size
        /// If new_cap is 0, no array is allocated
        /// @param new_cap the new capacity of the vector
        void reallocate(int new_cap) {
            if(new_cap < sz) {
                throw std::invalid_argument("new cap can't be smaller than size");  
            }
            if (new_cap == cap) {
                return;
            }
            T* new_data = nullptr;
            if (new_cap > 0) {
                new_data = new T[new_cap];
                for (int i = 0; i < sz; i++) {
                    new_data[i] = std::move(data[i]);
                }
            }
            delete[] data;
            data = new_data;
            cap = new_cap;
        }

        /// TODO: Reduces the capacity of the vector when there is substantial unused space
        /// If the size is at most one-fourth of the current capacity, reduces the capacity by half
        /// This function does not reduce the capacity below 1
        void shrink() {
            if (cap > 1 && sz <= cap / 4) {
                int new_cap = cap / 2;
                if (new_cap < 1) {
                    new_cap = 1;
                }
                reallocate(new_cap);
            }
        }
        
        /// TODO: Removes unused capacity from the vector
        /// Reduces the capacity to match the current size
        /// If the vector is empty, the capacity becomes 0
        /// The function has no effect if capacity is already equal to size
        void shrink_to_fit() {
            if (cap != sz) {
                reallocate(sz);
            }
        }

    private:
        /// TODO: Write a helper function to make a deep copy of another vector
        /// Copy the capacity and size
        /// Allocate a new array and copy all existing elements
        /// Assume the current vector has data as nullptr
        void clone(const Vector& other) {
            cap = other.cap;
            sz = other.sz;

            if(cap == 0) {
                data = nullptr;
            }
            else {
                data = new T[cap]{};

                for (int i = 0; i < sz; i++) {
                    data[i] = other.data[i];
                }
            }
        }

        /// TODO: Write helper function to transfer ownership from another vector
        /// Transfer the capacity, size, and data pointer
        /// Reset the source vector to an empty state
        /// Assume the current vector has data as nullptr
        void transfer(Vector& other) {
            cap = other.cap;
            sz = other.sz;
            data = other.data;

            other.cap = 0;
            other.sz = 0;
            other.data = nullptr;
        }

    public:
        /// TODO: Destructor
        ~Vector() {
            delete[] data;
        }

        /// TODO: Write the copy constructor
        /// Create an independent copy of the given vector
        Vector(const Vector& other) {
            clone(other);
        }

        /// TODO: Write the copy assignment operator
        /// Handle self-assignment and release existing memory
        /// Copy the contents of the given vector
        /// Return a reference to the current vector
        Vector& operator=(const Vector& other) {
            if (this != &other) {
                delete[] data;
                data = nullptr;
                cap = 0;
                sz = 0;
                clone(other);
            }
            return *this;
        }

        /// TODO: Write the move constructor
        /// Transfer ownership of the resources from the given vector
        /// Leave the source vector empty
        Vector(Vector&& other) {
            transfer(other);
        }

        /// TODO: Write the move assignment operator
        /// Handle self-assignment and release existing memory
        /// Transfer ownership of the resources from the given vector
        /// Return a reference to the current vector
        Vector& operator=(Vector&& other) {
            if (this != &other) {
                delete[] data;
                data = nullptr;
                cap = 0;
                sz = 0;
                transfer(other);
            }
            return *this;
        }

    public:
        /// TODO: Implement a bidirectional iterator for the Vector class
        /// Store a pointer to the vector and the current index
        /// Provide operations to access elements, move forward and backward,
        /// and compare iterator positions
        class iterator {
            friend class Vector;
            private:
                Vector* vec;
                int ind;
            public:
                /// TODO: Initialize the iterator with a vector pointer and an index
                iterator(Vector* v=nullptr, int i=-1) {
                    vec = v;
                    ind = i;
                }
                
                /// TODO: Return a reference to the element at the current position
                T& operator*() const {
                    return (*vec)[ind];
                }

                /// TODO: Return a pointer to the element at the current position
                T* operator->() const {
                    return &(*vec)[ind];
                }

                /// TODO: Move to the next element and return the updated iterator
                iterator& operator++() {
                    ind++;
                    return *this;
                }

                /// TODO: Move to the next element and return the previous iterator
                iterator operator++(int) {
                    iterator temp = *this;
                    ind++;
                    return temp;
                }

                /// TODO: Move to the previous element and return the updated iterator
                iterator& operator--() {
                    ind--;
                    return *this;
                }

                /// TODO: Move to the previous element and return the previous iterator
                iterator operator--(int) {
                    iterator temp = *this;
                    ind--;
                    return temp;
                }

                /// TODO: Return true if both iterators refer to the same vector and index
                bool operator==(iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind;
                }
                
                /// TODO: Return true if the iterators refer to different positions or vectors
                bool operator!=(iterator rhs) const {
                    return !(*this == rhs);
                }
        };

    public:
        /// TODO: Implement a bidirectional const_iterator for the Vector class
        /// Store a pointer to a constant vector and the current index
        /// Allow read-only access to elements
        /// Support forward and backward movement and iterator comparisons
        class const_iterator {
            private:
                const Vector* vec;
                int ind;
            
            public:
                /// TODO: Initialize the const_iterator with a vector pointer and an index
                const_iterator(const Vector* v=nullptr, int i=-1) {
                    vec = v;
                    ind = i;
                }

                /// TODO: Return a constant reference to the current element
                const T& operator*() const {
                    return (*vec)[ind];
                }

                /// TODO: Return a pointer to the current element without allowing modification
                const T* operator->() const {
                    return &(*vec)[ind];
                }

                /// TODO: Move forward and return the updated iterator
                const_iterator& operator++() {
                    ind++;
                    return *this;
                }

                /// TODO: Move forward and return the previous iterator
                const_iterator operator++(int) {
                    const_iterator temp = *this;
                    ind++;
                    return temp;
                }

                /// TODO: Move backward and return the updated iterator
                const_iterator& operator--() {
                    ind--;
                    return *this;
                }

                /// TODO: Move backward and return the previous iterator
                const_iterator operator--(int) {
                    const_iterator temp = *this;
                    ind--;
                    return temp;
                }

                /// TODO: Compare the vector pointers and indices for equality
                bool operator==(const_iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind;
                }

                /// TODO: Determine whether two const_iterators are different
                bool operator!=(const_iterator rhs) const {
                    return !(*this == rhs);
                }
        };
    public:
        /// TODO: Write the function to return an iterator to the first element
        iterator begin() {
            return iterator(this, 0);
        }

        /// TODO: Write the function to return an iterator past the last element
        iterator end() {
            return iterator(this, sz);
        }

        /// TODO: Write the function to return a const_iterator to the first element
        const_iterator begin() const {
            return const_iterator(this, 0);
        }

        /// TODO: Write the function to return a const_iterator past the last element
        const_iterator end() const {
            return const_iterator(this, sz);
        }

        /// TODO: Write the function to insert an element before the iterator position
        /// Inserts an element immediately before the given iterator position
        /// @param it     iterator defining the insertion position
        /// @param elem   the new element
        /// @return iterator of newly inserted element
        iterator insert(iterator it, const T& elem) {
            int index = it.ind;
            insert(index, elem);
            return iterator(this, index);
        }

        /// TODO: Write the function to erase an element at the iterator position
        /// Removes the element at the given iterator position
        /// @param it iterator defining the position of element to be removed
        /// @return iterator just beyond the removed element
        iterator erase(iterator it) {
            int index = it.ind;
            erase(index);
            return iterator(this, index);
        }
    
}; // Vector class

}  // namespace dsac::array
