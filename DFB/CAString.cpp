#include "./CAString.h"

CAString::CAString()
{
	_data = 0;
	_data_length = 0;
	CharArray::set("", 1);
}

CAString::CAString(const char* data_)
{
	_data = 0;
	_data_length = 0;
	CharArray::set(data_, CharArray::length(data_) + 1);
}

CAString::CAString(const CAString& to_copy_)
{
	_data = 0;
	_data_length = 0;
	CharArray::set(to_copy_._data, to_copy_._data_size);
}

CAString& CAString::operator=(const CAString& right_hand_side_)
{
	CharArray::set(right_hand_side_._data, right_hand_side_._data_size);
	return *this;
}

CAString& CAString::operator=(const char* right_hand_side_)
{
	CharArray::set(right_hand_side_, CharArray::length(right_hand_side_) + 1);
	return *this;
}

CAString& CAString::operator+=(const CAString& right_hand_side_)
{
	append(right_hand_side_);
	return *this;
}

CAString& CAString::operator+=(const char* right_hand_side_)
{
	append(right_hand_side_);
	return *this;
}

bool CAString::operator==(const CAString& right_hand_side_)
{
	if (_data_size == right_hand_side_._data_size)
	{
		for (size_t index = 0; index < _data_size; index++)
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

bool CAString::operator==(const char* right_hand_side_)
{
	return *this == CAString(right_hand_side_);
}

bool CAString::operator!=(const CAString& right_hand_side_)
{
	return !(*this == right_hand_side_);
}

bool CAString::operator!=(const char* right_hand_side_)
{
	return !(*this == CAString(right_hand_side_));
}

void CAString::append(const CAString& data_)
{
	size_t new_length = _data_size + data_._data_size - 1;
	char* new_data = new char[new_length];
	for (size_t index = 0; index < _data_size - 1; index++)
	{
		new_data[index] = _data[index];
	}
	for (size_t index = 0; index < data_._data_size; index++)
	{
		new_data[_data_size - 1 + index] = data_._data[index];
	}
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
	_data_size = new_length;
	_data_length = _data_size - 1;
}

void CAString::append(const char* data_)
{
	size_t new_length = _data_size + CharArray::length(data_);
	char* new_data = new char[new_length];
	for (size_t index = 0; index < _data_size - 1; index++)
	{
		new_data[index] = _data[index];
	}
	for (size_t index = 0; index < CharArray::length(data_) + 1; index++)
	{
		new_data[_data_size - 1 + index] = data_[index];
	}
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
	_data_size = new_length;
	_data_length = _data_size - 1;
}

void CAString::prepend(const CAString& data_)
{
	size_t new_size = data_._data_length + _data_length;
	char* new_data = new char[new_size];
	for (size_t index = 0; index < data_._data_length; index++)
	{
		new_data[index] = data_._data[index];
	}
	for (size_t index = 0; index <= _data_length; index++)
	{
		new_data[data_._data_length + index] = _data[index];
	}
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
	_data_size = new_size;
	_data_length = new_size - 1;
}

void CAString::prepend(const char* data_)
{
	size_t new_size = CharArray::length(data_) + _data_length;
	char* new_data = new char[new_size];
	for (size_t index = 0; index < CharArray::length(data_); index++)
	{
		new_data[index] = data_[index];
	}
	for (size_t index = 0; index <= _data_length; index++)
	{
		new_data[CharArray::length(data_) + index] = _data[index];
	}
	if (_data)
	{
		delete[] _data;
	}
	_data = new_data;
	_data_size = new_size;
	_data_length = new_size - 1;
}

void CAString::set(const char* data_)
{
	CharArray::set(data_, CharArray::length(data_) + 1);
}

void CAString::set(const CAString& data_)
{
	CharArray::set(data_._data, data_._data_size);
}

unsigned int CAString::length()
{
	return _data_length;
}

CAString CAString::substring(unsigned int inclusive_start_position_, unsigned int inclusive_end_position_)
{
	CAString result;

	result._data = new char[inclusive_end_position_ - inclusive_start_position_ + 2];
	for (unsigned int index = inclusive_start_position_; index <= inclusive_end_position_; index++)
	{
		result._data[index - inclusive_start_position_] = _data[index];
	}
	result._data[inclusive_end_position_ - inclusive_start_position_ + 1] = '\0';
	result._data_size = inclusive_end_position_ - inclusive_start_position_ + 2;
	result._data_length = result._data_size - 1;

	return result;
}

unsigned int CAString::indexOf(const char data_, unsigned int start_position_)
{
	for (unsigned int index = start_position_; index < _data_length; index++)
	{
		if (_data[index] == data_)
		{
			return index;
		}
	}
	return -1;
}

unsigned int CAString::lastIndexOf(const char data_, unsigned int end_position_)
{
	for (int index = end_position_; index >= 0; index--)
	{
		if (_data[index] == data_)
		{
			return index;
		}
	}
	return -1;
}
