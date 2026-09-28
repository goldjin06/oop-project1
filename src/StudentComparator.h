#pragma once

#include <memory>

#include "Student.h"

// 정렬 기준 추상 클래스 (Strategy 패턴). 1차 기준만 비교하고, 같으면 StudentManager가 학번으로 2차 정렬함
class StudentComparator {
public:
    virtual ~StudentComparator() = default;
    virtual bool less(const Student& a, const Student& b) const = 0;

    // 팩토리: 1=이름, 2=학번, 3=출생년도, 4=학과 (범위 밖이면 nullptr)
    static std::unique_ptr<StudentComparator> create(int option);
};

class NameComparator : public StudentComparator {
public:
    bool less(const Student& a, const Student& b) const override;  // 대소문자 구분 없음
};

class StudentIdComparator : public StudentComparator {
public:
    bool less(const Student& a, const Student& b) const override;
};

class BirthYearComparator : public StudentComparator {
public:
    bool less(const Student& a, const Student& b) const override;
};

class DepartmentComparator : public StudentComparator {
public:
    bool less(const Student& a, const Student& b) const override;  // 대소문자 구분 없음
};
