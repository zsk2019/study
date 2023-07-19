# 6. 场景题/算法题
#### （0） leetcode hot100至少刷两遍，剑指offer至少刷两遍 重中之重！！
面试中90%的算法题都从leetcode hot100和剑指offer中出 刷两遍非常有必要
#### （1） 介绍熟悉的设计模式（单例，简单工厂模式）
#### （2） 写单例模式，线程安全版本
```C++ version
class Singleton{
  private:
    static Singleton* instance;
    Singleton(){
      // initialize
    }
  public:
    static Singleton* getInstance(){
      if(instance==nullptr) instance=new Singleton();
      return instance;
    }
};
```
#### （3） 写三个线程交替打印ABC
```C++
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex mymutex;
condition_variable cv;
int flag=0;

void printa(){
    unique_lock<mutex> lk(mymutex);
    int count=0;
    while(count<10){
        while(flag!=0) cv.wait(lk);
        cout<<"thread 1: a"<<endl;
        flag=1;
        cv.notify_all();
        count++;
    }
    cout<<"my thread 1 finish"<<endl;
}
void printb(){
    unique_lock<mutex> lk(mymutex);
    for(int i=0;i<10;i++){
        while(flag!=1) cv.wait(lk);
        cout<<"thread 2: b"<<endl;
        flag=2;
        cv.notify_all();
    }
    cout<<"my thread 2 finish"<<endl;
}
void printc(){
    unique_lock<mutex> lk(mymutex);
    for(int i=0;i<10;i++){
        while(flag!=2) cv.wait(lk);
        cout<<"thread 3: c"<<endl;
        flag=0;
        cv.notify_all();
    }
    cout<<"my thread 3 finish"<<endl;
}
int main(){
    thread th2(printa);
    thread th1(printb);
    thread th3(printc);

    th1.join();
    th2.join();
    th3.join();
    cout<<" main thread "<<endl;


}
```
#### （4） 二维码登录的实现过程 场景题
![](fig/二维码登录流程.png)
#### （5） 不使用临时变量实现swap函数
* 使用异或/加减等方式，下面给出使用异或的实现方法
```C++
void swap(int& a,int& b){
  a=a^b;
  b=a^b;
  a=a^b;
}
```
#### （6） 实现一个strcpy函数（或者memcpy），如果内存可能重叠呢
#### （7） 实现快排
```C++
void swap(vector<int>& vec,int a,int b){
    vec[a]=vec[a]^vec[b];
    vec[b]=vec[a]^vec[b];
    vec[a]=vec[a]^vec[b];
}
int partition(vector<int>& vec,int start,int end){
    int pivot=vec[start+(end-start)/2];
    while(start<end){
        while(start<end and vec[start]<pivot) start++;
        while(start<end and vec[end]>pivot) end--;
        if(start<end) swap(vec,start,end);
    }
    return start;
}
void quickSort(vector<int>& vec,int start,int end){
    if(start>end) return;
    int pivot=partition(vec,start,end);
    quickSort(vec,start,pivot-1);
    quickSort(vec,pivot+1,end);
}
```
#### （8） 实现一个堆排序
堆排序的基本过程：
* 将n个元素的序列构建一个大顶堆或小顶堆
* 将堆顶的元素放到序列末尾
* 将前n-1个元素重新构建大顶堆或小顶堆，重复这个过程，直到所有元素都已经排序

整体时间复杂度为nlogn
```C++
#include<iostream>
#include<vector>
using namespace std;
void swap(vector<int>& arr, int a,int b){
    arr[a]=arr[a]^arr[b];
    arr[b]=arr[a]^arr[b];
    arr[a]=arr[a]^arr[b];
}
void adjust(vector<int>& arr,int len,int index){
    int maxid=index;
    // 计算左右子节点的下标   left=2*i+1  right=2*i+2  parent=(i-1)/2
    int left=2*index+1,right=2*index+2;

    // 寻找当前以index为根的子树中最大/最小的元素的下标
    if(left<len and arr[left]<arr[maxid]) maxid=left;
    if(right<len and arr[right]<arr[maxid]) maxid=right;

    // 进行交换，记得要递归进行adjust,传入的index是maxid
    if(maxid!=index){
        swap(arr,maxid,index);
        adjust(arr,len,maxid);
    }
}
void heapsort(vector<int>&arr,int len){
    // 初次构建堆，i要从最后一个非叶子节点开始，所以是(len-1-1)/2，0这个位置要加等号
    for(int i=(len-1-1)/2;i>=0;i--){
        adjust(arr,len,i);
    }

    // 从最后一个元素的下标开始往前遍历，每次将堆顶元素交换至当前位置，并且缩小长度（i为长度），从0处开始adjust
    for(int i=len-1;i>0;i--){
        swap(arr,0,i);
        adjust(arr,i,0);// 注意每次adjust是从根往下调整，所以这里index是0！
    }
}
int main(){
    vector<int> arr={3,4,2,1,5,8,7,6};

    cout<<"before: "<<endl;
    for(int item:arr) cout<<item<<" ";
    cout<<endl;

    heapsort(arr,arr.size());

    cout<<"after: "<<endl;
    for(int item:arr)cout<<item<<" ";
    cout<<endl;

    return 0;
}
```
#### （8） 实现一个插入排序
https://blog.csdn.net/left_la/article/details/8656425

