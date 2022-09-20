﻿#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <stack>
#include <deque>
#include <queue>
#include <numeric>
#include <string>
using namespace std;

class MyLinkedList {	// leetcode 707
public:
	MyLinkedList()
		: m_head(new Node()), m_len(0) {}

	~MyLinkedList()
	{
		while (m_head)
		{
			Node* temp = m_head;
			m_head = m_head->next;
			delete temp;
		}
	}

	int get(int index) {
		if (index >= m_len)
			return -1;

		Node* temp = m_head->next;
		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}
		return temp->val;
	}

	void addAtHead(int val) {
		Node* temp = new Node(val);
		temp->next = m_head->next;
		m_head->next = temp;
		++m_len;
	}

	void addAtTail(int val) {
		Node* temp = m_head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new Node(val);
		++m_len;
	}

	void addAtIndex(int index, int val) {
		if (index > m_len)	// 注意不是>=，因为允许在末尾添加元素
			return;
		Node* temp = m_head;
		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}
		Node* ins = new Node(val);
		ins->next = temp->next;
		temp->next = ins;
		++m_len;
	}

	void deleteAtIndex(int index) {
		if (index >= m_len)
			return;

		Node* temp = m_head;
		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}
		Node* del = temp->next;
		temp->next = temp->next->next;
		delete del;
		--m_len;
	}

	void print()
	{
		Node* temp = m_head->next;
		cout << "len: " << m_len << ", all: ";
		while (temp)
		{
			cout << temp->val << ", ";
			temp = temp->next;
		}
		cout << endl;
	}

private:
	struct Node
	{
		Node() : val(0), next(nullptr) {}
		Node(int v) : val(v), next(nullptr) {}
		int val;
		Node* next;
	};

	Node* m_head;
	
	int m_len;
};

class UnionFind	// 并查集
{
public:
	UnionFind() {}

	UnionFind(int n)
	{
		parent.reserve(n);
		for (int i = 0; i < n; ++i)
			parent.push_back(i);
	}

	void Union(int a, int b)
	{
		parent[Find(a)] = b;
	}

	int Find(int a)
	{	// 路径压缩
		return parent[a] == a ? a : (parent[a] = Find(parent[a]));
	}

private:
	vector<int> parent;
};

class UnionFind_leetcode399	// 并查集、维护权值
{
public:
	UnionFind_leetcode399() {}

	UnionFind_leetcode399(int n)
	{
		parent.reserve(n);
		for (int i = 0; i < n; ++i)
			parent.push_back(i);
	}

	void Union(int a, int b, unordered_map<int, unordered_map<int, double> >& ans)
	{
		if (parent[a] == a)
			parent[a] = b;
		else
		{
			int temp = Find(a, ans);
			parent[temp] = b;
			ans[temp][b] = ans[temp][a] * ans[a][b];	// 确保 ans[a][b] 再 Union 过程之前已被赋值
			ans[b][temp] = 1.0 / ans[temp][b];
		}
	}

	int Find(int a, unordered_map<int, unordered_map<int, double> >& ans)
	{	// 路径压缩
		if (parent[a] == a)
			return a;
		else
		{
			int temp = Find(parent[a], ans);
			ans[a][temp] = ans[a][parent[a]] * ans[parent[a]][temp];
			ans[temp][a] = 1.0 / ans[a][temp];
			parent[a] = temp;
			return parent[a];
		}
	}

private:
	vector<int> parent;
};

class Solution {
public:
	const int inf = 0x3f3f;

