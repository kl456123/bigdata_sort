#include "untils.h"



void generate_filename(std::string &prefix, int file_index, std::string &filename) {
	std::stringstream str;
	str << prefix << file_index;
	filename = str.str();
}

int open_dir(const char *dir_name, std::string *filesname) {
	DIR *dir = opendir(dir_name);
	struct dirent entry;
	struct dirent * result = &entry;
	int files_count = 0;
	while (true) {
		int res = readdir_r(dir, result, &result);
		if (res == 0) {
			if (result == NULL) {
				break;
			}
			else {
				if (!strcmp(entry.d_name, ".") || !strcmp(entry.d_name, "..")) {
					continue;
				}
				filesname[files_count] = std::string(dir_name) + std::string("/") + std::string(entry.d_name);
				files_count++;
			}
		}
		else {
			std::cout << "read directory fail!" << std::endl;
			exit(-1);
		}

	}
	return files_count;

}



void convert_string_to_numbers(std::string input_string, double *array, ll index) {
	char mask[10] = " \n";
	char *p = strtok(strdup(input_string.c_str()), mask);
	int counts = 0;
	while (p) {
		array[index + counts] = atof(p);
		p = strtok(NULL, mask);
		counts++;

	}
	return;
}

void convert_numbers_to_string(double *array, ll index, ll length, std::string &strout) {
	std::stringstream str;
	str << std::setprecision(PRECISION);

	for (ll i = 0; i < length; i++) {

		str << array[index + i];

		if ((i + 1) % MAXSIZE_PERLINE == 0) {
			str << std::endl;
		}
		else {
			str << " ";
		}
	}
	strout = str.str();
}
ll read_to_string(std::string &str, std::ifstream &fin, ll lines) {
	ll lines_count = 0;

	std::string tmp;
	while (getline(fin, tmp)) {
		// str += " ";
		str += tmp;
		str += "\n";
		lines_count++;
		if (lines_count == lines) {
			break;
		}
	}
	return lines_count;
}

ll read_to_array(double *array, std::ifstream &fin, ll lines, bool &empty) {
	std::string str;
	ll lines_count = read_to_string(str, fin, lines);
	convert_string_to_numbers(str, array, 0);
	if (lines_count < lines) {
		empty = true;
	}
	return lines_count;


}



inline void save_to_file(double *array, std::string filename, ll length) {
	std::ofstream fout;
	fout.open(filename, std::ios::app);

	std::string str;
	ll lines_count = length / MAXSIZE_PERLINE;
	for (ll i = 0; i < lines_count - 1; i++) {
		convert_numbers_to_string(array, i * MAXSIZE_PERLINE, MAXSIZE_PERLINE, str);
		fout << std::setprecision(PRECISION) << str;
	}
	fout.close();
}

ll partition(double *array, ll left, ll right) {
	double key = array[right];
	ll i = left - 1;
	double tmp;
	for (ll j = left; j <= right; j++) {
		if (array[j] <= key) {
			i++;
			tmp = array[j];
			array[j] = array[i];
			array[i] = tmp;
		}
	}

	return i;

}

void quick_sort(double *array, long long left, long long right) {
	//  just select the first one as key
	if (left < right) {
		int mid = partition(array, left, right);
		quick_sort(array, left, mid - 1);
		quick_sort(array, mid + 1, right);
	}
}

void merge_array_one(double *array1, double *array2, double *array3, ll len1, ll len2) {
	int index1 = 0, index2 = 0;
	for (ll k = 0; k < len1 + len2; k++) {
		if (array1[index1] > array2[index2]) {
			array3[k] = array2[index2];
			index2++;
		}
		else {
			array3[k] = array1[index1];
			index1++;
		}

	}
}

void _merge_files_one(std::ifstream &fin1, std::ifstream &fin2, std::ofstream &fout) {
	std::string str1, str2, str3;
	int flag1, flag2;
	fout << std::setprecision(PRECISION);
	double array1[MAXSIZE_PERLINE + 1], array2[MAXSIZE_PERLINE + 1], array3[MAXSIZE_PERLINE * 2];
	array1[MAXSIZE_PERLINE] = INF;
	array2[MAXSIZE_PERLINE] = INF;
	while (true) {
		flag1 = 0;
		flag2 = 0;
		if (getline(fin1, str1)) {
			flag1 = 1;
		}
		if (getline(fin2, str2)) {
			flag2 = 1;
		}
		if (flag1 && flag2) {
			convert_string_to_numbers(str1, array1, 0);
			convert_string_to_numbers(str2, array2, 0);
			merge_array_one(array1, array2, array3, MAXSIZE_PERLINE, MAXSIZE_PERLINE);
			convert_numbers_to_string(array3, 0, MAXSIZE_PERLINE * 2, str3);
			fout << str3;
			str3.clear();
		}
		else {
			if (!flag1 && flag2) {
				fout << str2 << std::endl;
				str2.clear();
			}
			else if (flag1 && !flag2) {
				fout << str1 << std::endl;
				str1.clear();
			}
			else {
				break;
			}
		}
	}
}

