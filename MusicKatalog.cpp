/*Создайте приложение «Каталог текстов песен».
Приложение должно иметь следующие возможности:
■ Добавление текста песни:
• Текст песни:
ӽ может быть введен с клавиатуры;
ӽ загружен из файла.
• Для каждой песни нужно указывать название песни, автора текста и
год создания песни (если он известен).
■ Удаление текста песни.
■ Изменение текста песни.
■ Отображение текста песни на экран.
■ Сохранение текста песни в файл.
■ Поиск и отображение всех песен одного автора.
■ Поиск и отображение всех песен, содержащих слово, указанное пользователем.*/

#define __CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

struct song
{
	string title;//название
	string author;//автор
	string text;
	int year;
};
void saveSize(int size) {
	string path = "source\\size.txt";
	ofstream all;
	all.open(path, ofstream::out);
	if (!all.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		all << size;
	}
	all.close();
}

void initSize(int& size) {
	string path;
	path = "source\\size.txt";
	ifstream inAll;
	inAll.open(path);

	if (!inAll.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		inAll >> size;
	}
	inAll.close();
}

void printCataFromFile(song*& a, int size);
void saveCataInFile(song* a, int size);
void printSong(song a);
void addTextFromFile(song& a) {
	string path;
	cout << "Тестовый файл fff. Вводить без расширения.\n";
	cout << "Введите имя файла чтобы загрузить текст:";
	getchar();
	getline(cin, path);
	path = "source\\" + path + ".txt";
	ifstream inText;
	inText.open(path);
	if (!inText.is_open())
	{
		cout << "Ошибка открытия файла!\n";
	}
	else
	{
		cout << "Текст из файла " << path << endl;
		system("pause");
		string str, str2;
		while (!inText.eof())
		{
			
			getline(inText, str);
			str2 += str + "\n";
		}	
		a.text = str2;
		cout << "\nТекст из файла " << path << " добавлен.";
		cout << endl;
	}
	inText.close();
}

int searchTitle(song* a, int size, string n) {

	bool s = true;
	cout << "\nПоиск - " << n << endl;
	for (int i = 0; i < size; i++) {
		if (_stricmp(a[i].title.c_str(), n.c_str()) == 0) { //поиск без учёта регистра
			cout << "\n" << i+1 << " - " << a[i].title << endl;
			s = false;
			return i;
		}
		
	}
	if (s) {
		cout << "Песня не найдена\n";
		return -1;
	}
}

bool confirm() {
	bool a;
	char c;
	cout << "Подтверждаете? Нажмите - Y\n";
	cin >> c;
	if (c != 'Y') {
		a = false;
		return a;
	}
	return a = true;
}

void delText(song& a) {
	if (confirm()) {
		a.text = "Нет текста";
		cout << "Текст удалён";
	}
	else cout << "Отмена\n";
}
void changeText(song*& a, int numb) {

}
void screenText(song a) {
	cout << a.text << endl;
}
void saveTextFile(song a) {
	string path = "source\\" + a.title + ".txt";
	ofstream all;
	all.open(path, ofstream::out);
	if (!all.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		all << a.text;
		cout << "\nТекст сохранён в файл " << path << endl;
	}
	all.close();
}
void dialogAddText(song& a) {
	cout << "Текст \n";
	cout << " 1 - Ввести с клавиатуры\n";
	cout << " 2 - Считать из файла\n";
	int f;
	cin >> f;
	if (f == 1) {
		cin.ignore();
		getline(cin, a.text);
	}
	if (f == 2) {
		addTextFromFile(a);
	}
}
song creatSong() {
	song temp;
	cout << "Название ";
	getchar();
	getline(cin, temp.title);
	cout << "Автор ";
	getline(cin, temp.author);
	cout << "Год создания ";
	cin >> temp.year;
	dialogAddText(temp);
	return temp;
}

void menuItem5(song& a) {
	int menu5;
	do
	{
		cout << "\n==Меню работы с текстом===" << endl;
		cout << "\t" << a.title << endl;
		cout << "1 - Добавление текста" << endl;
		cout << "2 - Текст на экран" << endl;
		cout << "3 - Сохранить текст в файл" << endl;
		cout << "4 - Изменение текста" << endl;
		cout << "5 - Удаление текста" << endl;
		cout << "0 - Выход в главное меню" << endl;
		cout << "\n==========================" << endl;
		
		cin >> menu5;
		cin.ignore();
		switch (menu5)
		{
		case 1: {
			dialogAddText(a);
		}
			  break;
		case 2: {
			screenText(a);
		}
			  break;
		case 3: {
			saveTextFile(a);
		}
			  break;
		case 5: {
			delText(a);
		}
			  break;
		default:
			break;
		}

	} while (menu5 != 0);

}
void printSong(song a) {
	cout << endl;
	cout << "---------------------------\n";
	cout << "Название - " << a.title << endl;
	cout << "Автор    - " << a.author << endl;
	cout << "Год      - " << a.year << endl;
	cout << "Текст    - " << a.text << endl;
	cout << "---------------------------\n";
}

