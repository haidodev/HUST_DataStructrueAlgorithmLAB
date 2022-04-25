#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i + 1;
    do {
        for (int i = 0; i < n; ++i){
            cout << arr[i] << " ";
        }
        //for (int elm : arr) cout << elm << " ";
        cout << endl;
    } while (next_permutation(arr.begin(), arr.end()));
}