#include <iostream>

#include <vector>
#include <cmath>

using namespace std;

#include "BackTrack.h"

// oplossing gebasseerd op voorbeeld in de cursus R. Stoop (p.73)
int main()
{
    cout << "N-Queens solver with backtrack!" << endl;
    cout << "n=";

    int n;

    cin >> n;

    solve_with_backtrack(n);

    return 0;
}
