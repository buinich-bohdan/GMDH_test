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
    size_t* use_count;
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
            , use_count(new size_t(1))
            , del_fn(default_delete<T>)
    {
    }

    shared_ptr(const shared_ptr& tmp)
            : shared_ptr(tmp.p, tmp.del_fn)
    {
        use_count = tmp.use_count;
        ++*use_count;
    }

    shared_ptr(T* pointer, void (*fn)(T*)) noexcept : p(pointer), use_count(new size_t(1)), del_fn(fn) {}

    shared_ptr(shared_ptr&& tmp) noexcept : p(std::move(tmp.p)), use_count(std::move(tmp.use_count)), del_fn(std::move(tmp.del_fn))
    {
        tmp.p = nullptr;
        tmp.use_count = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& tmp)
    {
        if (this != &tmp) {
            reset();
            p = tmp.p;
            use_count = tmp.use_count;
            del_fn = tmp.del_fn;
            ++*use_count;
        }
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& tmp)
    {
        shared_ptr::swap(tmp);
        return *this;
    }

    void swap(shared_ptr& tmp)
    {
        std::swap(p, tmp.p);
        std::swap(use_count, tmp.use_count);
        std::swap(del_fn, tmp.del_fn);
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
        use_count = new size_t(1);
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
    bool unique() const
    {
        return use_count != nullptr && *use_count == 1;
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