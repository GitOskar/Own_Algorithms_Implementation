#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define MIN_CODE -1
#define BUCKET_COUNT 1000

struct Data
{
    unsigned short priority;
    unsigned long long random_code;
    unsigned short codes_count;
    short codes[4];

    Data()
    {
        for ( short i=1 ; i<4 ; i++ )
            codes[ i ] = MIN_CODE;
    }
};

bool compare_random_code ( const Data & a, const Data & b )
{
    return a.random_code < b.random_code;
}


void sort_by_priority( Data* arr, const unsigned int & size )
{
    vector< Data > vectors[ 11 ];

    for ( unsigned int i=0 ; i<size ; i++ )
        vectors[ arr[i].priority ].push_back( arr[i] );

    unsigned it = 0;

    for ( unsigned short i=0 ; i<11 ; i++ )
        for ( Data x : vectors[i] )
        {
            arr[ it ] = x;
            it++;
        }
}

void sort_by_random_code( Data* arr, const unsigned int & size, unsigned int bucket_count )
{
    vector< Data > vectors[ bucket_count ];

    double divider = ( unsigned ) ( ceil ( 10000001.0 / double( bucket_count ) ) );

    for ( unsigned int i=0 ; i<size ; i++ )
        vectors[ ( unsigned ) floor( (double)arr[i].random_code / divider ) ].push_back( arr[i] );

    unsigned it=0;

    for ( unsigned int i=0 ; i<bucket_count ; i++ )
    {
        stable_sort( vectors[i].begin(), vectors[i].end(), compare_random_code );

        for ( Data x : vectors[i] )
        {
            arr[ it ] = x;
            it++;
        }
    }
}

void sort_by_codes( Data* arr, const unsigned int & size )
{

    unsigned int it;

    for ( short j=3 ; j>=0 ; j-- )
    {
        it = 0;

        vector< Data > vectors[ 256 ];

        for ( unsigned i=0 ; i<size ; i++ )
        {
            if ( arr[ i ].codes[ j ] == -1 )
            {
                arr[ it ] = arr[ i ];
                it++;
            }
            else
                vectors[ arr[ i ].codes[ j ] ].push_back( arr[ i ] );
        }


        for ( short k=0 ; k<256 ; k++ )
            for ( Data x : vectors[ k ] )
            {
                arr[ it ] = x;
                it++;
            }
    }
}

void result( Data* documents, const unsigned int & size )
{
    unsigned long long result = 0;

    for ( unsigned i=0 ; i<size ; i++ )
    {
        result += ( documents[i].random_code * i ) % 100000007;
        result %= 100000007;
    }

    cout << result;
}


int main()
{
    ios::sync_with_stdio( false );

    unsigned int documents_count, id;

    cin >> documents_count;

    Data* documents = new Data[ documents_count ];

    for ( unsigned int i=0 ; i<documents_count ; i++ )
    {
        cin >> id;

        cin >> documents[ id - 1 ].priority >> documents[ id - 1 ].random_code >> documents[ id - 1 ].codes_count;

        for ( unsigned int j=0 ; j<documents[ id - 1 ].codes_count ; j++ )
            cin >> documents[ id - 1 ].codes[ j ];
    }

    unsigned short sort_priority[4];

    cin >> sort_priority[0] >> sort_priority[1] >> sort_priority[2] >> sort_priority[3];

    short i = 3;
    for ( ; i>=0 ; i-- )
        if ( sort_priority[ i ] == 1 )
        {
            i--;
            break;
        }

    for ( ; i>=0 ; i-- )
        switch ( sort_priority[ i ] )
        {
            case 2:
            {
                sort_by_priority( documents, documents_count );
                break;
            }

             case 3:
            {
                sort_by_random_code( documents, documents_count, BUCKET_COUNT );
                break;
            }

            case 4:
            {
                sort_by_codes( documents, documents_count );
                break;
            }

        }

    result( documents, documents_count );

    return 0;

  }