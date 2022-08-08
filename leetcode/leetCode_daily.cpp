#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include <unordered_map>
using namespace std;
//202. ������
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
//54. ��������
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
//1706. �����δ�
vector<int> findBall(vector<vector<int>>& grid) {
	vector<int>ball_road(grid[0].size());
	for (int i = 0; i < grid[0].size(); i++) {
		bool runout = true;
		int level = 0, location = i;
		while (runout && level < grid.size()) {
			//�����Ҳ�
			if (grid[level][location] == 1) {
				//�Ҳ��е���
				if (location < grid[level].size() - 1 && grid[level][location + 1] == 1) {
					level++;
					location++;
					continue;
				}//ײǽ ���巴��
				else {
					runout = false;
					break;
				}
			}//�������
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
//14. �����ǰ׺
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
//43. �ַ������
string multiply(string num1, string num2) {
	string result = "";
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());
	for (int i = 0; i < num1.size(); i++) {
		string localtemp = "";
		int ch = num1[i] - '0';
		//��0
		for (int j = 0; j < i; j++) {
			localtemp += "0";
		}
		//���
		int flag = 0;
		for (int i = 0; i < num2.size(); i++) {
			int number = ch * (num2[i] - '0') + flag;
			localtemp += to_string(number % 10);
			flag = number / 10;
		}
		if (flag != 0)localtemp += to_string(flag);
		//�������
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
//19. ɾ������ĵ����� N �����
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
//234. ��������
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
//621. ���������
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
		}//�ҵ�����һ��������cpu����
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
//226��ת������
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
// 110.�ж��Ƿ���ƽ�������
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
//543. ��������ֱ��
int diameterOfBinaryTree(TreeNode* root) {
	if (root == nullptr)return 0;
	else {
		int diameter = treeHeight(root->left) + treeHeight(root->right);
		int subDiameter = max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right));
		return max(diameter, subDiameter);
	}
}


int main() {
	/*vector<int>list = { 1,2,3,4,5 };
	ListNode* head = new ListNode();
	head->val = list[0];
	ListNode* ptr = head;
	for (int i = 1; i < list.size(); i++) {
		ListNode* Nnode = new ListNode(list[i]);
		ptr->next = Nnode;
		ptr = Nnode;
	}*/
	vector<string> words = { "dd","aa","bb" };
	vector<char>tasks = { 'A','A','A','A','A','A','B','C','D','E','F','G' };
	//vector<char>tasks = { 'A','A','A','B','B','B' };
	leastInterval(tasks, 2);
	return 0;
}