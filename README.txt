[Project 1 - 학생 정보 관리 시스템]

1. 개발 환경
- OS: Windows 11 (Galaxy Book)
- IDE / 컴파일러: Microsoft Visual Studio (MSVC)

2. 컴파일 및 실행 방법 (Windows / MSVC 환경)
Windows 환경에서 MSVC를 사용해 테스트하실 경우, Developer Command Prompt(개발자 명령 프롬프트)에서 아래 명령어를 통해 컴파일 및 실행이 가능합니다.
  (1) 컴파일: cl.exe /EHsc /Fe:a.exe src\*.cpp
  (2) 실행: a.exe file1.txt

3. 컴파일 및 실행 방법 (Linux/Mac / g++ 환경)
UNIX 기반 환경(macOS, Linux)에서 g++를 사용하실 경우를 위해 Makefile을 동봉하였습니다.
  (1) 컴파일: 터미널에서 make 명령어를 입력합니다.
     $ make
  (2) 실행: 생성된 실행 파일에 텍스트 파일 이름을 인자로 넣어 실행합니다.
     $ ./a.exe file1.txt

4. 참고 사항
- 프로그램 실행 시 "file1.txt"가 존재하지 않으면 자동으로 생성됩니다.
- "file1.txt"가 이미 존재하는 경우 기존 데이터를 정상적으로 불러옵니다.