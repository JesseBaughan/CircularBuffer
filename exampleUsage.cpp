#include <iostream>
#include "CircularBuffer.hpp"

#define CIRCULAR_BUFFER_SIZE 8

int main(int argc, char *argv[])
{
    // Deifine the storage
    static float circular_buffer1_storage[CIRCULAR_BUFFER_SIZE] = {0};
    static uint8_t circular_buffer2_storage[CIRCULAR_BUFFER_SIZE] = {0};

    // Instantiate the buffer classes for each type specification
    CircularBuffer<float> floatBuffer(circular_buffer1_storage, CIRCULAR_BUFFER_SIZE);
    CircularBuffer<uint8_t> intBuffer(circular_buffer2_storage, CIRCULAR_BUFFER_SIZE);

    // Put some data in the buffers
    floatBuffer.put(69.69);
    uint8_t poo = 16;
    intBuffer.put(poo);

    float value = 0;
    floatBuffer.get(value);
    std::cout << "floatBuffer value: " << value << std::endl;

    uint8_t value2 = 0;
    intBuffer.get(value2);
    std::cout << "intBuffer value: " << unsigned(value2) << std::endl;

    //Check that the buffer is now empty

    return 0;
}
