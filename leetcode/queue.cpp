/**********************************************
  > File Name		: queue.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Apr 11 20:01:56 2023
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/
#include <utility>

template <typename>
class void_t {
    typedef void type;
};

template <bool v>
class bool_constant {
    static const bool value = v;
};

typedef bool_constant<false> false_type;
typedef bool_constant<true> true_type;

//enable_if
template <bool, typename = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

//declval
template <typename T>
T&& _declval(int);
template <typename T>
decltype(_declval<T>(0)) declval();

//memory directory
template <typename T, typename... Args, typename = decltype(new (declval<void*>()) T(declval<Args>()...))>
constexpr T* construct_at(T* location, Args... args) {

}

#define ALLOCATOR_TRAITS_HAS_XXX(NAME, PROPERTY) \
    template <typename T> NAME<T, T::PROPERTY>: true_type {}\
    template <typename T, typename = void> NAME: false_type {}

template <typename, typename T, typename... Args>
struct has_construct_impl: false_type {};

template <typename T, typename... Args>
struct has_construct_impl<decltype(declval<T>().construct(declval<Args>()...)), T, Args...>: true_type {};

template <typename T, typename... Args>
struct has_construct: has_construct_impl<void, T, Args...> {};

template <typename Alloc>
struct allocator_traits {
    typedef Alloc allocator_type;
    typedef typename allocator_type::value_type value_type;

    template <typename T, typename... Args, typename =
        enable_if<has_construct<allocator_type, T*, Args...>::value>>
    static void construct(allocator_type& a, T* tp, Args&&... args) {
        a.construct(tp, std::forward<Args>(args)...);
    }

    template <typename T, typename... Args, typename = void, typename =
        enable_if<!has_construct<T, Args...>::value>>
    static void construct(allocator_type&, T* tp, Args&&... args) {
        
    }
};



template <typename value_type, typename pointer, typename reference>
class deque_iterator {
private:
    pointer ptr;
public:
    deque_iterator(): ptr(nullptr) {}

    deque_iterator& operator++() {

    }
};

template <typename value_type, typename allocator> 
class deque_base {
    deque_base(const deque_base&);
    deque_base& operator=(const deque_base&);
public:
    typedef value_type& reference;
    typedef const value_type& const_reference;

};

template <typename value_type, typename allocator> 
class deque {
    
};

template <typename T>
class queue {
public:
    
};
