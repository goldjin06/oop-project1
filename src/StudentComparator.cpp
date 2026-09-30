#include "StudentComparator.h"

std::unique_ptr<StudentComparator> StudentComparator::create(int option)
{
    switch (option) {
    case 1: return std::make_unique<NameComparator>();
    case 2: return std::make_unique<StudentIdComparator>();
    case 3: return std::make_unique<BirthYearComparator>();
    case 4: return std::make_unique<DepartmentComparator>();
    default: return nullptr;
    }
}

// 아래 비교 함수들: a가 b보다 앞이면 true

// 대소문자를 구분하지 않고 a가 b보다 앞이면 true
static bool lessIgnoreCase(const std::string& a, const std::string& b)
{
    int n = a.size();
    if (b.size() < n) {
        n = b.size();
    }
    for (int i = 0; i < n; i++) {
        char x = a[i];
        char y = b[i];
        if (x >= 'A' && x <= 'Z') {
            x = x + ('a' - 'A');
        }
        if (y >= 'A' && y <= 'Z') {
            y = y + ('a' - 'A');
        }
        if (x != y) {
            return x < y;
        }
    }
    // 앞부분이 모두 같으면 짧은 쪽이 앞
    return a.size() < b.size();
}

bool NameComparator::less(const Student& a, const Student& b) const
{
    return lessIgnoreCase(a.getName(), b.getName());
}

bool StudentIdComparator::less(const Student& a, const Student& b) const
{
    return a.getStudentId() < b.getStudentId();
}

bool BirthYearComparator::less(const Student& a, const Student& b) const
{
    return a.getBirthYear() < b.getBirthYear();
}

bool DepartmentComparator::less(const Student& a, const Student& b) const
{
    return lessIgnoreCase(a.getDepartment(), b.getDepartment());
}
