#pragma once

#include <string>

#include "StudentRepository.h"

// 텍스트 파일 저장소: 한 줄에 학생 1명, '|'로 구분 (요구사항 5장)
class FileStudentRepository : public StudentRepository {
private:
    std::string path;
    bool ensureExists();  // 파일이 없으면 새로 만듦

public:
    explicit FileStudentRepository(const std::string& path);
    // 형식이 깨진 줄과 중복 학번 줄은 경고 출력 후 건너뜀 (먼저 나온 줄 우선)
    bool loadAll(std::vector<Student>& out) override;
    bool append(const Student& s) override;  // append 후 바로 flush
};
