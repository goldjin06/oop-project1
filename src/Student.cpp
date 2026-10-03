#include "Student.h"
#include "Validator.h" // 검증용
#include <sstream>     // 문자열을 자르기 위해 필요
#include <vector>      // 자른 문자열들을 담아둘 가변 배열을 위해 필요
#include <iomanip>     // 출력 열 너비를 맞추기 위해 필요

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
// 학번에서 년도만 잘라야 하므로 const 사용하지 않음
std::string Student::getAdmissionYear() const
{
    return studentId.substr(0, 4);
}

// 1. 객체의 데이터를 하나의 문자열로 만들기
std::string Student::serialize() const
{
    return name + "|" + studentId + "|" + birthYear + "|" + department + "|" + tel;
}

// 2. 문자열 쪼개서 다시 객체의 데이터로 만들기
bool Student::deserialize(const std::string& line, Student& out)
{
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    // '|' 기호를 기준으로 문자열을 잘라서 tokens배열에 순서대로 넣음
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    // 전화 번호 없을 때 뒷 부분이 '|'로 끝났다면 자동으로 전화번호 빈칸인걸로 인식하기
    if (!line.empty() && line.back() == '|') {
        tokens.push_back("");
    }

    // 항목이 정확히 5개가 아니면 false
    if (tokens.size() != 5) {
        return false;
    }

    // Validator에 있는 자르기함수 이용해서 앞뒤공백 자르기
    std::string tName = Validator::trim(tokens[0]);
    std::string tId = Validator::trim(tokens[1]);
    std::string tBirth = Validator::trim(tokens[2]);
    std::string tDept = Validator::trim(tokens[3]);
    std::string tTel = Validator::trim(tokens[4]);

    // Validator에 있는 검증 함수 이용해서 각 데이터 검증
    if (!Validator::isValidName(tName) ||
        !Validator::isValidStudentId(tId) ||
        !Validator::isValidBirthYear(tBirth) ||
        !Validator::isValidDepartment(tDept) ||
        !Validator::isValidTel(tTel)) {
        return false; // 하나의 검증이라도 통과 못 하면 false
    }

    // 모든 검사를 통과시 out객체에 데이터 넣고 true 반환
    out.name = tName;
    out.studentId = tId;
    out.birthYear = tBirth;
    out.department = tDept;
    out.tel = tTel;

    return true;
}

// 3. 콘솔 창에 표 형태로 정리해서 출력하기
std::ostream& operator<<(std::ostream& os, const Student& s)
{
    // 각 데이터 별 최대 공간 확보 후 데이터 출력
    os << std::left
       << std::setw(16) << s.name
       << std::setw(11) << s.studentId
       << std::setw(24) << s.department
       << std::setw(11) << s.birthYear
       << std::setw(12) << s.tel;
    return os;
}