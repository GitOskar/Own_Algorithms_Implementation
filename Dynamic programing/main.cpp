#include <iostream>
#include <vector>

using namespace std;

struct entry_value
{
    unsigned id, day, from_id, from_day;

    entry_value( unsigned id, unsigned day, unsigned from_id, unsigned from_day ): id(id), day(day), from_id(from_id), from_day(from_day) {}
};

void clear( unsigned day, unsigned medium_count, unsigned long long  arr )
{
    for ( unsigned int i=0 ; i < medium_count ; i++ )
        arr[ i ][ day ] = 0;
}

void sum( unsigned day, unsigned medium_count, unsigned long long arr, unsigned long long & result )
{
    for ( unsigned int i=0 ; i < medium_count ; i++ )
        result += arr[ i ][ day ];
}

int main()
{
    ios::sync_with_stdio( false );

    vector<entry_value> daily_citates[7];

    unsigned media_count, starting_medium, starting_day, day_count, citation_count;

    unsigned id, day, from_id, from_day;

    cin >> media_count >> starting_medium >> starting_day >> day_count >> citation_count;

    if ( media_count == 1 )
    {
        cout << 1;
        return 0;
    }

    unsigned long long arr = new unsigned long long[ media_count ];
    for ( unsigned int i=0 ; i < media_count ; i++ )
    {
        arr[i] = new unsigned long long[ 7 ];
        for ( unsigned j=0 ; j<7 ; j++ )
            arr[i][j] = 0;
    }

    arr[ starting_medium ][ starting_day ] = true;

    unsigned long long result = 1;

    for ( unsigned i=0 ; i < citation_count ; i++ )
    {
        cin >> id >> day >> from_id >> from_day;
        daily_citates[ day ].push_back( { id, day, from_id, from_day } );
    }

    unsigned current_day = (starting_day+1)%7;

    for ( unsigned i=1 ; i < day_count ; i++ )
    {
        clear( current_day, media_count, arr );

        for ( entry_value x : daily_citates[ current_day ] )
            arr[ x.id ][ x.day ] += ( arr[ x.from_id ][ x.from_day] %= 100000007 );

        sum( current_day, media_count, arr, result );
        current_day = (current_day+1)%7;
        result %= 100000007;
    }

    cout << result;
    return 0;
}