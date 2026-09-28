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

// TODO: 아래 비교 함수들 구현 (a가 b보다 앞이면 true)

bool NameComparator::less(const Student& a, const Student& b) const
{
    (void)a;
    (void)b;
    return false;
}

bool StudentIdComparator::less(const Student& a, const Student& b) const
{
    (void)a;
    (void)b;
    return false;
}

bool BirthYearComparator::less(const Student& a, const Student& b) const
{
    (void)a;
    (void)b;
    return false;
}

bool DepartmentComparator::less(const Student& a, const Student& b) const
{
    (void)a;
    (void)b;
    return false;
}
