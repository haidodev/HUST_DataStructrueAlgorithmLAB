#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
    string bigNumAddition(string &num1, string &num2){
        int prev = 0;
        string res = "";
        for (int i = num1.size() - 1, j = num2.size() - 1; i >= 0 || j >= 0; --i, --j){
            int cur = prev;
            if (i >= 0) cur += num1[i] - '0';
            if (j >= 0) cur += num2[j] - '0';
            res += ('0' + cur % 10);
            prev = cur / 10;
        }
        if (prev) res += ('0' + prev);
        reverse(begin(res), end(res));
        return res;
    }
    bool isAdditiveNumber(string num, int curIdx = 0, string prev1 = "", string prev2 = "", int sqnLen = 0) {
        cout << prev1 << "+" << prev2 << endl;
        if (curIdx == num.size()) return sqnLen > 2;
        if (!(prev1.empty() || prev2.empty())){
            string curNum = bigNumAddition(prev1, prev2);
            for (int i = 0; i < curNum.size(); ++i){
                if (curIdx + i >= num.size()) return false;
                if (curNum[i] != num[curIdx + i]) return false;
            }
            return isAdditiveNumber(num, curIdx + curNum.size(), prev2, curNum, sqnLen + 1);
        }
        if (num[curIdx] == '0') return isAdditiveNumber(num, curIdx + 1, prev2, "0", sqnLen + 1);
        string curNum = "";
        for (int i = 0; i + curIdx < num.size(); ++i){
            curNum += num[i + curIdx];
            if (isAdditiveNumber(num, i + curIdx + 1, prev2, curNum, sqnLen + 1)) return true;
        }
        return false;
    }
    int main(){
        string num = "01";
        if (isAdditiveNumber(num)) cout << "Yes";
        else cout << "No";
    }