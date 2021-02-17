#include "shell_code.hpp"
#include <windows.h>

void example()
{
    auto crafter = shell_code();

    crafter.make(0x48, 0xb8, reinterpret_cast<uint64_t>(GetModuleHandleA(nullptr))); // mov rax,<program base>

    uint8_t* buffer = new uint8_t[crafter.size()];
    crafter.get(buffer);

    std::cout << "shell code: " << std::hex;

    for (size_t i = 0; i < crafter.size(); i++) {
        std::cout << static_cast<int>(buffer[i]) << " ";
    }

    delete[] buffer;
}
