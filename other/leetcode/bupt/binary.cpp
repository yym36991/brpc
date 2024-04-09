// #include <iostream>
// #include <vector>
// using namespace std;

// vector<int> result(int num) {
//     vector<int>vec;
//     while(num > 1) {
//         int now = num % 2;
//         vec.push_back(now);
//         num /= 2;
//     }
//     vec.push_back(1);
//     return vec;
// }

// int main() {
//     int a, b;
//     while (cin >> a) { // 注意 while 处理多个 case
//         vector<int> res;
//         res = result(a);
//         for(int i = res.size()-1; i >=0 ; i--) {
//             cout << res[i];
//         }
//         cout << endl;
//     }
//     return 0;
// }



// #include <iostream>
// #include <vector>
// #include <queue>

// using namespace std;

// int hufm (vector<int>& num) {
//     priority_queue<int, vector<int>, greater<int>> pq(num.begin(), num.end());
//     int result = 0;
//     while (pq.size() > 1) {
//         int a = pq.top();
//         pq.pop();
//         int b = pq.top();
//         pq.pop();
//         pq.push(a + b);
//         result += a + b;
//     }
//     return result;
// }

// int main() {
//     int n;
//     while(cin >> n ) {
//         vector<int> nums(n);
//         int result = 0;
//         for(int i = 0; i < n; i++) {
//             cin >> nums[i];
//         }
//         result = hufm(nums);
//         cout << result << endl;
//     }
//     return 0;
// }


/*
树中所有叶子节点的权值乘以其到根节点的路径长度之和，为什么和构成的哈夫曼树所有节点相加的和相等？

在哈夫曼树中，树的带权路径长度（WPL）定义为所有叶子节点的权值乘以其到根节点的路径长度之和。这个定义保证了哈夫曼树是一棵带权路径长度最短的树，也就是说，哈夫曼树的WPL是最小的。
为什么哈夫曼树的所有节点相加的和等于叶子节点的权值乘以其到根节点的路径长度之和呢？这是因为在构建哈夫曼树的过程中，每次合并两个节点（可以是内部节点或叶子节点），新生成的节点的权值是前两个节点的权值之和。因此，在整个构建过程中，每个节点的权值都会被计算到叶子节点的路径长度中，并且每个节点的权值都会在路径长度中被累加多次（等于它参与合并的次数）。
由于哈夫曼树是通过不断合并节点构建而成的，每个节点的权值都参与了多次合并操作，所以最终所有节点相加的和等于叶子节点的权值乘以其到根节点的路径长度之和。这保证了哈夫曼树在结构上的一致性和有效性。


在机试中最常考察优先队列的应用便是哈夫曼树(Huffman Tree)。在一颗树中，从任意一个结点到达另一个结点的通路被称为路径，该路径上所需经过的边的个数被称为该路径的长度。如果树中结点带有表示某种意义的权值，那么从根结点到达该结点的带权路径长度再乘以该结点的权值就被称为该结点的带权路径长度。树中所有叶子结点的带权路径长度之和为该树的带权路径长度之和。给定n个带有权值的结点，以它们为叶子结点构造一颗带权路径长度和最小的二叉树，该二叉树即为哈夫曼树，同时也称为最优树。

由于n个带有权值的结点构成的哈夫曼树可能不唯一，所以关于哈夫曼树的机试题往往考察的是求解最小带权路径长度和。哈夫曼树的求法：

1、将所有结点放入集合K

2、若集合K中的剩余结点数大于1，则取出权值最小的两个结点，将它们两个构造成某个新结点的左右子结点，设这个新结点的权值为其两个子结点的权值和，并将该新结点放入集合K。

3、若集合K中仅剩余一个结点，则该结点即为构造出的哈夫曼树的根结点。构造过程中，所有中间结点的权值和，即为该哈夫曼树的带权路径和。


*/






















