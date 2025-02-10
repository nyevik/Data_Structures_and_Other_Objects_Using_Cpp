
#include <cassert> /** provides assert function */
#include <cstdlib> /** provides EXIT_SUCCESS */
#include <iomanip>
#include <iostream>

using namespace std;

/// @brief 
/// @param c 
/// @return 
double celsius_to_fahrenheight(double c)
// Precondition: c is a Celsius temperature no less than absolute zero (–273.15).
// Postcondition: The return value is the temperature c converted to Fahrenheit degrees.
{
    const double MINIMUM_CELSIUS = -273.15; // Absolute zero in Celsius degrees
    assert(c >= MINIMUM_CELSIUS);
    return (9.0 / 5.0) * c + 32;
}

void setup_cout_fractions(int fraction_digits)
{
    assert(fraction_digits >0);
    cout.precision(fraction_digits);
    cout.setf(ios::fixed, ios::floatfield);
    if (fraction_digits == 0)
        cout.unsetf(ios::showpoint);
    else
        cout.setf(ios::showpoint);
}

int main()
{
    const char HEADING1[] = "   Celsius";
    const char HEADING2[] = "Farenheit";
    const char LABEL1 = 'C';
    const char LABEL2 = 'F';
    const double TABLE_BEGIN = -100.0;
    const double TABLE_END  = 500.0;
    const double TABLE_STEP =  1.0;
    const int WIDTH = 9;
    const int DIGITS =1; //Number digits right of decimal pt

    double value1{0};
    double value2 =0;

    cout<< (9.0 / 5.0) << endl;
    setup_cout_fractions(DIGITS);
    cout << "CONVERSIONS from " << TABLE_BEGIN << " to " << TABLE_END << endl;
    cout << HEADING1 << " " << HEADING2 << endl;
    for (value1 = TABLE_BEGIN; value1 <= TABLE_END; value1 += TABLE_STEP)
    {
        value2 = celsius_to_fahrenheight(value1); //celsius_to_farenheight
        cout << setw(WIDTH) << value1 << LABEL1 << " ";
        cout << setw(WIDTH) << value2 << LABEL2 << endl;
    }

    return EXIT_SUCCESS;

}//end main()

