#include "FileStudentRepository.h"
#include "Student.h"
#include <fstream> // 파일 입출력하기 위해 필요
#include <iostream> // 경고 문구 출력하기 위해 필요

FileStudentRepository::FileStudentRepository(const std::string& path)
    : path(path)
{
}

// 1. 파일이 없으면 새로 만들어주는 기능
bool FileStudentRepository::ensureExists()
{
    std::ifstream in(path);
    if (in) {
        return true;
    }
    std::ofstream out(path);
    return static_cast<bool>(out);
}

// 2. 텍스트 파일에 있는 모든 학생 명단을 메모리로 읽어오기
bool FileStudentRepository::loadAll(std::vector<Student>& out)
{
    // 파일이 없으면 하나 만들어두고 시작
    if (!ensureExists()) {
        return false;
    }

    // 텍스트 파일을 읽기 전용으로 열기
    std::ifstream in(path);
    if (!in) {
        return false; 
    }

    std::string line;
    int lineNumber = 0; // 몇 번째 줄에서 에러가 났는지 알려주기 위한 변수

    // 텍스트 파일의 맨 위부터 맨 밑까지 한 줄씩 계속 읽어오기
    while (std::getline(in, line)) {
        lineNumber++;

        // Windows 메모장의 '\r' 찌꺼기 잘라내기
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // 빈 줄이면 다음 줄로 넘어가기
        if (line.empty()) {
            continue;
        }

        Student s; // 데이터를 채울 빈 껍데기 학생 준비

        // Student::deserialize로 조립 시도(실패하면 경고 띄우고 무시)
        if (!Student::deserialize(line, s)) {
            std::cout << "Warning: malformed format skipped (line " << lineNumber << ")\n";
            // 불량인 줄은 더 이상 기능들을 거치지 않고 텍스트 파일의다음 줄로 이동
            continue;
        }

        // 학번 중복 검사(먼저 적힌 사람이 우선)
        bool isDuplicate = false;
        for (const Student& existing : out) {
            if (existing.getStudentId() == s.getStudentId()) {
                isDuplicate = true;
                break; // 똑같은 학번을 찾았으니 더 찾을 필요 없이 반복문 탈출
            }
        }

        // 중복이면 경고 띄우고 이 줄은 무시해버림
        if (isDuplicate) {
            std::cout << "Warning: duplicate ID " << s.getStudentId() << " skipped (line " << lineNumber << ")\n";
            continue;
        }

        // 형식도 맞고 중복도 아니면, 최종적으로 out에 push
        out.push_back(s);
    }

    return true; // 정상적으로 텍스트 파일 전부 읽기 완료
}

// 3. 텍스트 파일 맨 밑에 새로운 학생 한 줄 추가하기
bool FileStudentRepository::append(const Student& s)
{
    // 텍스트 파일의 기존 데이터 손상 없이 밑에 이어쓰도록 함
    std::ofstream out(path, std::ios::app);
    // 텍스트 파일에 output 불가능하면 false 반환
    if (!out) {
        return false;
    }

    // serialize함수로 문자열로 만든 후 텍스트 파일에 추가
    out << s.serialize() << "\n";
    
    // 데이터 즉시 저장, 한 줄(한 학생의 데이터가 적힐 때)마다 저장하도록 함
    out.flush(); 

    return true;
}