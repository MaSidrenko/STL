#include<iostream>
#include<map>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n|----------------------------------------|\n"

#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednsday"),
	};
	
	/*for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}*/
	double a;
	cin >> a;
	if (a / 2 == 0)
	{
		cout << "1";
	}
	else
	{
		cout << 0;
	}
#endif // STL_MAP

}