#include "date.hh"
#include "dateperiod.hh"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Splits the given string into several strings, by using the given delimiter
// as a separator.
// Returns the splitted string as a vector such that each string part is an
// element of the vector.
vector<string> split(const string& str, const char delimiter)
{
    vector<string> result;
    string tmp = str;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not word.empty())
        {
            result.push_back(word);
        }

    }
    if(not tmp.empty())
    {
        result.push_back(tmp);
    }
    return result;
}

// Converts the given date (either in format dd.mm.yyyy or yyyy-mm-dd) into
// corresponding ints. These ints (date parts) are passed as reference
// parameters to the caller.
// Returns true, iff conversion succeeded.
bool dateStrToInts(const string& date, int& day, int& month, int& year)
{
    try
    {
        // Trying '.' as a sepator
        vector<string> date_parts = split(date, '.');
        if(date_parts.size() == 3)
        {
            day = stoi(date_parts.at(0));
            month = stoi(date_parts.at(1));
            year = stoi(date_parts.at(2));
        }
        else
        {
            // Trying '-' as a separator (ISO format)
            date_parts = split(date, '-');
            if(date_parts.size() == 3)
            {
                // ISO-format requires two digits in days and months
                if(date_parts.at(1).size() != 2 or
                   date_parts.at(2).size() != 2)
                {
                    return false;
                }

                day = stoi(date_parts.at(2));
                month = stoi(date_parts.at(1));
                year = stoi(date_parts.at(0));
            }
            else
            {
                return false;
            }
        }
    }
    catch (invalid_argument const& ex)
    {
        //cout << "invalid_argument: " << ex.what() << endl;
        return false;
    }
    return true;
}

// Sorts the given vector and prints differences between each
// adjacent elements.
// If the vector has less than two elements, prints the error
// message and returns.´
void printDatesAndDiffs(vector<Date> dates)
{
    if(dates.size() < 2)
    {
        cout << "Too few dates" << endl;
        return;
    }
    sort(dates.begin(), dates.end());
    for(unsigned int i = 0; i < dates.size() - 1; ++i)
    {
        DatePeriod period(dates.at(i), dates.at(i + 1));
        cout << "start: " << period.getStart()
             << " end: " << period.getEnd()
             << " diff: " << period.getDiff() << endl;
    }
}

int main()
{
    cout << "Enter dates: ";
    string dates = "";
    getline(cin, dates);
    vector<Date> date_vector;
    vector<string> date_str_vector = split(dates, ' ');
    for(string& date_str : date_str_vector)
    {
        int day = 0;
        int month = 0;
        int year = 0;
        if(dateStrToInts(date_str, day, month, year))
        {
            Date date(year, month, day);
            if(not date.isLegal())
            {
                // Wrong numbers
                cout << "Illegal date: " << date_str << endl;
            }
            else
            {
                date_vector.push_back(date);
            }

        }
        else
        {
            // Not numeric or not three parts or missing zeros in ISO-format
            cout << "Illegal date: " << date_str << endl;
        }
    }
    printDatesAndDiffs(date_vector);

    return 0;
}
