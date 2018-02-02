#include "./CharArray.h"

unsigned int CharArray::length(const char* data_)
{
	unsigned int length;
	for (length = 0; data_[length]; length++);
	return length;
}

CharArray::CharArray()
{
	_data = 0;
	_data_size = 0;
}

CharArray::CharArray(const char* data_)
{
	_data = 0;
	_data_size = 0;
	set(data_);
}

CharArray::CharArray(const char* data_, unsigned int data_size_)
{
	_data = 0;
	_data_size = 0;
	set(data_, data_size_);
}

CharArray::CharArray(const CharArray& to_copy_)
{
	_data = 0;
	_data_size = 0;
	set(to_copy_);
}

CharArray::~CharArray()
{
	if (_data)
	{
		delete[] _data;
	}
}

CharArray& CharArray::operator=(const CharArray& right_hand_side_)
{
	set(right_hand_side_);
	return *this;
}

CharArray& CharArray::operator=(const char* right_hand_side_)
{
	set(right_hand_side_);
	return *this;
}

CharArray& CharArray::operator+=(const CharArray& right_hand_side_)
{
	append(right_hand_side_);
	return *this;
}

CharArray& CharArray::operator+=(const char* right_hand_side_)
{
	append(right_hand_side_);
	return *this;
}

bool CharArray::operator==(const CharArray& right_hand_side_)
{
	if (_data_size == right_hand_side_._data_size)
	{
		for (unsigned int index = 0; index < _data_size; index++)
		{
			if (_data[index] != right_hand_side_._data[index])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool CharArray::operator!=(const CharArray& right_hand_side_)
{
	return !(*this == right_hand_side_);
}

void CharArray::append(const CharArray& data_)
{
	append(data_._data, data_._data_size);
}

void CharArray::append(const char* data_)
{
	append(data_, length(data_) + 1);
}

void CharArray::append(const char* data_, unsigned int data_size_)
{
	unsigned int new_size = _data_size + data_size_;
	char* new_data = new char[new_size];
	for (unsigned int index = 0; index < _data_size; index++)
	{
		new_data[index] = _data[index];
	}
	for (unsigned int index = 0; index < data_size_; index++)
	{
		new_data[_data_size + index] = data_[index];
	}
	_data_size = new_size;
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
}

void CharArray::prepend(const CharArray& data_)
{
	prepend(data_._data, data_._data_size);
}

void CharArray::prepend(const char* data_)
{
	prepend(data_, length(data_) + 1);
}

void CharArray::prepend(const char* data_, unsigned int data_size_)
{
	unsigned int new_size = _data_size + data_size_;
	char* new_data = new char[new_size];
	for (unsigned int index = 0; index < data_size_; index++)
	{
		new_data[index] = data_[index];
	}
	for (unsigned int index = 0; index < _data_size; index++)
	{
		new_data[data_size_ + index] = _data[index];
	}
	_data_size = new_size;
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
}

const char* CharArray::get() const
{
	return _data;
}

unsigned int CharArray::size() const
{
	return _data_size;
}

void CharArray::set(const CharArray& data_)
{
	set(data_._data, data_._data_size);
}

void CharArray::set(const char* data_)
{
	set(data_, length(data_) + 1);
}

void CharArray::set(const char* data_, unsigned int data_size_)
{
	if (_data)
	{
		delete[] _data;
	}
	_data_size = data_size_;
	_data = new char[_data_size];
	for (unsigned int index = 0; index < _data_size; index++)
	{
		_data[index] = data_[index];
	}
}
