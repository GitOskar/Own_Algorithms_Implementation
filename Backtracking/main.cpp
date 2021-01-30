#include <iostream>

struct Trace
{
    unsigned short a, b;
};

bool searching( Trace* arr, unsigned short size, unsigned index, bool* added, unsigned short ppl_needed, unsigned short persons_count )
{

    if ( index >= size )
        return true;

    if ( added [ arr[ index ].a ] || added [ arr[ index ].b ] )
    {
        if ( searching( arr, size, index+1, added, ppl_needed, persons_count ) )
            return true;

        return false;
    }

    else
    {
        if ( ppl_needed+1 > persons_count )
            return false;

        added [ arr[ index ].a ] = true;

        if ( searching( arr, size, index+1, added, ppl_needed+1, persons_count ) )
            return true;

        added [ arr[ index ].a ] = false;


        added [ arr[ index ].b ] = true;

        if ( searching( arr, size, index+1, added, ppl_needed+1, persons_count ) )
            return true;

        added [ arr[ index ].b ] = false;

        return false;
    }

}


using namespace std;

int main()
{
    ios::sync_with_stdio( false );

    unsigned short sets_count, station_count, trace_count, persons_count;

    cin >> sets_count;
    unsigned short a, b;

    Trace *arr = nullptr;
    bool *added = nullptr;

    for ( unsigned short i=0 ; i<sets_count ; i++ )
    {
        cin >> station_count >> trace_count >> persons_count;

        arr = new Trace[ trace_count ];
        added = new bool[ trace_count ];

        for ( unsigned j=0 ; j<trace_count ; j++ )
            added[ j ] = false;

        for ( unsigned short j=0 ; j<trace_count ; j++ )
        {
            cin >> a >> b;

            arr[ j ].a = a;
            arr[ j ].b = b;
        }

        if ( searching( arr, trace_count, 0, added, 0, persons_count ) )
            cout << "TAK\n";
        else
            cout << "NIE\n";

        delete[] arr;

    }

    return 0;
}