```C++
void insertSort(vector<int>& nums){
  int len=nums.size();
  for(int i=1;i<len;i++){
    int key=nums[i];
    int j=i-1;
    while(j>=0 and nums[j]>key){
      nums[j+1]=nums[j];
      j--;
    }
    nums[j+1]=key;
  }
}
```

#### （9） 快排存在的问题，如何优化
* 3 种快排基准选择方法：

随机（rand函数）、固定（队首、队尾）、三数取中（队首、队中和队尾的中间数）

* 4种优化方式：

优化1：当待排序序列的长度分割到一定大小后，使用插入排序

优化2：在一次分割结束后，可以把与Key相等的元素聚在一起，继续下次分割时，不用再对与key相等元素分割

优化3：优化递归操作

优化4：使用并行或多线程处理子序列
#### （10） 反转一个链表（招银网络二面）
```C++
ListNode* reverse(ListNode* root){
  ListNode* pre=nullptr,cur=root,nxt;
  while(cur!=nullptr){
    nxt=cur->next;
    cur->next=pre;
    pre=cur;cur=nxt;
  }
  return pre;
}
```
#### （11） Top K问题（可以采取的方法有哪些，各自优点？）（重点）
*Top K 问题的常见形式：*
>给定10000个整数，找第K大（第K小）的数<br>
 给定10000个整数，找出最大（最小）的前K个数<br>
给定100000个单词，求前K词频的单词<br>

*解决Top K问题若干种方法*
* 使用最大最小堆。求最大的数用最小堆，求最小的数用最大堆。
* Quick Select算法。使用类似快排的思路，根据pivot划分数组。
* 使用排序方法，排序后再寻找top K元素。
* 使用选择排序的思想，对前K个元素部分排序。
* 将1000.....个数分成m组，每组寻找top K个数，得到m×K个数，在这m×k个数里面找top K个数。

1. 使用最大最小堆的思路 （以top K 最大元素为例）<br>
按顺序扫描这10000个数，先取出K个元素构建一个大小为K的最小堆。每扫描到一个元素，如果这个元素大于堆顶的元素（这个堆最小的一个数），就放入堆中，并删除堆顶的元素，同时整理堆。如果这个元素小于堆顶的元素，就直接pass。最后堆中剩下的元素就是最大的前Top K个元素，最右的叶节点就是Top 第K大的元素。

>note：最小堆的插入时间复杂度为log(n)，n为堆中元素个数，在这里是K。最小堆的初始化时间复杂度是nlog(n)

C++中的最大最小堆要用标准库的priority_queue来实现。
```C++
struct Node {
    int value;
    int idx;
    Node (int v, int i): value(v), idx(i) {}
    friend bool operator < (const struct Node &n1, const struct Node &n2) ;
};

inline bool operator < (const struct Node &n1, const struct Node &n2) {
    return n1.value < n2.value;
}

priority_queue<Node> pq; // 此时pq为最大堆
```

2. 使用Quick Select的思路（以寻找第K大的元素为例）<br>
Quick Select脱胎于快速排序，提出这两个算法的都是同一个人。算法的过程是这样的：
首先选取一个枢轴，然后将数组中小于该枢轴的数放到左边，大于该枢轴的数放到右边。
此时，如果左边的数组中的元素个数大于等于K，则第K大的数肯定在左边数组中，继续对左边数组执行相同操作；
如果左边的数组元素个数等于K-1，则第K大的数就是pivot；
如果左边的数组元素个数小于K，则第K大的数肯定在右边数组中，对右边数组执行相同操作。

这个算法与快排最大的区别是，每次划分后只处理左半边或者右半边，而快排在划分后对左右半边都继续排序。
```
//此为Java实现
public int findKthLargest(int[] nums, int k) {
  return quickSelect(nums, k, 0, nums.length - 1);
}

// quick select to find the kth-largest element
public int quickSelect(int[] arr, int k, int left, int right) {
  if (left == right) return arr[right];
  int index = partition(arr, left, right);
  if (index - left + 1 > k)
    return quickSelect(arr, k, left, index - 1);
  else if (index - left + 1 == k)
    return arr[index];
  else
    return quickSelect(arr, k - (index - left + 1), index + 1, right);

}
```

