#include "MemoryMappedFile.hpp"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstdlib>
#include <utility>

MemoryMappedFile::MemoryMappedFile(const char *filename)
{
    struct stat fileStats;
    if (stat(filename, &fileStats) == 0) {
        size = std::move(fileStats).st_size;
        const auto fd = open(filename, O_RDONLY);       
        if (fd == -1)
            return;

        const auto addr = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
        close(fd);

        if (addr == MAP_FAILED) 
            return;

        data = static_cast<char*>(addr);
    }
}

MemoryMappedFile::~MemoryMappedFile()
{
    if (data != nullptr)
        munmap(data, size);
}
