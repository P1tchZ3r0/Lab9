
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Класс Book
class Book {
private:
    int id;
    string title;
    string author;
    int year;
    bool isAvailable;

public:
    // Конструктор
    Book(int bookId, const string& bookTitle, const string& bookAuthor, int bookYear)
        : id(bookId), title(bookTitle), author(bookAuthor), year(bookYear), isAvailable(true) {}

    // Геттеры (для инкапсуляции)
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsAvailable() const { return isAvailable; }

    // Сеттер для доступности
    void setAvailable(bool available) { isAvailable = available; }

    // Метод для вывода информации о книге
    void print() const {
        cout << "ID: " << id << ", Название: " << title << ", Автор: " << author
             << ", Год: " << year << ", Доступна: " << (isAvailable ? "Да" : "Нет") << endl;
    }
};

// Класс Library
class Library {
private:
    vector<Book> books;
    int nextId = 1;  // Автоинкремент для ID

    // Метод для сохранения в файл (опционально)
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Ошибка сохранения в файл." << endl;
            return;
        }
        for (const auto& book : books) {
            file << book.getId() << "," << book.getTitle() << "," << book.getAuthor() << ","
                 << book.getYear() << "," << (book.getIsAvailable() ? "1" : "0") << endl;
        }
    }

    // Метод для загрузки из файла (опционально)
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Файл не найден, начинаем с пустой библиотеки." << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> fields;
            while (getline(ss, token, ',')) {
                fields.push_back(token);
            }
            if (fields.size() == 5) {
                int id = stoi(fields[0]);
                string title = fields[1];
                string author = fields[2];
                int year = stoi(fields[3]);
                bool available = (fields[4] == "1");
                Book book(id, title, author, year);
                book.setAvailable(available);
                books.push_back(book);
                nextId = max(nextId, id + 1);
            }
        }
    }

public:
    // Конструктор: загружаем данные из файла при запуске
    Library() {
        loadFromFile("library.csv");
    }

    // Деструктор: сохраняем данные в файл при выходе
    ~Library() {
        saveToFile("library.csv");
    }

    // Добавление книги
    void AddBook(const string& title, const string& author, int year) {
        Book newBook(nextId++, title, author, year);
        books.push_back(newBook);
        cout << "Книга добавлена." << endl;
    }

    // Удаление книги по ID
    void RemoveBook(int id) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getId() == id) {
                books.erase(it);
                cout << "Книга удалена." << endl;
                return;
            }
        }
        cout << "Книга не найдена." << endl;
    }

    // Поиск книги по названию (возвращает вектор, т.к. может быть несколько)
    vector<Book> FindBookByTitle(const string& title) const {
        vector<Book> result;
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                result.push_back(book);
            }
        }
        return result;
    }

    // Получение списка доступных книг
    vector<Book> GetAvailableBooks() const {
        vector<Book> result;
        for (const auto& book : books) {
            if (book.getIsAvailable()) {
                result.push_back(book);
            }
        }
        return result;
    }

    // Взять книгу
    void BorrowBook(int id) {
        for (auto& book : books) {
            if (book.getId() == id && book.getIsAvailable()) {
                book.setAvailable(false);
                cout << "Книга взята." << endl;
                return;
            }
        }
        cout << "Книга не найдена или уже взята." << endl;
    }

    // Вернуть книгу
    void ReturnBook(int id) {
        for (auto& book : books) {
            if (book.getId() == id && !book.getIsAvailable()) {
                book.setAvailable(true);
                cout << "Книга возвращена." << endl;
                return;
            }
        }
        cout << "Книга не найдена или уже доступна." << endl;
    }
};

// Функция для вывода списка книг
void printBooks(const vector<Book>& booksList) {
    if (booksList.empty()) {
        cout << "Книги не найдены." << endl;
    } else {
        for (const auto& book : booksList) {
            book.print();
        }
    }
}

int main() {
    Library library;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Удалить книгу\n";
        cout << "3. Найти книгу по названию\n";
        cout << "4. Показать все доступные книги\n";
        cout << "5. Взять книгу\n";
        cout << "6. Вернуть книгу\n";
        cout << "7. Выйти\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        cin.ignore();  // Очистка буфера для getline

        switch (choice) {
            case 1: {
                string title, author;
                int year;
                cout << "Название: ";
                getline(cin, title);
                cout << "Автор: ";
                getline(cin, author);
                cout << "Год: ";
                cin >> year;
                library.AddBook(title, author, year);
                break;
            }
            case 2: {
                int id;
                cout << "ID книги для удаления: ";
                cin >> id;
                library.RemoveBook(id);
                break;
            }
            case 3: {
                string title;
                cout << "Название для поиска: ";
                getline(cin, title);
                auto found = library.FindBookByTitle(title);
                printBooks(found);
                break;
            }
            case 4: {
                auto available = library.GetAvailableBooks();
                printBooks(available);
                break;
            }
            case 5: {
                int id;
                cout << "ID книги для взятия: ";
                cin >> id;
                library.BorrowBook(id);
                break;
            }
            case 6: {
                int id;
                cout << "ID книги для возврата: ";
                cin >> id;
                library.ReturnBook(id);
                break;
            }
            case 7:
                cout << "Выход..." << endl;
                break;
            default:
                cout << "Неверный выбор." << endl;
        }
    } while (choice != 7);

    return 0;
}