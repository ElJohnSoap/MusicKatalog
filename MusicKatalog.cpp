/*Создайте приложение «Каталог текстов песен».
Приложение должно иметь следующие возможности:
■ Добавление текста песни:
• Текст песни:
ӽ может быть введен с клавиатуры;
ӽ загружен из файла.
• Для каждой песни нужно указывать название песни, автора текста и
год создания песни (если он известен).
■ Удаление текста песни.
// отменили ■ Изменение текста песни.
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
	string text; //текст	
	int year;	// год
	string fileWithText; // файл с текстом
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
}//сохранение размера каталога
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

void printCatalogFromFile(song*& a, int size);
void saveCatalogToFile(song* a, int size);
void printSong(song a);
void initializingAFileWithText(song& a);

void addTextFromFile(song& a) {
	string pathSourse, pathDest;
	cout << "Тестовый файл fff. Вводить без расширения.\n";
	cout << "Введите имя файла чтобы загрузить текст:";
	getchar();
	getline(cin, pathSourse);
	pathSourse = "source\\" + pathSourse + ".txt";
	pathDest = "source\\" + a.title + ".txt";
	if (pathSourse == pathDest) {
		return;
	}
	ifstream sourseFile;
	ofstream destFile;
	sourseFile.open(pathSourse);
	destFile.open(pathDest, ofstream::out);
	if (!sourseFile.is_open())
	{
		cout << "Ошибка открытия файла!\n";
	}
	else
	{
		cout << "Текст из файла " << pathSourse << endl;
		system("pause");
		string str;
		getline(sourseFile, str);
		while (!sourseFile.eof())
		{
			destFile << str << endl;
			getline(sourseFile, str);
		}
		destFile << str;
		a.fileWithText = pathDest;
		cout << "\nТекст из файла " << pathSourse << " добавлен.";
		cout << endl;
	}
	sourseFile.close();
	destFile.close();
}

int findTitle(song* a, int size, string n) {

	bool s = true;
	//cout << "\nПоиск - " << n << endl;
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
} // подтверждение действия

void delText(song& a) {
	if (confirm()) {
		a.fileWithText.clear();
		cout << "Текст удалён";
		a.text = "нет текста";
	}
	else cout << "Отмена\n";
}
/*void changeText(song& a) {
	cin.ignore();
	string temp;
	getline(cin, temp);
	a.text += "\n" + temp + "\n";
}*/
void showTextOnScreen(song a) {
	string path;
	path = a.fileWithText;
	ifstream File;
	File.open(path);

	if (!File.is_open())
	{
		cout << "Ошибка открытия файла!\n";
	}
	else
	{
		string str;
		while (getline(File, str))
		{
			cout << str << endl;
		}
	}
	File.close();
}

void saveTextToFile(song a) {
	string path = "source\\" + a.title + ".txt";
	ofstream save;
	a.fileWithText = path;
	save.open(path, ofstream::out);
	if (!save.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		int pos = -1;
		cin.ignore();
		cout << "Для окончания ввода нажмите ~\n";
		do
		{
			string temp, end = "~";
			getline(cin, temp);
			save << temp << endl;
			pos = temp.rfind(end); //проверка строки на наличие символа окончания ввода (~)
		} while (pos == -1);
		cout << "\nТекст сохранён в файл " << path << endl;
	}
	save.close();
}

void findText(song* a, int size, string end) {
	for (int i = 0; i < size; i++) {
		ifstream File;
		string path = a[i].fileWithText;
		if (a[i].text == "нет текста") {
			continue;
		}
		File.open(path);
		if (!File.is_open())
		{
			cout << "Ошибка!";
		}
		else
		{
			string str;
			while (getline(File, str))
			{
				if (str.find(end) != -1) {
					cout << endl << a[i].title << endl;
				}
			}
		}
		File.close();
	}
}

void showDialogToAddText(song& a) {
	cout << "Текст \n";
	cout << " 1 - Ввести с клавиатуры\n";
	cout << " 2 - Считать из файла\n";
	cout << " 3 - Пропустить\n";
	int f;
	cin >> f;
	if (f == 1) {
		saveTextToFile(a);
	}
	else if (f == 2) {
		addTextFromFile(a);
	}
	initializingAFileWithText(a);
}
void initializingAFileWithText(song& a) {
	if (a.fileWithText.length() == 0) {
		a.text = "Нет текста";
	}
	else {
		string path;
		path = a.fileWithText;
		ifstream File;
		File.open(path);
		string str;
		getline(File, str);
		a.text = str;
		File.close();
	}
}

song createSong() {
	song temp;
	cout << "Название ";
	//getchar();
	getline(cin, temp.title);
	cout << "Автор ";
	getline(cin, temp.author);
	cout << "Год создания ";
	cin >> temp.year;
	showDialogToAddText(temp);
	initializingAFileWithText(temp);
	return temp;
}

