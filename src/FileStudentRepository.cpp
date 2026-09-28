#include "FileStudentRepository.h"

#include <fstream>

FileStudentRepository::FileStudentRepository(const std::string& path)
    : path(path)
{
}

bool FileStudentRepository::ensureExists()
{
    std::ifstream in(path);
    if (in) {
        return true;
    }
    std::ofstream out(path);
    return static_cast<bool>(out);
}

bool FileStudentRepository::loadAll(std::vector<Student>& out)
{
    if (!ensureExists()) {
        return false;
    }
    // TODO: 한 줄씩 읽어서 끝의 '\r' 제거 → Student::deserialize
    //       형식이 깨진 줄, 중복 학번 줄은 경고 출력 후 건너뜀 (요구사항 D8)
    (void)out;
    return true;
}

bool FileStudentRepository::append(const Student& s)
{
    // TODO: std::ios::app으로 열어 s.serialize() 한 줄 쓰고 flush
    (void)s;
    return true;
}
