/* Inspired by:
 * https://www.youtube.com/watch?v=sLlGEUO_EGE
 *
 * Exploring memory allocation
 * Compile by calling:
 * g++ memory_allocation_tracker.cpp -std=c++14
 *
 */

#include <stdlib.h>
#include <iostream>
#include <memory>

struct MemAllocationMetrics{
    size_t TotalAllocated = 0;
    size_t TotalFreedMem = 0;

    size_t CurrentUsage() { return TotalAllocated - TotalFreedMem; }
};

static MemAllocationMetrics s_MemAllocationMetrics;


void* operator new(size_t size) {
    // std::cout << "Allocating " << size << " bytes" << std::endl;
    s_MemAllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    // std::cout << "Freeing " << size << " bytes of memory" << std::endl;
    s_MemAllocationMetrics.TotalFreedMem += size;
    free(memory);
}

static void PrintMemoryUsage(){
    std::cout << "Memory usage: " << s_MemAllocationMetrics.CurrentUsage() << " bytes" << std::endl;
}

struct SomeObj{
    int a, b, c;
};

int main(){

    SomeObj* obj = new SomeObj;
    PrintMemoryUsage();
    {
        std::unique_ptr<SomeObj> obj = std::make_unique<SomeObj>();
        PrintMemoryUsage();
    }
    PrintMemoryUsage();
    delete obj;
    PrintMemoryUsage();
    return 0;
}


