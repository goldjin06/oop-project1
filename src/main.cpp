#include <iostream>
#include <memory>

#include "FileStudentRepository.h"
#include "StudentManager.h"
#include "StudentUI.h"

int main(int argc, char* argv[])
{
    // 실행 인자로 파일 경로 1개를 받아야 함
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " file1.txt\n";
        return 1;
    }

    // 파일이 없으면 만들고, 있으면 기존 데이터를 읽어옴
    StudentManager manager(std::make_unique<FileStudentRepository>(argv[1]));
    if (!manager.load()) {
        std::cerr << "Cannot open file: " << argv[1] << '\n';
        return 1;
    }

    StudentUI(manager).run();
    return 0;
}
