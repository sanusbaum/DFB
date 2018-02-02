#ifndef CHARARRAY_H
#define CHARARRAY_H

// Author: Spencer Nusbaum
// Date: 1/31/2018
// Class Name: CharArray
// Purpose: Provide an encapsulation of char data and its' size. Allow
//     operations to assign, add, compare, append, prepend, get, and set the
//     internal data.
class CharArray
{
	
protected:

	// protected so subclasses can manage data and data size
	unsigned int _data_size;
	char* _data;

	// returns the length of a '\0' terminated char array
	unsigned int length(const char* data_);

public:

	// Constructor for empty data and size;
	CharArray(); 
	// Constructor for '\0' terminated data
	CharArray(const char* data_);
	// Constructor for data of a specific size
	CharArray(const char* data_, unsigned int data_size_);
	// Constructor for a copy of another CharArray object
	CharArray(const CharArray& to_copy_);

	// Deconstructor to free allocated resources
	~CharArray();

	// Assignment operator by CharArray reference
	CharArray& operator=(const CharArray& right_hand_side_);
	// Assignment operator by '\0' terminated char pointer
	CharArray& operator=(const char* right_hand_side_);
	// Addition operator by CharArray reference
	CharArray& operator+=(const CharArray& right_hand_side_);
	// Addition operator by char array pointer
	CharArray& operator+=(const char* right_hand_side_);

	// Comparison operator for equality
	bool operator==(const CharArray& right_hand_side_);
	// Comparison operator for difference
	bool operator!=(const CharArray& right_hand_side_);
	
	// Appending by CharArray reference
	virtual void append(const CharArray& data_);
	// Appending by '\0' terminated data
	virtual void append(const char* data_);
	// Appending by data of specific size
	virtual void append(const char* data_, unsigned int data_size_);

	// Prepending by CharArray reference
	virtual void prepend(const CharArray& data_);
	// Prepending by '\0' terminated data
	virtual void prepend(const char* data_);
	// Prepending by data of a specific size
	virtual void prepend(const char* data_, unsigned int data_size_);

	// returns internal data pointer
	const char* get() const;

	// returns size of internal data
	unsigned int size() const;

	// Sets internal data to a CharArray reference
	virtual void set(const CharArray& data_);
	// Sets internal data to '\0' terminated data
	virtual void set(const char* data_);
	// Sets internal data to data of a specific size
	virtual void set(const char* data_, unsigned int data_size_);

};

#endif // CHARARRAY_H