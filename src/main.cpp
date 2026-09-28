#include <fstream>
#include <iostream>
#include <string>

namespace {

// 표준 입력에서 한 줄을 읽음. EOF면 false를 반환해서 호출한 쪽이 안전하게 종료할 수 있게 함.
// Windows 줄바꿈(\r\n)의 끝 '\r'은 제거함.
bool readLine(std::string& line)
{
    if (!std::getline(std::cin, line)) {
        return false;
    }
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return true;
}

// [min, max] 범위의 메뉴 번호를 읽음. EOF면 -1, 잘못된 입력이면 0을 반환함.
int readMenu(int min, int max)
{
    std::string line;
    if (!readLine(line)) {
        return -1;
    }
    if (line.size() != 1 || line[0] < '0' + min || line[0] > '0' + max) {
        std::cout << "Invalid input\n";
        return 0;
    }
    return line[0] - '0';
}

// 데이터 파일이 없으면 새로 만듦. 이미 있으면 그대로 사용함.
bool ensureFileExists(const std::string& path)
{
    std::ifstream in(path);
    if (in) {
        return true;
    }
    std::ofstream out(path);
    return static_cast<bool>(out);
}

// 1. Insertion: 학생 정보를 필드 순서대로 입력받음. EOF면 false를 반환함.
bool doInsertion()
{
    std::string name, id, birth, dept, tel;

    std::cout << "Name ? ";
    if (!readLine(name)) return false;
    std::cout << "Student ID (10 digits)? ";
    if (!readLine(id)) return false;
    std::cout << "Birth Year (4 digits) ? ";
    if (!readLine(birth)) return false;
    std::cout << "Department ? ";
    if (!readLine(dept)) return false;
    std::cout << "Tel ? ";
    if (!readLine(tel)) return false;

    // TODO: 입력값 검증, 학번 중복 검사("Error : Already inserted"), 파일에 저장
    return true;
}

// 2. Search: 검색 메뉴를 보여주고 검색어를 입력받음. EOF면 false를 반환함.
bool doSearch()
{
    std::cout << "- Search -\n"
              << "1. Search by name\n"
              << "2. Search by student ID (10 digits)\n"
              << "3. Search by admission year (4 digits)\n"
              << "4. Search by birth year (4 digits)\n"
              << "5. Search by department name\n"
              << "6. List All\n"
              << "> ";

    int choice = readMenu(1, 6);
    if (choice < 0) return false;
    if (choice == 0) return true;

    // 검색 메뉴 번호별 검색어 프롬프트 (6번 List All은 검색어 없음)
    static const char* const prompts[] = {
        "",
        "Name keyword? ",
        "Student ID? ",
        "Admission year? ",
        "Birth year? ",
        "Department name keyword? ",
    };

    std::string keyword;
    if (choice != 6) {
        std::cout << prompts[choice];
        if (!readLine(keyword)) return false;
    }

    // TODO: 검색어로 레코드 필터링, 현재 정렬 옵션으로 정렬, 표 출력
    std::cout << "Name           StudentID    Dept                  Birth Year  Tel\n";
    return true;
}

// 3. Sorting Option: 정렬 기준을 선택받음. EOF면 false를 반환함.
bool doSortOption(int& sortOption)
{
    std::cout << "- Sorting Option\n"
              << "1. Sort by Name\n"
              << "2. Sort by Student ID\n"
              << "3. Sort by Birth Year\n"
              << "4. Sort by Department name\n"
              << "> ";

    int choice = readMenu(1, 4);
    if (choice < 0) return false;
    if (choice > 0) {
        sortOption = choice;  // TODO: StudentManager의 비교 객체 교체
    }
    return true;
}

} // namespace

int main(int argc, char* argv[])
{
    // 실행 인자로 파일 경로 1개를 받아야 함
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " file1.txt\n";
        return 1;
    }

    const std::string path = argv[1];
    if (!ensureFileExists(path)) {
        std::cerr << "Cannot open file: " << path << '\n';
        return 1;
    }
    // TODO: 파일에서 학생 데이터 불러오기

    int sortOption = 1;  // 기본값: 이름순 정렬
    // 메인 메뉴 루프: 4(Exit)나 EOF가 들어올 때까지 반복
    bool running = true;
    while (running) {
        std::cout << "1. Insertion\n"
                  << "2. Search\n"
                  << "3. Sorting Option\n"
                  << "4. Exit\n"
                  << "> ";

        switch (readMenu(1, 4)) {
        case -1: running = false; break;  // EOF: 종료
        case 1: running = doInsertion(); break;
        case 2: running = doSearch(); break;
        case 3: running = doSortOption(sortOption); break;
        case 4: running = false; break;
        default: break;                   // 잘못된 입력: 메뉴를 다시 표시
        }
    }
    return 0;
}