	int maximumRemovals(string s, string p, vector<int>& removable) {	// leetcode 1898 9/20/22
		int min = 0, max = removable.size();
		while (min < max)	// 注意要考虑等于的情况，比如 0 - 10 中找 7
							// 若去掉等于号，则 mid 的值 0.5 进 1，min = mid，因为 min 被考虑过
							// mid 的值 0.5 取掉，max = mid，因为 max 被考虑过
							// 即使如此还是有问题，比如只有两个元素，或者二分查找最大的元素，等于号则不会有问题
							// 所以对于二分查找指定数的问题，一定是小于等于
							// 这题不同的是，min = 0 永远符合条件，min 只会取符合条件的值，最后返回 min，有等于号会死循环
							// 这道题类似与二分查找第一个小于指定值的值的索引，假设不存在相等的值。但当数组中
							// 没有小于的值时会返回索引 0，答案错误，而这道题 0 永远成立，所以不存在这个问题
		{
			int mid = min + max + 1 >> 1;
			if (sub_1898(mid, removable, s, p))
				min = mid;
			else
				max = mid - 1;	// 注意这里的逻辑，符合的 mid 赋值给 min ，不符合，max = mid - 1，
		}
		return min;
	}
	bool sub_1898(int k, vector<int>& removable, string s, string p)
	{
		int len_s = s.length(), len_p = p.length();
		vector<bool> sign(len_s, false);
		for (int i = 0; i < k; ++i)
			sign[removable[i]] = true;
		int i = 0, j = 0;
		for (; i < len_s && j < len_p; ++i)
			if (!sign[i] && s[i] == p[j])
				++j;
		return j == len_p ? true : false;
	}

