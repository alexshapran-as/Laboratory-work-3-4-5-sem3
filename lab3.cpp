#include "stdafx.h"
#include <iostream>
#include "file.h"
#include <string>
#include <fstream>
#include <iomanip>

int main()
{
	system("chcp 65001");
	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;

	cout << endl << "***Лабораторная работа №3 - реализация утилиты ls***" << endl << endl;
	string basepath;
	getline(cin, basepath);
	if (basepath.find("ls ") == -1)
	{
		cout << "Команда не найдена!" << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}
	basepath.erase(0, 3);
	ls(basepath);

	system("chcp 65001");
	cout << endl << "***Лабораторная работа №4 - реализация утилиты cp***" << endl << endl;
	string destpath;
	getline(cin,basepath);
	if (basepath.find("cp ") == -1)
	{
		cout << "Команда не найдена!" << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}
	basepath.erase(0, 3);
	for (unsigned int i = { 0 }; i < basepath.size(); ++i)
	{
		if (basepath[i] == ' ')
		{
			string temp = basepath;
			unsigned int pos = temp.find(' ', 0);
			temp.erase(0, pos+1);
			destpath = temp;
			basepath.erase(pos, basepath.size());
		}
	}
	cp(basepath, destpath);
	system("chcp 65001");
	cout << endl << "***Лабораторная работа №5 - реализация поиска слова в файле***" << endl << endl;
	cout << "Введите путь к директории, где следует искать файл: ";
	getline(cin, basepath);
	cout << "Введите слово/фразу для поиска: ";
	system("chcp 1251");
	string word;
	getline(cin,word);
	system("chcp 65001");
	cout << endl << "Данное слово найдено в файлах: " << endl;
	for (unsigned int i = { 0 }; i < find(basepath, word).size(); ++i)
		cout << "[+] " << (find(basepath, word))[i] << endl;

	system("pause");
	return 0;
}
