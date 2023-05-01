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
    intBuffer.put(16);

    // Get data from the buffers
    float value = 0;
    uint8_t value2 = 0;
    floatBuffer.get(value);
    intBuffer.get(value2);

    // Print the value we got from the buffers
    std::cout << "intBuffer value: " << unsigned(value2) << std::endl;
    std::cout << "floatBuffer value: " << value << std::endl;

    //Check that the buffer is now empty
    if(floatBuffer.empty()) std::cout << "floatBuffer empty" << std::endl;
    if(intBuffer.empty()) std::cout << "intBuffer empty" << std::endl;

    return 0;
}
