#include <cstring>
#include <cassert>
#include <memory>

struct MemoryBuffer
{
    // Data
    char* m_Buffer;
    size_t m_SizeInBytes;

    // Constructor
    MemoryBuffer(const size_t inSizeInBytes)
    : m_Buffer(new char[inSizeInBytes]),
      m_SizeInBytes(inSizeInBytes)
    {
    }

    // Destructor
    ~MemoryBuffer()
    {
        delete[] m_Buffer;
    }

    // Copy constructor
    MemoryBuffer(const MemoryBuffer& inSrc)
    : m_Buffer(new char[inSrc.m_SizeInBytes]),
      m_SizeInBytes(inSrc.m_SizeInBytes)
    {
        memcpy(m_Buffer, inSrc.m_Buffer, m_SizeInBytes);
    }

    // Move constructor
    MemoryBuffer(MemoryBuffer&& inSrc)
    : m_Buffer(inSrc.m_Buffer),
      m_SizeInBytes(inSrc.m_SizeInBytes)
    {
        inSrc.m_Buffer = nullptr;
        inSrc.m_SizeInBytes = 0;
    }

    // Copy assignment operator
    MemoryBuffer& operator=(const MemoryBuffer& inRhs)
    {
        if (this != &inRhs)
        {
            delete[] m_Buffer;
            m_Buffer = new char[inRhs.m_SizeInBytes];
            m_SizeInBytes = inRhs.m_SizeInBytes;
            memcpy(m_Buffer, inRhs.m_Buffer, m_SizeInBytes);
        }
        return *this;
    }

    // Move assignment operator
    MemoryBuffer& operator=(MemoryBuffer&& inRhs)
    {
        if (this != &inRhs)
        {
            m_Buffer = inRhs.m_Buffer;
            m_SizeInBytes = inRhs.m_SizeInBytes;
            inRhs.m_Buffer = nullptr;
            inRhs.m_SizeInBytes = 0;
        }
        return *this;
    }
};

int main() 
{
    // Testing the default constructor
    MemoryBuffer a(512);
    assert(a.m_Buffer != nullptr);
    assert(a.m_SizeInBytes == 512);

    // Testing the Copy constructor
    MemoryBuffer b(a);
    assert(b.m_Buffer != nullptr);
    assert(b.m_SizeInBytes == 512);

    // Testing the Move constructor
    MemoryBuffer c(std::move(b));
    assert(b.m_Buffer == nullptr);
    assert(b.m_SizeInBytes == 0);
    assert(c.m_Buffer != nullptr);
    assert(c.m_SizeInBytes == 512);

    // Testing the assignment operator
    MemoryBuffer d(16);
    d = c;
    assert(d.m_Buffer != nullptr);
    assert(d.m_SizeInBytes == 512);

    // Testing the Move assignment operator
    MemoryBuffer e(16);
    e = std::move(d);
    assert(d.m_Buffer == nullptr);
    assert(d.m_SizeInBytes == 0);
    assert(e.m_Buffer != nullptr);
    assert(e.m_SizeInBytes == 512);

	return 0;
}