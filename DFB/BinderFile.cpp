#include "./BinderFile.h"

CharArray BinderFile::length(CharArray data_)
{
	CharArray result;
	unsigned int data_size = data_.size();
	while (data_size)
	{
		unsigned int data_size_part = data_size % 10;
		char data_number = data_size_part + '0';
		result.prepend(&data_number, 1);
		data_size /= 10;
	}
	for (int i = result.size(); i < 10; i++)
	{
		result.prepend("0", 1);
	}

	return result;
}

unsigned int BinderFile::atoi(const char* data_)
{
	unsigned int value = 0;
	for (int i = 0; data_[i] != '\0'; i++)
	{
		value *= 10;
		value += data_[i] - '0';
	}
	return value;
}

BinderFile::BinderFile()
{
}

BinderFile::BinderFile(CharArray import_string_)
{
	unsigned int position = 0;
	char number[11];

	// _import_path
	for (int i = 0; i < 11; i++)
	{
		number[i] = import_string_.get()[position + i];
	}
	if (number[10] == ':')
	{
		number[10] = '\0';
		unsigned int import_path_size = atoi(number);
		
		_import_path.CharArray::set(import_string_.get() + 11, import_path_size);
		position += 11 + import_path_size;
	}

	// _export_path
	for (int i = 0; i < 11; i++)
	{
		number[i] = import_string_.get()[position + i];
	}
	if (number[10] == ':')
	{
		number[10] = '\0';
		unsigned int import_path_size = atoi(number);
		
		_export_path.CharArray::set(import_string_.get() + 11 + position, import_path_size);
		position += 11 + import_path_size;
	}

	// _file_data
	for (int i = 0; i < 11; i++)
	{
		number[i] = import_string_.get()[position + i];
	}
	if (number[10] == ':')
	{
		number[10] = '\0';
		unsigned int import_path_size = atoi(number);
		
		_file_data.set(import_string_.get() + 11 + position, import_path_size);
		position += 11 + import_path_size;
	}

	// _file_extras
	for (int i = 0; i < 11; i++)
	{
		number[i] = import_string_.get()[position + i];
	}
	if (number[10] == ':')
	{
		number[10] = '\0';
		unsigned int import_path_size = atoi(number);
		
		_file_extras.CharArray::set(import_string_.get() + 11 + position, import_path_size);
		position += 11 + import_path_size;
	}

	// _execute_string
	for (int i = 0; i < 11; i++)
	{
		number[i] = import_string_.get()[position + i];
	}
	if (number[10] == ':')
	{
		number[10] = '\0';
		unsigned int import_path_size = atoi(number);
		
		_execute_string.CharArray::set(import_string_.get() + 11 + position, import_path_size);
		position += 11 + import_path_size;
	}
}

BinderFile::BinderFile(
	CAString import_path_,
	CAString export_path_,
	CharArray file_data_,
	CAString file_extras_,
	CAString execute_string_)
{
	_import_path = import_path_;
	_export_path = export_path_;
	_file_data = file_data_;
	_file_extras = file_extras_;
	_execute_string = execute_string_;
}

BinderFile::BinderFile(CAString import_path_) // only sets _import_path and _file_data
{
	_import_path = import_path_;
	
	// ex: C:\path\to\file.exe
	// ex: C:/path/to/file.exe
	// ex: path_to_file.exe
	unsigned int start_position = import_path_.lastIndexOf('/');
	if (start_position == -1)
	{
		start_position = import_path_.lastIndexOf('\\');
		if (start_position == -1)
		{
			_export_path = import_path_;
		}
		else
		{
			_export_path = import_path_.substring(start_position + 1);
		}
	}
	else
	{
		_export_path = import_path_.substring(start_position + 1);
	}

	std::ifstream import_file(import_path_.get(), std::ios::in | std::ios::binary);
	if (import_file)
	{
		import_file.seekg(0, import_file.end);
		size_t import_file_size = import_file.tellg();
		import_file.seekg(0, import_file.beg);
		char* file_data = new char[import_file_size];
		import_file.read(file_data, import_file_size);
		_file_data.set(file_data, import_file_size);
		delete[] file_data;

		import_file.close();
	}
}

CAString BinderFile::get_import_path()
{
	return _import_path;
}

CAString BinderFile::get_export_path()
{
	return _export_path;
}

CharArray BinderFile::get_file_data()
{
	return _file_data;
}

CAString BinderFile::get_file_extras()
{
	return _file_extras;
}

CAString BinderFile::get_execute_string()
{
	return _execute_string;
}

void BinderFile::set_import_path(CAString import_path_)
{
	_import_path = import_path_;
}

void BinderFile::set_export_path(CAString export_path_)
{
	_export_path = export_path_;
}

void BinderFile::set_file_data(CharArray file_data_)
{
	_file_data = file_data_;
}

void BinderFile::set_file_extras(CAString file_extras_)
{
	_file_extras = file_extras_;
}

void BinderFile::set_execute_string(CAString execute_string_)
{
	_execute_string = execute_string_;
}

CharArray BinderFile::generate_export_string()
{
	CharArray result;

	result.append(length(_import_path));
	result.append(":", 1);
	result.append(_import_path);

	result.append(length(_export_path));
	result.append(":", 1);
	result.append(_export_path);

	result.append(length(_file_data));
	result.append(":", 1);
	result.append(_file_data);

	result.append(length(_file_extras));
	result.append(":", 1);
	result.append(_file_extras);

	result.append(length(_execute_string));
	result.append(":", 1);
	result.append(_execute_string);

	return result;
}

void BinderFile::reimport()
{
	std::ifstream input_file(_import_path.get(), std::ios::in | std::ios::binary);
	if (input_file)
	{
		input_file.seekg(0, input_file.end);
		unsigned int size_of_input_file = input_file.tellg();
		input_file.seekg(0, input_file.beg);
		char* buffer_for_input_file = new char[size_of_input_file];
		input_file.read(buffer_for_input_file, size_of_input_file);

		_file_data.set(buffer_for_input_file, size_of_input_file);

		input_file.close();
	}
}

void BinderFile::export_file()
{
	std::ofstream output_file(_export_path.get(), std::ios::out | std::ios::binary);
	if (output_file)
	{
		output_file.write(_file_data.get(), _file_data.size());
		output_file.close();
	}
}

void BinderFile::export_file(CAString temporary_export_path_)
{
	std::ofstream output_file(temporary_export_path_.get(), std::ios::out | std::ios::binary);
	if (output_file)
	{
		output_file.write(_file_data.get(), _file_data.size());
		output_file.close();
	}
}

void BinderFile::execute()
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	size_t length = strlen(_execute_string.get());
	std::wstring text_wchar(length, L'#');
	mbstowcs(&text_wchar[0], _execute_string.get(), length);

	CreateProcess(NULL, &text_wchar[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
}