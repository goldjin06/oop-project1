#include "Validator.h"
#include <cctype> // isdigit 함수를 쓰기 위해 추가

// 1. 문자열이 숫자로만 구성되어 있는지 확인하는 함수 선언
bool Validator::isAllDigits(const std::string& s)
{
    if (s.empty()) {
        return false;
    }
    // 문자 c가 숫자가 아니라면 if문이 참으로 실행되어 리턴값이 false 
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// 2. 학번 검증
bool Validator::isValidStudentId(const std::string& s)
{
    // 길이 검증 10자리
    if (s.length() != 10) {
        return false;
    }
    // 위에 선언한 isAllDigits함수를 사용하여 학번이 숫자로만인지 검증
    return isAllDigits(s);
}

// 3. 출생년도 검증
bool Validator::isValidBirthYear(const std::string& s)
{
    // 길이 검증 4자리
    if (s.length() != 4) {
        return false;
    }
    // 숫자로만인지 검증
    return isAllDigits(s);
}

// 4. 전화번호 검증
bool Validator::isValidTel(const std::string& s)
{
    // 12자리 초과 시 false
    if (s.length() > 12) {
        return false;
    }
    // 전화번호 생략 시 검사 미진행, 숫자로만인지 검증
    if (s.length() > 0 && !isAllDigits(s)) {
        return false;
    }
    return true;
}

// 5. 이름 검증
bool Validator::isValidName(const std::string& s)
{
    // 아예 공백이거나 공백포함 15자리 초과 시 false
    if (s.empty() || s.length() > 15) {
        return false;
    }
    // '|'는 필드를 나누는 기호이므로 만약 이름에 포함되어 있다면 false
    for (char c : s) {
        if (c == '|') {
            return false;
        }
    }
    return true;
}

// 6. 학과 검증 ('|' 포함되어 있다면 false)
bool Validator::isValidDepartment(const std::string& s)
{
    for (char c : s) {
        if (c == '|') {
            return false;
        }
    }
    return true;
}

// 7. 앞뒤 공백 제거
std::string Validator::trim(const std::string& s)
{
    // 글자가 아예 없다면 그대로 반환
    if (s.empty()) {
        return s;
    }
    // 공백이 아닌 칸 중 첫번째 칸 위치 값 저장
    size_t first = s.find_first_not_of(" \t");
    // 공백만 있다면 빈 값 반환
    if (first == std::string::npos) {
        return ""; 
    }
    // 공백이 아닌 칸 중 마지막 칸 위치 값 저장
    size_t last = s.find_last_not_of(" \t");
    // 공백이 아닌 칸 중 첫번째 칸부터 마지막 칸까지만 남기고 앞뒤 공백 자르고 그 값 출력
    return s.substr(first, (last - first + 1));
}