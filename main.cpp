#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

// ����� Resource
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
    // ����������� �� ���������
    Resource() : id(0), title(""), author(""), category(""), year(0), access_link(""), views(0) {}

    // ����������� � �����������
    Resource(int id, const std::string& title, const std::string& author, const std::string& category, int year, const std::string& access_link, int views)
    : id(id), title(title), author(author), category(category), year(year), access_link(access_link), views(views) {}

    // ������ ��� �������������� �������
    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setAuthor(const std::string& newAuthor) { author = newAuthor; }
    void setCategory(const std::string& newCategory) { category = newCategory; }
    void setYear(int newYear) { year = newYear; }
    void setAccessLink(const std::string& newLink) { access_link = newLink; }
    void setViews(int newViews) { views = newViews; }

    // ������ ��� ��������� �������
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getCategory() const { return category; }
    int getYear() const { return year; }
    std::string getAccessLink() const { return access_link; }
    int getViews() const { return views; }

    // ����� ��� ����������� ���������� � �������
    void display() const {
        std::cout << "ID: " << id << "\n��������: " << title << "\n�����: " << author
                  << "\n���������: " << category << "\n���: " << year
                  << "\n������: " << access_link << "\n���������: " << views << "\n";
    }

    // ����� ��� ��������� ID
    void setId(int newId) { id = newId; }

    // ����� ��� ���������� ������� � ����
    void saveToFile(std::ofstream& file) const {
        file << id << " " << title << " " << author << " " << category << " "
             << year << " " << access_link << " " << views << "\n";
    }

    // ����� ��� �������� ������� �� �����
    void loadFromFile(std::ifstream& file) {
        file >> id >> title >> author >> category >> year >> access_link >> views;
    }
};

// ������� ��� ��������������� ���������� ID
int generateId(const std::vector<Resource>& resources) {
    int maxId = 0;
    for (const auto& res : resources) {
        if (res.getId() > maxId) {
            maxId = res.getId();
        }
    }
    return maxId + 1;
}

// ������� ��� ���������� ������ �������
void addResource(std::vector<Resource>& resources, const std::string& filename) {
    Resource newRes;
    newRes.setId(generateId(resources));

    std::cout << "������� �������� �������: ";
    std::cin.ignore();
    std::string title;
    std::getline(std::cin, title);
    newRes.setTitle(title);

    std::cout << "������� ������: ";
    std::string author;
    std::getline(std::cin, author);
    newRes.setAuthor(author);

    std::cout << "������� ���������: ";
    std::string category;
    std::getline(std::cin, category);
    newRes.setCategory(category);

    std::cout << "������� ���: ";
    int year;
    while (!(std::cin >> year) || year < 0) {
        std::cout << "����������, ������� ���������� ���: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    newRes.setYear(year);

    std::cout << "������� ������: ";
    std::cin.ignore();
    std::string link;
    std::getline(std::cin, link);
    newRes.setAccessLink(link);

    std::cout << "������� ���������� ����������: ";
    int views;
    while (!(std::cin >> views) || views < 0) {
        std::cout << "����������, ������� ���������� ���������� ����������: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    newRes.setViews(views);

    resources.push_back(newRes);

    // ���������� ������ � ���� ����� ���������� �������
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "������ �������� ����� ��� ������.\n";
        return;
    }

    for (const auto& res : resources) {
        res.saveToFile(file);
    }

    file.close();
    std::cout << "������ ������� �������� � ��������!\n";
}

// ������� ��� �������������� �������
void editResource(std::vector<Resource>& resources, int id, const std::string& filename) {
    for (auto& res : resources) {
        if (res.getId() == id) {
            std::cout << "�������������� ������� � ID: " << id << "\n";
            addResource(resources, filename);  // ��������������� �������� ����� �� �� ������� ����������

            // ���������� ������ � ���� ����� �������������� �������
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "������ �������� ����� ��� ������.\n";
                return;
            }

            for (const auto& res : resources) {
                res.saveToFile(file);
            }

            file.close();
            return;
        }
    }
    std::cout << "������ � ����� ID �� ������.\n";
}

// ������� ��� �������� �������
void deleteResource(std::vector<Resource>& resources, int id, const std::string& filename) {
    for (auto it = resources.begin(); it != resources.end(); ++it) {
        if (it->getId() == id) {
            resources.erase(it);
            std::cout << "������ � ID: " << id << " ������� �����.\n";

            // ���������� ������ � ���� ����� �������� �������
            std::ofstream file(filename);
            if (!file) {
                std::cerr << "������ �������� ����� ��� ������.\n";
                return;
            }

            for (const auto& res : resources) {
                res.saveToFile(file);
            }

            file.close();
            return;
        }
    }
    std::cout << "������ � ����� ID �� ������.\n";
}

// ������� ��� ��������� ���� ��������
void displayAll(const std::vector<Resource>& resources) {
    for (const auto& res : resources) {
        res.display();
        std::cout << "============================\n";
    }
}

// ������� ��� �������� ����������
void calculateTotalViews(const std::vector<Resource>& resources) {
    int totalViews = 0;
    for (const auto& res : resources) {
        totalViews += res.getViews();
    }
    std::cout << "����� ���������� ���������� ���� ��������: " << totalViews << std::endl;
}

// ������� ��� �������� ������ �� �����
void loadData(const std::string& filename, std::vector<Resource>& resources) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "������ �������� ����� ��� ������.\n";
        return;
    }

    resources.clear(); // ������� ������ ����� ��������� ������
    Resource temp;
    while (file) {
        temp.loadFromFile(file);
        if (file) { // �������� �� ������ ������ ������ ������
            resources.push_back(temp);
        }
    }

    file.close();
    std::cout << "������ ������� ��������� �� ����� " << filename << ".\n";
}

// ������� ����
int main()
{
    system("chcp 1251>0");
    std::vector<Resource> resources;
    std::string filename = "����.txt";

    loadData(filename, resources); // �������� ������ ��� ������ ���������

    int choice;

    while (true) {
        std::cout << "\n����:\n1. �������� ���� ��������\n2. �������� ������\n3. ������������� ������\n4. ������� ������\n5. ���������� ���������\n6. �����\n";
        std::cout << "�������� ��������: ";

        if (!(std::cin >> choice)) {
            std::cout << "����������, ������� ���������� �����.\n";
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
            std::cout << "������� ID ������� ��� ��������������: ";
            std::cin >> id;
            editResource(resources, id, filename);
        } else if (choice == 4) {
            int id;
            std::cout << "������� ID ������� ��� ��������: ";
            std::cin >> id;
            deleteResource(resources, id, filename);
        } else if (choice == 5) {
            calculateTotalViews(resources);
        } else if (choice == 6) {
            std::cout << "����� �� ���������...\n";
            break;
        } else {
            std::cout << "�������� �����.\n";
        }
    }

    return 0;
}
