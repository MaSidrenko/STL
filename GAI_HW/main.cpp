#include<iostream>
#include<map>
#include<string>
#include<string.h>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n|-------------------------------|\n"

void add_offens(std::string offens, std::string num_car, std::map<std::string, std::string>& offenses);
void print(std::map<std::string, std::string>& offenses);

void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string num_car;
	std::string offens;
	std::map<std::string, std::string> offenses =
	{
		{"АБ123Г", "Превышение скорости"},
		{"ДМ352А", "Проезд на запрещающий сигнал светофора"},
		{"СA500Д", "Движение во встречном направлении по дороге с односторонним движением"},
		{"БА404Г", "Пересечение двойной сплошной полосы"},
		{"АД954В", "Движение по тротуару"}
	};
	print(offenses);
	add_offens(offens, num_car, offenses);
	print(offenses);
}

void add_offens(std::string offens, std::string num_car, std::map<std::string, std::string>& offenses)
{
	cout << "Введите номер машины: "; cin >> num_car; cout << endl;
	cout << "Введите правонарушение: "; std::getline(cin >> std::ws, offens);
	system("CLS");
	offenses.insert(std::pair<std::string, std::string>(num_car, offens));
}
void print(std::map<std::string, std::string>& offenses)
{
	for (std::map<std::string, std::string>::iterator it = offenses.begin(); it != offenses.end(); ++it)
	{
		cout << it->first << tab << it->second; cout << endl;
	}
	cout << endl;
}