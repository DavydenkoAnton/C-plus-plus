//  4. Файл содержит имена и фамилии. Отсортировать список людей по фамилии,
//  записать в другой файл. Отсортировать по имени, записать в третий файл. 
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
using namespace std;

int main()
{
	ifstream fin("Name_Surname.txt");
	ofstream name_out("n_output.txt");
	ofstream sur_out("s_output.txt");
	vector<string> name;
	vector<string> surname;
	string str;
	smatch m; 
	regex e1("([A-Za-z]).* ");//регекс для имени (правило)
	regex e2("\\b([A-Za-z]*)");//регекс для фамилии (правило)
	while (fin >> str) {
		regex_search(str, m, e1);//проверяем по правилу имя и запихиваем в str
		name.push_back(str);//тут str(имя) запихиваем в вектор

		regex_search(str, m, e2);//проверяем фамилию по правилу и запихиваем в str
		name.push_back(str);//тут str(фамилию) запихиваем в вектор
	}
	sort(name.begin(), name.end());// сортируем вектор имен
	for (vector<string>::iterator it = name.begin(); it < name.end(); it++) {
		name_out << *it << endl;//тут имя запихиваем в файл
	}
	sort(surname.begin(), surname.end());// сортируем вектор фамилий
	for (vector<string>::iterator it = surname.begin(); it < surname.end(); it++) {
		sur_out << *it << endl;//тут фамилию запихиваем в файл
	}
	fin.close();
	name_out.close();
	sur_out.close();
	return 0;
}