void _merge_files_one_faster(std::ifstream &fin1, std::ifstream &fin2, std::ofstream &fout) {
	double array1[BUFFERSIZELINES * MAXSIZE_PERLINE + 1], array2[BUFFERSIZELINES * MAXSIZE_PERLINE + 1], array3[BUFFERSIZELINES * 2];
	array1[BUFFERSIZELINES * MAXSIZE_PERLINE] = INF;
	array2[BUFFERSIZELINES * MAXSIZE_PERLINE] = INF;
	std::string str1, str2, str3;
	ll lines = BUFFERSIZELINES;
	bool empty1, empty2;
	empty1 = false;
	empty2 = false;
	ll real_lines1, real_lines2;

	while (true) {
		if (!empty1) {
			real_lines1 = read_to_string(str1, fin1, lines);
		}
		if (!empty2) {
			real_lines2 = read_to_string(str2, fin2, lines);
		}


		if (real_lines1 && real_lines2) {
			if (real_lines1 < lines) {
				array1[real_lines1 * MAXSIZE_PERLINE] = INF;

			}
			if (real_lines2 < lines) {
				array2[real_lines2 * MAXSIZE_PERLINE] = INF;
			}
			convert_string_to_numbers(str1, array1, 0);
			convert_string_to_numbers(str2, array2, 0);
			merge_array_one(array1, array2, array3, real_lines1 * MAXSIZE_PERLINE, real_lines2 * MAXSIZE_PERLINE);
			convert_numbers_to_string(array3, 0, real_lines1 * MAXSIZE_PERLINE + real_lines2 * MAXSIZE_PERLINE , str3);
			fout << str3;
			str1.clear();
			str2.clear();
			str3.clear();
		}
		if (!real_lines1 && real_lines2) {
			fout << str2;
			empty1 = true;
			str2.clear();
		}
		if (real_lines1 && !real_lines2) {
			fout << str1;
			empty2 = true;
			str1.clear();
		}
		if (!real_lines1 && !real_lines2) {
			break;
		}
	}
}



void handler(char *filename, double *array ) {
	time_t start = time(0);

	std::ifstream fin;
	std::cout << "Read from file " << filename << std::endl;

	fin.open(filename);
	int file_index = 0;
	std::string output_filename = "";
	std::string prefix = "test/sorted_data_";
	//	test_memory(test,MAXARRAY);
	while (true) {
		bool full = 0;
		test_read(fin, array, full);
		//	test_print(test);
		//	test_quick_sort(test);
		quick_sort(array, 0, MAXARRAY - 1);
		generate_filename(prefix, file_index, output_filename);
		save_to_file(array, output_filename, MAXARRAY);
		file_index++;
		if (!full) {
			break;
		}
	}
	fin.close();
	time_t end = time(0);
	double duration = end - start;
	std::cout << std::setprecision(PRECISION - 10);
	std::cout << "mapping time: " << duration << std::endl;
}

void merge_files_one(std::string filename1, std::string filename2, std::string filename3) {
	std::ifstream fin1(filename1);
	std::ifstream fin2(filename2);
	std::ofstream fin3(filename3);
	_merge_files_one_faster(fin1, fin2, fin3);
	fin1.close();
	fin2.close();
	fin3.close();
	remove(filename1.c_str());
	remove(filename2.c_str());
}

void merge_dir_one(std::string dir_name) {
	time_t start = time(0);
	Dir dir = Dir(dir_name);
	std::string twofiles[2];
	while (true) {


		if (dir.get_two_files(twofiles) == -1) {
			break;
		}
		std::string prefix = "./test/merged_data_";
		std::string filename;
		generate_filename(prefix, dir.get_new_index(), filename);
		merge_files_one(twofiles[0], twofiles[1], filename);
	}
	time_t end = time(0);
	double duration = end - start;
	std::cout << std::setprecision(PRECISION - 10);
	std::cout << "reducing time: " << duration << std::endl;

}






