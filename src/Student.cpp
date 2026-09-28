#include "Student.h"

Student::Student() = default;

Student::Student(const std::string& name, const std::string& id,
                 const std::string& birth, const std::string& dept,
                 const std::string& tel)
    : name(name), studentId(id), birthYear(birth), department(dept), tel(tel)
{
}

const std::string& Student::getName() const { return name; }
const std::string& Student::getStudentId() const { return studentId; }
const std::string& Student::getBirthYear() const { return birthYear; }
const std::string& Student::getDepartment() const { return department; }
const std::string& Student::getTel() const { return tel; }

std::string Student::getAdmissionYear() const
{
    return studentId.substr(0, 4);
}

std::string Student::serialize() const
{
    // TODO: 필드를 '|'로 이어 붙여 반환
    return "";
}

bool Student::deserialize(const std::string& line, Student& out)
{
    // TODO: '|'로 나눠 필드 5개인지 확인하고, 형식이 맞으면 out에 채워서 true 반환
    (void)line;
    (void)out;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
    // TODO: std::left + std::setw로 열 너비 맞춰 한 줄 출력 (Name 16, StudentID 11, Dept 24, Birth Year 11, Tel 12)
    (void)s;
    return os;
}
