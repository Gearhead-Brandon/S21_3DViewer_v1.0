#include <variant>
#include <iostream>
#include <string>

// void processVariant(const std::variant<int, double, std::string>& var) {
//     if (const int* val = std::get_if<int>(&var)) {
//         std::cout << "Integer value: " << *val << std::endl;
//     } else if (const double* val = std::get_if<double>(&var)) {
//         std::cout << "Double value: " << *val << std::endl;
//     } else if (const std::string* val = std::get_if<std::string>(&var)) {
//         std::cout << "String value: " << *val << std::endl;
//     // } else if (const bool* val = std::get_if<bool>(&var)) {
//     //     std::cout << "String value: " << *val << std::endl;
//     } else {
//         std::cout << "Invalid type" << std::endl;
//     }
// }

// class VariantWrapper {
// private:
//     std::variant<int, double, std::string> data;

// public:
//     template <typename T = int>
//     T* getIf() {
//         return std::get_if<T>(&data);
//     }

//     template <typename T>
//     VariantWrapper& operator=(const T& newValue) {
//         data = newValue;
//         return *this;
//     }
// };

// void f (int a = 10, int b = 20){
//     std::cout << a << " " << b << std::endl;
// }

// int main() {
//     // std::variant<int, double, std::string> var = 3.14;
//     // processVariant(var);
//     f();

//     // std::cout << "size = " << sizeof(var) << std::endl;
//     VariantWrapper wrapper;
    
//     wrapper = 42; // Присваивание целочисленного значения
//     int* intValue = wrapper.getIf();
//     if (intValue) {
//         std::cout << "Integer value: " << *intValue << std::endl;
//     }

//     wrapper = 3.14; // Присваивание значения типа double
//     double* doubleValue = wrapper.getIf<double>();
//     if (doubleValue) {
//         std::cout << "Double value: " << *doubleValue << std::endl;
//     }

//     wrapper = std::string("Hello"); // Присваивание строки
//     std::string* stringValue = wrapper.getIf<std::string>();
//     if (stringValue) {
//         std::cout << "String value: " << *stringValue << std::endl;
//     }


//     return 0;
// }

// #include <any>
// #include <iostream>

// void printValue(std::any value) {
//     if (value.has_value()) {
//         if(const int* val = std::any_cast<int>(&value)){
//             std::cout << "Integer value: " << *val << std::endl;
//         } else if(const double* val = std::any_cast<double>(&value)) {
//             std::cout << "Double value: " << *val << std::endl;
//         } else if(const std::string* val = std::any_cast<std::string>(&value)) {
//             std::cout << "String value: " << *val << std::endl;
//         } else {
//             std::cout << "Invalid type" << std::endl;
//         }
//     } else {
//         std::cout << "Value is empty" << std::endl;
//     }
// }

template <typename T>
class Debug{

public:
    Debug() = delete;
};   

int main() {

    //Debug<decltype(f())>();

    // val = std::string("Hello");
    // printValue(val);

    return 0;
}