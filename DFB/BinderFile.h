#ifndef BINDERFILE_H
#define BINDERFILE_H

#include "./CAString.h" // CAString, CharArray
#include <fstream> // std::ifstream
#include <Windows.h> // STARTUPINFO, PROCESS_INFORMATION, ZeroMemory, text_wchar, mbstowcs, CreateProcess

// Author: Spencer Nusbaum
// Date: 2/1/2018
// Class Name: BinderFile
// Purpose: Provide an encapsulation of a file and its' attributes/properties. Specifically, the
//     import path, export path, file data, file extras (such as read-only, etc.), and an execute
//     string for the file, to execute in a new process if set.
class BinderFile
{

	// BinderFile properties
	CAString _import_path;
	CAString _export_path;
	CharArray _file_data;
	CAString _file_extras;
	CAString _execute_string;

protected:

	// Returns the length of the CharArray data_, in a 10 character CharArray
	static CharArray length(CharArray data_);

	// Returns the equivalent decimal number represented in a 10 character char*, into an 
	//     unsigned int
	static unsigned int atoi(const char* data_);

public:

	// Constructor for new BinderFile of blank properties
	BinderFile();
	// Constructor for existing BinderFile data in a CharArray format
	BinderFile(CharArray import_string_);
	// Constructor for specification of each BinderFile property
	BinderFile(
		CAString import_path_,
		CAString export_path_,
		CharArray file_data_,
		CAString file_extras_,
		CAString execute_string_);
	// Constructor for an existing file path, import_path_, for properties to be set from
	BinderFile(CAString import_path_);

	// Returns the import path
	CAString get_import_path();
	// Returns the export path
	CAString get_export_path();
	// Returns the file data
	CharArray get_file_data();
	// Returns the file extras data
	CAString get_file_extras();
	// Returns the execute string 
	CAString get_execute_string();

	// Sets the import path
	void set_import_path(CAString import_path_);
	// Sets the export path
	void set_export_path(CAString export_path_);
	// Sets the file data
	void set_file_data(CharArray file_data_);
	// Sets the file extras data
	void set_file_extras(CAString file_extras_);
	// Sets the execute string
	void set_execute_string(CAString execute_string_);

	// Returns an exported form of the BinderFile properties, that can later be imported by
	//     BinderFile
	CharArray generate_export_string();

	// Reimports the file from the import path set in the BinderFile properties
	void reimport();
	// Exports the file to the export path set in the BinderFile properties
	void export_file();
	// Exports the file to the temporary_export_path_
	void export_file(CAString temporary_export_path_);

	// Executes the execute string in the BinderFile properties in a new process
	void execute();

};

#endif // BINDERFILE_H