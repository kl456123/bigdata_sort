#include "Dir.h"
#include "untils.h"

Dir::Dir(std::string dir_name) {
	this->dir_name = dir_name;
	this->filescount = open_dir(this->dir_name.c_str(), this->filesname);
	this->maxindex = this->filescount - 1;
}
void Dir::update_files() {
	this->filescount = open_dir(this->dir_name.c_str(), this->filesname);
	this->nowfile = 0;
}
int Dir::get_two_files(std::string *twofiles) {


	if (this->nowfile + 1 >= this->filescount) {
		this->update_files();
	}
	if (this->filescount == 1) {

		return -1;
	}
	twofiles[0] = this->filesname[this->nowfile];
	twofiles[1] = this->filesname[this->nowfile + 1];
	this->nowfile += 2;
	return 0;
}

int Dir::get_new_index() {

	this->incr_max_index();
	return this->maxindex;
}
void Dir::incr_max_index() {
	this->maxindex++;
}
int Dir::get_files_count() {
	return this->filescount;
}
std::string * Dir::get_files_name() {
	return this->filesname;
}



