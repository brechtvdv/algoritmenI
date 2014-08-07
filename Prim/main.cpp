#include "ggraaf.h"
#include "prim.h"
#include<fstream>

#include <iostream>

using namespace std;

int main()
{
    GewogenGraaf<ONGERICHT, int> gg;

    string line;
    ifstream is("test.txt");

    if(is.is_open())
    {
        try
        {
            gg.lees(is);
        } catch(GraafExceptie e)
        {
            cout << e << endl;
            return 1;
        }

    } else {
        cout << "Kon bestand niet uitlezen" << endl;
    }

    Prim<ONGERICHT, int> primke (gg);

    primke.start();

    primke.print_mob();

    return 0;
}
