#include "stdafx.h"
#include <iostream>
#include "file.h"
#include <experimental/filesystem>
#include <sys\stat.h>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

namespace fs = std::experimental::filesystem;

void ls(std::string basepath)
{
	system("chcp 1251");
	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;
	using std::ios_base;

	std::ofstream fout;
	fout.open("C:/cpp/texts/files.txt");
	if (!fout.is_open())
	{
		cout << "[-] �� ���������� ������� ����!";
		cin.get();
		exit(EXIT_FAILURE);
	}

	string * str; // ������ � ����������� � ������ � ����������
	string temp;
	unsigned int count = { 0 }; // ���������� ������ � ���������� (���-�� ����� � ��������� �����)

	fs::path p = basepath; // ����

	for (auto & it : fs::recursive_directory_iterator(p)) // ����������� �������� - �������� �� ���� ������, ������ � ���������
		fout << it << endl;
	fout.close();

	std::ifstream fin;
	fin.open("C:/cpp/texts/files.txt");
	if (!fin.is_open())
	{
		cout << "[-] �� ���������� ������� ����!";
		cin.get();
		exit(EXIT_FAILURE);
	}
	while (!fin.eof())
	{
		while (getline(fin, temp))
		{
			count++;
		}
	}
	fin.clear();
	fin.seekg(0, ios_base::beg);
	cout << endl << "� �������� " << p << " ��������� ��������� ����� � �����:" << endl;
	str = new string[count];
	for (unsigned int i = { 0 }; i < count; ++i)
	{
		getline(fin, str[i]);
		str[i].erase(0, basepath.size() + 1); // ������� ���������� � ����, ��������� ������ �������� ������, ����������
		cout << str[i];
		string temp = basepath;
		temp += "\\" + str[i];
		p = temp;
		try
		{
			cout << endl << "������: " << fs::file_size(p) << " ����";
		}
		catch (fs::filesystem_error& e)
		{
			cout << " - ����������";
		}
		struct stat buff;
		stat(basepath.c_str(), &buff);
		struct tm * timeinfo = localtime(&buff.st_ctime); 
		cout << endl << asctime(timeinfo);
		demo_perms(fs::status(p).permissions());
		cout << endl;
		//std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime); // assuming system_clock
		//std::cout << endl << "����� ���������� ���������: " << std::asctime(std::localtime(&cftime));
	}

	fin.close();
	//string name = "Doooone";
	//fs::path p = basepath +"/"+ name;
	//fs::create_directories(p / "web" / "css");
	delete[] str;
}

void demo_perms(fs::perms p)
{
	std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "�������� ������" : "-") << std::endl
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "�������� ������" : "-") << std::endl
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "�������� ����������/�����" : "-") << std::endl
		<< ((p & fs::perms::group_read) != fs::perms::none ? "� ������ ������������� ����� ���� ���������� �� ������" : "-") << std::endl
		<< ((p & fs::perms::group_write) != fs::perms::none ? "� ������ ������������� ����� ���� ���������� �� ������" : "-") << std::endl
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "� ������ ������������� ����� ���� ���������� �� ���������� / �����" : "-") << std::endl
		<< ((p & fs::perms::others_read) != fs::perms::none ? "������ ������������ ����� ���������� �� ������" : "-") << std::endl
		<< ((p & fs::perms::others_write) != fs::perms::none ? "������ ������������ ����� ���������� �� ������" : "-") << std::endl
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "������ ������������ ����� ���������� �� ����������/�����" : "-") << std::endl;
}

void cp(std::string& basepath, std::string& destpath)
{
	for (const fs::directory_entry& x : fs::directory_iterator(basepath))
	{
		try
		{
			fs::copy(x.path(), destpath / x.path().filename(), fs::copy_options::recursive);
		}
		catch (fs::filesystem_error& e)
		{
			std::cout << e.what() << std::endl << "There is a problem with the file: " 
			<< destpath / x.path().filename() << std::endl;
		}
	}
}

std::vector<std::string> find(std::string basepath,const std::string& str)
{
	setlocale(0, "rus");
	using std::vector;
	using std::string;
	using std::cout;
	using std::endl;
	using std::cin;
	using std::ios_base;
	
	vector<string> v;
	string * str_file;
	string temp;
	unsigned int count = { 0 };

	std::ofstream fout;
	fout.open("C:/cpp/texts/files.txt");
	if (!fout.is_open())
	{
		cout << "[-] �� ���������� ������� ���� files.txt!";
		cin.get();
		exit(EXIT_FAILURE);
	}
	for (auto & it : fs::recursive_directory_iterator(basepath)) 
		fout << it << endl;
	fout.close();

	std::ifstream fin;
	fin.open("C:/cpp/texts/files.txt");
	if (!fin.is_open())
	{
		cout << "[-] �� ���������� ������� ���� files.txt!";
		cin.get();
		exit(EXIT_FAILURE);
	}
	while (!fin.eof())
	{
		while (getline(fin, temp))
		{
			count++;
		}
	}
	fin.clear();
	fin.seekg(0, ios_base::beg);
	str_file = new string[count];
	for (unsigned int i = { 0 }; i < count; ++i)
	{
		getline(fin, str_file[i]);
		for (unsigned int j = { 0 }; j < str_file[i].size(); ++j)
		{
			if (str_file[i][j] == '\\')
			{
				str_file[i][j] = '/'; // ������ ������ ��� ����������� ������ �����
			}
		}
		std::ifstream fin2;
		fin2.open(str_file[i]);
		if (!fin2.is_open())
		{
			//cout << "[-] �� ���������� ������� ���� " << str_file[i] << "!";
			continue;
		}
		while (!fin2.eof())
		{
			getline(fin2, temp);
			//cout << temp << endl;
			if (temp.find(str) != -1)
				v.push_back(str_file[i]); // ���������� � ������ ����� � ������, � ������� ���� ������� �����
		}
		fin2.close();
	}
	fin.close();
	return v;
}