#include<iostream>
#include<map>
#include<list>
#include<string>
#include<string.h>
#include<conio.h>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n|-------------------------------|\n"


const std::map<int, std::string> VIOLATIONS =
{
	{1, "Ремень безопасности"},
	{2, "Парковка в не положеном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превыгение скорости"},
	{5, "Отсутсвие водительский прав"},
	{6, "Отсуствие права управелниея автомобилем"},
	{7, "Отсутсвие страховки"},
	{8, "Проез на красный свет"},
	{9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в не трезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструкцию автомобиля"},
	{14, "Перевозка негаборитного груза"},
	{15, "Превышение маскимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"}
};

class Crime
{
	int id;
	std::string place;
	std::string time;
public:
	int get_violations_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string& get_time()const
	{
		return time;
	}
	
	void set_violations_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		this->time = time;
	}
	Crime(int violations_id, const std::string& place, const std::string& time)
	{
		set_violations_id(violations_id);
		set_place(place);
		set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG

	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG

	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ": " << obj.get_place() << " - " << obj.get_violation();
}
std::ostream& operator<<(std::ostream& os, std::pair<int, std::string>& obj)
{
	return os << delimeter << "Номер: " << obj.first << "\nПреступление: " << obj.second;
}
void add_offens(int offens, std::string place, std::string time, std::string num_car, std::map<std::string, std::list<Crime>>& offenses);
void print(std::map<std::string, std::list<Crime>>& database);
void Write_to_file(std::map<std::string, std::list<Crime>>& database, std::string file_name);
void Read_from_file(std::string file_name);

void main()
{
	setlocale(LC_ALL, "Russian");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//std::string num_car;
	//std::string offens;
	int offens;
	std::string place;
	std::string time;
	std::string num_car;
	std::map <std::string, std::list<Crime>> database =
	{
		{"a777bb", {Crime(1, "Ул. Ленина", "18:10 1.09.2024"), Crime(2, "Ул. Крупской", "12:25 20.08.2024")} },
		{"a000bb", {Crime(6, "Ул. Космонавтов", "17:50 1.08.2024"), Crime(8, "Ул. Космонавтов", "17:45 1.08.2024")} },
		{"a001aa", {Crime(10, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(9, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:55 1.08.2024")}},
		{"a002aa", {Crime(1, "Ул. Ленина", "18:10 1.09.2024")}}
	};
	Write_to_file(database, "police_database.txt");
	Read_from_file("police_database.txt");
	//for (std::pair<int, std::string> i : VIOLATIONS)cout << i;

}

void add_offens(int offens, std::string place, std::string time, std::string num_car, std::map<std::string, std::list<Crime>>& database)
{
	/*cout << "Введите номер машины: "; cin >> num_car; cout << endl;
	cout << "Введите правонарушение: "; std::getline(cin >> std::ws, offens);
	system("CLS");*/
	cout << "Введите номер машины: "; cin >> num_car; cout << endl;
	cout << "Введите номер преступления из списка: ";
	for (std::pair<int, std::string> i : VIOLATIONS)cout << i;
	cin >> offens;
	cout << "Введите когда было совершенно правонарушение: "; cin >> time;
	Crime crime(offens, place, time);
	//database.insert(std::pair<std::string, std::list<Crime>>(num_car, Crime(offens, place, time));
}
void print(std::map<std::string, std::list<Crime>>& database)
{
	for (std::map<std::string, std::list<Crime>>::iterator map_it = database.begin(); map_it != database.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimeter << endl;
	}
}
void Write_to_file(std::map<std::string, std::list<Crime>>& database, std::string file_name)
{
	std::ofstream fout;
	fout.open(file_name);
	for (std::map<std::string, std::list<Crime>>::iterator map_it = database.begin(); map_it != database.end(); ++map_it)
	{
		fout << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << "\t" << *it << endl;
		}
		fout << delimeter << endl;
	}
	fout.close();
	std::string cmd = "notepad " + file_name;
	system(cmd.c_str());
}
void Read_from_file(std::string file_name)
{
	std::ifstream fin(file_name);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			cout << buffer << endl;
		}
		fin.close();
	}
}