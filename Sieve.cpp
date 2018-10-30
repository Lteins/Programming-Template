
// C++ program to print all primes smaller than or equal to 
// n using Sieve of Eratosthenes 
// @Complexity: O(n*log(log(n)))
// @Splace: O(n)
#include<iostream>
#include<vector>
using namespace std; 
typedef long long ll;
vector<ll> SieveOfEratosthenes(ll n) 
{ 
    // Create a boolean array "prime[0..n]" and initialize 
    // all entries it as true. A value in prime[i] will 
    // finally be false if i is Not a prime, else true. 
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    for (ll p=2; p*p<=n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p 
            for (ll i=p*2; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
    vector<ll> ret;
    // Print all prime numbers 
    for (ll p=2; p<=n; p++) 
       if (prime[p]) 
        ret.push_back(p); 

    return ret;      
} 
  
// Driver Program to test above function 
int main() 
{ 
    vector<ll> primes = SieveOfEratosthenes(100);
    for (int i=0;i<primes.size();i++)
        cout << primes[i] << " ";
    cout << endl;
    return 0; 
} 