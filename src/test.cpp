#include "test.h"


void test_open_dir(std::string &dir_name) {
	Dir dir = Dir(dir_name);
	int files_count = dir.get_files_count();
	std::string *filesname = dir.get_files_name();
	std::cout << "There are " << files_count << " files in all" << std::endl;
	for (int i = 0; i < files_count; i++) {
		std::cout << filesname[i] << std::endl;
	}
	std::string twofiles[2];
	dir.get_two_files(twofiles);
	if (!twofiles) {
		std::cout << twofiles[0] << " " << twofiles[1] << std::endl;
	}
}

void test_read(std::ifstream &fin, double *array, bool &full) {
	//	ifstream fin(filename);
	if (!fin) {
		std::cout << "Error when reading" << std::endl;
		exit(-1);
	}
	std::string s;

	long long numbers_count = 0;

	while (getline(fin, s)) {
		convert_string_to_numbers(s, array, numbers_count);
		numbers_count += MAXSIZE_PERLINE;
		if (numbers_count == MAXARRAY) {
			full = 1;
			break;
		}
#ifdef DEBUG
		if (numbers_count == 10) {
			break;
		}
#endif // DEBUG
	}

}


void test_memory(double *array, int length) {
	for (int i = 0; i < length; i++) {
		//      write on memory
		array[i] = 0;
		//		read from memory
		//		std::cout<<array[i];
	}
	std::cout << "memory test done!" << std::endl;
	return;
}

void test_print(double *array) {
	int counts = 0;
	while (counts < 10) {
		std::cout << std::setprecision(PRECISION) << array[counts] << " ";
		counts++;
	}
	std::cout << std::endl;

}

void test_quick_sort(double *array) {
	quick_sort(array, 0, 9);
	for (int i = 0; i < 10; i++) {
		std::cout << array[i] << " ";
	}
}

void test_merge_array_one() {
	std::string str1, str2;
	std::ifstream fin("data.txt");
	double array1[MAXSIZE_PERLINE], array2[MAXSIZE_PERLINE], array3[MAXSIZE_PERLINE * 2];
	getline(fin, str1);
	getline(fin, str2);
	convert_string_to_numbers(str1, array1, 0);
	convert_string_to_numbers(str2, array2, 0);
	merge_array_one(array1, array2, array3, MAXSIZE_PERLINE, MAXSIZE_PERLINE);
	for (ll i = 0; i < MAXSIZE_PERLINE * 2; i++) {
		std::cout << std::setprecision(PRECISION) << array3[i] << " ";
	}
	std::cout << std::endl;


}



void test_merge_dir_one(std::string dir_name) {
	Dir dir = Dir(dir_name);
	std::string twofiles[2];
	if (dir.get_two_files(twofiles)) {
		std::cout << "there are not two files" << std::endl;
		return;
	}
	std::string prefix = "./test/merged_data";

	std::string filename;

	generate_filename(prefix, dir.get_new_index(), filename);
	merge_files_one(twofiles[0], twofiles[1], filename);
}

void test_remove() {
	std::string filename = "./test";
	std::ofstream fin;
	fin.open(filename, std::ios::trunc);
	fin.close();
	remove(filename.c_str());
}

void test_read_to_array(std::string filename) {
	ll lines = 10;
	ll length = lines * MAXSIZE_PERLINE;
	double array[length];
	memset(array, 0, sizeof(array));
	std::string str;
	bool empty = 0;
	std::ifstream fin(filename);
	ll real_lines = read_to_array(array, fin, lines, empty);

	std::cout << "test read to array from " << filename << std::endl;
	if (empty) {
		std::cout << "data is not enough !" << std::endl;
	}
	convert_numbers_to_string(array, 0, length, str);
	std::cout << str;
}

void test_read_to_string(std::string filename) {
	ll lines = 10;
	std::ifstream fin(filename);
	std::string str;
	std::cout << "test read to string from " << filename << std::endl;
	ll real_lines = read_to_string(str, fin, lines);
	if (real_lines < lines) {
		std::cout << "data is not enough !" << std::endl;
	}
	std::cout << str;
}
