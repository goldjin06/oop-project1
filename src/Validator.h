#pragma once

#include <string>

// 입력 검증 (static 함수만 모아둔 클래스, 요구사항 3장)
class Validator {
public:
    static bool isValidName(const std::string& s);       // 1~15자, '|' 금지
    static bool isValidStudentId(const std::string& s);  // 정확히 10자리 숫자
    static bool isValidBirthYear(const std::string& s);  // 정확히 4자리 숫자
    static bool isValidDepartment(const std::string& s); // '|' 금지, 빈 값 허용
    static bool isValidTel(const std::string& s);        // 0~12자리 숫자
    static bool isAllDigits(const std::string& s);
    static std::string trim(const std::string& s);       // 앞뒤 공백 제거
};