void addSong(song*& songCata, int& size) {
	song* temp = new song[size + 1];
	for (int i = 0; i < size; i++) {
		temp[i] = songCata[i];
	}
	temp[size] = creatSong();
	delete[]songCata;
	songCata = temp;
	size++;
}

void printCata(song* a, int size) {
	for (int i = 0; i < size; i++) {
		cout << "\n№" << i + 1 << " ";
		printSong(a[i]);
	}
	cout << endl;
}

void searchAuthor(song* a, song*& f, int size, int& size2, string n) {
	bool s = true;
	int count = 0;
	cout << "\nПесни автора -  " << n << endl;
	for (int i = 0; i < size; i++) {

		if (_stricmp(a[i].author.c_str(), n.c_str()) == 0) {
			s = false;
			count++;
		}
	}
	if (count) {
		song* temp = new song[count];
		for (int i = 0, j = 0; i < size; i++) {
			if (_stricmp(a[i].author.c_str(), n.c_str()) == 0) {
				temp[j] = a[i];
				j++;
			}
		}
		delete[]f;
		f = temp;
		size2 = count;
	}
	if (s) cout << "Автор не найден";
}

void fill(song*& songCata) {
	songCata[0] = { "Forrest Gump", "Robert Zemeckis", "ппроп", 1940};
	songCata[1] = { "The Curious Case", "David Fincher", "пррт", 1225};
	songCata[2] = { "The Shining", "Stanley Kubrick", "вап", 2600};
	songCata[3] = { "Fight Club", "David Fincher", "ыпыпы", 5000};
	songCata[4] = { "Tough nut", "John McTiernan", "ыапра", 4500};
	songCata[5] = { "RoboCop", "Paul Verhoeven", "ыарыр", 4500};
	songCata[6] = { "Alien", "Ridley Scott", "ыары", 1900};
	songCata[7] = { "World War Z", "Marc Forster", "ыапрыа", 1500};
	songCata[8] = { "The Game", "David Fincher", "ыарры", 2010};
	songCata[9] = { "Terminator 2", "James Cameron", "ыаррыа", 2050};
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int size, size2 = 0;
	initSize(size);
	song* songFind = new song[size2];
	song* songCata = new song[size];
	//fill(songCata);
	printCataFromFile(songCata, size);
	
	int menu;
	do {
		cout << "\n=====Главное меню=========" << endl;
		cout << "\n1 - Показ всех песен" << endl;
		cout << "2 - Добавление песни" << endl;
		cout << "3 - Поиск по названию" << endl;
		cout << "4 - Поиск по автору" << endl;
		cout << "5 - Изменение текста песни" << endl;
		cout << "0 - Выход" << endl;
		cout << "\n==========================" << endl;

		cin >> menu;
		cin.ignore();
		switch (menu) {
		case 1: {
			printCata(songCata, size);
		}
			  break;

		case 2: {
			addSong(songCata, size);
		}
			  break;

		case 3: {
			cout << "Введите название - ";
			string n;
			getline(cin, n);
			searchTitle(songCata, size, n);
		}
			  break;

		case 4: {
			cout << "Введите автора - ";
			string n;
			getline(cin, n);
			searchAuthor(songCata, songFind, size, size2, n);
			printCata(songFind, size2);
		}
			  break;
		case 5: {
			cout << "Введите название - ";
			string n;
			getline(cin, n);
			int numb = searchTitle(songCata, size, n);
			if (numb == -1) {
				break;
			}
			menuItem5(songCata[numb]);
		}
			  break;
		case 6: {

		}
			  break;
		}
	}
	while (menu != 0);
	saveSize(size);
	saveCataInFile(songCata, size);
	//printCata(songCata, size);
	delete[]songCata;
	delete[]songFind;
	return 0;
}

/*string find, s; //поиск слова
getline(cin, s);
getline(cin, find);
int pos = s.find(find); // поиск
if (pos == -1)
cout << "not finded" << endl;
else
cout << "finded in " << pos << " simvol position" << endl;*/

void saveCataInFile(song* a, int size) {
	string path = "source\\catalog.txt";
	ofstream all;
	all.open(path, ofstream::out);
	if (!all.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		for (int i = 0; i < size; i++) {
			all << a[i].title << "\n" << a[i].author << "\n" << a[i].text << "\n" << a[i].year << endl;
		}
	}
	all.close();
}
void printCataFromFile(song *&a, int size) {
	int i = 0;
	string path, temp;
	path = "source\\catalog.txt";
	ifstream inAll;
	inAll.open(path);

	if (!inAll.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		while (i<size)
		/*while (!inAll.eof()) не понял почему, но при таком условии
								конец файла достигается позже чем заканчивается массив
								хотя внешне всё должно быть ок
								Проверял - пытается ещё два прохода сделать 
								и уходит за пределы массива*/
		{
			
			getline(inAll, a[i].title);
			getline(inAll, a[i].author);
			getline(inAll, a[i].text);
			inAll >> a[i].year;
			getline(inAll, temp); //считывает \n после инта
			
			cout << a[i].title << " " << a[i].author << " " << a[i].text << " " << a[i].year << endl;
			i++;
		}
	}
	inAll.close();
	//return a;
}