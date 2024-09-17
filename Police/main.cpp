#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<map>
#include<list>
#include<ctime>
#include<string>
#include<string.h>
#include<conio.h>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n|---------------------------|\n"

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
	//std::string license_plate;
	int id;
	std::string place;
	tm time;
public:
	//const std::string& set_license_plate()const
	//{
	//	return license_plate;
	//}
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_viovation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	//void set_license_plate(const std::string& license_plate)
	//{
	//	this->license_plate = license_plate;
	//}
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//1. Создаем временную строку для того что бы пропарсить полученную строку:
		char* time_buffer = new char[time.size() + 1] {};
		//2. Копируем полученную строку в буффер:
		strcpy(time_buffer, time.c_str());
		//Ф-ция strcpy(dst, src); копирует содержимое строки источника (scr - Source) в строку получателя (dst - Destination) 
		
		//3.Создаем массив для хранения элементов времени:
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
			//Ф-ция std::atoi() 'ASCII-string to int' преобразует строку в целое число.
		delete[] time_buffer;

		//4. Сохраняем элементы времени в структуру 'tm':
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;

		//this->time = time;
	}
	//			Constructors:
	Crime(/*const std::string& license_plate*/ int violation_id, const std::string& place, const std::string time)
	{
		this->time = {};
		//set_license_plate(license_plate);
		set_violation_id(violation_id);
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
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_viovation();
}

void print(const std::map<std::string, std::list<Crime>>& database);
void Write_to_file(std::map<std::string, std::list<Crime>>& database, const std::string file_name);
void Read_from_file(const std::string file_name);

void main()
{
	setlocale(LC_ALL, "");
	//Crime crime(1, "Ул. Ленина", "18:10 1.09.2024");
	//cout << crime << endl;

	std::map <std::string, std::list<Crime>> database =
	{
		{"a777bb", {Crime(1, "Ул. Ленина", "18:10 1.09.2024"), Crime(2, "Ул. Крупской", "12:25 20.08.2024")} },
		{"a000bb", {Crime(6, "Ул. Космонавтов", "17:50 1.08.2024"), Crime(8, "Ул. Космонавтов", "17:45 1.08.2024")} },
		{"a001aa", {Crime(10, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(9, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:55 1.08.2024")}}
	};
	print(database);

}

void print(const std::map<std::string, std::list<Crime>>& database)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = database.begin(); map_it != database.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimeter << endl;
	}
}

void Write_to_file(std::map<std::string, std::list<Crime>>& database, const std::string file_name)
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

void Read_from_file(const std::string file_name)
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