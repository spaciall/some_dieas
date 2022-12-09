// ConsoleApplication8.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <atomic>

#define ReadLock(lock)
#define WriteLock(lock)

class Foo 
{
public:
	std::atomic<int32_t> m_index = 0;
	std::string m_name = "";
};

std::unordered_map<int32_t, Foo*>  foos;

int main()
{
	auto foo1 = new Foo;
	foo1->m_index = 1;
	foo1->m_name = "foo1's name";
	// 필요한 경우에만 데이터 구조에 Write Lock을 잡음
	WriteLock(lock);
	{
		foos[1] = foo1;
	}
	Foo* foo1_to_modify = nullptr;
	// 변경이 필요한 경우 Read Lock을 잡아서 해당 데이터만 읽어 옴
	ReadLock(lock)
	{
		foo1_to_modify = foos[1];
	}
	foo1_to_modify->m_name = "foo1's modified name"
	// 변경 후 Write Lock을 잡고 데이터 업데이트
	WriteLock(lock);
	{
		foos[1] = foo1_to_modify;
	}
	// m_index는 atomic이므로 Lock을 신경쓰지 않고 변경하고 싶을 때 변경
	foo1_to_modify->m_index++;
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
