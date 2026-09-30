#include "StudentManager.h"

#include <algorithm>

StudentManager::StudentManager(std::unique_ptr<StudentRepository> repo)
    : repo(std::move(repo)), comparator(std::make_unique<NameComparator>())
{
}

bool StudentManager::load()
{
    return repo->loadAll(students);
}

bool StudentManager::existsId(const std::string& id) const
{
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getStudentId() == id) {
            return true;
        }
    }
    return false;
}

bool StudentManager::insert(const Student& s)
{
    if (existsId(s.getStudentId())) {
        return false;
    }
    students.push_back(s);
    return repo->append(s);
}

// 검색 함수 (요구사항 D1)
// 모든 항목: 완전 일치 (띄어쓰기·대소문자 포함)

std::vector<Student> StudentManager::searchByName(const std::string& key) const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getName() == key) {
            result.push_back(students[i]);
        }
    }
    sortResult(result);
    return result;
}

std::vector<Student> StudentManager::searchByStudentId(const std::string& key) const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getStudentId() == key) {
            result.push_back(students[i]);
        }
    }
    sortResult(result);
    return result;
}

std::vector<Student> StudentManager::searchByAdmissionYear(const std::string& key) const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getAdmissionYear() == key) {
            result.push_back(students[i]);
        }
    }
    sortResult(result);
    return result;
}

std::vector<Student> StudentManager::searchByBirthYear(const std::string& key) const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getBirthYear() == key) {
            result.push_back(students[i]);
        }
    }
    sortResult(result);
    return result;
}

std::vector<Student> StudentManager::searchByDepartment(const std::string& key) const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getDepartment() == key) {
            result.push_back(students[i]);
        }
    }
    sortResult(result);
    return result;
}

std::vector<Student> StudentManager::listAll() const
{
    std::vector<Student> result;
    for (int i = 0; i < students.size(); i++) {
        result.push_back(students[i]);
    }
    sortResult(result);
    return result;
}

void StudentManager::setComparator(std::unique_ptr<StudentComparator> c)
{
    if (c) {
        comparator = std::move(c);
    }
}

void StudentManager::sortResult(std::vector<Student>& v) const
{
    // STL sort -> comparator 기준으로 비교하고, 값이 같으면 학번으로 2차 정렬
    std::sort(v.begin(), v.end(), [this](const Student& a, const Student& b) {
        if (comparator->less(a, b)) return true;    // 기준상 a가 앞
        if (comparator->less(b, a)) return false;   // 기준상 b가 앞
        return a.getStudentId() < b.getStudentId(); // 같으면 학번순
    });
}
