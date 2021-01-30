#include <iostream>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Node
{
    vector <string> higher_priority_names;
    bool forbidden;
    bool visited;
    Node() :forbidden( 0 ), visited( 0 ) {}
};

int main()
{
    ios::sync_with_stdio(false);
    bool good;
    unsigned short t;
    unsigned int surname_count, pair_count;
    string surname1, surname2;
    cin >> t;

    for ( unsigned short i=0 ; i<t ; i++)
    {
        cin >> surname_count >> pair_count;
        map< string, Node > graph;

        for ( unsigned int j=0 ; j < surname_count ; j++ )
            cin >> surname1;

        for ( unsigned int j=0 ; j < pair_count ; j++ )
        {
            cin >> surname1 >> surname2;
            graph[surname2].higher_priority_names.push_back(surname1);
        }
        cin.ignore();
        getline( cin, surname1 );
        stringstream s1( surname1 );

        vector < string > forbidden_names;

        for ( unsigned int j=0 ; j < surname_count ; j++ )
        {
            s1 >> surname1;
            graph[surname1].visited = 1;

            good = true;

            for ( string x : graph[surname1].higher_priority_names )
            {
                if ( !graph[x].forbidden && !graph[x].visited )
                {
                    forbidden_names.push_back( x );
                    graph[x].forbidden = 1;
                }
            }

            for ( string x : forbidden_names )
            {
                if ( x == surname1 )
                {
                    cout << "NIE\n\n";
                    good = false;
                    break;
                }
            }

            if (!good)
                break;
        }

        if ( good )
            cout << "TAK\n\n";
    }
    return 0;
}
