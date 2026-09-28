#pragma once

#include <ostream>
#include <string>

// 학생 레코드 하나. 필드는 전부 private이고 getter만 제공함 (수정·삭제 없는 스펙과 일치)
class Student {
private:
    std::string name;        // 최대 15자
    std::string studentId;   // 정확히 10자리 숫자
    std::string birthYear;   // 정확히 4자리 숫자
    std::string department;  // 공백 포함 가능
    std::string tel;         // 최대 12자리 숫자 (앞자리 0 때문에 string)

public:
    Student();
    Student(const std::string& name, const std::string& id,
            const std::string& birth, const std::string& dept,
            const std::string& tel);

    const std::string& getName() const;
    const std::string& getStudentId() const;
    std::string getAdmissionYear() const;   // 학번 앞 4자리
    const std::string& getBirthYear() const;
    const std::string& getDepartment() const;
    const std::string& getTel() const;

    // 파일 한 줄로 변환: "Name|StudentID|BirthYear|Department|Tel"
    std::string serialize() const;
    // 파일 한 줄을 Student로 변환. 형식이 깨졌으면 false
    static bool deserialize(const std::string& line, Student& out);

    // 표 한 줄 출력 (std::left + std::setw, 요구사항 8장)
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
