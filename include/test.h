#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include "Dir.h"
#include "untils.h"
#include "cfg.h"
#include <stdlib.h>
#include <string.h>

void test_open_dir(std::string &);
void test_read(std::ifstream &, double *, bool &);
void test_memory(double *, int );

void test_remove();

void test_merge_dir_one(std::string );



void test_merge_array_one() ;
void test_read_to_string(std::string);
void test_quick_sort(double *);
void test_print(double *);
void test_read_to_array(std::string );

#endif