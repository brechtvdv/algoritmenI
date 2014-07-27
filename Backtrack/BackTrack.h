#ifndef BACKTRACK_H_INCLUDED
#define BACKTRACK_H_INCLUDED

bool toegelaten (vector<int> &koninginnen, int rij, int kolom)
{
    // overloop voorlopige oplossing
    for(int i=0; i<koninginnen.size(); i++)
    {
        // rij of kolom al bezet
        if(i == rij || koninginnen[i] == kolom)
            return false;
        // diagonaal al bezet
        if(abs(i-rij) == abs(koninginnen[i]-kolom))
            return false;
    }
    return true;
}

// voor bepaalde rij kandidaten zoeken (dus alle kolommen overlopen en controleren of er geen conflict met oplossing is)
vector<int> bepaalKandidaten (vector<int> &koninginnen, int k, int n){
    vector<int> kandidaten;

    // alle kolommen overlopen
    for(int j=0; j<n; j++){
        //check toegelaten met oplossing
        if(toegelaten(koninginnen, k, j)) kandidaten.push_back(j);
    }

    return kandidaten;
}


void print_oplossing(vector<int> &oplossing, int n)
{
    cout << "Oplossing: " << endl;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
          if(oplossing[i] == j){ cout<<'Q'; }
          else { cout<<'_'; }
        }
        cout<<endl;
    }
    cout << endl;
}

void backtracking (vector<int> &koninginnen, int k, int n) {
    // Onderstel k > 0
    // voor alle konininginnen een geschikte kandidaat gevonden
    if(koninginnen.size() == n) {
        print_oplossing(koninginnen, n);
    }
    else{
        // Bepaal Vk
        vector<int> kandidaten = bepaalKandidaten(koninginnen, k, n);

        for(int i=0; i<kandidaten.size(); i++){
            koninginnen.push_back(kandidaten[i]);
            // recursief verder zoeken
            backtracking(koninginnen, k++, n);
            // terugkeren
            koninginnen.pop_back();
        }
    }

}


void solve_with_backtrack(int n)
{
    vector<int> koninginnen;
    backtracking(koninginnen, 0, n);   // recursive
}

#endif // BACKTRACK_H_INCLUDED
