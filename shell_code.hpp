#include <iostream>

class shell_code {
private:
    uint8_t* buffer{};
    size_t buffer_size = 0;
public:
    shell_code() {
        buffer = new uint8_t[0x1000];
    }

    ~shell_code() {
        delete[] buffer;
    }

    template<typename T>
    void make(const T& v) {
        if (std::is_same<T, int>::value) {
            *reinterpret_cast<uint8_t*>(buffer + buffer_size) = *reinterpret_cast<const uint8_t*>(&v);
            buffer_size += sizeof(uint8_t);
        }
        else {
            *reinterpret_cast<T*>(buffer + buffer_size) = v;
            buffer_size += sizeof(T);
        }
    }

    template<typename F, typename... R>
    void make(const F& first, const R&... rest)
    {
        make(first);
        make(rest...);
    }

    void get(uint8_t* getter) {
        for (size_t i = 0; i < buffer_size; i++) {
            getter[i] = buffer[i];
        }
    }

    void* get() {
        return buffer;
    }

    size_t size() {
        return buffer_size;
    }
};