3. 使用选择排序的思想对前K个元素排序 （ 以寻找前K大个元素为例）<br>
扫描一遍数组，选出最大的一个元素，然后再扫描一遍数组，找出第二大的元素，再扫描一遍数组，找出第三大的元素。。。。。以此类推，找K个元素，时间复杂度为O(N*K)
#### （12） 8G的int型数据，计算机的内存只有2G，怎么对它进行排序？（外部排序）（百度一面）
我们可以使用外部排序来对它进行处理。首先将整个文件分成许多份，比如说m份，划分的依据就是使得每一份的大小都能放到内存里。然后我们用快速排序或者堆排序等方法对每一份数据进行一个内部排序，变成有序子串。接着对这m份有序子串进行m路归并排序。取这m份数据的最小元素，进行排序，输出排序后最小的元素到结果中，同时从该元素所在子串中读入一个元素，直到所有数据都被输出到结果中为止。

https://blog.csdn.net/ailunlee/article/details/84548950

#### （13） 自己构建一棵二叉树，使用带有null标记的前序遍历序列
在写二叉树相关算法的时候，如果需要自己构造测试用例（自己构造一棵二叉树），往往是一件很麻烦的事情，我们可以用一个带有null标记的前序遍历序列来进行构造。 **需要注意的是vec2tree()参数中的start是引用传递，而不是简单的参数值传递**。
```C++
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct treeNode{
    string val;
    treeNode* left,*right;
    treeNode(string val):val(val){
        left=nullptr;
        right=nullptr;
    }
};

treeNode* vec2tree(vector<string>& vec,int& start){
    treeNode* root;
    if(vec[start]=="null"){
        start+=1;
        root=nullptr;
    }else{
        root=new treeNode(vec[start]);
        start+=1;
        root->left=vec2tree(vec,start);
        root->right=vec2tree(vec,start);
    }
    return root;
}

void tree2vec(treeNode *root,vector<string>& vec){
    if(root==nullptr){
        vec.push_back("null");
    }else{
        vec.push_back(root->val);
        tree2vec(root->left,vec);
        tree2vec(root->right,vec);
    }
}

int main(){
    vector<string> vec={"2","4","5","7","null","null","null","null","3","6","null","null","2","null","null"};
    int index=0,&start=index;
    treeNode* root=vec2tree(vec,start);
    //displaytree(root);
    vector<string> mvec;
    tree2vec(root,mvec);
    for(string item:mvec) cout<<item<<" ";
    cout<<endl;
    return 0;
```
#### （14） 介绍一下b树和它的应用场景有哪些
B树也叫做B-树，或者平衡多路树，它是每个节点最多有m个子树的**平衡树**。一个m阶的B树具有如下几个特征：
1. 根结点至少有两个子女。
2. 每个中间节点都包含至多m个子树 ， 每个节点包含的元素个数是其子树个数-1（其中 m/2 <= k <= m）
3. 所有的叶子结点都位于同一层。
4. 每个节点中的元素从小到大排列，节点当中k-1个元素正好是k个子树包含的元素的值域分划。

b树主要应用于文件系统中，在数据库中（mongoDB）也有应用，与B+树相比好处应该是有时不需要访问到叶节点就可以获取数据。

查询时间复杂度是logN
#### （15） 介绍一下b+树和它的应用场景有哪些
B+树是一种特殊的B树，它把数据都存储在叶子节点，并且叶节点间有指针连接。内部只存关键字（其中叶子节点的最小值作为索引）和孩子指针，简化了内部节点。

应用场景主要是数据库的索引

查询时间复杂度也是logN
https://zhuanlan.zhihu.com/p/110202102

https://blog.csdn.net/hguisu/article/details/7786014
#### （16） 介绍一下红黑树和它的应用场景有哪些
红黑树是一种特殊的二叉查找树，它在每一个节点上都使用红色或黑色进行标记，通过一些性质确保它是始终平衡的。
它的性质是这样的：
1. 每个节点不是红色就是黑色。
2. 根节点是黑色的。
3. 叶节点的空节点是黑色的。
4. 如果一个节点是红色的，那么它的两个子节点是黑色的。
5. 对于任意节点，从它到叶节点的每条路径上都有相同数目的黑色节点。

红黑树的插入，查询，删除在一般情况和最坏情况下的时间复杂度都是O(log(n))

应用场景主要是STL中map，set的实现，优点在于支持频繁的修改，因为查询删除插入时间复杂度都是logN

