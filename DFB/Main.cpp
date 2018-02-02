#include "./Binder.h" // Binder, BinderFile, CAString, CharArray
#include <iostream> // std::cout, std::endl;
#include <cstdlib> // exit, atoi

void show_usage(const char* path_)
{
	std::cout << path_ << std::endl;
	std::cout << std::endl;
	std::cout << "\t a [<filename>] [<export_path>][<execute_string>] add a file" << std::endl;
	std::cout << "\t e [<file_id>[<export_path>]] export files" << std::endl;
	std::cout << "\t i [<file_id>] import files again from original import paths" << std::endl;
	std::cout << "\t l [<file_id>] list all files" << std::endl;
	std::cout << "\t r [<file_id>] remove file" << std::endl;
	std::cout << "\t x [<file_id>] execute file" << std::endl;
	std::cout << "\t h help" << std::endl;
}

int main(int argc_, char** argv_)
{
	CAString binder_path(argv_[0]);
	Binder binder(binder_path);

	if (argc_ == 1)
	{
		show_usage(argv_[0]);
		exit(1);
	}
	else if (argc_ >= 2)
	{
		switch (argv_[1][0])
		{
		case 'a':
		case 'A':
			{
				// add
				if (argc_ < 3)
				{
					std::cout << "Invalid usage" << std::endl;
					show_usage(argv_[0]);
					exit(1);
				}
			
				CAString file_path(argv_[2]);
				BinderFile* file = new BinderFile(file_path);

				if (argc_ >= 4)
				{
					CAString export_path(argv_[3]);
					file->set_export_path(export_path);
				}

				if (argc_ >= 5)
				{
					CAString execute_string(argv_[4]);
					file->set_execute_string(execute_string);
				}

				binder.add_file(file);

				binder.save();

				break;
			}
		case 'e':
		case 'E':
			// export
			if (argc_ == 3)
			{
				unsigned int file_id = atoi(argv_[2]);
				if (file_id < binder.get_number_of_files())
				{
					binder.get_file(file_id)->export_file();
				}
				else
				{
					std::cout << "Invalid file ID" << std::endl;
				}
			}
			else if (argc_ == 4)
			{
				unsigned int file_id = atoi(argv_[2]);
				if (file_id < binder.get_number_of_files())
				{
					binder.get_file(file_id)->export_file(argv_[3]);
				}
				else
				{
					std::cout << "Invalid file ID" << std::endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < binder.get_number_of_files(); i++)
				{
					binder.get_file(i)->export_file();
				}
			}
			break;
		case 'i':
		case 'I':
			// import files again
			if (argc_ == 3)
			{
				unsigned int file_id = atoi(argv_[2]);
				if (file_id < binder.get_number_of_files())
				{
					binder.get_file(file_id)->reimport();
				}
				else
				{
					std::cout << "Invalid file ID" << std::endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < binder.get_number_of_files(); i++)
				{
					binder.get_file(i)->reimport();
				}
			}

			binder.save();

			break;
		case 'l':
		case 'L':
			// list files
			if (argc_ == 3)
			{
				std::cout << atoi(argv_[2]) << ".) " << binder.get_file(atoi(argv_[2]))->get_import_path().get() << ", " << binder.get_file(atoi(argv_[2]))->get_export_path().get() << std::endl;
			}
			else
			{
				std::cout << "Number of files: " << binder.get_number_of_files() << std::endl;
				std::cout << std::endl;
				std::cout << "ID.) Import Path, Export Path, Execute String" << std::endl;
				for (unsigned int i = 0; i < binder.get_number_of_files(); i++)
				{
					std::cout << i << ".) " << binder.get_file(i)->get_import_path().get() << ", " << binder.get_file(i)->get_export_path().get() << ", " << binder.get_file(i)->get_execute_string().get() << std::endl;
				}
			}
			break;
		case 'r':
		case 'R':
			// remove files
			{
				if (argc_ == 3)
				{
					unsigned int file_id = atoi(argv_[2]);
					if (file_id < binder.get_number_of_files())
					{
						binder.remove_file(file_id);
					}
					else
					{
						std::cout << "Invalid file ID" << std::endl;
					}
				}
				else
				{
					for (unsigned int i = 0; i < binder.get_number_of_files(); i++)
					{
						binder.remove_file(i);
					}
				}

				binder.save();

				break;
			}
		case 'x':
		case 'X':
			// execute file(s)
			if (argc_ == 3)
			{
				unsigned int file_id = atoi(argv_[2]);
				if (file_id < binder.get_number_of_files())
				{
					binder.get_file(file_id)->execute();
				}
				else
				{
					std::cout << "Invalid file ID" << std::endl;
				}
			}
			else
			{
				for (unsigned int i = 0; i < binder.get_number_of_files(); i++)
				{
					binder.get_file(i)->execute();
				}
			}
			Sleep(1000);

			break;
		case 'h':
		case 'H':
			show_usage(argv_[0]);
			exit(1);
		default:
			std::cout << "Invalid usage" << std::endl;
			show_usage(argv_[0]);
			exit(1);
		}
	}

	return 0;
}