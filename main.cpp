#include <iostream>
#include <memory>

struct Foo {
    Foo() = default;
    Foo(const Foo&) = default;
    Foo(Foo&&) noexcept = default;
    virtual ~Foo() = default;

    Foo& operator=(const Foo&) = default;
    Foo& operator=(Foo&&) noexcept = default;

    virtual void my_func() = 0;
};

struct Bar : public Foo {
    Bar() : Foo{} {};

    void my_func() override { std::cout << "Bar::my_func\n"; }
    void baz() { my_func(); }

    [[no_unique_address]] [[msvc::no_unique_address]] std::allocator<int> alloc;
    int* ptr{ nullptr };
};

int main() {
    Bar bar;

    bar.baz(); // Read access violation. Appears to be a bug where vtable is nulled out.

    return 0;
}