#ifndef DIR_H
#define DIR_H
#include <iostream>
#include <string>
#include "cfg.h"

class Dir {
private:
	int filescount;
	std::string dir_name;
	std::string filesname[MAXFILES];
	int nowfile = 0;
	int maxindex;
public:
	Dir(std::string );
	// virtual ~Dir();
	void update_files();
	int get_two_files(std::string *);
	int get_new_index();
	void incr_max_index();
	int get_files_count();

	std::string *get_files_name();

};

#endif // DIR_H
