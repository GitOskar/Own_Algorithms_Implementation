#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Passenger
{
    unsigned int in, out;
    Passenger ( unsigned int in, unsigned int out ) :in(in), out(out) {}
};

bool compare(const Passenger& a, const Passenger& b)
{
    return a.in < b.in;
}

int main()
{
    ios::sync_with_stdio( false );

    unsigned short set_count;
    unsigned int passenger_count, min, in, out, max_out;

    cin >> set_count;

    for ( unsigned short i = 0 ; i<set_count ; i++ )
    {

        min = 0;
        max_out = 0;
        cin >> passenger_count;

        vector <Passenger> arr;

        for ( unsigned int j = 0 ; j<passenger_count ; j++ )
        {
            cin >> in >> out;
            arr.push_back( Passenger(in, out) );
        }

        sort( arr.begin(), arr.end(), compare );

        for ( auto x : arr )
        {
            if ( x.in >= max_out )
            {
                min ++;
                max_out = x.out;
                continue;
            }

            if ( max_out > x.out )
                max_out = x.out;

        }
        cout << min << endl;
    }
    return 0;
}