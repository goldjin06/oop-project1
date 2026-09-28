#include "StudentUI.h"

#include <iostream>

#include "Validator.h"

StudentUI::StudentUI(StudentManager& m)
    : manager(m)
{
}

void StudentUI::run()
{
    // 4(Exit)나 EOF가 들어올 때까지 반복
    while (!inputClosed) {
        std::cout << "1. Insertion\n"
                  << "2. Search\n"
                  << "3. Sorting Option\n"
                  << "4. Exit\n"
                  << "> ";

        switch (readMenu(1, 4)) {
        case 1: doInsertion(); break;
        case 2: doSearch(); break;
        case 3: doSortOption(); break;
        case 4: return;
        default: break;  // 잘못된 입력이나 EOF: 루프 조건에서 처리
        }
    }
}

bool StudentUI::readLine(std::string& line)
{
    if (!std::getline(std::cin, line)) {
        inputClosed = true;
        return false;
    }
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return true;
}

int StudentUI::readMenu(int min, int max)
{
    std::string line;
    if (!readLine(line)) {
        return -1;
    }
    line = Validator::trim(line);
    if (line.size() != 1 || line[0] < '0' + min || line[0] > '0' + max) {
        std::cout << "Invalid input\n";
        return 0;
    }
    return line[0] - '0';
}

std::string StudentUI::prompt(const std::string& msg, bool (*valid)(const std::string&))
{
    std::string line;
    while (true) {
        std::cout << msg;
        if (!readLine(line)) {
            return "";
        }
        line = Validator::trim(line);
        if (valid(line)) {
            return line;
        }
        std::cout << "Invalid input\n";  // TODO: 필드별로 구체적인 에러 메시지
    }
}

void StudentUI::doInsertion()
{
    std::string name = prompt("Name ? ", Validator::isValidName);
    if (inputClosed) return;
    std::string id = prompt("Student ID (10 digits)? ", Validator::isValidStudentId);
    if (inputClosed) return;
    std::string birth = prompt("Birth Year (4 digits) ? ", Validator::isValidBirthYear);
    if (inputClosed) return;
    std::string dept = prompt("Department ? ", Validator::isValidDepartment);
    if (inputClosed) return;
    std::string tel = prompt("Tel ? ", Validator::isValidTel);
    if (inputClosed) return;

    if (!manager.insert(Student(name, id, birth, dept, tel))) {
        std::cout << "Error : Already inserted\n";
    }
}

void StudentUI::doSearch()
{
    std::cout << "- Search -\n"
              << "1. Search by name\n"
              << "2. Search by student ID (10 digits)\n"
              << "3. Search by admission year (4 digits)\n"
              << "4. Search by birth year (4 digits)\n"
              << "5. Search by department name\n"
              << "6. List All\n"
              << "> ";

    int choice = readMenu(1, 6);
    if (choice <= 0) return;

    // 6번 List All은 검색어를 받지 않음
    if (choice == 6) {
        printTable(manager.listAll());
        return;
    }

    // 검색 메뉴 번호별 검색어 프롬프트
    static const char* const prompts[] = {
        "",
        "Name keyword? ",
        "Student ID? ",
        "Admission year? ",
        "Birth year? ",
        "Department name keyword? ",
    };

    std::string key;
    std::cout << prompts[choice];
    if (!readLine(key)) return;
    key = Validator::trim(key);

    switch (choice) {
    case 1: printTable(manager.searchByName(key)); break;
    case 2: printTable(manager.searchByStudentId(key)); break;
    case 3: printTable(manager.searchByAdmissionYear(key)); break;
    case 4: printTable(manager.searchByBirthYear(key)); break;
    case 5: printTable(manager.searchByDepartment(key)); break;
    }
}

void StudentUI::doSortOption()
{
    std::cout << "- Sorting Option\n"
              << "1. Sort by Name\n"
              << "2. Sort by Student ID\n"
              << "3. Sort by Birth Year\n"
              << "4. Sort by Department name\n"
              << "> ";

    int choice = readMenu(1, 4);
    if (choice <= 0) return;
    manager.setComparator(StudentComparator::create(choice));
}

void StudentUI::printTable(const std::vector<Student>& v) const
{
    // TODO: 헤더도 operator<<와 같은 열 너비로 맞추기, 0건이면 "No matching student." (요구사항 D4)
    std::cout << "Name           StudentID    Dept                  Birth Year  Tel\n";
    for (const Student& s : v) {
        std::cout << s << '\n';
    }
}