#### （17） 怎么写sql取表的前1000行数据（招银网络二面）
```sql
select * limit 1000
from t1
```
#### （18） N个骰子出现和为m的概率
#### （19） 海量数据问题（可参考左神的书）
#### （20） 一致性哈希
#### （21）希尔排序说一下/手撕
https://www.cnblogs.com/chengxiao/p/6104371.html
希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。
#### （22）Dijkstra算法说一下
#### （23）实现一个动态数组要怎么实现，说思路（腾讯teg一面）
模拟STL中vector的实现即可，去看一下vector的源码。
#### （24）最小生成树算法说一下
#### （25） 海量数据的bitmap使用原理
bitmap算法就是使用一个比特映射一个值，它可以用在整数排序和数据压缩上，因为使用一个比特位去存储一个数，所以它可以大大节省空间。

它的具体过程是：先根据数组中元素最大的数N计算需要分配多大的空间。
如果使用int型数组的形式来保存的话，一个int = 4字节  =4*8比特 = 32比特。也就是一个int数可以映射32个数据（图1），然后需要找到最大的数Max，表示最多需要的位数，所以需要开辟的数组空间为int a[1+Max/32]。
然后需要推导一个整数a内如何映射32个数据，方法是将待存储的数据模32，然后将a中相应位置的比特置为1。
依此方法映射每一个元素，待读取的时候扫描每个比特位，遇到值为1的就还原该数字。
![](fig/bitmap1.png)

**移位计算公式：**
N/32就是将N的二进制右移log32（也就是5）位 ： N>>5<br>
N%32就是求N的后5位：N& 0x1F  (0x1F = 00011111)<br>
模32然后相应位置置为1： a[i] |= 1<< N & 0x1F<br>

所以总的公式为： a[ N>>5 ] |= 1<< N & 0x1F<br>

**BitMap算法评价**
* 优点：
    1. 运算效率高，不进行比较和移位；
    2. 占用内存少，比如最大的数MAX=10000000；只需占用内存为MAX/8=1250000Byte=1.25M。
* 缺点：
    1. 所有的数据不能重复，即不可对重复的数据进行排序。（少量重复数据查找还是可以的，用2-bitmap）。
    2. 所需要的空间随着最大元素的增大而增大，当数据类似（1，1000，10万）只有3个数据的时候，用bitmap时间复杂度和空间复杂度相当大，只有当数据比较密集时才有优势。

#### （26） 布隆过滤器原理与优点
布隆过滤器是一个比特向量或者比特数组，它本质上是一种概率型数据结构，用来查找一个元素是否在集合中，支持高效插入和查询某条记录。常作为针对超大数据量下高效查找数据的一种方法。

**它的具体工作过程是这样子的：**
假设布隆过滤器的大小为m（比特向量的长度为m），有k个哈希函数，它对每个数据用这k个哈希函数计算哈希，得到k个哈希值，然后将向量中相应的位设为1。在查询某个数据是否存在的时候，对这个数据用k个哈希函数得到k个哈希值，再在比特向量中相应的位查找是否为1，如果某一个相应的位不为1，那这个数据就肯定不存在。但是如果全找到了，则这个数据有可能存在。

**为什么说有可能存在呢？**
因为不同的数据经过哈希后可能有相同的哈希值，在比特向量上某个位置查找到1也可能是由于某个另外的数据映射得到的。

**支持删除操作吗**
目前布隆过滤器只支持插入和查找操作，不支持删除操作，如果要支持删除，就要另外使用一个计数变量，每次将相应的位置为1则计数加一，删除则减一。

布隆过滤器中哈希函数的个数需要选择。如果太多则很快所有位都置为1，如果太少会容易误报。

**布隆过滤器的大小以及哈希函数的个数怎么选择？**
k 为哈希函数个数，m 为布隆过滤器长度，n 为插入的元素个数，p 为误报率
![](fig/布隆过滤器.png)
#### （27） 布隆过滤器处理大规模问题时的持久化，包括内存大小受限、磁盘换入换出问题
#### （28）实现一个队列，并且使它支持多线程，队列有什么应用场景（阿里三面）
```C++
//评测题目:
class FIFOQueue
{
vector<int> vec(initCap,0);
int start=0,end=0;
condition_variable cv;
mutex m;
bool flag=false;// isFull
  bool enqueue(int v) {
  	unique_lock<mutex></mutex> lk(m);
    while(flag==true) cv.wait(lk);
        end=(end+1)%initCap;
        vec[end]=v;
        cv.notifyall();
        return true;
    }
  }
  int dequeue() {
  unique_lock<mutex></mutex> lk(m);
  	if(start!=end){
    	int val = vec[start];
    	start=(start+1)%initCap;
        flag=false;
    	cv.notifyall();
        return val;
    }else{
    	flag=false;
    	cv.notifyall();
    	return -1;
  	}
  }
}
```
以上代码是面试时写的，并没有运行，也许有错误，请客观参考