#pragma once
#include <cstddef>

struct MemoryMappedFile
{
    char *data = nullptr;
    std::size_t size = 0;

    MemoryMappedFile(const char *filename);
    ~MemoryMappedFile();

    MemoryMappedFile(const MemoryMappedFile &) = delete;
    MemoryMappedFile(MemoryMappedFile &&) = default;
    MemoryMappedFile& operator=(const MemoryMappedFile &) = delete;

    inline char* begin() { return data; }
    inline char* end() { return data + size; }

    inline char* begin() const { return data; }
    inline char* end() const { return data + size; }
    inline const char* cbegin() const { return data; }
    inline const char* cend() const { return data + size; }

    inline operator bool() const { return data != nullptr; }
};
