#pragma once
class TEST1
{
public:
	TEST1() = default;
	TEST1(const TEST1&) = default;
	~TEST1() = default;
	TEST1& operator=(const TEST1&) = default;
};

class TEST2
{
public:
	TEST2(const TEST2&) = delete;
	TEST2& operator=(const TEST2&) = delete;
	void* operator new(size_t) = delete; // new�� �Ҵ޴��� ���ϵ��� �Ѵ�.
};

struct TEST3
{
	//void f(int i) { std::cout << 1 << std::endl; }
	//void f(double d) = delete; ����ȭ ����
};


