[실행 환경]
- OS: Windows
- 컴파일러: MSVC (Visual Studio Compiler)
- C++ 표준: C++14 이상

[빌드 방법]
Visual Studio의 개발자 명령 프롬프트(Developer Command Prompt) 또는 설정된 터미널에서 소스 코드가 있는 디렉토리(src)로 이동한 후, 아래 명령어를 입력하여 빌드합니다.
> cl.exe /EHsc /Fe:a.exe *.cpp

[실행 방법]
빌드가 완료되어 실행 파일이 생성되면, 장부 파일 이름(file1.txt)을 뒤에 붙여서 아래와 같이 실행합니다.
> a.exe file1.txt