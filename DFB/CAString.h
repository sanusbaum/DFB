#ifndef CASTRING_H
#define CASTRING_H

#include "./CharArray.h" // CharArray

// Author: Spencer Nusbaum
// Date: 1/31/2018
// Class Name: CAString
// Purpose: Provide an encapsulation of '\0' terminated char data, as well as
//     provide operations to assign, add, compare, append, prepend, get and set
//     the internal data.
class CAString : public CharArray
{

	// Different than _data_size from CharArray and is one or zero less than
	// _data_size because it doesn't count the '\0' character as a character.
	unsigned int _data_length;

public:

	// Constructor for empty data
	CAString();
	// Constructor for '\0' terminated data
	CAString(const char* data_);
	// Constructor for a copy of another CAString object
	CAString(const CAString& to_copy_);
	
	// Assignment operator by CAString reference
	CAString& operator=(const CAString& right_hand_side_);
	// Assignment operator by '\0' terminated char data
	CAString& operator=(const char* right_hand_side_);

	// Addition operator by CAString reference
	CAString& operator+=(const CAString& right_hand_side_);
	// Addition operator by '\0' terminated char pointer
	CAString& operator+=(const char* right_hand_side_);

	// Comparison operator by CAString reference for equality
	bool operator==(const CAString& right_hand_side_);
	// Comparison operator by '\0' terminated char pointer for equality
	bool operator==(const char* right_hand_side_);
	// Comparison operator by CAString reference for difference
	bool operator!=(const CAString& right_hand_side_);
	// Comparison operator by '\0' terminated char pointer
	bool operator!=(const char* right_hand_side_);

	// Appending by CAString reference
	virtual void append(const CAString& data_);
	// Appending by '\0' terminated char pointer
	virtual void append(const char* data_);
	
	// Prepending by CAString reference, assumes and manages the terminating '\0'
	virtual void prepend(const CAString& data_);
	// Prepending by '\0' terminated char pointer, assumes and manages the terminating '\0'
	virtual void prepend(const char* data_);

	// Sets internal data to '\0' terminated char pointer
	virtual void set(const char* data_);
	// Sets internal data to CAString reference
	virtual void set(const CAString& data_);

	// Returns length of the data
	unsigned int length();

	// Returns a substring inclusive from it's start to end positions provided
	CAString substring(unsigned int inclusive_start_position_, unsigned int inclusive_end_position_ = -1);
	
	// Returns the index of a specified '\0' terminated char pointer, starting at start_position_
	unsigned int indexOf(const char data_, unsigned int start_position_ = 0);
	
	// Returns the last index of a specified '\0' terminated char pointer, starting at start_position_
	unsigned int lastIndexOf(const char data_, unsigned int end_position_ = -1);

};

#endif // CASTRING_H