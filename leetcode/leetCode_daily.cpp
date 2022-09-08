#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>
#include <unordered_map>
using namespace std;
//202. 快乐数
bool isHappy(int n) {
	if (n == 1)return true;
	map<int, int>mmp;
	mmp[n] = 1;
	while (true) {
		vector<int>v;
		while (n > 0) {
			v.push_back(n % 10);
			n /= 10;
		}
		for (int i = 0; i < v.size(); i++) {
			n += pow(v[i], 2);
		}
		if (mmp.find(n) != mmp.end()) {
			return false;
		}
		else {
			mmp[n] = 1;
		}
		if (n == 1)return true;
	}
	return false;
}
//54. 螺旋矩阵
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	vector<vector<bool>> visited;
	for (unsigned i = 0; i < matrix.size(); i++)
	{
		vector<bool>b;
		b.resize(matrix[i].size());
		visited.push_back(b);
	}
	int i = 0, j = 0;
	bool isroad = true;
	vector<int>road;
	while (isroad) {
		isroad = false;
		while (i < matrix.size() && j < matrix[i].size() && visited[i][j] == false) {
			road.push_back(matrix[i][j]);
			visited[i][j++] = true;
			isroad = true;
		}
		j--;
		i++;
		while (i < matrix.size() && j < matrix[i].size() && visited[i][j] == false) {
			road.push_back(matrix[i][j]);
			visited[i++][j] = true;
			isroad = true;
		}
		i--;
		j--;
		while (i < matrix.size() && j >= 0 && visited[i][j] == false) {
			road.push_back(matrix[i][j]);
			visited[i][j--] = true;
			isroad = true;
		}
		j++;
		i--;
		while (i >= 0 && j >= 0 && visited[i][j] == false) {
			road.push_back(matrix[i][j]);
			visited[i--][j] = true;
			isroad = true;
		}
		i++;
		j++;
	}
	return road;
}
//1706. 球会落何处
vector<int> findBall(vector<vector<int>>& grid) {
	vector<int>ball_road(grid[0].size());
	for (int i = 0; i < grid[0].size(); i++) {
		bool runout = true;
		int level = 0, location = i;
		while (runout && level < grid.size()) {
			//导向右侧
			if (grid[level][location] == 1) {
				//右侧有挡板
				if (location < grid[level].size() - 1 && grid[level][location + 1] == 1) {
					level++;
					location++;
					continue;
				}//撞墙 挡板反向
				else {
					runout = false;
					break;
				}
			}//导向左侧
			else {
				if (location >= 1 && grid[level][location - 1] == -1) {
					level++;
					location--;
					continue;
				}
				else {
					runout = false;
					break;
				}
			}
		}
		ball_road[i] = (runout ? location : -1);
	}
	return ball_road;
}
//14. 最长公共前缀
string longestCommonPrefix(vector<string>& strs) {
	int index = 0;
	bool match = true;
	string longestCommonPrefix = "";
	while (match) {
		char ch;
		for (int i = 0; i < strs.size(); i++) {
			if (strs[i].size() > index) {
				if (i == 0)ch = strs[i][index];
				else {
					if (strs[i][index] != ch) {
						match = false;
						break;
					}
				}
			}
			else {
				match = false;
				break;
			}
		}
		if (match) {
			longestCommonPrefix.push_back(ch);
			index++;
		}
	}
	return longestCommonPrefix;
}
//43. 字符串相乘
string multiply(string num1, string num2) {
	string result = "";
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	for (int i = 0; i < num1.size(); i++) {
		string localtemp = "";
		int ch = num1[i] - '0';
		//补0
		for (int j = 0; j < i; j++) {
			localtemp += "0";
		}
		//相乘
		int flag = 0;
		for (int i = 0; i < num2.size(); i++) {
			int number = ch * (num2[i] - '0') + flag;
			localtemp += to_string(number % 10);
			flag = number / 10;
		}
		if (flag != 0)localtemp += to_string(flag);
		//两数相加
		int index = 0;
		flag = 0;
		string localresult = "";
		while (index < result.size() && index < localtemp.size()) {
			char temp = result[index] + localtemp[index] - '0' + flag;
			if (temp > '9') {
				flag = 1;
				temp -= 10;
			}
			else {
				flag = 0;
			}
			index++;
			localresult.push_back(temp);
		}
		while (index < result.size()) {
			char temp = result[index] + flag;
			if (temp > '9') {
				flag = 1;
				temp -= 10;
			}
			else {
				flag = 0;
			}
			index++;
			localresult.push_back(temp);
		}
		while (index < localtemp.size()) {
			char temp = localtemp[index] + flag;
			if (temp > '9') {
				flag = 1;
				temp -= 10;
			}
			else {
				flag = 0;
			}
			index++;
			localresult.push_back(temp);
		}
		if (flag != 0)localresult += to_string(flag);
		result = localresult;
	}
	reverse(result.begin(), result.end());
	while (result[0] == '0' && result.size() > 1)result = result.substr(1);
	return result;
}
//19. 删除链表的倒数第 N 个结点
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
ListNode* removeNthFromEnd(ListNode* head, int n) {
	vector<int>v;
	ListNode* ptr = head;
	while (ptr != nullptr) {
		v.push_back(ptr->val);
		ptr = ptr->next;
	}
	if (n <= v.size()) {
		v[v.size() - n] = -1;
	}
	head = nullptr;
	ptr = nullptr;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] != -1) {
			if (i == 0) {
				head = new ListNode(v[0]);
				ptr = head;
			}
			else {
				ptr->next = new ListNode(v[i]);
				ptr = ptr->next;
			}

		}
	}
	return head;
}
//234. 回文链表
bool isPalindrome(ListNode* head) {
	string s;
	while (head != nullptr) {
		s.push_back(head->val);
		head = head->next;
	}
	string rs = s;
	reverse(rs.begin(), rs.end());
	return rs == s;
}
//187. Repeated DNA Sequences
vector<string> findRepeatedDnaSequences(string s) {
	vector<string> sv;
	unordered_map<string, int>mmp;
	if (s.length() <= 10)return sv;
	for (int i = 0; i < s.size() - 10; i++) {
		string local = s.substr(i, 10);
		mmp[local]++;
		if (mmp[local] == 2)sv.push_back(local);

	}
	return sv;
}
//2357. Make Array Zero by Subtracting Equal Amounts
int minimumOperations(vector<int>& nums) {
	sort(nums.begin(), nums.end(), less<>());
	int index = 0, count = 0;
	while (index < nums.size()) {
		while (index < nums.size() && nums[index] == 0)index++;
		if (index < nums.size())count++;
		for (int i = index + 1; i < nums.size(); i++) {
			nums[i] -= nums[index];
		}
		if (index < nums.size())nums[index] = 0;
	}
	return count;
}
//328. Odd Even Linked List
ListNode* oddEvenList(ListNode* head) {
	vector<int>odd, even;
	int index = 1;
	ListNode* ptr = head;
	while (ptr != nullptr) {
		if (index % 2 == 1) {
			odd.push_back(ptr->val);
		}
		else {
			even.push_back(ptr->val);
		}
		ptr = ptr->next;
		index++;
	}
	ptr = head;
	for (int i = 0; i < odd.size(); i++) {
		ListNode* node = new ListNode(odd[i]);
		ptr->next = node;
		ptr = node;
	}
	for (int i = 0; i < even.size(); i++) {
		ListNode* node = new ListNode(even[i]);
		ptr->next = node;
		ptr = node;
	}
	return head;
}
//148. Sort List
ListNode* sortList(ListNode* head) {
	vector<int>v;
	ListNode* ptr = head;
	while (ptr != nullptr) {
		v.push_back(ptr->val);
		ptr = ptr->next;
	}
	sort(v.begin(), v.end(), less<>());
	if (v.size() > 1)head->val = v[0];
	ptr = head;
	for (int i = 0; i < v.size(); i++) {
		ListNode* node = new ListNode(v[i]);
		ptr->next = node;
		ptr = node;
	}
	return head;
}
//2131. Longest Palindrome by Concatenating Two Letter Words
int longestPalindrome(vector<string>& words) {
	map<string, int> words_count;
	for (unsigned i = 0; i < words.size(); i++)
	{
		words_count[words[i]]++;
	}
	bool single = false;
	int count = 0;
	map<string, int>::iterator it = words_count.begin();
	while (it != words_count.end()) {
		string word = it->first;
		if (word[0] == word[1] && it->second != 0) {
			if (it->second % 2 == 1) {
				if (!single) {
					count += it->second * 2;
					single = true;
				}
				else {
					count += it->second / 2 * 4;
				}
			}
			else {
				count += it->second * 2;
			}

		}
		else if (word[0] != word[1] && it->second != 0) {
			string pattern = "12";
			pattern[0] = word[1];
			pattern[1] = word[0];
			map<string, int>::iterator match = words_count.find(pattern);
			if (match != words_count.end()) {
				count += min(it->second, match->second) * 4;
				it->second = 0;
				match->second = 0;
			}
		}
		it++;
	}
	return count;
}
//621. 任务调度器
struct task
{
	char ch;
	int restNum;
};
bool cmp(task t1, task t2) {
	return t1.restNum > t2.restNum;
}
int leastInterval(vector<char>& tasks, int n) {
	if (n == 0)return tasks.size();
	map<char, int>taskMap;
	for (unsigned i = 0; i < tasks.size(); i++)
	{
		taskMap[tasks[i]]++;
	}
	map<char, int>::iterator it = taskMap.begin();
	vector<task>v;
	while (it != taskMap.end()) {
		task t;
		t.ch = it->first;
		t.restNum = it->second;
		v.push_back(t);
		it++;
	}
	sort(v.begin(), v.end(), cmp);
	int count = 0;
	vector<char>result;
	queue<char>wait;
	map<char, int>waitmap;
	while (v[0].restNum != 0) {
		int index = 0;
		char localChar = ' ';
		bool match = false;
		map<char, int>::iterator target;
		target = waitmap.find(v[index].ch);
		while (index < v.size() && waitmap.find(v[index].ch) != waitmap.end()
			&& waitmap.find(v[index].ch)->second != -1) {
			index++;
		}//找到了下一个操作的cpu任务
		if (index < v.size() && v[index].restNum != 0) {
			result.push_back(v[index].ch);
			v[index].restNum--;
			localChar = v[index].ch;
			int i = index + 1;
			while (i<v.size() && v[i].restNum>v[i - 1].restNum) {
				swap(v[i], v[i - 1]);
				i++;
			}
		}
		else {
			result.push_back(' ');
		}
		if (wait.size() > 0 && count >= n) {
			waitmap[wait.front()] = -1;
			wait.pop();
		}
		if (index <= v.size() && wait.size() < n) {
			wait.push(localChar);
			waitmap[localChar] = 1;
		}
		count++;
	}
	return count;

}
//226反转二叉树
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr)return root;
	else {
		TreeNode* node = root->left;
		root->left = root->right;
		root->right = node;
		invertTree(root->left);
		invertTree(root->right);
	}
	return root;
}
// 110.判断是否是平衡二叉树
int treeHeight(TreeNode* root) {
	if (root == nullptr)return 0;
	return max(treeHeight(root->left), treeHeight(root->right)) + 1;
}
bool isBalanced(TreeNode* root) {
	if (abs(treeHeight(root->left) - treeHeight(root->right)) <= 1) {
		return isBalanced(root->left) && isBalanced(root->right);
	}
	return false;
}
//543. 二叉树的直径
int diameterOfBinaryTree(TreeNode* root) {
	if (root == nullptr)return 0;
	else {
		int diameter = treeHeight(root->left) + treeHeight(root->right);
		int subDiameter = max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right));
		return max(diameter, subDiameter);
	}
}
//437.路经总和
int roadNum = 0;
void dfs(TreeNode* root, int targetSum) {
	if (root == nullptr)return;
	if (root->val == targetSum) {
		roadNum++;
	}
	if (root->left != nullptr)dfs(root->left, targetSum - root->val);
	if (root->right != nullptr)dfs(root->right, targetSum - root->val);
}
int pathSum(TreeNode* root, int targetSum) {
	if (root != nullptr) {
		dfs(root, targetSum);
		if (root->left != nullptr)pathSum(root->left, targetSum);
		if (root->right != nullptr)pathSum(root->right, targetSum);
	}
	return roadNum;
}
TreeNode* buildTreeByLevel(vector<int>v) {
	TreeNode* root = nullptr;
	queue<TreeNode*>nodeQueue;
	int index = 0;
	if (v.size() > 0) {
		root = new TreeNode(v[index++]);
		nodeQueue.push(root);
	}
	while (index < v.size()) {
		TreeNode* leftNode = nullptr, * rightNode = nullptr;
		if (v[index] != INT_MAX) {
			leftNode = new TreeNode(v[index++]);
			nodeQueue.front()->left = leftNode;
			nodeQueue.push(leftNode);
		}
		else {
			index++;
		}
		if (index < v.size() && v[index] != INT_MAX)
		{
			rightNode = new TreeNode(v[index++]);
			nodeQueue.front()->right = rightNode;
			nodeQueue.push(rightNode);
		}
		else {
			index++;
		}
		nodeQueue.pop();
	}
	return root;
}
//74. 搜索二维矩阵
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	vector<int>v;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			v.push_back(matrix[i][j]);
		}
	}
	bool match = false;
	int i = 0, j = v.size() - 1;
	while (i < j && !match) {
		int mid = (i + j) / 2;
		if (v[mid] < target)i = mid + 1;
		else if (v[mid] > target)j = mid;
		else {
			match = true;
			break;
		}
	}
	if (i == j && v[i] == target)match = true;
	return match;
}
//108. 将有序数组转换为二叉搜索树 自己的解答
void getList(vector<int> nums, int i, int j, vector<int>& list) {
	if (i > j)return;
	else if (i == j) {
		list.push_back(nums[i]);
		return;
	}
	else {
		int mid = (i + j) / 2;
		list.push_back(nums[mid]);
		getList(nums, i, mid - 1, list);
		getList(nums, mid + 1, j, list);
	}
}
TreeNode* buildSearchTree(TreeNode* root, int val) {
	if (root == nullptr)root = new TreeNode(val);
	else if (root->val > val) {
		if (root->left != nullptr) {
			buildSearchTree(root->left, val);
		}
		else {
			root->left = new TreeNode(val);
		}
	}
	else {
		if (root->right != nullptr) {
			buildSearchTree(root->right, val);
		}
		else {
			root->right = new TreeNode(val);
		}
	}
	return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
	vector<int> list;
	TreeNode* root = nullptr;
	getList(nums, 0, nums.size() - 1, list);
	for (unsigned i = 0; i < list.size(); i++)
	{
		if (list[i] != INT_MAX)root = buildSearchTree(root, list[i]);
	}
	return root;
}
//更简单的题解
TreeNode* helper_arrayToBST(vector<int>& nums, int i, int j) {
	if (i > j) {
		return nullptr;
	}
	int mid = (i + j) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = helper_arrayToBST(nums, i, mid - 1);
	root->right = helper_arrayToBST(nums, mid + 1, j);
	return root;
}
TreeNode* sortedArrayToBST_easy(vector<int>& nums) {
	return helper_arrayToBST(nums, 0, nums.size() - 1);
}

