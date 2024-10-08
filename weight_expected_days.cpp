#include <iostream>
#include <fstream>
#include <tuple>

using namespace std;

// Function to compute modular inverse using Fermat's Little Theorem
long long mod_inverse(long long a, long long p) {
    long long result = 1;
    long long exponent = p - 2;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        exponent /= 2;
    }
    return result;
}

// Function to calculate the expected number of days to reach weight G
tuple<long long, long long> expected_days(long long W, long long G, long long L) {
    long long mod = 998244353; // Ensure this is defined
    long long D;  // Expected days as p/q
    long long q;

    if (L == 0) {
        // If L is 0, we can only lose weight
        D = (W - G) * (W - G + 1) / 2;
        q = 1;  // Denominator remains 1
    } else {
        // Calculate p and q based on W, G, and L
        long long diff = W - G;
        D = (diff * (diff + 1)) / 2;
        q = (2 * diff) + 1;
    }

    // Calculate p/q in lowest terms
    long long p = D; // Numerator
    long long inverse_q = mod_inverse(q, mod);
    long long final_result = (p * inverse_q) % mod;

    return make_tuple(final_result, q);
}

int main() {
    // Define mod at the top of main if needed globally
    long long mod = 998244353;

    // Input and output file streams
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    if (!input_file.is_open() || !output_file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int T;
    input_file >> T; // Number of test cases

    for (int i = 0; i < T; ++i) {
        long long W, G, L;
        input_file >> W >> G >> L;

        auto [expected_days_result, q] = expected_days(W, G, L);

        // Calculate final output
        expected_days_result = (expected_days_result + mod) % mod;

        output_file << "Case #" << (i + 1) << ": " << expected_days_result << endl;
    }

    // Close the file streams
    input_file.close();
    output_file.close();

    return 0;
}
