#include "StudentManager.h"

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
    for (const Student& s : students) {
        if (s.getStudentId() == id) {
            return true;
        }
    }
    return false;
}

bool StudentManager::insert(const Student& s)
{
    // TODO: existsId로 중복 검사 → students에 추가 → repo->append(s)
    (void)s;
    return true;
}

// TODO: 검색 함수 구현 (요구사항 D1)
//       이름·학과: 부분 일치 + 대소문자 구분 없음 / 학번·입학년도·출생년도: 완전 일치
//       결과는 sortResult로 정렬해서 반환

std::vector<Student> StudentManager::searchByName(const std::string& key) const
{
    (void)key;
    return {};
}

std::vector<Student> StudentManager::searchByStudentId(const std::string& key) const
{
    (void)key;
    return {};
}

std::vector<Student> StudentManager::searchByAdmissionYear(const std::string& key) const
{
    (void)key;
    return {};
}

std::vector<Student> StudentManager::searchByBirthYear(const std::string& key) const
{
    (void)key;
    return {};
}

std::vector<Student> StudentManager::searchByDepartment(const std::string& key) const
{
    (void)key;
    return {};
}

std::vector<Student> StudentManager::listAll() const
{
    // TODO: students 복사 → sortResult
    return {};
}

void StudentManager::setComparator(std::unique_ptr<StudentComparator> c)
{
    if (c) {
        comparator = std::move(c);
    }
}

void StudentManager::sortResult(std::vector<Student>& v) const
{
    // TODO: std::stable_sort + comparator->less(), 값이 같으면 학번으로 2차 정렬
    (void)v;
}