//230. 二叉搜索树中第K小的元素
void kthSmallest_helper(TreeNode* root, vector<int>& v) {
	if (root == nullptr)return;
	kthSmallest_helper(root->left, v);
	v.push_back(root->val);
	kthSmallest_helper(root->right, v);
}
int kthSmallest(TreeNode* root, int k) {
	vector<int> v;
	kthSmallest_helper(root, v);
	return v[k];
}

//173. 二叉搜索树迭代器
class BSTIterator {
public:
	vector<int>BSTIterator_v;
	int BSTIterator_index = 0;
	void inorder(TreeNode* root, vector<int>& v) {
		if (root == nullptr) {
			return;
		}
		inorder(root->left, v);
		v.push_back(root->val);
		inorder(root->right, v);
	}
	vector<int> inorder_use(TreeNode* root) {
		vector<int>v;
		inorder(root, v);
		return v;
	}
	BSTIterator(TreeNode* root) {
		BSTIterator_v = inorder_use(root);
	}

	int next() {
		return BSTIterator_v[BSTIterator_index++];
	}

	bool hasNext() {
		return BSTIterator_index < BSTIterator_v.size();
	}
};
//994. 腐烂的橘子
vector<bool> orangesVisit;
bool orangesInfected = false;
int orangesRotting(vector<vector<int>>& grid) {
	orangesVisit.resize(grid.size() * grid[0].size());
	int count = 0;
	do {
		vector<vector<int>> temp = grid;
		orangesInfected = false;
		for (int i = 0; i < grid.size(); i++)
		{
			vector<int> current = grid[i];
			for (int u = 0; u < current.size(); u++)
			{
				if (current[u] == 2 && orangesVisit[i * current.size() + u] == false) {
					orangesVisit[i * current.size() + u] = true;
					if (i - 1 >= 0 && grid[i - 1][u] == 1) {//向上
						orangesInfected = true;
						temp[i - 1][u] = 2;
					}
					if (u - 1 >= 0 && grid[i][u - 1] == 1) {//向左
						orangesInfected = true;
						temp[i][u - 1] = 2;
					}
					if (u + 1 < current.size() && grid[i][u + 1] == 1) {//向右
						orangesInfected = true;
						temp[i][u + 1] = 2;
					}
					if (i + 1 < grid.size() && grid[i + 1][u] == 1) {//向下
						orangesInfected = true;
						temp[i + 1][u] = 2;
					}
				}
			}
		}
		if (orangesInfected)count++;
		grid = temp;
	} while (orangesInfected);
	bool hasGood = false;
	for (int i = 0; i < grid.size() && !hasGood; i++)
	{
		for (int u = 0; u < grid[i].size() && !hasGood; u++)
		{
			if (grid[i][u] == 1) {
				hasGood = true;
			}
		}
	}
	if (hasGood) {
		return  -1;
	}
	else {
		return count;
	}
}
//417. 太平洋大西洋水流问题
int pointToAtlantic[205][205] = { 0 };
int pointToPacific[205][205] = { 0 };
//可以去太平洋的
void Pacific_help(vector<vector<int>>& heights, int i, int j) {
	int n = heights.size(), m = heights[0].size();
	if (i < n && j < m) {
		//可以往右延伸
		if (j < m - 1 && heights[i][j] <= heights[i][j + 1] && pointToPacific[i][j + 1] == 0) {
			pointToPacific[i][j + 1] = 1;
			Pacific_help(heights, i, j + 1);
		}
		//可以往下延伸
		if (i < n - 1 && heights[i][j] <= heights[i + 1][j] && pointToPacific[i + 1][j] == 0) {
			pointToPacific[i + 1][j] = 1;
			Pacific_help(heights, i + 1, j);
		}
		//可以往左延伸
		if (j >= 1 && heights[i][j] <= heights[i][j - 1] && pointToPacific[i][j - 1] == 0) {
			pointToPacific[i][j - 1] = 1;
			Pacific_help(heights, i, j - 1);
		}
		//可以往上延伸
		if (i >= 1 && heights[i][j] <= heights[i - 1][j] && pointToPacific[i - 1][j] == 0) {
			pointToPacific[i - 1][j] = 1;
			Pacific_help(heights, i - 1, j);
		}
	}
}
void Atlantic_help(vector<vector<int>>& heights, int i, int j) {
	int n = heights.size(), m = heights[0].size();
	if (i >= 0 && j >= 0) {
		//可以往左延伸
		if (j >= 1 && heights[i][j] <= heights[i][j - 1] && pointToAtlantic[i][j - 1] == 0) {
			pointToAtlantic[i][j - 1] = 1;
			Atlantic_help(heights, i, j - 1);
		}
		//可以往上延伸
		if (i >= 1 && heights[i][j] <= heights[i - 1][j] && pointToAtlantic[i - 1][j] == 0) {
			pointToAtlantic[i - 1][j] = 1;
			Atlantic_help(heights, i - 1, j);
		}
		//可以往右延伸
		if (j < m - 1 && heights[i][j] <= heights[i][j + 1] && pointToAtlantic[i][j + 1] == 0) {
			pointToAtlantic[i][j + 1] = 1;
			Atlantic_help(heights, i, j + 1);
		}
		//可以往下延伸
		if (i < n - 1 && heights[i][j] <= heights[i + 1][j] && pointToAtlantic[i + 1][j] == 0) {
			pointToAtlantic[i + 1][j] = 1;
			Atlantic_help(heights, i + 1, j);
		}
	}
}
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
	int n = heights.size(), m = heights[0].size();
	vector<vector<int>> result;
	for (int i = 0; i < m; i++)
	{
		pointToPacific[0][i] = 1;
		pointToAtlantic[n - 1][i] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		pointToPacific[i][0] = 1;
		pointToAtlantic[i][m - 1] = 1;
	}
	for (int i = 0; i < m; i++)
	{
		Pacific_help(heights, 0, i);
		Atlantic_help(heights, n - 1, i);
	}
	for (int i = 0; i < n; i++)
	{
		Pacific_help(heights, i, 0);
		Atlantic_help(heights, i, m - 1);
	}
	for (int i = 0; i < n; i++)
	{
		for (int u = 0; u < m; u++)
		{
			if (pointToAtlantic[i][u] & pointToPacific[i][u]) {
				vector<int>temp = { i,u };
				result.push_back(temp);
			}
		}
	}
	return result;
}
//210. 课程表 II 拓扑
vector<int>courseLater[2010];
int course_mention[2010];
bool hasCourseCircle = false;
void dfs_course(int root, stack<int>& courseStack) {
	course_mention[root] = 1;
	if (courseLater[root].size() > 0) {
		for (int i = 0; i < courseLater[root].size(); i++)
		{
			int courseId = courseLater[root][i];
			if (course_mention[courseId] == 0) {
				dfs_course(courseLater[root][i], courseStack);
				if (hasCourseCircle)return;
			}
			else if (course_mention[courseId] == 1) {
				hasCourseCircle = true;
				return;
			}
		}
	}
	courseStack.push(root);
	course_mention[root] = 2;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
	stack<int>courseStack;
	vector<int>result;
	for (int i = 0; i < prerequisites.size(); i++)
	{
		vector<int>pre = prerequisites[i];
		courseLater[pre[1]].push_back(pre[0]);
	}
	for (int i = 0; i < numCourses && !hasCourseCircle; i++)
	{
		if (course_mention[i] == 0) {
			dfs_course(i, courseStack);
		}
	}
	if (hasCourseCircle) {
		result.clear();
		return result;
	}
	while (courseStack.size() > 0) {
		result.push_back(courseStack.top());
		courseStack.pop();
	}
	return result;
}
//815.困难题目 公交路线
int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
	if (source == target)return 0;
	int n = routes.size();
	//使用一个哈希表 存储每一个站点对应了多少个车站
	map<int, vector<int>>siteMap;
	//车站线路的连边的存储表
	vector<vector<int>> edge(n, vector<int>(n));
	for (int currentBus = 0; currentBus < n; currentBus++)
	{
		for (int site : routes[currentBus])
		{
			for (int storedBusNum : siteMap[site]) {
				edge[storedBusNum][currentBus] = true;
				edge[currentBus][storedBusNum] = true;
			}
			siteMap[site].push_back(currentBus);
		}
	}
	vector<int>dis(n, -1);
	queue<int>q;
	for (int site : siteMap[source])
	{
		dis[site] = 1;
		q.push(site);
	}
	while (q.size() > 0) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if (edge[x][i] && dis[i] == -1) {
				dis[i] = dis[x] + 1;
				q.push(i);
			}
		}
	}
	int dis_Destination = INT_MAX;
	for (int bus : siteMap[target]) {
		if (dis[bus] != -1) {
			dis_Destination = min(dis[bus], dis_Destination);
		}
	}
	return dis_Destination == INT_MAX ? -1 : dis_Destination;
}
//100. 相同的树
bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == nullptr && q == nullptr) {
		return true;
	}
	else if (p == nullptr || q == nullptr) {
		return false;
	}
	else if (p->val != q->val) {
		return false;
	}
	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
