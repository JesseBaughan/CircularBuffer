/**
 * @file CircularBuffer.h
 *
 * @brief Provides a thread-safe (for single producer/consumer) implementation
 * of a Circular Buffer.
 * This is heavily based off the github repo found at this link:
 * https://github.com/embeddedartistry/embedded-resources/blob/master/examples/c/circular_buffer_tests/circular_buffer_tests.c
 * 
 * This implementation is threadsafe for a single producer and single consumer
 * because put/get functions only modify head/tail respectively. The result is that
 * this implementation requires 1 extra slot in the buffer which it can't use.
 * To support more than a single produce/consumer, syncronization via mutex (or similar)
 * would be required.
 *
 * MODIFICATIONS:
 * - The orignal C library has been ported to C++ to provide a cleaner interface/implentation.
 *
 * - The peek function has been modified to only allow peeking of the oldest value in the buffer
 * (where tail points too) this is to suit our particular use-case.
 *
 * - A new function called removeTailElement() has been added to allow deleting of the oldest
 * element in the buffer.
 * 
 * - Templated the class. We are currently only handling double, float, uint32_t, uint16_t and uint8_t
 * due to a lack of testing for other types.
 *
 * @author Jesse Baughan - jesse.baughan@gmail.com
 *
 */

#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

template<typename T>
class CircularBuffer
{
public:
    /** @brief Constructor for circular buffer class
     * 
     * @param a pointer to the storage buffer 
     * @param the size of the storage buffer
    */
    CircularBuffer(T *buffer, size_t size);

    /** @brief Threadsafe put function that rejects data is the buffer is full.
     * 
     * @param data being put into the buffer
     * @returns 0 on success, -1 if the buffer is full
    */
    int tryPut(T data);

    /** @brief Non-threadsafe put function that will replace oldest
     * value in buffer if the buffer is full.
     * 
     * @param data being put into the buffer
    */
    void put(T data);

    /** @brief Retrieve a value from the buffer
     * 
     * @param data being returned from the buffer
     * @returns 0 on success, -1 if the buffer is empty
    */
    int get(T &data);

    /** @brief Look at the value located at the tail index (oldest)
     *  without removing it from the buffer.
     * 
     * @param data being returned from the buffer
    */
    int peek(T &data);

    /** @brief Deletes the element located at the tail of the buffer 
     * 
     * @returns 0 on success, -1 if the buffer is empty 
    */
    int removeTailElement();

    /** @brief Checks if the buffer is empty
     * 
     * @returns true if the buffer is empty
    */
    bool empty();

    /** @brief Checks if the buffer is full
     * 
     * @returns true if the buffer is full
    */
    bool full();

    /** @brief Check the capacity of the buffer
     * 
     * @returns the maximum capacity of the buffer
    */
    size_t capacity();

    /** @brief Check the number of elements currently stored in the buffer
     * 
     * @returns numbner of elements in the buffer
    */
    size_t size();

    /** @brief Reset buffer back to starting state (head == tail)
    */
    void reset();

private:
    static inline size_t advanceHeadTailValue(size_t value, size_t max);

    T* _buffer;
    size_t _head;
    size_t _tail;
    size_t _max; // of the buffer
};

#endif /* _CIRCULAR_BUFFER_ */
