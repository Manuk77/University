#include <iostream>
#include <cstring>
#include <cctype>

class String {

public:
    // Default constructor
    String() : data(new char[16]), length(0), capacity(16) {}

    // Constructor with char array
    String(const char* str) : length(std::strlen(str)) {
        capacity = length + 16;
        data = new char[capacity];
        std::strcpy(data, str);
    }

    // Copy constructor
    String(const String& other) : length(other.getLength()) {
        capacity = length + 16;
        data = new char[capacity];
        std::strcpy(data, other.getData());
    }

    String(const int& number) {
        std::string str = std::to_string(number);
        capacity = str.length() + 16;
        length = str.length();
        data = new char [capacity];
        for(int i = 0; i < length; ++i) {
            data[i] = str[i];
        }
    }
    // Destructor
    ~String() {
        delete[] data;
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.getLength();
            data = new char[capacity + 16];
            std::strcpy(data, other.getData());
        }
        return *this;
    }

    // Equality operator
    bool operator==(const String& other) const {
        return std::strcmp(data, other.getData()) == 0;
    }

    // Inequality operator
    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    // Addition operator
    String operator+(const String& other) const {
        size_t newLength = length + other.getLength();
        char* newData = new char[newLength + 16];
        std::strcpy(newData, data);
        std::strcat(newData, other.getData());
        String result(newData);
        delete[] newData;
        return result;
    }

    // Subscript operator
    char& operator[](size_t index) {
        if (isValidIndex(index))
            return data[index];
        std::cout<<"index must not be negative!"<<std::endl;
    }

    // Input operator
    friend std::istream& operator>>(std::istream& is, String& str) {
        char buffer[4096];
        is >> buffer;
        str = buffer;
        return is;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.getData();
        return os;
    }

    operator int() const {
        int result;
        std::sscanf(data, "%d", &result);
        return result;
    }

    // Copy method
    String copy() const {
        return String(*this);
    }

    // Substring method
    String subString(size_t start, size_t length) const {
        if (start >= this->length)
            throw std::out_of_range("Start index out of range");

        String result;
        result.setLength(length);
        result.setData(new char[length + 16]);
        std::strncpy(result.getData(), data + start, length);
        result.getData()[length] = '\0';
        return result;
    }

    void remove(size_t start, size_t end) {
        if (start <= end && isValidIndex(start) && isValidIndex(end)) {
            size_t substringLength = end - start + 1;
            size_t newLength = length - substringLength;

            for (size_t i = start; i < length - substringLength; i++) {
                data[i] = data[i + substringLength];
            }

            data[newLength ] = '\0';
            length = newLength;
        }

    }

    void toLower() {
        for (size_t i = 0; i < length; ++i) {
            data[i] = std::tolower(data[i]);
        }
    }

    void toUpper() {
        for (size_t i = 0; i < length; ++i) {
            data[i] = std::toupper(data[i]);
        }
    }
    size_t size() const {
        return length;
    }

    bool isEmpty() const {
        return length == 0;
    }

    bool isSubstring(const String& other) const {
        for (size_t i = 0; i <= length - other.getLength(); ++i) {
            size_t j;

            for (j = 0; j < other.getLength(); ++j) {
                if (data[i + j] != other.getData()[j]) {
                    break;
                }
            }
            if (j == other.getLength()) {
                return true;
            }
        }
        return false;
    }

    size_t getLength() const {
        return length;
    }

    char* getData() const {
        return data;
    }

    void setData(char* newData) {
        data = newData;
        length = std::strlen(newData);
    }


private:
    void setLength(size_t newLength) {
        this->length = newLength;
    }

    char* data;
    size_t length;
    size_t capacity;

    bool isValidIndex(size_t index) {
        if (index >= length)
            return false;
        return true;
    }
};

int main() {
    String str = "123";
    String str1 = str.copy();
    std::cout<<str1<<std::endl;

}
