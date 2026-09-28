#pragma once

#include <string>
#include <vector>

#include "StudentManager.h"

// 콘솔 입출력 전담. 로직은 StudentManager에 맡김
class StudentUI {
private:
    StudentManager& manager;
    bool inputClosed = false;  // EOF가 들어오면 true → 메인 루프 종료

public:
    explicit StudentUI(StudentManager& m);
    void run();  // 메인 메뉴 루프

private:
    bool readLine(std::string& line);  // getline + 끝의 '\r' 제거. EOF면 false
    int readMenu(int min, int max);    // 범위 밖이거나 숫자가 아니면 0, EOF면 -1
    // 올바른 값이 들어올 때까지 해당 필드만 다시 물어봄 (요구사항 D5)
    std::string prompt(const std::string& msg, bool (*valid)(const std::string&));

    void doInsertion();
    void doSearch();
    void doSortOption();
    void printTable(const std::vector<Student>& v) const;
};
