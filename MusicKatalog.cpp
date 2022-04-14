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
void printSong(song a);
void addTextFromFile(song& a) {
	string path;
	cout << "Введите имя файла чтобы загрузить текст:";
	getchar();
	getline(cin, path);
	path = path + ".txt";
	ifstream inText;
	inText.open(path);
	if (!inText.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		string str, str2;
		while (!inText.eof())
		{
			
			getline(inText, str);
			str2 += str + "\n";
		}	
		a.text = str2;
		cout << a.text;
		cout << endl;
	}
	inText.close();
}

void saveCataInFile(song*& a, int size) {
	string path = "catalog.txt";
	ofstream all;
	all.open(path, ofstream::app);
	if (!all.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{ 
		for (int i = 0; i < size; i++) {
			all.write((char*)&a[i], sizeof(song));
		}
	}
	all.close();
}
void printCataFromFile(song*a) {
	string path;
	path = "catalog.txt";
	ifstream inCata;
	inCata.open(path);
	if (!inCata.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		song temp;
		while (inCata.read((char*)&temp, sizeof(song)))
		{
			printSong(temp);
		}
	}
	inCata.close();
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
	cout << "Текст \n";
	cout << " 1 - Ввести с клавиатуры\n";
	cout << " 2 - Считать из файла\n";
	int f;
	cin >> f;
	if (f == 1) {
		getline(cin, temp.text);
	}
	if (f == 2) {
		addTextFromFile(temp);
	}
	return temp;
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
	cout << "\nПесн автора -  " << n << endl;
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

	int size = 10, size2 = 0;
	song* songFind = new song[size2];
	song* songCata = new song[size];
	fill(songCata);
	//addSong(songCata, size);
	//printSong(songCata[10]);
	//saveCataInFile(songCata, size);
	printCataFromFile(songCata);
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
