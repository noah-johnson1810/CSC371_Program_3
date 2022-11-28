#include <iostream>
#include <fstream>

using namespace std;

long long power(long long x, long long y, long long p)
{
    long long res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}


bool millerTest(long long d, long long n, int a)
{
    long long x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true;
    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}

bool isPrime(int n)
{
    bool isPrime = true;
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // try miller rabin 15 times to test primality 
    for (int i = 0; i < 15; i++) {
        int a = 2 + rand() % (n - 4);
        if (!millerTest(d, n, a))
            isPrime = false;
    }
    return isPrime;
}

long long countNonWitnesses(long long numToTest) {
    long long numNonWitnesses = 0;
    long long d = numToTest - 1;
    while (d % 2 == 0 && d != 0)
        d /= 2;
    for (int i = 2; i < numToTest - 2; i++) {
        if (millerTest(d, numToTest, i))
            numNonWitnesses++;
    }
    return numNonWitnesses;
}


int main() {
    long long numToTest;
    long long numNonWitnesses;
    cin >> numToTest;

    if (isPrime(numToTest)) {
        cout << numToTest << " is prime" << endl;
    }
    else {
        numNonWitnesses = countNonWitnesses(numToTest);
        cout << numToTest << " " << numNonWitnesses;
    }

}