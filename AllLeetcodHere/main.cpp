﻿#include "Solution02.h"

/* notes
	vector<int> a(2, 8); // 这样生成含有两个元素且值为8的向量
	3 >> 1 右移（左移）操作只适用于整数，比除法快，优先级比除法低，答案与整数除法相同：3 >> 1 为 1
	非静态变量不能在类外定义
	vector 初始化 : v(length)，可直接设置容量

*/

void test()
{
	Solution s;
	vector<vector<int> > t = { {1, 3},{2, 6},{8, 10},{15, 18} };
	s.merge(t);
	
}

int main(void)
{
	test();
}
