#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Student.h"
#include "StudentComparator.h"
#include "StudentRepository.h"

// 핵심 로직 (입출력 코드 없음): 학생 목록 관리, 검색, 정렬
class StudentManager {
private:
    std::vector<Student> students;
    std::unique_ptr<StudentRepository> repo;        // 저장소 (소유)
    std::unique_ptr<StudentComparator> comparator;  // 현재 정렬 기준 (기본값: 이름순)

public:
    explicit StudentManager(std::unique_ptr<StudentRepository> repo);
    bool load();

    bool existsId(const std::string& id) const;
    bool insert(const Student& s);  // 학번이 중복이면 false

    std::vector<Student> searchByName(const std::string& key) const;
    std::vector<Student> searchByStudentId(const std::string& key) const;
    std::vector<Student> searchByAdmissionYear(const std::string& key) const;
    std::vector<Student> searchByBirthYear(const std::string& key) const;
    std::vector<Student> searchByDepartment(const std::string& key) const;
    std::vector<Student> listAll() const;

    void setComparator(std::unique_ptr<StudentComparator> c);  // 정렬 기준 교체

private:
    // comparator->less()로 정렬, 값이 같으면 학번순
    void sortResult(std::vector<Student>& v) const;
};
