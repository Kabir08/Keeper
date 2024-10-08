#include <bits/stdc++.h>

using namespace std;

// Function to generate prime numbers up to max_n using Sieve of Eratosthenes
vector<int> sieve_of_eratosthenes(int max_n) {
    vector<bool> is_prime(max_n + 1, true);
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not primes

    for (int start = 2; start * start <= max_n; ++start) {
        if (is_prime[start]) {
            for (int multiple = start * start; multiple <= max_n; multiple += start) {
                is_prime[multiple] = false;
            }
        }
    }

    vector<int> primes;
    for (int num = 2; num <= max_n; ++num) {
        if (is_prime[num]) {
            primes.push_back(num);
        }
    }
    return primes;
}

// Function to count N-subtractorizations
int count_n_subtractorizations(int N, const vector<int>& primes) {
    int count = 0;
    unordered_set<int> prime_set(primes.begin(), primes.end()); // For quick lookup

    // Loop over all primes less than or equal to N
    for (int prime : primes) {
        if (prime > N) break; // Only consider primes up to N

        // Check if there exists a prime r such that q = prime + r is also prime
        for (int r : primes) {
            if (r > N) break; // r must be less than or equal to N
            int q = prime + r; // Calculate q as p + r
            if (q <= N && prime_set.count(q)) {
                count++; // Found a valid (q, r) pair
                break; // Count this prime once for this N
            }
        }
    }
    return count;
}

int main() {
    ifstream input_file("input1.txt");
    ofstream output_file("output1.txt");

    if (!input_file.is_open() || !output_file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int T;
    input_file >> T;
    vector<int> queries(T);
    int max_n = 0;

    for (int i = 0; i < T; ++i) {
        input_file >> queries[i];
        max_n = max(max_n, queries[i]);
    }

    // Generate primes up to max_n
    vector<int> primes = sieve_of_eratosthenes(max_n);

    // Process each query
    for (int i = 0; i < T; ++i) {
        int N = queries[i];
        int n_subtr_count = count_n_subtractorizations(N, primes);
        output_file << "Case #" << (i + 1) << ": " << n_subtr_count << endl;
    }

    input_file.close();
    output_file.close();

    return 0;
}
