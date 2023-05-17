#include <iostream>
#include <numeric>
#include <vector>
#include <list>
#include <type_traits>
#include <tuple>

template <typename T>
struct enable_if_vector_list : std::false_type { };

template <typename T>
struct enable_if_vector_list<std::vector<T> > : std::true_type { };

template <typename T>
struct enable_if_vector_list<std::list<T> > : std::true_type { };

template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T val)
{
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&val);
    for (int i = sizeof(T) - 1; i >= 0; i--) {
        std::cout << static_cast<int>(*(ptr + i));
        if (i > 0)
            std::cout  << ".";
    }

    std::cout << std::endl;
}

template <typename T, std::enable_if_t<std::is_same<typename std::remove_const<T>::type, std::string>::value, bool> = true>
void print_ip(const T &val)
{
    std::cout << val << std::endl;
}

template <typename T, std::enable_if_t<enable_if_vector_list<T>::value, bool> = true>
void print_ip(const T &val)
{
    const auto size = val.size();
    decltype(val.size()) idx = 0;
    for (auto it = val.cbegin(); it != val.cend(); ++it, ++idx) {
        std::cout << *it;
        if (idx < size - 1)
            std::cout << ".";
    }

    std::cout << std::endl;
}

template <typename T, bool IsEnd>
void printTupleElement(const T &val)
{
    std::cout << val;
    if (!IsEnd)
        std::cout << ".";
}

template <typename T, std::size_t... Idx>
void printTuple(const T &val, std::index_sequence<Idx...>)
{
    (printTupleElement<typename std::tuple_element<Idx, T>::type, Idx == std::tuple_size<T>::value - 1>(std::get<Idx>(val)), ...);
}

template <typename T, std::size_t Size = std::tuple_size<T>::value/*, std::enable_if_t<is_req_tuple<T>::value, bool> = true*/>
void print_ip(const T &val)
{
    printTuple(val, std::make_index_sequence<Size>{});
    std::cout << std::endl;
}

int main()
{
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});
    print_ip(std::string{"Hello, World!"});
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});

    // без проверки типов в std::tuple
    print_ip(std::make_tuple(123, 456, 789, 0));

    return 0;
}

