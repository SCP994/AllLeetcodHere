﻿#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

typedef unsigned long long ull;

class Solution
{
public:
	vector<vector<int> > updateMatrix(vector<vector<int> >& mat);	// leetcode 542 10/18/22

	void bfs_542_1(int x, int y, vector<vector<int> >& mat, vector<vector<int> >& vis, vector<vector<int> >& result);

	void bfs_542_2(vector<vector<int> >& mat, vector<vector<int> >& vis, vector<vector<int> >& result);

	vector<vector<int> > updateMatrix_(vector<vector<int> >& mat);	// 多源 BFS

	vector<vector<int>> highestPeak(vector<vector<int>>& isWater);	// leetcode 1765 10/19/22 多源 BFS

	int minKnightMoves(int x, int y);	// leetcode 1197 10/20/22 BFS

	int minKnightMoves_(int x, int y);	// 双向 BFS

	int extend_1197(unordered_map<int, int>& m1, unordered_map<int, int>& m2, deque<pair<int, int> >& q);

	int shortestPathBinaryMatrix(vector<vector<int>>& grid); // leetcode 1091 10/21/22 双向 BFS，朴素 BFS 可能更快

	int extend_1091(unordered_map<int, int>& m_oppo, unordered_map<int, int>& m, deque<pair<int, int> >& q, int n, vector<vector<int> >& grid);

	int nearestExit(vector<vector<char>>& maze, vector<int>& entrance); // leetcode 1926 10/22/22 BFS

	int shortestPath(vector<vector<int>>& grid, int k); // leetcode 1293 10/23/22 BFS 最短路

	int openLock(vector<string>& deadends, string target); // leetcode 752 10/24/22

	int openLock_(vector<string>& deadends, string target); // A* 算法

	int f(string state, string& target);

	int ladderLength(string beginWord, string endWord, vector<string>& wordList); // leetcode 127 10/25/22 （双向）BFS

	int minimumOperations(vector<int>& nums, int start, int goal); // leetcode 2059 10/26/22 双向 BFS

	int extend_2059(unordered_map<int, int>& m_q, unordered_map<int, int>& m, deque<int>& q, vector<int>& nums);

	int slidingPuzzle(vector<vector<int>>& board); // leetcode 773 10/27/22 A* 算法

	bool check(string& str);

	int f_773(string& state); // 估价函数

	int shortestPathLength(vector<vector<int>>& graph); // leetcode 847 10/29/22 BFS ***

	int cutOffTree(vector<vector<int>>& forest); // leetcode 675 11/1-2/22 A* 算法

	void maxHeapify(vector<vector<int> >& v, int heapSize, int i);

	int f_675(int x1, int y1, int x2, int y2);

	int minCost(vector<vector<int>>& grid); // leetcode 1368 11/3/22 双端队列 BFS

	int minimumObstacles(vector<vector<int>>& grid); // leetcode 2290 11/4/22 双端队列 BFS *

	bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination); // leetcode 490 11/5/22 DFS BFS

	bool exist(vector<vector<char>>& board, string word); // leetcode 79 11/6/22 回溯 ***

	bool dfs_79(int i, int j, int idx, int m, int n, int len, vector<vector<char> >& board, string& word);

	int getMaximumGold(vector<vector<int>>& grid); // leetcode 1219 11/7/22 回溯 DFS

	int dfs_1219(vector<vector<int> >& grid, int m, int n, int x, int y);

	bool makesquare(vector<int>& matchsticks); // leetcode 473 11/8/22 DFS 回溯

	bool dfs_473(vector<int>& matchsticks, int len, int idx, int count, int sum, int avg);

	bool makesquare_(vector<int>& matchsticks); // 排序 回溯

	bool dfs_473_(int idx, int avg, int len, vector<int>& matchsticks, vector<int>& edges);

	bool makesquare__(vector<int>& matchsticks); // 状态压缩 DP ***

private:
	const int inf = 0x3f3f3f3f;

	vector<int> dis = { 0, 1, 0, -1, 0 };
};

