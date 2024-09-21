#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<map>
#include<list>
#include<ctime>
#include<string>
#include<sstream>
#include<string.h>
#include<conio.h>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n|---------------------------|\n"

#define Enter		13
#define Escape		27
#define UP_ARROW	72
#define DOWN_ARROW	80

//const char* MENU_TIEMS[] =
//{
//	"1. Загрузить базу данных из файла",
//	"2. Сохранить базу даных в файл",
//	"3. Вывести базу данных на экран",
//	"4. Вывести информацию по номер",
//	"5. Добавить нарушение",
//};
//const int MENU_SIZE = sizeof(MENU_TIEMS) / sizeof(MENU_TIEMS[0]);

const std::map<int, std::string> MENU_ITEMS =
{
	{1, "Загрузить базу данных из файла"},
	{2, "Сохранить базу даных в файл"},
	{3, "Вывести базу данных на экран"},
	{4, "Вывести информацию по номер"},
	{5, "Добавить нарушение"},
};


const std::map<int, std::string> VIOLATIONS =
{
	{0, "N/A"},
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
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
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
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}
	//			Constructors:
	explicit Crime(/*const std::string& license_plate*/ int violation_id = 0, const std::string& place = "N/A", const std::string& time = "00:00 01.01.1970")
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

std::ofstream& operator<<(std::ofstream& of, const Crime& obj)
{
	of << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place() /*<< " - " << obj.get_viovation()*/;
	return of;
}

std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}
int menu();
void print(const std::map<std::string, std::list<Crime>>& database);
void Write_to_file(std::map<std::string, std::list<Crime>>& database, const std::string file_name);
std::map<std::string, std::list<Crime>> Read_from_file(const std::string& file_name);

//#define SAVE_CHECK
//#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef SAVE_CHECK
	std::map <std::string, std::list<Crime>> database =
	{
		{"a777bb", {Crime(1, "Ул. Ленина", "18:10 1.09.2024"), Crime(2, "Ул. Крупской", "12:25 20.08.2024")} },
		{"a000bb", {Crime(6, "Ул. Космонавтов", "17:50 1.08.2024"), Crime(8, "Ул. Космонавтов", "17:45 1.08.2024")} },
		{"a001aa", {Crime(10, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(9, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:50 1.08.2024"), Crime(11, "Ул. Пролетраская", "21:55 1.08.2024")}}
	};
	//print(database);
	Write_to_file(database, "database.txt");
#endif // SAVE_CHECK
	
#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>> database = Read_from_file("database.txt");
	print(database);
#endif // LOAD_CHECK
	std::map<std::string, std::list<Crime>> database = Read_from_file("database.txt");
	do 
	{
		switch (menu())
		{
		case 0: return;
		case 1: database = Read_from_file("database.txt");				   break;
		case 2: Write_to_file(database, "database.txt");				   break;
		case 3: print(database);										   break;
		case 4: cout << "Скоро будет" << endl;system("PAUSE");			   break;
		case 5: cout << "Скоро будет" << endl;system("PAUSE");			   break;
		}
	} while (true);
}
int menu()
{
	int selcted_item = 1; 
	char key;
	do
	{
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 1; i <= MENU_ITEMS.size(); i++)
		{
			cout << (i == selcted_item ? "[" : " ");
			cout << i << ". ";
			cout.width(32);
			cout << std::left;
			if(i == selcted_item)SetConsoleTextAttribute(hConsole, 0x70);
			cout << MENU_ITEMS.at(i);
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << (i == selcted_item ? "  ]" : " ");
			cout << endl;
		}
		key = _getch();
		switch (key)
		{
		case UP_ARROW:	/* if (selcted_item > 1)*/selcted_item--; break;
		case DOWN_ARROW: /*if (selcted_item < MENU_ITEMS.size())*/selcted_item++; break;
		case Enter:		 return selcted_item;
		case Escape:	 return 0;
		}
		if (selcted_item == MENU_ITEMS.size() + 1)selcted_item = 1;
		if (selcted_item == 0)selcted_item = MENU_ITEMS.size();
		//system("PAUSE");
	} while (key != Escape);
	return selcted_item;
}

void print(const std::map<std::string, std::list<Crime>>& database)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = database.begin(); map_it != database.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout /*<< "\t"*/ << *it << endl;
		}
		cout << delimeter << endl;
	}
	cout << "Количество номеров в базе данных: " << database.size() << endl;
	system("PAUSE");
}

void Write_to_file(std::map<std::string, std::list<Crime>>& database, const std::string file_name)
{
	std::ofstream fout;
	fout.open(file_name);
	for (std::map<std::string, std::list<Crime>>::iterator map_it = database.begin(); map_it != database.end(); ++map_it)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << *it << ",";
		}
		//fout.seekp(-1, std::ios::cur); //Метод seelp(offset, direction) задает позицию курсора записи(p - put)
									   //-1 смещение на один символ обратно, std::ios:cur - показывает что смещение производится от текующей позиции курсора
		//fout << ";\n"
		fout << endl;
	}
	fout.close();
	std::string cmd = "notepad " + file_name;
	system(cmd.c_str());
}

std::map<std::string, std::list<Crime>> Read_from_file(const std::string& file_name)
{
	std::map<std::string, std::list<Crime>> database;
	std::ifstream fin(file_name);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string licence_plate;
			std::getline(fin, licence_plate, ':');
			//if (licence_plate.empty())continue;
			licence_plate.erase(0, licence_plate.find_first_not_of("\n"));
			fin.ignore();

			std::string crimes;
			std::getline(fin, crimes);
			char* sz_buffer = new char[crimes.size() + 1]{};
			strcpy(sz_buffer, crimes.c_str());
			char delimiters[] = ",";
			Crime crime;
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				std::string s_crime(pch);
				std::stringstream ss_crime(s_crime, std::ios_base::in | std::ios_base::out);
				ss_crime >> crime;
				database[licence_plate].push_back(crime);
			}
			//cout << endl;
			delete[]  sz_buffer;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file " << file_name << " not found" << endl;
	}
	system("PAUSE");
	return database;
}