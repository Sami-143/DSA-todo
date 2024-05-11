// <-------Lab 2------->
// Task No1 (Balanced Paranthesis)

class Solution {
public:
    bool isValid(string s) {
        int n = s.size();

        stack <char> st;
        bool flag = true;

        for(int idx = 0;idx < n ; idx++)
        {
            if(s[idx] == '(' or s[idx] == '{' or s[idx] == '[')
            {
                st.push(s[idx]);
            }
            else if(s[idx] == ')')
            {
                if(!st.empty() and st.top() == '(')
                {
                  st.pop();
                }
                else
                {
                  flag = false;
                  break;
                }
            }
            else if(s[idx] == ']')
            {
                if(!st.empty() and st.top() == '[')
                {
                  st.pop();
                }
                else
                {
                  flag = false;
                  break;
                }
            }
            else if(s[idx] == '}')
            {
                if(!st.empty() and st.top() == '{')
                {
                  st.pop();
                }
                else
                {
                  flag = false;
                  break;
                }
            }
        }

        if(!st.empty())
        {
          return false;
        }
        return true;
    }
};

// <----Task 2---->(Get min Stack value)
// Solved:


class MinStack 
{
    int min_stack;
    stack<int> st;
public:
    MinStack() 
    {
      min_stack = INT_MAX;
    }
    
    void push(int val) 
    {
      if (val <= min_stack)
      {
        st.push(min_stack);
        min_stack = val;
      }
        st.push(val);
    }
    
    void pop() 
    {
      if(!st.empty() and st.top() == min_stack)
      {
        st.pop();
        min_stack = st.top();
        st.pop();
      }
      else{
        st.pop();
      }
      
    }
    
    int top() {
      return st.top();
    }
    
    int getMin() 
    {
        return min_stack;
    }
};


// <----Task 3---->(Trap Water)
// Solved:
class Solution {
public:
    
int trap(vector<int>& height) {
    int n = height.size(); 
    int leftMax = height[0]; 
    int rightMax = height[n - 1]; 
    int leftPointer = 1; 
    int rightPointer = n - 2;
    int trappedWater = 0;
    while (leftPointer <= rightPointer) {
        if (height[leftPointer] >= leftMax) {
            
            leftMax = height[leftPointer];
            leftPointer++;
        } else if (height[rightPointer] >= rightMax) {
            
            rightMax = height[rightPointer];
            rightPointer--;
        } else {
            int shorterMax = min(leftMax, rightMax);
            trappedWater += shorterMax - height[leftPointer];
            leftPointer++; 
        }

    }
    return trappedWater;
}

};

// <----Task 4---->(Trap Water)
// Solved:

stack<int> nums;
stack<string> values;
string result = "";
int number = 0;
for (char c : s) {
    if (isdigit(c))
        number = number * 10 + (c - '0');
    else if (c == '[') {
        values.push(result);
        nums.push(number);
        result = "";
        number = 0;
    }
    else if (c == ']') {
        int times = nums.top();
        nums.pop();
        string prevStr = values.top();
        values.pop();
        for (int i = 0; i < times; i++) {
            prevStr += result;
        }
        result = prevStr;
    }
    else
        result += c;
}
return result;

// <----Task 5---->(Get min Stack value)
// Solved:
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int max_water =0;
        while (left < right) {
        // Calculate the width between the two lines.
        int width = right - left;
        // Calculate the minimum height of the two lines.
        int minHeight = min(height[left], height[right]);
        int water = width * minHeight;

        // Update the maximum water if the current water is greater.
        max_water = max(max_water, water);

        // Move the pointers towards each other.
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return max_water;
    }
};


// <----Task 7---->
// Solved:

class MyStack {
    int N;
    queue<int> q1;
    queue<int> q2;

public:
    MyStack() {
        N = 0;
    }

    void push(int x) {
        q2.push(x);
        N++;
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    int pop() {
        if (empty()) {
            return -1; 
        }
        int topElement = q1.front();
        q1.pop();
        N--;
        return topElement;
    }

    int top() {
        return q1.front();
    }

    bool empty() {
        return N == 0;
    }
};


class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        int circount=(students.begin(),students.end(),0);
        int sqcount=(students.begin(),students.end(),1);
        while(!students.empty())
        {
            if(students[0]==sandwiches[0])
            {
                students.erase(students.begin());
                sandwiches.erase(sandwiches.begin());
                if(students[0]==0)
                {
                    circount-=1;
                }
                else
                {
                    sqcount-=1;
                }
            }
            else
            {
                students.push_back(students[0]);
                students.erase(students.begin());
            }
            if ((students[0] == 0 && circount == 0) || (students[0] == 1 && sqcount == 0)) {
                break;
            }
        }
        return students.size();
    }
};

// <----Task 8---->
// Solved:

class FrontMiddleBackQueue {
public:
     vector<int> q;
     int fi;
     int ri;
    FrontMiddleBackQueue() {
        
    }
    
    void pushFront(int val) {
          int index=0;
          q.insert(q.begin()+index,val);   
          ri+=1;
    }
    
    void pushMiddle(int val) {
        int index=(fi+ri)/2;
        q.insert(q.begin()+index,val);  
        ri+=1;
    }
    
    void pushBack(int val) {
        ri+=1;
        q[ri]=val;
    }
    
    int popFront() {
         if(q.empty())
        {
            return -1;
        }
        else
        {
           int ans = q[0];
           q.erase(q.begin()+0);
           ri-=1;
           return ans;
        }
    }
    
    int popMiddle() {
        if(q.empty())
        {
            return -1;
        }
        else
        {
         int index=(fi+ri)/2;
         int ans = q[(fi+ri)/2];
         q.erase(q.begin()+index);
         ri-=1;
         return ans;
        }
    }
    
    int popBack() 
    {
         if(q.empty())
        {
            return -1;
        }
        else
        {
          int ans = q[ri];
          q.erase(q.begin()+ri);
          ri-=1;
          return ans;
        }
    }
}:

// <----Task 9---->
// Solved:

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) 
    {
        int j=2000000;
          int maxsum=0;
          for(int i=0; i<nums.size()-1; i++)
          {
              int k= max(nums[i],nums[(i+1)%nums.size()]);
              if(k<0)
              {
                 maxsum=k;
              }
              else if(k+maxsum>maxsum)
              {
                  if(j!=nums[i])
                  {
                    maxsum=maxsum+k;
                  }
                   j=k;
              }
          }
          return maxsum;
    }
};

// <----Task 10---->
// Solved:

class Solution {
public:
vector<int> a;
    vector<int> asteroidCollision(vector<int>& asteroids) {
         for(int i =0; i<asteroids.size()-1 ; i++)
         {
             if(asteroids[i]==asteroids[i+1] && asteroids[i]<0 ||asteroids[i+1]<0)
             {
                  asteroids.erase(asteroids.begin()+i);
                  asteroids.erase(asteroids.begin()+(i+1));
             }
             else if(asteroids[i]<0 && asteroids[i+1]>0)
             {
                 a.push_back(asteroids[i + 1]);
             }
             else if(asteroids[i+1]<0 && asteroids[i]>0)
             {
                 a.push_back(asteroids[i]);
             }
             else if(asteroids[i]>0 && asteroids[i+1]>0 || asteroids[i]<0 && asteroids[i+1]<0 )
             {
               a.push_back(asteroids[i]);
               a.push_back(asteroids[i+1]);
             }
         }
         return a;
    }
};