#include <iostream>
#include "cfg.h"
#include <string>
#include "untils.h"
#include "Dir.h"
#include "test.h"


//#define DEBUG



int num_files = MAXSIZE / MAXARRAY;

double arrays[MAXARRAY];



using namespace std;

void test(std::string filename) {
	test_read_to_array(filename);
}




int main() {

	char filename[10] = "data.txt";
	// random_generte <double> (filename);
	// handler(filename, arrays);
	//	test_merge_file_one("./data/sorted_data_3","./data/sorted_data_4","merged_data");
	string dir_name = "test";

	//	test_open_dir(dir_name);
	//	test_remove();

	merge_dir_one(dir_name);
#ifdef TEST
	// test("./test_/sorted_data_0");
	// test_merge_dir_one(dir_name);
	// test_read_to_string("./_test/sorted_data_0");
#endif

	return 0;
}
