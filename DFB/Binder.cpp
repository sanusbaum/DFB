#include "./Binder.h"

void Binder::import()
{
	std::ifstream binder_file(_binder_path.get(), std::ios::in | std::ios::binary);
	if (binder_file)
	{
		// seek the end of the file to get the file size
		binder_file.seekg(0, binder_file.end);
		unsigned int size_of_binder_file = binder_file.tellg();

		// seek 11 behind the end of the file to try to get the binder binary size
		binder_file.seekg(size_of_binder_file - 11, binder_file.beg);
		char* number = new char[11];
		binder_file.read(number, 11);
		
		if (number[10] == ':')
		{
			// calculate binder binary size
		    unsigned int binder_binary_size = 0;
			number[10] = '\0';
			for (int i = 0; number[i] != '\0'; i++)
			{
				binder_binary_size *= 10;
				binder_binary_size += number[i] - '0';
			}

			// seek the begining of the binary and store the binder binary
			char* binder_binary = new char[binder_binary_size];
			binder_file.seekg(0, binder_file.beg);
			binder_file.read(binder_binary, binder_binary_size);
			_binder_binary.set(binder_binary, binder_binary_size);

			// store the position of the next data segment
			unsigned int binder_file_position = binder_file.tellg();

			// for the rest of the data in the file except the last 11 which we already read in, do...
			while (binder_file_position < size_of_binder_file - 11)
			{
				// read in the next 11 for the next data unit size
				binder_file.read(number, 11);
				number[10] = '\0';
				
				// calculate the data segment size
				unsigned int data_segment_size = 0;
				for (int i = 0; number[i] != '\0'; i++)
				{
					data_segment_size *= 10;
					data_segment_size += number[i] - '0';
				}

				// read in the next data segment of data segment size
				char* data_segment = new char[data_segment_size];
				binder_file.read(data_segment, data_segment_size);

				// convert the data segment into a CharArray
				CharArray data_segment_castring(data_segment, data_segment_size);

				// Allow BinderFile to parse data_segment_castring
				_files.push_back(new BinderFile(data_segment_castring));

				// update the position of the file we are in for the while loop conditional
				binder_file_position = binder_file.tellg();
			}
		}
		else
		{
			// seek the begining of the binary and store the binder binary
			char* binder_binary = new char[size_of_binder_file];
			binder_file.seekg(0, binder_file.beg);
			binder_file.read(binder_binary, size_of_binder_file);
			_binder_binary.set(binder_binary, size_of_binder_file);
		}
	}
}

CharArray Binder::length(CharArray data_)
{
	CharArray result;

	// calculate a CharArray version of the data_size
	unsigned int data_size = data_.size();
	while (data_size)
	{
		unsigned int data_size_part = data_size % 10;
		char data_number = data_size_part + '0';
		result.prepend(&data_number, 1);
		data_size /= 10;
	}

	// make the result ten digits
	for (int i = result.size(); i < 10; i++)
	{
		result.prepend("0", 1);
	}

	return result;
}

Binder::Binder(CAString binder_path_)
{
	_binder_path = binder_path_;

	import();
}

Binder::~Binder()
{
	for (unsigned int index = 0; index < _files.size(); index++)
	{
		delete _files.at(index);
	}
}

void Binder::add_file(BinderFile* file_)
{
	_files.push_back(file_);
}

BinderFile* Binder::get_file(unsigned int index_)
{
	if (index_ < _files.size())
	{
		return _files.at(index_);
	}
	return NULL;
}

unsigned int Binder::get_number_of_files()
{
	return _files.size();
}

void Binder::save()
{
	CAString binder_path = _binder_path;
	binder_path.append(".temporary");

	std::ofstream binder_file(binder_path.get(), std::ios::out | std::ios::binary);
	if (binder_file)
	{
		// write the binder binary
		binder_file.write(_binder_binary.get(), _binder_binary.size());

		// write the files via generate_export_string() on BinderFile objects
		for (unsigned int i = 0; i < _files.size(); i++)
		{
			CharArray file_length = length(_files.at(i)->generate_export_string());
			file_length.append(":", 1);
			binder_file.write(file_length.get(), file_length.size());
			binder_file.write(_files.at(i)->generate_export_string().get(), _files.at(i)->generate_export_string().size());
		}

		// write the length of the binder binary, as a string of ten digits at
		// the end of the file, followed by a ':'
		CharArray binder_file_length = length(_binder_binary);
		binder_file_length.append(":", 1);
		binder_file.write(binder_file_length.get(), binder_file_length.size());

		// clean up resources
		binder_file.close();
		
		// Create rename path for the running binary
		CAString rename_path(_binder_path);
		rename_path += ".temp";

		// Remove the rename path file if it exists
		remove(rename_path.get());

		// Swaps the original binary path name to the rename path, then the
		//     .temporary file created earlier in binder_path renamed to the
		//     original binary path name
		rename(_binder_path.get(), rename_path.get());
		rename(binder_path.get(), _binder_path.get());
	}
}

bool Binder::remove_file(unsigned int index_)
{
	if (index_ < _files.size())
	{
		_files.erase(_files.begin() + index_);
		return true;
	}
	return false;
}