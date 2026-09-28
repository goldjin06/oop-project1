#pragma once

#include <vector>

#include "Student.h"

// 저장소 추상 클래스: StudentManager는 이 인터페이스에만 의존함
class StudentRepository {
public:
    virtual ~StudentRepository() = default;
    virtual bool loadAll(std::vector<Student>& out) = 0;  // 저장된 레코드 전부 읽기
    virtual bool append(const Student& s) = 0;            // 새 레코드 하나 저장
};
