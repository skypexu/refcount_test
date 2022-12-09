#include "refcountedobj.h"
#include "intrusive_ptr.hpp"
#include <memory>
#include <chrono>
#include <iostream>

class Object : public butil::RefCountedObject {
public:
    int i;
};

typedef butil::intrusive_ptr<Object> ObjectRef;

class Object2 {
public:
    int i;
};

int total;

void f1(ObjectRef ref)
{
    total += ref->i;
}

typedef std::shared_ptr<Object2> Object2Ref;

void f2(Object2Ref ref)
{
    total += ref->i;
}

int main()
{
    Object *o = new Object;
    o->i = 100;
    ObjectRef ref(o);
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000000; ++i) {
        f1(ref);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "total=" << total << " elapsed time: " << elapsed_seconds.count() << "s\n";
    
    Object2Ref ref2 = std::make_shared<Object2>();
    total = 0;
    ref2->i = 100;
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < 100000000; ++i) {
        f2(ref2);
    }
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
    std::cout << "total=" << total << " elapsed time: " << elapsed_seconds.count() << "s\n";
}

