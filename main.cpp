#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

// Класс Resource
class Resource {
private:
    int id;
    std::string title;
    std::string author;
    std::string category;
    int year;
    std::string access_link;
    int views;

public:
    // Конструктор по умолчанию
    Resource() : id(0), title(""), author(""), category(""), year(0), access_link(""), views(0) {}

    // Конструктор с параметрами
    Resource(int id, const std::string& title, const std::string& author, const std::string& category, int year, const std::string& access_link, int views)
    : id(id), title(title), author(author), category(category), year(year), access_link(access_link), views(views) {}

    // Методы для редактирования свойств
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setAuthor(const std::string& newAuthor) { author = newAuthor; }
    void setCategory(const std::string& newCategory) { category = newCategory; }
    void setYear(int newYear) { year = newYear; }
    void setAccessLink(const std::string& newLink) { access_link = newLink; }
    void setViews(int newViews) { views = newViews; }

    // Методы для получения свойств
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCategory() const { return category; }
    int getYear() const { return year; }
    std::string getAccessLink() const { return access_link; }
    int getViews() const { return views; }

    // Метод для отображения информации о ресурсе
    void display() const {
        std::cout << "ID: " << id << "\nНазвание: " << title << "\nАвтор: " << author
                  << "\nКатегория: " << category << "\nГод: " << year
                  << "\nСсылка: " << access_link << "\nПросмотры: " << views << "\n";
    }

    // Метод для установки ID
    void setId(int newId) { id = newId; }

    // Метод для сохранения ресурса в файл
    void saveToFile(std::ofstream& file) const {
        file << id << " " << title << " " << author << " " << category << " "
             << year << " " << access_link << " " << views << "\n";
    }

    // Метод для загрузки ресурса из файла
    void loadFromFile(std::ifstream& file) {
        file >> id >> title >> author >> category >> year >> access_link >> views;
    }
};

// Функция для автоматического присвоения ID
int generateId(const std::vector<Resource>& resources) {
    int maxId = 0;
    for (const auto& res : resources) {
        if (res.getId() > maxId) {
            maxId = res.getId();
        }
    }
    return maxId + 1;
}

// Функция для добавления нового ресурса
void addResource(std::vector<Resource>& resources, const std::string& filename) {
    Resource newRes;
    newRes.setId(generateId(resources));

    std::cout << "Введите название ресурса: ";
    std::cin.ignore();
    std::string title;
    std::getline(std::cin, title);
    newRes.setTitle(title);

    std::cout << "Введите автора: ";
    std::string author;
    std::getline(std::cin, author);
    newRes.setAuthor(author);

    std::cout << "Введите категорию: ";
    std::string category;
    std::getline(std::cin, category);
    newRes.setCategory(category);

    std::cout << "Введите год: ";
    int year;
    while (!(std::cin >> year) || year < 0) {
        std::cout << "Пожалуйста, введите корректный год: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    newRes.setYear(year);

    std::cout << "Введите ссылку: ";
    std::cin.ignore();
    std::string link;
    std::getline(std::cin, link);
    newRes.setAccessLink(link);

    std::cout << "Введите количество просмотров: ";
    int views;
    while (!(std::cin >> views) || views < 0) {
        std::cout << "Пожалуйста, введите корректное количество просмотров: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    newRes.setViews(views);

    resources.push_back(newRes);

    // Сохранение данных в файл после добавления ресурса
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла для записи.\n";
        return;
    }

    for (const auto& res : resources) {
        res.saveToFile(file);
    }

    file.close();
    std::cout << "Ресурс успешно добавлен и сохранен!\n";
}

// Функция для редактирования ресурса
void editResource(std::vector<Resource>& resources, int id, const std::string& filename) {
    for (auto& res : resources) {
        if (res.getId() == id) {
            std::cout << "Редактирование ресурса с ID: " << id << "\n";
            addResource(resources, filename);  // Переприсваиваем значение через ту же функцию добавления

            // Сохранение данных в файл после редактирования ресурса
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "Ошибка открытия файла для записи.\n";
                return;
            }

            for (const auto& res : resources) {
                res.saveToFile(file);
            }

            file.close();
            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден.\n";
}

// Функция для удаления ресурса
void deleteResource(std::vector<Resource>& resources, int id, const std::string& filename) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->getId() == id) {
            resources.erase(it);
            std::cout << "Ресурс с ID: " << id << " успешно удалён.\n";

            // Сохранение данных в файл после удаления ресурса
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "Ошибка открытия файла для записи.\n";
                return;
            }

            for (const auto& res : resources) {
                res.saveToFile(file);
            }

            file.close();
            return;
        }
    }
    std::cout << "Ресурс с таким ID не найден.\n";
}

// Функция для просмотра всех ресурсов
void displayAll(const std::vector<Resource>& resources) {
    for (const auto& res : resources) {
        res.display();
        std::cout << "============================\n";
    }
}

// Функция для подсчета просмотров
void calculateTotalViews(const std::vector<Resource>& resources) {
    int totalViews = 0;
    for (const auto& res : resources) {
        totalViews += res.getViews();
    }
    std::cout << "Общее количество просмотров всех ресурсов: " << totalViews << std::endl;
}

// Функция для загрузки данных из файла
void loadData(const std::string& filename, std::vector<Resource>& resources) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Ошибка открытия файла для чтения.\n";
        return;
    }

    resources.clear(); // Очищаем массив перед загрузкой данных
    Resource temp;
    while (file) {
        temp.loadFromFile(file);
        if (file) { // Проверка на случай чтения пустой строки
            resources.push_back(temp);
        }
    }

    file.close();
    std::cout << "Данные успешно загружены из файла " << filename << ".\n";
}

// Главное меню
int main()
{
    system("chcp 1251>0");
    std::vector<Resource> resources;
    std::string filename = "офис.txt";

    loadData(filename, resources); // Загрузка данных при старте программы

    int choice;

    while (true) {
        std::cout << "\nМеню:\n1. Просмотр всех ресурсов\n2. Добавить ресурс\n3. Редактировать ресурс\n4. Удалить ресурс\n5. Подсчитать просмотры\n6. Выйти\n";
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cout << "Пожалуйста, введите корректный выбор.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            displayAll(resources);
        } else if (choice == 2) {
            addResource(resources, filename);
        } else if (choice == 3) {
            int id;
            std::cout << "Введите ID ресурса для редактирования: ";
            std::cin >> id;
            editResource(resources, id, filename);
        } else if (choice == 4) {
            int id;
            std::cout << "Введите ID ресурса для удаления: ";
            std::cin >> id;
            deleteResource(resources, id, filename);
        } else if (choice == 5) {
            calculateTotalViews(resources);
        } else if (choice == 6) {
            std::cout << "Выход из программы...\n";
            break;
        } else {
            std::cout << "Неверный выбор.\n";
        }
    }

    return 0;
}
