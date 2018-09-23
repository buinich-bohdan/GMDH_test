#include <iostream>

template <class T>
void default_delete(T* p)
{
    delete p;
}
template <class T>
void default_array_delete(T* p)
{
    delete[] p;
}

template <class T>
class shared_ptr {
private:
    T* p;
    int* use_count = nullptr;
    void (*del_fn)(T*) = NULL;

public:
    shared_ptr()
            : p(nullptr)
            , use_count(nullptr)
            , del_fn(default_delete<T>)
    {
    }

    explicit shared_ptr(T* pointer)
            : p(pointer)
            , use_count(new int(1))
            , del_fn(default_delete<T>)
    {
    }

    shared_ptr(const shared_ptr& x)
            : shared_ptr(x.p, x.del_fn)
    {
        use_count = x.use_count;
        ++*use_count;
    }

    shared_ptr(T* pointer, void (*fn)(T*)) noexcept : p(pointer), use_count(new int(1)), del_fn(fn) {}

    shared_ptr(shared_ptr&& x) noexcept : p(std::move(x.p)), use_count(std::move(x.use_count)), del_fn(std::move(x.del_fn))
    {
        x.p = nullptr;
        x.use_count = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& x)
    {
        if (this != &x) {
            reset();
            p = x.p;
            use_count = x.use_count;
            del_fn = x.del_fn;
            ++*use_count;
        }
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& x)
    {
        shared_ptr::swap(x);
        return *this;
    }

    void swap(shared_ptr& x)
    {
        std::swap(p, x.p);
        std::swap(use_count, x.use_count);
        std::swap(del_fn, x.del_fn);
    }

    void reset()
    {
        this->~shared_ptr();
        p = nullptr;
        use_count = nullptr;
    }
    void reset(T* p, void (*fn)(T*))
    {
        reset();
        use_count = new int(1);
        this->p = p;
        del_fn = fn;
    }

    T& operator->() const
    {
        return p;
    }

    T& operator*() const
    {
        return *p;
    }

    int used_count() const
    {
        return use_count != nullptr ? *use_count : 0;
    }

    ~shared_ptr()
    {
        if (use_count != nullptr && --*use_count == 0) {
            del_fn(p);
            delete use_count;
        }
    }
};

int main()
{
    shared_ptr<int> test1;
    shared_ptr<int> test2 (new int(100));
    test1 = test2;
    std::cout << *test1 << std::endl;
    std::cout << *test2 << std::endl;
    std::cout << test1.used_count() << std::endl;

    test2.reset();
    std::cout << test1.used_count() << std::endl;
    test1.reset(new int(10), default_delete);
    std::cout << test1.used_count() << std::endl;
    test1 = shared_ptr<int>(new int (10));
    std::cout << test1.used_count() << std::endl;

    return 0;
}