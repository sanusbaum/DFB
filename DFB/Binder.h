#ifndef BINDER_H
#define BINDER_H

#include <fstream> // std::ifstream, std::ofstream
#include <vector> // std::vector
#include "./BinderFile.h" // BinderFile, CAString, CharArray

// Author: Spencer Nusbaum
// Date: 2/2/2018
// Class Name: Binder
// Purpose: Provide functionality similar to a physical binder, but for digital file objects. Allow
//     to add files, get files, remove files, import, and export files.
class Binder
{

	std::vector<BinderFile*> _files;
	CAString _binder_path;
	CharArray _binder_binary;

	// Imports the digital file binder binary data based off the configured binder binary path.
	// Imports binder binary in format:
	//     <binder_binary>
	//     <file_data>
	//     <binder_size>:
	// where binder_size is a ten digit string representing the number of bytes in
	// the binder binary.
	void import();

	// Returns the length of the CharArray data_, in a 10 character CharArray
	static CharArray length(CharArray data_);

public:

	// Constructor which takes the path to the digital file binder binary
	Binder(CAString binder_path_);

	// Deconstructor cleans up allocated file resources
	~Binder();

	// Adds a file to the internal collection of files
	void add_file(BinderFile* file_);

	// Gets a file from the internal collection of files at the specified index_ if it exists
	BinderFile* get_file(unsigned int index_);

	// Returns the number of files in the internal collection of files
	unsigned int get_number_of_files();

	// Saves the digital file binder binary with the current Binder properties
	void save();

	// Removes a file from the internal collection of files at the specified index_ if it exists
	bool remove_file(unsigned int index_);

};

#endif // BINDER_H