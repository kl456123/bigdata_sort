#ifndef UNTILS_H
#define UNTILS_H

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <random>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <sys/types.h>
#include <dirent.h>
#include "Dir.h"
#include "cfg.h"
#include <stdlib.h>
#include "test.h"
#include <time.h>


int open_dir(const char *, std::string *);

template <typename T>
void random_generte(char *filename, bool turc = 0) {
	std::ifstream fin(filename);
	if (fin && !turc) {
		fin.close();
		return;
	}
	fin.close();

	std::ofstream fout;
	fout.open(filename, std::ios::trunc | std::ios::out);
	if (fout.is_open()) {

		fout.precision(PRECISION);
		int nums = MAXLINE;
		std::stringstream buffer;
		buffer << std::setprecision(PRECISION);
		while (nums) {
			for (int i = 0; i < 10; i++) {
				T random_number = static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / MAX));
				buffer << random_number << " ";
			}
			buffer << std::endl;
			nums--;
			if (nums % BUFFERSIZELINES) {
				fout << std::setprecision(PRECISION) << buffer.str();
				buffer.str("");
			}
		}

	}
	std::cout << "data generated done!" << std::endl;
	fout.close();
	return ;

}

void convert_string_to_numbers(std::string , double *, ll );

void convert_numbers_to_string(double *, ll , ll , std::string &);

ll partition(double *, ll , ll );

void quick_sort(double *, ll , ll );

void _merge_files_one(std::ifstream &, std::ifstream &, std::ofstream &);

void merge_array_one(double *, double *, double *, ll , ll );

void merge_dir_one(std::string );

void handler(char *, double *);

void generate_filename(std::string &, int , std::string &);

void merge_files_one(std::string , std::string , std::string );

inline void save_to_file(double *array, std::string filename, ll length);


ll read_to_array(double *array, std:: ifstream &fin, ll length, bool &);

void _merge_files_one_faster(std::ifstream &fin1, std::ifstream &fin2, std::ofstream &fout);

ll read_to_string(std::string &str, std::ifstream &fin, ll lines);
#endif