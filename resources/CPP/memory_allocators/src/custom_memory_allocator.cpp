//
// Created by Pawel Stoworowicz.
// Contact: pawel.stoworowicz@gmail.com
// MIT license
//

// Based upon this video: https://www.youtube.com/watch?v=pP15kDeXJU0 (this is gold literally!)
// To compile: g++ memory_allocation_tracker.cpp -std=c++14

// std::allocator
// std::allocator_traits

#include <vector>
#include <limits>
#include <memory>
#include <iostream>

template <typename T>
class TrackingAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    struct rebind {
        using other = TrackingAllocator<U>;
    };

    TrackingAllocator() = default;

    template <typename U>
    TrackingAllocator(const TrackingAllocator<U> &other) {} // copy constructor

    pointer allocate(size_type numbOfObjects) {
        mAllocations += numbOfObjects;
        return static_cast<pointer>(operator new(sizeof(T) * numbOfObjects));
    }

    pointer allocate(size_type numbOfObjects, const_void_pointer hint) {
        // hint is a pointer to the nearest element which was allocated previously
        // it's done to improve locality of allocated memory
        return allocate(numbOfObjects);

    }

    void deallocate(pointer to_destroy, size_type numbOfObjects) {
        operator delete(to_destroy);
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    template <typename U, typename... Args>
    void construct(U *p, Args && ...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U *to_destroy) {
        to_destroy->~U();
    }

    size_type get_allocations() const {
        return mAllocations;
    }
private:
    static size_type mAllocations;
};

template <typename T>
typename TrackingAllocator<T>::size_type TrackingAllocator<T>::mAllocations = 0;

int main() {

    using TAint = TrackingAllocator<int>;
    using TAdouble = TAint::rebind<double>::other;
    std::vector<int, TrackingAllocator<int>> v(5);
    std::cout << v.get_allocator().get_allocations() << std::endl;
    return 0;
}