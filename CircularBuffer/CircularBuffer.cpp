#include <stdlib.h>
#include <assert.h>

#include "CircularBuffer.hpp"

template<typename T>
CircularBuffer<T>::CircularBuffer(T *buffer, size_t size)
	: _buffer(buffer), _head(0), _tail(0), _max(size)
{
	assert(buffer && size > 1);

	_buffer = buffer;
	_max = size;

	assert(empty());
}

// For thread safety, do not use put - use try_put.
// Because this version, which will overwrite the existing contents
// of the buffer, will involve modifying the tail pointer, which is also
// modified by get.
template<typename T>
void CircularBuffer<T>::put(T data)
{
	assert(_buffer);

	_buffer[_head] = data;
	if(full())
	{
		// THIS CONDITION IS NOT THREAD SAFE
		_tail = advanceHeadTailValue(_tail, _max);
	}

	_head = advanceHeadTailValue(_head, _max);
}

// This put function is threadsafe because it does not 
// modify the tail pointer.
template<typename T>
int CircularBuffer<T>::tryPut(T data)
{
	assert(_buffer);

	int r = -1;

	if (!full())
	{
		_buffer[_head] = data;
		_head = advanceHeadTailValue(_head, _max);
		r = 0;
	}

	return r;
}

template<typename T>
int CircularBuffer<T>::get(T &data)
{
	assert(_buffer);

	int r = -1;

	if (!empty())
	{
		data = _buffer[_tail];
		_tail = advanceHeadTailValue(_tail, _max);
		r = 0;
	}

	return r;
}

template<typename T>
int CircularBuffer<T>::peek(T &data)
{
	int r = -1;
	assert(_buffer);

	// We can't look beyond the current buffer size
	if (empty() || size() < 1)
	{
		return r;
	}

	data = _buffer[_tail];

	return 0;
}

template<typename T>
int CircularBuffer<T>::removeTailElement()
{
	assert(_buffer);

	int r = -1;

	if (!empty())
	{
		_tail = advanceHeadTailValue(_tail, _max);
		r = 0;
	}

	return r;
}

template<typename T>
size_t CircularBuffer<T>::advanceHeadTailValue(size_t value, size_t max)
{
	// We don't use modulo operator here as modulo is an expensive operation.
	if (++value == max)
	{
		value = 0;
	}

	return value;
}

template<typename T>
bool CircularBuffer<T>::empty()
{
	return _head == _tail;
}

template<typename T>
bool CircularBuffer<T>::full()
{
	// We want to check, not advance, so we don't save the output here
	return advanceHeadTailValue(_head, _max) == _tail;
}

template<typename T>
void CircularBuffer<T>::reset()
{
	_head = 0;
	_tail = 0;
}

template<typename T>
size_t CircularBuffer<T>::capacity()
{
	// We account for the space we can't use for thread safety
	return _max - 1;
}

template<typename T>
size_t CircularBuffer<T>::size()
{
	// We account for the space we can't use for thread safety
	size_t size = _max - 1;

	if (!full())
	{
		if (_head >= _tail)
		{
			size = (_head - _tail);
		}
		else
		{
			size = (_max + _head - _tail);
		}
	}

	return size;
}

// Explicit instantiation of template for supported types.
template class CircularBuffer<double>;
template class CircularBuffer<float>;
template class CircularBuffer<uint32_t>;
template class CircularBuffer<uint16_t>;
template class CircularBuffer<uint8_t>;
template class CircularBuffer<char>;