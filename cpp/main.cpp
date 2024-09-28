#include <iostream>

// function overload as argument, name conflict
// 函数做参数, 函数名同名
// https://stackoverflow.com/questions/30393285/stdfunction-fails-to-distinguish-overloaded-functions
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


int main() {

}
