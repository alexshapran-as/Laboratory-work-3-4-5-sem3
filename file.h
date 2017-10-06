#pragma once
#ifndef FILE_H_
#define FILE_H_
#include <string>
#include <vector>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
void ls(std::string);
void cp(std::string&,std::string&);
std::vector<std::string> find(std::string,const std::string&);
void demo_perms(fs::perms p);
#endif