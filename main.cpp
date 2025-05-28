#include <iostream>
#include <string>
#include <array>
#include <typeinfo>

template<typename T>
std::string getTypeName() {
    return "unknown";
}

template<>
std::string getTypeName<int>() {
    return "int";
}

template<>
std::string getTypeName<double>() {
    return "double";
}

template<>
std::string getTypeName<std::string>() {
    return "std::string";
}


template<typename T>
class Package {
private:
    T item;
public:
    Package(T i) : item(i) {}
    void label() {
        std::cout << "Generic package containing: " << ::getTypeName<T>() << "\n";
    }
};

// Specialization for std::string
template<>
class Package<std::string> {
private:
    std::string item;
public:
    Package(std::string i) : item(i) {}
    void label() {
        std::cout << "Book package: \"" << item << "\"\n";
    }
};

// Partial specialization for pointers
template<typename T>
class Package<T*> {
private:
    T* item;
public:
    Package(T* i) : item(i) {}
    void label() {
        std::cout << "Fragile package for pointer to type: " << ::getTypeName<T>() << "\n";
    }
};

template<typename T, int Size>
class Box {
private:
    std::array<T, Size> items;
    int count = 0;
public:
    bool addItem(const T& item) {
        if (count < Size) {
            items[count++] = item;
            std::cout << "Added item to box: \"" << item << "\"\n";
            return true;
        }
        return false;
    }

    void printItems() const {
        std::cout << "Box contents:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << " - " << items[i] << "\n";
        }
    }
};

template<typename T>
void shipItem(const T& item) {
    std::cout << "Shipping item of type: " << ::getTypeName<T>() << "\n";
}

template<>
void shipItem(const double& item) {
    std::cout << "Shipping temperature-controlled item: " << item << "°C\n";
}

int main() {
 /*
Generic package containing: int
Book package: "C++ Primer"
Fragile package for pointer to type: double
Added item to box: "The Pragmatic Programmer"
Added item to box: "Clean Code"
Box contents:
- The Pragmatic Programmer
- Clean Code
Shipping item of type: int
Shipping item of type: std::string
Shipping temperature-controlled item: 22.5°C
 */

    // Package int
    Package<int> intPackage(32);
    intPackage.label();

    // Package string
    Package<std::string> bookPackage("C++ Primer");
    bookPackage.label();

    // Package double
    double temp = 40.0;
    Package<double*> fragilePackage(&temp);
    fragilePackage.label();

    // Box string, 3
    Box<std::string, 3> bookBox;
    bookBox.addItem("The Pragmatic Programmer");
    bookBox.addItem("Clean Code");

    // printItems()
    bookBox.printItems();

    // shipitem() int, string, double
    shipItem(10);
    shipItem(std::string("std::string"));
    shipItem(22.5);








    return 0;
}