	//vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)	// leetcode 399 9/16-17/22
	//{
	//	int len_equations = equations.size(), len_queries = queries.size(), count = 0, tempInt1, tempInt2, tempInt3;
	//	string tempStr1, tempStr2;
	//	unordered_set<string> stringSet;
	//	unordered_map<string, int> stringToNums;	// 字符串对应到并查集的数字
	//	unordered_map<int, unordered_map<int, double> > ans;
	//	vector<double> result(len_queries);
	//	for (int i = 0; i < len_equations; ++i)
	//		for (int j = 0; j < 2; ++j)
	//		{
	//			tempStr1 = equations[i][j];
	//			if (stringSet.find(tempStr1) == stringSet.end())
	//			{
	//				stringSet.insert(tempStr1);
	//				stringToNums[tempStr1] = count++;
	//			}
	//		}
	//	UnionFind_leetcode399 uf(count);
	//	for (int i = 0; i < len_equations; ++i)
	//	{
	//		tempInt1 = stringToNums[equations[i][0]];
	//		tempInt2 = stringToNums[equations[i][1]];
	//		ans[tempInt1][tempInt2] = values[i];
	//		ans[tempInt2][tempInt1] = 1.0 / values[i];
	//		ans[tempInt1][tempInt1] = 1.0;
	//		ans[tempInt2][tempInt2] = 1.0;	// 先算再 Union
	//		if (uf.Find(tempInt1, ans) != uf.Find(tempInt2, ans))
	//			uf.Union(tempInt1, tempInt2, ans);
	//	}
	//	for (int i = 0; i < len_queries; ++i)
	//	{
	//		tempStr1 = queries[i][0];
	//		tempStr2 = queries[i][1];
	//		tempInt1 = stringToNums[tempStr1];
	//		tempInt2 = stringToNums[tempStr2];
	//		if (stringSet.find(tempStr1) == stringSet.end() || stringSet.find(tempStr2) == stringSet.end()
	//			|| uf.Find(tempInt1, ans) != uf.Find(tempInt2, ans))
	//			result[i] = -1.0;
	//		else
	//		{
	//			tempInt3 = uf.Find(tempInt1, ans);
	//			result[i] = ans[tempInt1][tempInt3] * ans[tempInt3][tempInt2];
	//		}
	//	}
	//	return result;
	//}
	unordered_map<string, string> p;
	unordered_map<string, double> w;
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		int n = equations.size();
		for (auto e : equations) {
			p[e[0]] = e[0];
			p[e[1]] = e[1];
			w[e[0]] = 1.0;
			w[e[1]] = 1.0;
		}
		for (int i = 0; i < n; ++i) {
			vector<string> e = equations[i];
			string a = e[0], b = e[1];
			string pa = find(a), pb = find(b);
			if (pa == pb) continue;
			p[pa] = pb;
			w[pa] = w[b] * values[i] / w[a];
		}
		int m = queries.size();
		vector<double> ans(m);
		for (int i = 0; i < m; ++i) {
			string c = queries[i][0], d = queries[i][1];
			ans[i] = p.find(c) == p.end() || p.find(d) == p.end() || find(c) != find(d) ? -1.0 : w[c] / w[d];
		}
		return ans;
	}
	string find(string x) {	// 并查集
		if (p[x] != x) {
			string origin = p[x];
			p[x] = find(p[x]);
			w[x] *= w[origin];	// 路径压缩、更新权值，权值为子除以父
		}
		return p[x];
	}

	//int numIslands(vector<vector<char>>& grid)	// leetcode 200 9/14/22 三个思路 bfs dfs 并查集
	//{
	//	int m = grid.size(), n = grid[0].size(), count = 0;	// 注意完全不用设置 sign 来标志是否被访问过，直接把 grid 相应位置改为 0 即可
	//	deque<pair<int, int> > coordinates;
	//	for (int i = 0; i < m; ++i)
	//		for (int j = 0; j < n; ++j)
	//			if (grid[i][j] == '1')
	//			{
	//				++count;
	//				coordinates.push_back(pair<int, int>(i, j));
	//				bfs(grid, coordinates, m, n);
	//			}
	//	return count;
	//}
	void bfs(vector<vector<char> >& grid, deque<pair<int, int> >& coordinates, int m, int n)
	{
		int x, y;
		vector<int> dirs = { -1, 0, 1, 0, -1 };
		while (!coordinates.empty())
		{
			auto p = coordinates.front();
			coordinates.pop_front();
			for (int k = 0; k < 4; ++k)
			{
				x = p.first + dirs[k];
				y = p.second + dirs[k + 1];
				if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == '1')
				{
					coordinates.push_back({ x, y });
					grid[x][y] = '0';
				}
			}
		}
	}
	// dfs 与 bfs 类似
	int numIslands(vector<vector<char>>& grid)	// UnionFind *
	{
		int m = grid.size(), n = grid[0].size();
		UnionFind uf(m * n);
		set<int> s;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == '1')
				{
					if (i < m - 1 && grid[i + 1][j] == '1')
						uf.Union((i + 1) * n + j, i * n + j);	// 注意这里 i 乘的是列数 n 而不是行数 m！
					if (j < n - 1 && grid[i][j + 1] == '1')
						uf.Union(i * n + j + 1, i * n + j);
				}
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (grid[i][j] == '1')
					s.insert(uf.Find(i * n + j));
		//ans += grid[i][j] == '1' && i * n + j == find(i * n + j);	// 另一种计算方法，ans 即返回值，注意一个岛屿只有一个点使等式成立
		return s.size();
	}

	//vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {	// leetcode 496 9/13/22
	//	int m = nums1.size(), n = nums2.size(), temp = -1;
	//	vector<int> result(m);
	//	for (int i = n - 1, j = m - 1; j >= 0; --i)
	//	{
	//		if (nums2[i] > nums1[j])
	//			temp = nums2[i];
	//		else if (nums2[i] == nums1[j])
	//		{
	//			result[j] = temp;
	//			temp = -1;
	//			i = n;
	//			--j;
	//		}
	//	}
	//	return result;
	//}
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {	// 单调栈解法
		int m = nums1.size(), n = nums2.size();
		stack<int> numsStack;
		vector<int> result(m);
		unordered_map<int, int> numsMap;

		for (int i = n - 1; i >= 0; --i)
		{
			while (!numsStack.empty() && numsStack.top() < nums2[i])	// 维护一个单调栈
				numsStack.pop();
			if (!numsStack.empty())
				numsMap[nums2[i]] = numsStack.top();	// 每个元素的右边最大值存入 hash 表
			else
				numsMap[nums2[i]] = -1;
			numsStack.push(nums2[i]);
		}
		for (int i = 0; i < m; ++i)
			result[i] = numsMap[nums1[i]];	// 时间复杂度 O(m + n)
		return result;
	}

	int chalkReplacer(vector<int>& chalk, int k) {	// leetcode 1894 9/12/22
		int n = chalk.size();	// 思路还行，时间、空间效率一般，C++ 11 可以使用 long long 和 unsigned long long
		long sum = 0;		// 参考代码里思路更好
		vector<long> sum_index(n, 0);	//注意
		for (int i = 0; i < n; ++i)
		{
			sum += chalk[i];
			sum_index[i] = sum;
		}

		cout << sum_index[n - 1] << endl;

		long temp = k - k / sum_index[n - 1] * sum_index[n - 1];
		k = temp;
		if (k == 0)
			return 0;

		int min = 0, max = n - 1, mid;

		while (true)
		{
			mid = (min + max) / 2;
			if (sum_index[mid] < k)
				min = mid + 1;
			else if (sum_index[mid] == k)
				return mid + 1;
			else
			{
				if (mid == 0 || sum_index[mid - 1] <= k)
					return mid;
				else
					max = mid - 1;
			}
		}
		return 0;
	}
	//int chalkReplacer(vector<int>& chalk, int k) {
	//	int n = chalk.size();
	//	long long total = accumulate(chalk.begin(), chalk.end(), 0LL);
	//	k %= total;
	//	int res = -1;
	//	for (int i = 0; i < n; ++i) {	// 只用遍历一遍，不用相加
	//		if (chalk[i] > k) {
	//			res = i;
	//			break;
	//		}
	//		k -= chalk[i];
	//	}
	//	return res;
	//}

	int minSpeedOnTime(vector<int>& dist, double hour) {	// leetcode 1870 9/10/22
		int n = dist.size();
		if (n - 1 >= hour)
			return -1;

		int max = dist[0], min = 1, speed;	// 因为 hour 精确到小数点后两位，所以距离最大值为最大值的 100 倍
		for (int i = 0; i < n; ++i)			// 我并没有这么写，但两者效率都挺低
			if (max < dist[i])				// max 也可以简单粗暴的设为题目给的上限 1e7
				max = dist[i];

		double decimal = hour - (int)hour;
		if (decimal != 0)
		{
			double anotherMax = dist[n - 1] / decimal;
			if (anotherMax > max)
			{
				if (anotherMax - (int)anotherMax != 0)
					max = anotherMax + 1;
				else
					max - anotherMax;
			}
		}

		while (true)
		{
			speed = (min + max) / 2;
			if (judgeSpeed(dist, hour, speed))
				if (speed > 1 && judgeSpeed(dist, hour, speed - 1))
					max = speed - 1;
				else
					return speed;
			else
				min = speed + 1;
		}
		return speed;
	}
	bool judgeSpeed(vector<int>& dist, double hour, int speed)
	{
		int n = dist.size();
		double sum = 0, tempD, tempI;
		for (int i = 0; i < n - 1; ++i)
		{
			tempD = (double)dist[i] / speed;
			tempI = dist[i] / speed;
			sum += tempD > tempI ? tempI + 1 : tempI;
		}
		sum += (double)dist[n - 1] / speed;
		return sum <= hour ? true : false;
	}

	int networkDelayTime(vector<vector<int>>& times, int n, int k) {	// leetcode 743 9/9/22 9/18/22
		vector<vector<int> > edges(n + 1, vector<int>(n + 1, inf));
		for (auto& i : times) edges[i[0]][i[1]] = i[2];
		vector<bool> vis(n + 1, false);	// true 或 false 用来判断该点是否已经找到最短路径！！！
		vector<int> dis(n + 1, inf);
		dis[k] = 0;
		for (int i = 0; i < n; ++i)	// 最多 n 个循环
		{
			int t = -1;
			for (int j = 1; j <= n; ++j)
				if (!vis[j] && (t == -1 || dis[t] > dis[j]))	// 找最小的 dis
					t = j;
			vis[t] = true;
			for (int j = 1; j <= n; ++j)
				dis[j] = min(dis[j], dis[t] + edges[t][j]);	// 更新距离
		}
		int result = *max_element(++dis.begin(), dis.end());	// 别忘了跳过第 0 个元素
		return result == inf ? -1 : result;
	}

	bool containsCycle(vector<vector<char>>& grid) {	// leetcode 1559 9/8/22 ***
		int m = grid.size(), n = grid[0].size();
		if (m == 1 || n == 1)
			return false;

		UnionFind unionFind(m * n);

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				int temp = grid[i][j];
				int a = i * n + j, b = (i + 1) * n + j, c = i * n + j + 1;
				if (i < m - 1 && grid[i + 1][j] == temp)
				{
					if (unionFind.Find(a) == unionFind.Find(b))
						return true;
					else
						unionFind.Union(a, b);
				}
				if (j < n - 1 && grid[i][j + 1] == temp)
				{
					if (unionFind.Find(a) == unionFind.Find(c))
						return true;
					else
						unionFind.Union(a, c);
				}
			}
		}
		return false;
	}

	int cherryPickup(vector<vector<int>>& grid) {	// leetcode 741 没写出来
		int m = grid.size(), n = grid[0].size();
		if (grid[0][0] == -1 || grid[m - 1][n - 1] == -1)
			return 0;

		vector<vector<int> > down_right(m, vector<int>(n, 0));
		vector<vector<int> > up_left(m, vector<int>(n, 0));

		printVector(grid);
		cout << endl;

		down_right[0][0] = grid[0][0];
		grid[0][0] = 0;
		for (int i = 1; i < n; ++i)
		{
			if (grid[0][i] == -1 || down_right[0][i - 1] == -1)
				down_right[0][i] = -1;
			else
				down_right[0][i] = down_right[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < m; ++i)
		{
			if (grid[i][0] == -1 || down_right[i - 1][0] == -1)
				down_right[i][0] = -1;
			else
				down_right[i][0] = down_right[i - 1][0] + grid[i][0];
		}

		printVector(down_right);
		cout << endl;

		for (int i = 1; i < m; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				if (down_right[i - 1][j] == -1 && down_right[i][j - 1] == -1 || grid[i][j] == -1)
					down_right[i][j] = -1;
				else if (grid[i - 1][j] == -1)
				{
					grid[i][j - 1] = 0;
					if (j - 1 == 0)
					{
						for (int k = 0; k < i; ++k)
							grid[k][0] = 0;
					}
					down_right[i][j] = down_right[i][j - 1] + grid[i][j];
				}
				else if (grid[i][j - 1] == -1)
				{
					grid[i - 1][j] = 0;
					if (i - 1 == 0)
					{
						for (int k = 0; k < j; ++k)
							grid[0][k] = 0;
					}
					down_right[i][j] = down_right[i - 1][j] + grid[i][j];
				}
				else
				{
					if (down_right[i - 1][j] > down_right[i][j - 1])
					{
						down_right[i][j] = down_right[i - 1][j] + grid[i][j];
						//grid[i - 1][j] = 0;
					}
					else
					{
						down_right[i][j] = down_right[i][j - 1] + grid[i][j];
						//grid[i][j - 1] = 0;
					}
				}
			}
		}
		grid[m - 1][n - 1] = 0;
		int d_r = down_right[m - 1][n - 1];
		if (d_r == -1)
			return 0;

		printVector(grid);
		cout << endl;

		printVector(down_right);
		cout << endl;

		up_left[m - 1][n - 1] = grid[m - 1][n - 1];
		for (int i = n - 2; i >= 0; --i)
		{
			if (grid[0][i] == -1 || up_left[0][i + 1] == -1)
				up_left[0][i] = -1;
			else
				up_left[0][i] = up_left[0][i + 1] + grid[0][i];
		}
		for (int i = m - 2; i >= 0; --i)
		{
			if (grid[i][0] == -1 || up_left[i + 1][0] == -1)
				up_left[i][0] = -1;
			else
				up_left[i][0] = up_left[i + 1][0] + grid[i][0];
		}

		for (int i = m - 2; i >= 0; --i)
		{
			for (int j = n - 2; j >= 0; --j)
			{
				if (up_left[i + 1][j] == -1 && up_left[i][j + 1] == -1 || grid[i][j] == -1)
					up_left[i][j] = -1;
				else if (grid[i + 1][j] == -1)
				{
					up_left[i][j] = up_left[i][j + 1] + grid[i][j];
				}
				else if (grid[i][j + 1] == -1)
				{
					up_left[i][j] = up_left[i + 1][j] + grid[i][j];
				}
				else
				{
					if (up_left[i + 1][j] > up_left[i][j + 1])
					{
						up_left[i][j] = up_left[i + 1][j] + grid[i][j];
					}
					else
					{
						up_left[i][j] = up_left[i][j + 1] + grid[i][j];
					}
				}
			}
		}
		int u_l = up_left[0][0];
		if (u_l == -1)
			return 0;

		return d_r + u_l;
	}

	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {	// leetcode 733 9/5/22
		if (image[sr][sc] == color)
			return image;

		int m = image.size(), n = image[0].size();
		vector<vector<int> > sign(m, vector<int>(n, 0));	// 不需要标志数组，直接修改image颜色，见参考代码（因为传的对象引用，修改会改变函数外对象的值）
		vector<vector<int> > result(m, vector<int>(n, 0));
		sign[sr][sc] = 1;

		deque<pair<int, int> > coordinates;
		coordinates.push_back(pair<int, int>(sr, sc));

		int x, y;
		int temp = image[sr][sc];
		while (!coordinates.empty())
		{
			x = coordinates.front().first;
			y = coordinates.front().second;

			if (x >= 1 && image[x - 1][y] == temp && sign[x - 1][y] == 0)
			{
				sign[x - 1][y] = 1;
				coordinates.push_back(pair<int, int>(x - 1, y));
			}
			if (y < n - 1 && image[x][y + 1] == temp && sign[x][y + 1] == 0)
			{
				sign[x][y + 1] = 1;
				coordinates.push_back(pair<int, int>(x, y + 1));
			}
			if (x < m - 1 && image[x + 1][y] == temp && sign[x + 1][y] == 0)
			{
				sign[x + 1][y] = 1;
				coordinates.push_back(pair<int, int>(x + 1, y));
			}
			if (y >= 1 && image[x][y - 1] == temp && sign[x][y - 1] == 0)
			{
				sign[x][y - 1] = 1;
				coordinates.push_back(pair<int, int>(x, y - 1));
			}
			coordinates.pop_front();
		}
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (sign[i][j] == 1)
				{
					result[i][j] = color;
				}
				else
				{
					result[i][j] = image[i][j];
				}
			}
		}
		return result;
	}
	//const int dx[4] = { 1, 0, 0, -1 };
	//const int dy[4] = { 0, 1, -1, 0 };
	//vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
	//	int currColor = image[sr][sc];
	//	if (currColor == color) {
	//		return image;
	//	}
	//	int n = image.size(), m = image[0].size();
	//	queue<pair<int, int>> que;
	//	que.emplace(sr, sc);
	//	image[sr][sc] = color;
	//	while (!que.empty()) {
	//		int x = que.front().first, y = que.front().second;
	//		que.pop();
	//		for (int i = 0; i < 4; i++) {
	//			int mx = x + dx[i], my = y + dy[i];
	//			if (mx >= 0 && mx < n && my >= 0 && my < m && image[mx][my] == currColor) {
	//				que.emplace(mx, my);
	//				image[mx][my] = color;
	//			}
	//		}
	//	}
	//	return image;
	//}

	int minPathSum(vector<vector<int>>& grid) {	// leetcode 64	// 进阶版，允许各个方向的移动 *
		int m = grid.size(), n = grid[0].size();
		vector<vector<int> > dis(m, vector<int>(n, 0));	// m 行 n 列的值全为 0 的二维向量

		dis[0][0] = grid[0][0];
		for (int i = 1; i < n; ++i)
		{
			dis[0][i] = dis[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < m; ++i)
		{
			dis[i][0] = dis[i - 1][0] + grid[i][0];
		}

		for (int i = 1; i < m; ++i)
		{
			for (int j = 1; j < n; ++j)
			{
				dis[i][j] = min(dis[i - 1][j], dis[i][j - 1]) + grid[i][j];
			}
		}

		return dis[m - 1][n - 1];
	}
	int min(int a, int b)
	{
		return a < b ? a : b;
	}

	vector<vector<int>> generate(int numRows) {	// leetcode 118
		vector<vector<int> > result(numRows);	// 向量这里的numRows可以为变量
		for (int i = 0; i < numRows; ++i)
		{
			vector<int> temp(i + 1);
			result[i] = temp;
		}
		result[0][0] = 1;

		for (int i = 1; i < numRows; ++i)
		{
			result[i][0] = 1;
			result[i][i] = 1;
			for (int j = 1; j < i; ++j)
			{
				result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
			}
		}
		return result;
	}
	//vector<vector<int>> generate(int numRows) {	// 参考答案
	//	vector<vector<int>> ans;
	//	for (int i = 0; i < numRows; ++i) {
	//		vector<int> t(i + 1, 1);	// 了解这种初始化方法
	//		for (int j = 1; j < i; ++j) t[j] = ans[i - 1][j] + ans[i - 1][j - 1];
	//		ans.push_back(t);	// push_back更快
	//	}
	//	return ans;
	//}

	vector<int> searchRange(vector<int>& nums, int target) {	// leetcode 34 *
		int len = nums.size();

		vector<int> result(2);
		result[0] = -1;
		result[1] = -1;
		int start = 0, end = 0;
		int p = 0, q = len - 1;

		while (p <= q)
		{
			if (nums[(p + q) / 2] < target)	// 应该使用找到最左下标的方法
				p = (p + q) / 2 + 1;
			else if (nums[(p + q) / 2] > target)
				q = (p + q) / 2 - 1;
			else
			{
				result[0] = (p + q) / 2;
				result[1] = (p + q) / 2;

				end = result[1] + 1;
				while (end <= q)
				{
					if (nums[(end + q) / 2] > target)
						q = (end + q) / 2 - 1;
					else if (nums[(end + q) / 2] == target)
					{
						result[1] = (end + q) / 2;
						end = result[1] + 1;
					}
				}
				start = result[0] - 1;
				while (p <= start)
				{
					if (nums[(start + p) / 2] < target)
						p = (start + p) / 2 + 1;
					else if (nums[(start + p) / 2] == target)
					{
						result[0] = (start + p) / 2;
						start = result[0] - 1;
					}
				}
				break;
			}
		}
		return result;
	}

	int minCostClimbingStairs(vector<int>& cost) {	// leetcode 746
		int len = cost.size();
		int* dp = new int[len + 1];
		dp[0] = 0;
		dp[1] = 0;
		for (int i = 2; i < len + 1; ++i)
		{
			if (dp[i - 1] + cost[i - 1] < dp[i - 2] + cost[i - 2])	// 状态转移方程
				dp[i] = dp[i - 1] + cost[i - 1];
			else
				dp[i] = dp[i - 2] + cost[i - 2];
		}
		return dp[len];
	}

	int climbStairs(int n) {	// leetcode 70
		if (n <= 2)
			return n;

		int p = 1, q = 1, r = 2;
		for (int i = 2; i < n; ++i)
		{
			p = q;
			q = r;
			r = p + q;
		}
		return r;
	}

	// 调试相关
	void printVector(vector<vector<int> >& nums)
	{
		for (auto i = nums.begin(); i != nums.end(); ++i)
		{
			for (auto j = (*i).begin(); j != (*i).end(); ++j)
			{
				cout << *j << "   ";
			}
			cout << endl;
		}
	}
};

/* notes
	vector<int> a(2, 8); // 这样生成含有两个元素且值为8的向量
	3 >> 1 右移（左移）操作只适用于整数，比除法快，优先级比除法低，答案与整数除法相同：3 >> 1 为 1

*/
void test1()
{	
	Solution solution;
	string s = "qobftgcueho";
	string p = "obue";
	vector<int> removable = { 5 };
	cout << solution.maximumRemovals(s, p, removable) << endl;
}

int main(void)
{
	test1();
}