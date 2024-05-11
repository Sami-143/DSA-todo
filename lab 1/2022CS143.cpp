// Leet code task 1
// ---------------->>>>>>>
class Solution
{
    public:
        vector<int> smallerNumbersThanCurrent(vector<int> & nums){
            vector<int> out;
            for(int idx = 0;idx<nums.size();idx++)
            {
                int counter = 0;
                for(int idx1 = 0;idx1<nums.size();idx1++)
                {
                    if(nums[idx] > nums[idx1])
                    {
                        counter++;
                    }
                }
                out.push_back(counter);
            }
            return out;
        }
};

// Leet Code task 2
// ---------------->>>>>>>
class Solution
{
    public:
        int removeElements(vector<int> &nums,int val)
        {
            int counter = 0;
            int k = 0;
            for(int i=1;i<nums.size();)
            {
                if(nums[i]== val)
                {
                    nums.erase(nums.begin + i);
                }
                else
                {
                    counter ++;
                }
            }
            k = nums.size();
            return k;

        }

};



// Leet Code Task 3
// ---------------->>>>>>>
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for(int i = 0; i < 3 ; i++){
            for(int j = 0; j<4;j++){
                if(target == matrix[i][j]){
                    return true;
                }
            }
        }
        return false;
    }
};


//LeetCode Task No 4
// ---------------->>>>>>>
class Solution
{
  public:
        int removeDuplicates(vector<int> &nums)
        {
            int j =1;
            for(int i=1;i<nums.size();i++)
            {
                if(nums[i] != nums[i-1])
                {
                    nums[j] = nums[i];
                    j++;
                }
            }
            return j;
        } 
};


//LeetCode Task No 5
// ---------------->>>>>>>

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int current_sum = nums[0];
        int max_sum = nums[0];
        for(int i = 1; i<nums.size();i++){
            current_sum = max(nums[i],current_sum + nums[i]);
            max_sum = max(current_sum,max_sum);     
        }
        return max_sum;
    }
};

//LeetCode Task No 6
// ---------------->>>>>>>
class Solution {
public:
    int firstBadVersion(int n) {
        int right = n;
        int left = 1;
        while(left<right){
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)){
                right = mid;
            }
            else{
                left = mid + 1;
            }   
        }
        return left;
    }
};


//LeetCode Task No 7
// ---------------->>>>>>>
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) 
    {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};