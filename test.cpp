#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        int n = nums.size();
        while(n != 1){
            
            for(int i=0; i<n; i++){
                if(i%2){//奇
                    nums[i] = max(nums[2*i], nums[2*i+1]);
                }
                else{
                    nums[i] = min(nums[2*i], nums[2*i+1]);
                }
            }
            n/=2;
        }
        return nums[0];
    }
};

int main(){
    
    int n = nums.size();
        while(n != 1){
            
            for(int i=0; i<n; i++){
                if(i%2){//奇
                    nums[i] = max(nums[2*i], nums[2*i+1]);
                }
                else{
                    nums[i] = min(nums[2*i], nums[2*i+1]);
                }
            }
            n/=2;
        }
        return nums[0]; 
    return 0;
}