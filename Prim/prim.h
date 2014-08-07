#ifndef PRIM_H_INCLUDED
#define PRIM_H_INCLUDED

#include <queue>
#include <vector>

using namespace std;

enum Kleur {
    WIT, GRIJS, ZWART
};

template<typename T>
struct KnoopRelatie{
    int van;
    int naar;
    T gewicht;

    KnoopRelatie(int v, int n, T g) : van(v), naar(n), gewicht(g) {};

    // als de andere relatie kleiner gewicht heeft
    // -> hogere prioriteit
    bool operator<(const KnoopRelatie& o) const
    {
        return o.gewicht<gewicht;
    }
};

template<GraafType TYPE, typename T>
class Prim
{
    public:
        Prim(GewogenGraaf<TYPE, T> gg);
        void start();
        void add_mogelijke_buren(int startkn);
        void print_mob();
        void wis_reeds_toegevoegde_knopen();

    protected:
        GewogenGraaf<TYPE, T> gg;
        priority_queue<KnoopRelatie<T> > pq;
        vector<int> pad;
        vector<Kleur> kleuren;

        // totale gewicht van de MOB (=minimaal overspannende boom)
        int totale_gewicht = 0;
        int aantal_knopen = 0;
};

template<GraafType TYPE, typename T>
Prim<TYPE, T>::Prim(GewogenGraaf<TYPE, T> gg)
{
    this->gg  = gg;
}

template<GraafType TYPE, typename T>
void Prim<TYPE, T>::start()
{
    cout << "PRIM ALGO" << endl;

    // aantal knopen in graaf
    aantal_knopen = gg.aantal_knopen();

    // vectoren init
    pad.reserve(aantal_knopen);
    kleuren.reserve(aantal_knopen);
    for(int i=0; i<aantal_knopen; i++)
            kleuren[i] = WIT;

    // we beginnen bij knoop 0
    // deze is dus al ontdekt
    int startkn = 0;
    pad.push_back(startkn);
    kleuren[startkn] = ZWART;

    add_mogelijke_buren(startkn);

    // elke knoop moet aan beurt komen
    while(!pq.empty())
    {
        // volgende knoop met hoogste prioriteit
        KnoopRelatie<T> relatie = pq.top();

        int kn = relatie.naar;

        // nog niet in de MOB
        if(kleuren[kn]!=ZWART)
        {
            pad.push_back(kn);
            kleuren[kn] = ZWART;
            totale_gewicht += relatie.gewicht;

            add_mogelijke_buren(kn);
        }
        pq.pop();
    }

    cout << "totale gewicht: " << totale_gewicht << endl;
}

template<GraafType TYPE, typename T>
void Prim<TYPE, T>::add_mogelijke_buren(int van)
{
    Knoop k = gg[van];

    // buren toevoegen
    // First: nummer buur
    // Second: verbindingsnummer
    for(std::map<int,int>::iterator it=k.begin(); it!=k.end(); it++)
    {
        int naar = (*it).first;

        // kan zijn dat een knoop meerdere keren toegevoegd wordt
        if(kleuren[naar]!=ZWART)
        {
            int verbindingsNr = (*it).second;
            int gewicht = gg.gewicht(verbindingsNr);

            KnoopRelatie<T> relatie(van, naar, gewicht);
            pq.push(relatie);

            // potentieel voor MOB
            kleuren[naar] = GRIJS;
        }
    }
}

template<GraafType TYPE, typename T>
void Prim<TYPE, T>::print_mob()
{
    for(int i=0; i<gg.aantal_knopen(); i++)
    {
        cout << "Van: " << i << " naar: " << pad[i] << endl;
    }
}


#endif // PRIM_H_INCLUDED
