#include <memo/Memorizer.h>

#include <iostream>
#include <string>

int main() {
    memo::Memorizer cached_lambda([](const std::string& val){return val;}, memo::Cache<std::string, std::string>());
    std::cout << cached_lambda(std::string("hello world")) << std::endl;
}
