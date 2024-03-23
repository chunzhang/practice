/*
Facebook/Google/Apple/Amazon/TikTok


Design an algorithm that accepts a stream of integers and retrieves the product of the last k integers of the stream.

Implement the ProductOfNumbers class:

ProductOfNumbers() Initializes the object with an empty stream.
void add(int num) Appends the integer num to the stream.
int getProduct(int k) Returns the product of the last k numbers in the current list. You can assume that always the current list has at least k numbers.
The test cases are generated so that, at any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.

 

Example:

Input
["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]

Output
[null,null,null,null,null,null,20,40,0,null,32]

Explanation
ProductOfNumbers productOfNumbers = new ProductOfNumbers();
productOfNumbers.add(3);        // [3]
productOfNumbers.add(0);        // [3,0]
productOfNumbers.add(2);        // [3,0,2]
productOfNumbers.add(5);        // [3,0,2,5]
productOfNumbers.add(4);        // [3,0,2,5,4]
productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
productOfNumbers.add(8);        // [3,0,2,5,4,8]
productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32 
 

Constraints:

0 <= num <= 100
1 <= k <= 4 * 10^4
At most 4 * 10^4 calls will be made to add and getProduct.
The product of the stream at any point in time will fit in a 32-bit integer.
*/

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */


// idea is to maintain the "prefix product" of the streamed number
// -- this works because the condidiotn "The product of the stream at any point in time will fit in a 32-bit integer"
// -- when encounter zero, reset the prefix product
// -- to simplify coding, product[0] is set to 1 as the base
// time: O(1)
// space: O(N)
class ProductOfNumbers {
public:
    ProductOfNumbers() : m_prod(1,1) {
        
    }
    
    void add(int num) {
        if(!num) {  // any k-product beyond zero is zero, so reset
            m_prod.clear();
            m_prod.push_back(1);  // used as base to simplify coding
        }
        else {
            m_prod.push_back(num*m_prod.back());
        }
    }
    
    int getProduct(int k) {
        int sz = m_prod.size();  // actual size is sz-1, since m_prod[0] is used as the base
        if(k <= sz-1)
            return m_prod.back() / m_prod[sz-k-1];
        else
            return 0;
    }

private:
    vector<int> m_prod;  // prefix product starting from a non-zero element; m_prod[0]==1 used as base
};