//101. 对称二叉树
bool isSymmetricTree(TreeNode* p, TreeNode* q) {
	if (p == nullptr && q == nullptr) {
		return true;
	}
	else if (p == nullptr || q == nullptr) {
		return false;
	}
	else if (p->val != q->val) {
		return false;
	}
	return isSameTree(p->left, q->right) && isSameTree(p->right, q->left);
}
bool isSymmetric(TreeNode* root) {
	if (root == nullptr)return true;
	return isSymmetricTree(root->left, root->right);
}
//动态规划学习系列
//62. 不同路径
int uniquePaths(int m, int n) {
	vector<vector<int>>paths(m, vector<int>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			if (j == 0 && i == 0)paths[i][j] = 1;
			else if (j == 0)paths[i][j] = paths[i - 1][j];
			else if (i == 0)paths[i][j] = paths[i][j - 1];
			else {
				paths[i][j] = paths[i][j - 1] + paths[i - 1][j];
			}
		}
	}
	return paths[m - 1][n - 1];
}
//63. 不同路径 II(存在障碍物)
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	int n = obstacleGrid.size(), m = obstacleGrid[0].size();
	vector<vector<int>>paths(n, vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (obstacleGrid[i][j] == 1)paths[i][j] = 0;
			else {
				if (j == 0 && i == 0)paths[i][j] = 1;
				else if (j == 0) {
					paths[i][j] = paths[i - 1][j];
				}
				else if (i == 0)paths[i][j] = paths[i][j - 1];
				else {
					paths[i][j] = paths[i][j - 1] + paths[i - 1][j];
				}
			}
		}
	}
	return paths[n - 1][m - 1];
}
//64. 最小路径和
int minPathSum(vector<vector<int>>& grid) {
	int n = grid.size(), m = grid[0].size();
	vector<vector<int>>pathSum(n, vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (j == 0 && i == 0)pathSum[i][j] = grid[i][j];
			else if (i == 0)pathSum[i][j] = pathSum[i][j - 1] + grid[i][j];
			else if (j == 0)pathSum[i][j] = pathSum[i - 1][j] + grid[i][j];
			else {
				pathSum[i][j] = min(pathSum[i - 1][j], pathSum[i][j - 1]) + grid[i][j];
			}
		}
	}
	return pathSum[n - 1][m - 1];
}
//120. 三角形最小路径和
int minimumTotal(vector<vector<int>>& triangle) {
	int minTotal = INT_MAX;
	for (int i = 0; i < triangle.size(); i++)
	{
		int m = triangle[i].size();
		for (int u = 0; u < m; u++)
		{
			if (i == 0)break;
			else if (u == 0) {
				triangle[i][u] += triangle[i - 1][u];
			}
			else if (u == m - 1) {
				triangle[i][u] += triangle[i - 1][u - 1];
			}
			else {
				triangle[i][u] += min(triangle[i - 1][u - 1], triangle[i - 1][u]);
			}
		}
	}
	for (int num : triangle[triangle.size() - 1])
	{
		minTotal = min(minTotal, num);
	}
	return minTotal == INT_MAX ? 0 : minTotal;
}
//931. 下降路径最小和
int minFallingPathSum(vector<vector<int>>& matrix) {
	int n = matrix.size(), m = matrix[0].size();
	vector<vector<int>>dp(n, vector<int>(m));
	int minPathSum = INT_MAX;
	if (m == 1) {
		minPathSum = 0;
		for (int i = 0; i < n; i++)
		{
			minPathSum += matrix[i][0];
		}
		return minPathSum;
	}
	for (int i = 0; i < n; i++)
	{
		for (int u = 0; u < m; u++)
		{
			if (i == 0)dp[i][u] = matrix[i][u];
			else if (u == 0) {
				dp[i][u] = min(dp[i - 1][u], dp[i - 1][u + 1]) + matrix[i][u];
			}
			else if (u == m - 1) {
				dp[i][u] = min(dp[i - 1][u - 1], dp[i - 1][u]) + matrix[i][u];
			}
			else {
				dp[i][u] = min(min(dp[i - 1][u - 1], dp[i - 1][u]), dp[i - 1][u + 1]) + matrix[i][u];
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		minPathSum = min(minPathSum, dp[n - 1][i]);
	}
	return minPathSum == INT_MAX ? 0 : minPathSum;

}
//1289. 下降路径最小和 II (给你一个 n x n 整数矩阵 arr ，请你返回 非零偏移下降路径 数字和的最小值)
int minFallingPathSumII(vector<vector<int>>& grid) {
	int n = grid.size(), m = grid[0].size();
	vector<vector<int>>dp(n, vector<int>(m));
	int minPathSum = INT_MAX;
	if (m == 1)return grid[0][0];
	int minIndex1 = -1, minIndex2 = -1;
	for (int i = 0; i < n; i++)
	{
		//更新动态规划值
		int val = grid[0][i];
		dp[0][i] = val;
		//更新最小值和第二小值
		if (val < (minIndex1 == -1 ? INT_MAX : dp[0][minIndex1])) {
			minIndex2 = minIndex1;
			minIndex1 = i;
		}
		else if (val < (minIndex2 == -1 ? INT_MAX : dp[0][minIndex2])) {
			minIndex2 = i;
		}
	}
	//再转移剩余行
	for (int i = 1; i < n; i++)
	{
		for (int u = 0; u < m; u++)
		{
			if (minIndex1 == u) {
				dp[i][u] = dp[i - 1][minIndex2] + grid[i][u];
			}
			else {
				dp[i][u] = dp[i - 1][minIndex1] + grid[i][u];
			}
		}
		minIndex1 = -1, minIndex2 = -1;
		for (int u = 0; u < m; u++)
		{
			int val = dp[i][u];
			if (val < (minIndex1 == -1 ? INT_MAX : dp[i][minIndex1])) {
				minIndex2 = minIndex1;
				minIndex1 = u;
			}
			else if (val < (minIndex2 == -1 ? INT_MAX : dp[i][minIndex2])) {
				minIndex2 = u;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		minPathSum = min(minPathSum, dp[n - 1][i]);
	}
	return minPathSum == INT_MAX ? 0 : minPathSum;
}
//1575. 统计所有可行路径
class countRoutesClass {
public:
	int mod = 1000000007;
	vector<vector<int>>dp;
	int countRoutesHelp(vector<int>& locations, int start, int finish, int fuel) {
		if (dp[start][fuel] != -1) {
			return dp[start][fuel];
		}
		// 如果一步到达不了，说明从位置 u 不能到达 end 位置
		// 将结果 0 写入缓存器并返回
		int need = abs(locations[start] - locations[finish]);
		if (need > fuel) {
			dp[start][fuel] = 0;
			return 0;
		}
		// 计算油量为 fuel，从位置 u 到 end 的路径数量
		// 由于每个点都可以经过多次，如果 u = end，那么本身就算一条路径
		int sum = start == finish ? 1 : 0;
		for (int i = 0; i < locations.size(); i++)
		{
			if (i != start) {
				need = abs(locations[i] - locations[start]);
				if (fuel >= need) {
					sum += countRoutesHelp(locations, i, finish, fuel - need);
					sum %= mod;
				}
			}
		}
		dp[start][fuel] = sum;
		return dp[start][fuel];
	}
	int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
		int n = locations.size();
		dp.resize(n);
		for (int i = 0; i < locations.size(); i++) {
			vector<int>v(fuel + 1, -1);
			dp[i] = v;
		}
		int num = 0;
		countRoutesHelp(locations, start, finish, fuel);
		return dp[start][fuel];
	}
};
//198. 打家劫舍
int rob(vector<int>& nums) {
	int n = nums.size();
	vector<vector<int>>dp(n, vector<int>(2));
	dp[n - 1][0] = 0;
	dp[n - 1][1] = nums[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		dp[i][0] = max(dp[i + 1][0], dp[i + 1][1]);
		dp[i][1] = dp[i + 1][0] + nums[i];
	}
	return max(dp[0][1], dp[0][0]);
}
//322. 零钱兑换 动态规划
int coinChangeHelp(vector<int>& coins, int amount, vector<int>& countdp) {
	if (amount < 0)return -1;
	if (amount == 0)return 0;
	if (countdp[amount - 1] != 0)return countdp[amount - 1];
	int Min = INT_MAX;
	for (int coin : coins)
	{
		int res = coinChangeHelp(coins, amount - coin, countdp);
		if (res >= 0 && res < Min) {
			Min = res + 1;
		}
	}
	countdp[amount - 1] = (Min == INT_MAX ? -1 : Min);
	return countdp[amount - 1];
}
int coinChange(vector<int>& coins, int amount) {
	if (amount < 1)return 0;
	vector<int>countdp;
	countdp.resize(amount);
	return coinChangeHelp(coins, amount, countdp);
}
//416. 分割等和子集 动态规划 接近0/1背包问题
bool canPartition(vector<int>& nums) {
	int sum = 0, maxNum = 0, n = nums.size();
	if (n < 2)return false;

	for (int i = 0; i < n; i++)
	{
		maxNum = max(maxNum, nums[i]);
		sum += nums[i];
	}
	if (sum % 2 == 1)return false;
	int target = sum / 2;
	if (maxNum > target)return false;
	vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
	//dp[num][target]：是否存在一种选取方案使得被选取的num的和等于target
	dp[0][nums[0]] = true;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j <= target; j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (nums[i] == j) {
				dp[i][j] = true;
			}
			else if (nums[i] < j) {
				dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
			}
			if (dp[i][target])return true;
		}
	}
	return dp[n - 1][target];
}
//152. 乘积最大子数组  be chosen or not be chosen
int maxProduct(vector<int>& nums) {
	vector<int>maxF(nums), minF(nums);
	for (int i = 1; i < nums.size(); i++)
	{
		maxF[i] = max(nums[i], max(maxF[i - 1] * nums[i], minF[i - 1] * nums[i]));
		minF[i] = min(nums[i], min(maxF[i - 1] * nums[i], minF[i - 1] * nums[i]));
	}
	sort(maxF.begin(), maxF.end(), greater<int>());
	return maxF[0];
}
//3. 无重复字符的最长子串 滑动窗口
int lengthOfLongestSubstring(string s) {
	string substring, temp;
	map<char, int>stringMap;
	for (int i = 0; i < s.length(); i++)
	{
		if (stringMap.find(s[i]) == stringMap.end()) {
			temp = temp + s[i];
			stringMap[s[i]] = i;
		}
		else {
			if (temp.size() > substring.size()) {
				substring = temp;
			}
			int repeatIndex = temp.find(s[i]);
			string retain = temp.substr(repeatIndex + 1) + s[i];
			string abandon = temp.substr(0, repeatIndex);
			temp = retain;
			for (int i = 0; i < abandon.length(); i++)
			{
				stringMap.erase(stringMap.find(abandon[i]));
			}
		}
	}
	if (temp.size() > substring.size()) {
		substring = temp;
	}
	return substring.length();
}
//16. 最接近的三数之和 排序+双指针
int threeSumClosest(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end(), less<int>());
	int gap = INT_MAX, sum = 0;
	for (int i = 0; i < nums.size() - 2; i++)
	{
		int a = nums[i], left = i + 1, right = nums.size() - 1, localTarget = target - a;
		while (right - left > 1) {
			if (nums[left] + nums[right] > localTarget)right--;
			else if (nums[left] + nums[right] < localTarget)left++;
			else {
				return target;
			}
		}
		int temp = a + nums[left] + nums[right];
		if (abs(temp - target) < gap) {
			gap = abs(temp - target);
			sum = temp;
		}
	}
	return sum;
}
//76. 最小覆盖子串 unordered_map相比map不需要排序，完全节约时间
bool fillIn(unordered_map<char, int>tmap, unordered_map<char, int>temp) {
	for (const auto& p : tmap) {
		if (temp[p.first] < p.second)return false;
	}
	return true;
}
string minWindow(string s, string t) {
	if (t.length() > s.length())return "";
	if (t.length() == s.length() && t == s)return t;
	unordered_map<char, int>tmap, temp;
	int l = 0, r = -1, distance = INT_MAX, ansL = -1;
	//我们可以用一个哈希表表示 tt 中所有的字符以及它们的个数，用一个哈希表动态维护窗口中所有的字符以及它们的个数，如果这个动态表中包含 t 的哈希表中的所有字符，
	//并且对应的个数都不小于 tt 的哈希表中各个字符的个数，那么当前的窗口是「可行」的
	for (int i = 0; i < t.length(); i++)
	{
		tmap[t[i]]++;
	}
	bool change = false;
	while (r < (int)s.length()) {
		if (tmap.find(s[++r]) != tmap.end()) {
			temp[s[r]]++;
		}
		while (fillIn(tmap, temp) && l <= r) {
			if (r - l + 1 < distance) {
				distance = r - l + 1;
				ansL = l;
			}
			if (tmap.find(s[l]) != tmap.end()) {
				temp[s[l]]--;
			}
			l++;
		}
	}
	return ansL == -1 ? string() : s.substr(ansL, distance);
}
//789. 逃脱阻碍者 曼哈顿距离
bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
	int man = abs(target[0]) + abs(target[1]);
	for (int i = 0; i < ghosts.size(); i++)
	{
		int dis = abs(ghosts[i][0] - target[0]) + abs(ghosts[i][1] - target[1]);
		if (dis <= man)return false;
	}
	return true;
}
//剑指 Offer II 004. 只出现一次的数字 
int singleNumber(vector<int>& nums) {
	unordered_map<int, int>mmap;
	for (int i = 0; i < nums.size(); i++)
	{
		mmap[nums[i]]++;
	}
	auto it = mmap.begin();
	while (it != mmap.end()) {
		if (it->second == 1)return it->first;
		it++;
	}
	return 1;
}
//剑指 Offer II 005. 单词长度的最大乘积
bool maxProduct_cmp(string a, string b) {
	return a.length() > b.length();
}
bool maxProduct_sameWord(string a, string b) {
	for (int i = 0; i < a.length(); i++)
	{
		if (b.find(a[i]) != string::npos)return false;
	}
	return true;
}
int maxProduct(vector<string>& words) {
	sort(words.begin(), words.end(), maxProduct_cmp);
	int max = 0;
	for (int i = 0; i < words.size(); i++)
	{
		string temp = words[i];
		for (int u = i + 1; u < words.size(); u++)
		{
			int mullength = words[u].length() * temp.length();
			if (u == i + 1 && mullength < max)return max;
			if (mullength > max && maxProduct_sameWord(words[u], temp)) {
				max = mullength;
			}
		}
	}
	return max;
}
//剑指 Offer II 006. 排序数组中两个数字之和
vector<int> twoSum(vector<int>& numbers, int target) {
	int i = 0, j = numbers.size() - 1;
	while (i <= j) {
		int sum = numbers[i] + numbers[j];
		if (sum == target) {
			return vector<int>{ i, j };
		}
		else if (sum > target)j--;
		else i++;
	}
	return vector<int>{ i, j };
}
//剑指 Offer II 007. 数组中和为 0 的三个数
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>>temp, ans;
	if (nums.size() < 3)return temp;
	unordered_map<int, int>mmap;
	sort(nums.begin(), nums.end());
	int i, j, k;
	for (i = 0; i < nums.size() - 2; i++)
	{
		if (mmap.find(nums[i]) != mmap.end())continue;
		mmap[nums[i]] = 1;
		j = i + 1, k = nums.size() - 1;
		while (j < k) {
			int sum = nums[i] + nums[j] + nums[k];
			if (sum == 0) {
				temp.push_back(vector<int>{nums[i], nums[j], nums[k]});
				j++;
				k--;
			}
			else if (sum > 0) k--;
			else if (sum < 0)j++;
		}
	}
	int bound = temp.size() - 1;
	for (i = 0; i < bound; i++) {
		bool match = false;
		for (int j = i + 1; j < temp.size(); j++) {
			if (temp[i][0] == temp[j][0] && temp[i][1] == temp[j][1]) {
				match = true;
				break;
			}
		}
		if (!match)ans.push_back(temp[i]);
	}
	if (temp.size() > 1)ans.push_back(temp[temp.size() - 1]);
	return ans;
}
//213. 打家劫舍 II
int doublerob(vector<int>& nums) {
	int len = nums.size(), maxn = 0;
	vector<vector<int>>dp(len, vector<int>(2));
	vector<vector<int>>bp(len, vector<int>(2));
	dp[0][0] = bp[1][0] = 0;
	dp[0][1] = nums[0];
	bp[1][1] = nums[1];
	for (int i = 1; i < len - 1; i++)
	{
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
		dp[i][1] = dp[i - 1][0] + nums[i];
	}
	for (int i = 2; i < len; i++)
	{
		bp[i][0] = max(bp[i - 1][0], bp[i - 1][1]);
		bp[i][1] = bp[i - 1][0] + nums[i];
	}
	return max(max(dp[len - 2][0], dp[len - 2][1]), max(bp[len - 1][0], bp[len - 1][1]));
}
//55. 跳跃游戏
bool canJump(vector<int>& nums) {
	int maxlen = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if (i > maxlen)return false;
		maxlen = max(maxlen, i + nums[i]);
	}
	return true;
}
//79. 单词搜索
bool exist_word_dfs(vector<vector<char>>& board, string s, vector<vector<int>>& visit, int x, int y, int index) {
	if (board[x][y] != s[index]) {
		return false;
	}
	else if (index == s.length() - 1) {
		return true;
	}
	visit[x][y] = true;
	int width = board[0].size(), height = board.size();
	bool result = false;
	vector<pair<int, int>>directions = { {0,1},{0,-1},{1,0},{-1,0} };
	for (const auto& dir : directions)
	{
		int newi = x + dir.first, newj = y + dir.second;
		if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
			if (!visit[newi][newj]) {
				bool flag = exist_word_dfs(board, s, visit, newi, newj, index + 1);
				if (flag) {
					result = true;
					break;
				}
			}
		}
	}
	visit[x][y] = false;
	return result;
}
bool exist(vector<vector<char>>& board, string word) {
	int h = board.size(), w = board[0].size();
	vector<vector<int>> visit(h, vector<int>(w));
	for (int i = 0; i < h; i++)
	{
		for (int u = 0; u < w; u++) {
			bool flag = exist_word_dfs(board, word, visit, i, u, 0);
			if (flag) {
				return true;
			}
		}
	}
	return false;
}
//22. Generate Parentheses
void generateParenthesis_help(vector<string>& temp, string s, int left, int right) {
	if (left == 0 && right == 0) {
		temp.push_back(s);
		return;
	}
	if (left > 0) {
		generateParenthesis_help(temp, s + "(", left - 1, right);
	}
	if (left < right) {
		generateParenthesis_help(temp, s + ")", left, right - 1);
	}
}
vector<string> generateParenthesis(int n) {
	vector<string>ans;
	generateParenthesis_help(ans, "", n, n);
	return ans;
}
//17. 电话号码的字母组合
void letterCombinations_help(vector<string>& ans, unordered_map<int, vector<char>>phone, string digits, string temp, int index) {
	if (index == digits.size()) {
		ans.push_back(temp);
		return;
	}
	vector<char> ch = phone[digits[index] - '0'];
	for (int i = 0; i < ch.size(); i++) {
		temp.push_back(ch[i]);
		letterCombinations_help(ans, phone, digits, temp, index + 1);
		temp.pop_back();
	}
}
vector<string> letterCombinations(string digits) {
	vector<string>ans;
	unordered_map<int, vector<char>>phone;
	phone[2] = { 'a','b','c' };
	phone[3] = { 'd','e','f' };
	phone[4] = { 'g','h','i' };
	phone[5] = { 'j','k','l' };
	phone[6] = { 'm','n','o' };
	phone[7] = { 'p','q','r','s' };
	phone[8] = { 't','u','v' };
	phone[9] = { 'w','x','y','z' };
	letterCombinations_help(ans, phone, digits, "", 0);
	return ans;
}
//34. 在排序数组中查找元素的第一个和最后一个位置
vector<int> searchRange(vector<int>& nums, int target) {
	vector<int>ans = { -1,-1 };
	if (nums.size() == 0 || (nums.size() == 1 && nums[0] != target)) {
		return ans;
	}
	int i = 0, j = nums.size() - 1, index = -1, left, right;
	while (i < j) {
		int mid = (i + j) / 2;
		if (nums[mid] == target) {
			index = mid;
			break;
		}
		else if (nums[mid] > target) {
			j = mid;
		}
		else {
			i = mid + 1;
		}
	}
	if (index == -1) {
		return ans;
	}
	else {
		ans.clear();
		left = right = index;
		while (left >= 0 && nums[left] == target)left--;
		while (right < nums.size() && nums[right] == target)right++;
		ans = { left + 1,right - 1 };
		return ans;
	}
}

int main() {
	//vector<int>list = { 1,2,3 };
	//ListNode* head = new ListNode();
	//head->val = list[0];
	//ListNode* ptr = head;
	//for (int i = 1; i < list.size(); i++) {
	//	ListNode* Nnode = new ListNode(list[i]);
	//	ptr->next = Nnode;
	//	ptr = Nnode;
	//}

	//vector<vector<char>>board = { {'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'} };
	vector<vector<char>>board = { {'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','B'},{'A','A','A','A','B','A'} };
	//vector<vector<int>>routes = { {0,1,6,16,22,23},{14,15,24,32},{4,10,12,20,24,28,33},{1,10,11,19,27,33},{11,23,25,28},{15,20,21,23,29},{29} };
	vector<int>nums = { 5,7,7,8,8,10 };
	vector<int>house = { 186,419,83,408 };
	searchRange(nums, 6);
	return 0;
}