#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <Windows.h>

using namespace std;

const string base_name = "base.txt";

void print_base(const map<string, list<string>>& base);
void save_base(const map<string, list<string>>& base);
void load_base(map<string, list<string>>& base);

int main()
{
	setlocale(LC_ALL, "Russian");
	system("color 0A");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 120, 50 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);

	map<string, list<string>> base/* =
	{
		pair<string, list<string>>("m123ru777", {"Driving through on red light", "Driving over speed limit"}),
		pair<string, list<string>>("m446ru011", {"Wrong place parking"}),
		pair<string, list<string>>("k848vk011", {"Drunk Driving", "Insulting police"}),
	}*/;

	//save_base(base);
	load_base(base);
	print_base(base);
	
}

void print_base(const map<string, list<string>>& base)
{
	for (map<string, list<string>>::const_iterator it = base.begin(); it != base.end(); it++)
	{
		cout << it->first << ":\t";
		for (list<string>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); l_it++)
		{
			cout << *l_it; //<< ", ";
			if (l_it != it->second.end())cout << ", ";
		}
		//cout << "\b \b;\n";
		//cout << "\b \b";
		cout << ";\n";
	}
}

void save_base(const map<string, list<string>>& base)
{
	ofstream fout(base_name);

	for (map<string, list<string>>::const_iterator it = base.begin(); it != base.end(); it++)
	{
		fout << it->first << ":";
		for (list<string>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); l_it++)
		{
			fout << *l_it; //<< ", ";
			if (l_it != --(it->second.end()))fout << ",";
		}
		//fout << "\b \b;\n";
		//fout << "\b \b";
		fout << ";\n";
	}
	fout.close();
	string command = "start notepad " + base_name;
	system(command.c_str());
}

void load_base(map<string, list<string>>& base)
{
	ifstream fin(base_name);

	string id;
	//string crime;
	string crimes;

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			getline(fin, id, ':');
			//if (id.size() < 2)continue;

			getline(fin, crimes, ';');
			fin.ignore();
			for (int i = 0, next_comma = i; i < crimes.size();i = next_comma)
			{
				next_comma = crimes.find(',', i+1);
				string crime(crimes, i+1, (next_comma > 0 ? next_comma - i - 1 : crimes.size()-i));
				base[id].push_back(crime);
			}
		}
	}
	else
	{
		cerr << "File not found" << endl;
	}

	fin.close();
}