/*
描述
查找一个数组的第K小的数，注意同样大小算一样大。 如  2 1 3 4 5 2 第三小数为3。
输入描述：
输入有多组数据。 每组输入n，然后输入n个整数(1<=n<=1000)，再输入k。
输出描述：
输出第k小的整数。
示例1
输入：
6
2 1 3 5 2 2
3
复制
输出：
3



#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    while(cin >> n) {
        set<int>sint;
        for(int i = 0; i < n; i++) {
            
            int tem ;
            cin >> tem;
            sint.insert(tem);
        }
        int k;
        cin >> k;
        int i = 1;
        int result = 0;
        for(auto it = sint.begin(); it != sint.end(); it++) {
            if(k == i) {
                result = *it;
                break;
            }
            i++;
            
        }
        cout << result << endl;

    }
}



描述
给定一个n*n的矩阵，求该矩阵的k次幂，即P^k。
输入描述：
第一行：两个整数n（2<=n<=10）、k（1<=k<=5），两个数字之间用一个空格隔开，含义如上所示。 接下来有n行，每行n个正整数，其中，第i行第j个整数表示矩阵中第i行第j列的矩阵元素Pij且（0<=Pij<=10）。另外，数据保证最后结果不会超过10^8。
输出描述：
对于每组测试数据，输出其结果。格式为： n行n列个整数，每行数之间用空格隔开，注意，每行最后一个数后面不应该有多余的空格。
示例1
2 2
9 8
9 3
3 3
4 8 4
9 3 0
3 5 7
5 2
4 0 3 0 1
0 0 5 8 5
8 9 8 5 3
9 6 1 7 8
7 2 5 7 3


153 96
108 81
1216 1248 708
1089 927 504
1161 1151 739
47 29 41 22 16
147 103 73 116 94
162 108 153 168 126
163 67 112 158 122
152 93 93 111 97



#include <iostream>
#include <vector>

using namespace std;

// 矩阵乘法函数
vector<vector<int>> matrix_multiply(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2) {
    int n = matrix1.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

int main() {
    int n, k;
    while(cin >> n >> k) {
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matrix[i][j];
            }
        }

        vector<vector<int>> result = matrix;
        for (int i = 1; i < k; i++) {
            result = matrix_multiply(result, matrix);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << result[i][j];
                if (j != n - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}


描述
牌只有1到9，手里拿着已经排好序的牌a，对方出牌b，用程序判断手中牌是否能够压过对方出牌。  规则：出牌牌型有5种   [1]一张 如4 则5...9可压过 [2]两张 如44 则55，66，77，...，99可压过 [3]三张 如444 规则如[2] [4]四张 如4444 规则如[2] [5]五张 牌型只有12345 23456 34567 45678 56789五个，后面的比前面的均大。
输入描述：
输入有多组数据。 每组输入两个字符串(字符串大小不超过100)a，b。a字符串代表手中牌，b字符串代表出的牌。
输出描述：
压过输出YES 否则NO。
示例1
输入：
12233445566677
33
复制
输出：
YES

122344555677778
12345
YES






#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string str1;
    string str2;
    while(cin >> str1 >> str2) {
        int num = str2.size();
        int str2_num = stoi(str2);
        string res = "NO";
        bool flag = false;

        for (int i = 0; i < str1.size() - num + 1; i++) {
            string str_tem = str1.substr(i, num);
            if (num < 5) {
                char c0 = str_tem.front();
                for(auto s : str_tem) {
                    if (s != c0){
                        flag = true;
                        break;
                    }
                    flag = false;  // 重置
                }
                if(flag) {
                    continue;
                }
                int str_tem_num = stoi(str_tem);
                if (str_tem_num > str2_num) {
                    res = "YES";
                    break;
                }
            } else {
                char c0 = str2.front();
                int res_num = 0;
                bool flag_5 = false;
                for (int j = 0; j < str1.size(); j++) {
                    if (c0 > str1[j]) {
                        continue;
                    }
                    res_num = 1;
                    char t0 = str1[j];
                    for (int k = j + 1; k < str1.size(); k++) {
                        if (str1[k] - t0 == 1) {
                            res_num++;
                            t0 = str1[k];
                            if (res_num >= 5) {
                                flag_5 = true;
                                break;
                            }
                        }
                    }
                    i = i + res_num; // 加速
                    if (flag_5) {
                        res = "YES";
                        break;
                    }
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

描述
有一棵树，输出某一深度的所有节点，有则输出这些节点，无则输出EMPTY。该树是完全二叉树。
输入描述：
输入有多组数据。 每组输入一个n(1<=n<=1000)，然后将树中的这n个节点依次输入，再输入一个d代表深度。
输出描述：
输出该树中第d层得所有节点，节点间用空格隔开，最后一个节点后没有空格。
示例1
输入：
4
1 2 3 4
2
复制
输出：
2 3







#include <iostream>
#include <vector>
#include <string>

using namespace std;

int layer(int n) {
    int res = 1;
    if (n >= 2 && n <=3) {
        res = 2;
    } else if (n >= 4 && n <= 7) {
        res = 3;
    } else if (n >= 8 && n <= 15) {
        res = 4;
    }  else if (n >= 16 && n <= 31) {
        res = 5;
    } else if (n >= 32 && n <= 63) {
        res = 6;
    } else if (n >= 64 && n <= 127) {
        res = 7;
    } else if (n >= 128 && n <= 255) {
        res = 8;
    } else if (n >= 256 && n <= 511) {
        res = 9;
    } else if (n >= 512 && n <= 1023) {
        res = 10;
    }
    return res;
}

int qrt(int x, int n) {
    int res = 1;
    for(int i = 0; i < n; i++) {
        res *= x;
    }
    return res;
}

int main() {
    int n;
    while(cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }
        int d;
        cin >> d;
        int hight = layer(nums.size());
        if (d > hight) {
            cout << "EMPTY" << endl;
            continue;
        }else if (d == hight) {
            int idx = qrt(2, d -1) - 1;
            for (int i = idx; i < nums.size(); i++) {
                cout << nums[i];
                if(i != nums.size() -1) {
                    cout << " ";
                }
            }
            cout << endl;
        } else {
            int first = qrt(2, d -1) - 1;
            int end = qrt(2, d) - 2;
            for(int i = first; i <= end; i++) {
                cout << nums[i];
                if (i != nums[end]) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}

描述
    读入一组字符串（待操作的），再读入一个int n记录记下来有几条命令，总共有2中命令：1、翻转  从下标为i的字符开始到i+len-1之间的字符串倒序；2、替换  命中如果第一位为1，用命令的第四位开始到最后的字符串替换原读入的字符串下标 i 到 i+len-1的字符串。每次执行一条命令后新的字符串代替旧的字符串（即下一条命令在作用在得到的新字符串上）。     命令格式：第一位0代表翻转，1代表替换；第二位代表待操作的字符串的起始下标int i；第三位表示需要操作的字符串长度int len。
输入描述：
输入有多组数据。 每组输入一个字符串（不大于100）然后输入n，再输入n条指令（指令一定有效）。
输出描述：
根据指令对字符串操作后输出结果。
示例1
输入：
bac
2
003
112as
复制
输出：
cab
cas

描述
输入数组长度 n 输入数组      a[1...n] 输入查找个数m 输入查找数字b[1...m]   输出 YES or NO  查找有则YES 否则NO 。
输入描述：
输入有多组数据。 每组输入n，然后输入n个整数，再输入m，然后再输入m个整数（1<=m,n<=100）。
输出描述：
如果在n个数组中输出YES否则输出NO。
示例1
输入：
5
1 5 2 4 3
3
2 5 6
复制
输出：
YES
YES
NO


#include <iostream>
#include <set>
using namespace std;

int main() {
    int a, b;
    while(cin >> a) {
        set<int> sa;
        for (int i = 0; i < a; i++) {
            int tem;
            cin >> tem;
            sa.insert(tem);
        }
        cin >> b;
        while (b--) {
            int tb;
            cin >> tb;
            if (sa.find(tb) != sa.end()) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}

描述
第一行输入一个数n，1 <= n <= 1000，下面输入n行数据，每一行有两个数，分别是x y。输出一组x y，该组数据是所有数据中x最小，且在x相等的情况下y最小的。 
输入描述：
输入有多组数据。 每组输入n，然后输入n个整数对。
输出描述：
输出最小的整数对。
示例1
输入：
5  
3 3  
2 2  
5 5  
2 1  
3 6
复制
输出：
2 1

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> nums (n, vector<int>(2, 0));
        for (int i = 0; i < n; i++) {
            cin >> nums[i][0] >> nums[i][1];
        }
        sort(nums.begin(), nums.end());
        cout << nums[0][0] << " " << nums[0][1] << endl;
    }
    return 0;
}

描述
输入一系列整数，建立二叉排序树，并进行前序，中序，后序遍历。
输入描述：
输入第一行包括一个整数n(1<=n<=100)。 接下来的一行包括n个整数。
输出描述：
可能有多组测试数据，对于每组数据，将题目所给数据建立一个二叉排序树，并对二叉排序树进行前序、中序和后序遍历。 每种遍历结果输出一行。每行最后一个数据之后有一个换行。 输入中可能有重复元素，但是输出的二叉树遍历序列中重复元素不用输出。
示例1
输入：
5
1 6 5 9 8
复制
输出：
1 6 5 9 8 
1 5 6 8 9 
5 8 9 6 1 


*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():val(0), left(nullptr), right(nullptr){}
    TreeNode(int v): val(v), left(nullptr), right(nullptr){}
    TreeNode(int v, TreeNode* l, TreeNode* r):val(v), left(l), right(r){}
};

TreeNode* InsertNode(TreeNode* node, int val) {
    if (!node) {
        return new TreeNode(val);
    }
    if (node->val < val) {
        node->right = InsertNode(node->right, val);
    } else {
        node->left = InsertNode(node->left, val);
    }
    return node;
}

class result {
 public:
  void 
};