void theMenuForWorkingWithText(song& a) {
	int menu5;
	do
	{
		cout << "\n==Меню работы с текстом===" << endl;
		cout << "\t" << a.title << endl;
		cout << "1 - Добавление текста" << endl;
		cout << "2 - Текст на экран" << endl;
		cout << "3 - Сохранить текст в файл" << endl;
		cout << "4 - Удаление текста" << endl;
		cout << "0 - Выход в главное меню" << endl;
		cout << "\n==========================" << endl;
		
		cin >> menu5;
		cin.ignore();
		switch (menu5)
		{
		case 1: {
			showDialogToAddText(a);
		}
			  break;
		case 2: {
			showTextOnScreen(a);
		}
			  break;
		case 3: {
			saveTextToFile(a);
		}
			  break;
		
		case 4: {
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
	temp[size] = createSong();
	delete[]songCata;
	songCata = temp;
	size++;
}

void delSong(song*& songCata, int& size, int numb) {
	song* temp = new song[size - 1];
	for (int i = 0, j = 0; i < size; i++, j++) {
		if (i==numb)
			j--;
		else
			temp[j] = songCata[i];
	}
	delete[]songCata;
	songCata = temp;
	size--;
}

void printCatalog(song* a, int size) {
	for (int i = 0; i < size; i++) {
		cout << "\n№" << i + 1 << " ";
		printSong(a[i]);
	}
	cout << endl;
}

void findAuthor(song* a, song*& f, int size, int& size2, string n) {
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

/*void fill(song*& songCata) {
	songCata[0] = { "Forrest Gump", "Robert Zemeckis", "нет текста", 1940, " "};
	songCata[1] = { "The Curious Case", "David Fincher", "нет текста", 1225, " "};
	songCata[2] = { "The Shining", "Stanley Kubrick", "нет текста", 2600, " "};
	songCata[3] = { "Fight Club", "David Fincher", "нет текста", 5000, " "};
	songCata[4] = { "Tough nut", "John McTiernan", "нет текста", 4500, " "};
	songCata[5] = { "RoboCop", "Paul Verhoeven", "нет текста", 4500, " "};
	songCata[6] = { "Alien", "Ridley Scott", "нет текста", 1900, " "};
	songCata[7] = { "World War Z", "Marc Forster", "нет текста", 1500, " "};
	songCata[8] = { "The Game", "David Fincher", "нет текста", 2010, " "};
	songCata[9] = { "Terminator 2", "James Cameron", "нет текста", 2050, " "};
}*/

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int size, size2 = 0;
	initSize(size);
	song* songFind = new song[size2];
	song* songCatalog = new song[size];
	//fill(songCata);
	printCatalogFromFile(songCatalog, size);
	string n;
	int menu;
	do {
		cout << "\n=====Главное меню=========" << endl;
		cout << "\n1 - Показ всех песен" << endl;
		cout << "2 - Добавление песни" << endl;
		cout << "3 - Поиск по названию" << endl;
		cout << "4 - Поиск по автору" << endl;
		cout << "5 - Поиск по тексту" << endl;
		cout << "6 - Изменение текста песни" << endl;
		cout << "7 - Удаление песни" << endl;
		cout << "0 - Выход" << endl;
		cout << "\n==========================" << endl;

		cin >> menu;
		cin.ignore();
		switch (menu) {
		case 1:
			printCatalog(songCatalog, size);
		break;

		case 2: 
			addSong(songCatalog, size);
			cout << "Добавлено";
		break;

		case 3: {
			cout << "Введите название - ";
			getline(cin, n);
			findTitle(songCatalog, size, n);
		}
		break;

		case 4: {
			cout << "Введите автора - ";
			getline(cin, n);
			findAuthor(songCatalog, songFind, size, size2, n);
			printCatalog(songFind, size2);
		}
		break;

		case 5: {
			cout << "Введите слово для поиска в тексте - ";
			getline(cin, n);
			findText(songCatalog, size, n);			
		}
			  break;

		case 6: {
			cout << "Введите название песни для работы с текстом - ";
			getline(cin, n);
			int numb = findTitle(songCatalog, size, n);
			if (numb == -1) {
				break;
			}
			theMenuForWorkingWithText(songCatalog[numb]);
		}
			  break;

		case 7: {
			cout << "Введите название - ";
			getline(cin, n);
			int numb = findTitle(songCatalog, size, n);
			if (numb == -1) {
				break;
			}
			cout << "Удаление из каталога " << songCatalog[numb].title << endl;
			if (confirm()) {
				delSong(songCatalog, size, numb);
				cout << "Удалено";
			}
			else cout << "Отмена\n";
		}
		break;
		}
	}
	while (menu != 0);

	saveSize(size);
	saveCatalogToFile(songCatalog, size);
	//printCata(songCata, size);
	delete[]songCatalog;
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

void saveCatalogToFile(song* a, int size) {
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
			all << a[i].title << "\n" << a[i].author << "\n" << a[i].text << "\n" 
				<< a[i].year << "\n" << a[i].fileWithText << endl;
		}
	}
	all.close();
}
void printCatalogFromFile(song *&a, int size) {
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
			getline(inAll, temp);
			getline(inAll, a[i].fileWithText);//считывает \n после инта
			//cout << a[i].title << " " << a[i].author << " " << a[i].text << " " << a[i].year << endl;
			i++;
		}
	}
	inAll.close();
}