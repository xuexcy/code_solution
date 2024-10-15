#include <iostream>
#include <functional>

/**
@question: overloaded function as argument, name conflict
    - @cn: 函数做参数, 函数名同名
@solution: 调用时使用 static_cast<function_pointer>(function_name);
@ref: https://stackoverflow.com/questions/30393285/stdfunction-fails-to-distinguish-overloaded-functions
**/
namespace function_name_conflict
{
void function() {}
void function(int i) { std::cout << i << std::endl; }
template <class F>
void invoke(F f) {
    f();
}
void run() {
    // no: <unresolved overloaded function type>
    // invoke(function);
    // yes
    invoke(static_cast<void(*)()>(function));
}
} // namespace function_name_conflict



/**
@question: user defined struct as unordered_map key
    - @cn: 自定义类做 unordered_map 的 key
@solution:
    - 1. 定义 hash_function: 定义一个Hasher or 特化 std::hash
    - 2. 定义 comparison function for equality： operator==(rhs) or 特化 std::equal
@ref: https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
@ref: https://en.cppreference.com/w/cpp/utility/hash
*/
namespace user_defined_struct_as_unordered_map_key {
struct Key {
    int first{0};
    std::string second;
    Key(const Key& key) = default;
    // c++20
    // bool operator==(const Key rhs) const = default;

    // bool operator==(const Key rhs) const {
    //     return first == rhs.first&& second == rhs.second;
    // }
};
struct KeyHasher {
    size_t operator()(const Key& key) const noexcept {
        std::size_t h1 = std::hash<int>{}(key.first);
        std::size_t h2 = std::hash<std::string>{}(key.second);
        return h1 ^ (h2 << 1);
    }
};
}  // namespace self_defined_class_as_unordered_map_key
template <>
struct std::hash<user_defined_struct_as_unordered_map_key::Key> {
    std::size_t operator()(const user_defined_struct_as_unordered_map_key::Key& key) const noexcept {
        std::size_t h1 = std::hash<int>{}(key.first);
        std::size_t h2 = std::hash<std::string>{}(key.second);
        return h1 ^ (h2 << 1);
    }
};
namespace user_defined_struct_as_unordered_map_key {
void run() {
    std::unordered_map<Key, int> un_m;
    std::unordered_map<Key, int, KeyHasher> un_m_2;
    // c++20
    // auto key_hash = [](const Key& key) {
    std::function<size_t(const Key& key)> key_hash = [](const Key& key) {
        return std::hash<int>{}(key.first) ^ (std::hash<std::string>{}(key.second) << 1);
    };
    std::function<bool(const Key&, const Key&)> key_equal = [](const Key& lhs, const Key& rhs) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    };
    std::unordered_map<Key, int, decltype(key_hash), decltype(key_equal)> un_m_3;
}
}  // namespace user_defined_struct_as_unordered_map_key



int main() {

}
