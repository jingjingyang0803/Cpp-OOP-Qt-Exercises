#include "date.hh"
#include "datetime.hh"
#include "dateexception.hh"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Splits the given string into several strings, by using the given delimiter
// as a separator.
// Returns the splitted string as a vector such that each string part is an
// element of the vector.
// User can specify if empty parts will be ignored or not.
vector<string> split(const string& str, const char delimiter,
                     bool ignore_empty = false)
{
    vector<string> result;
    string tmp = str;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int main()
{
    cout << "Enter dates and times: ";
    string whole_input = "";
    getline(cin, whole_input);
    vector<string> dates_and_times = split(whole_input, ';', true);
    vector<shared_ptr<Date>> dates;

    // Going through the given dates and times
    for(string& date_and_time : dates_and_times)
    {
        // Trying to create Date and DateTime objects
        try
        {
            vector<string> parts = split(date_and_time, ' ', true);
            if(parts.size() == 3)
            {
                dates.push_back(make_shared<Date>(stoi(parts.at(0)),
                                                  stoi(parts.at(1)),
                                                  stoi(parts.at(2))));
            }
            else if(parts.size() == 6)
            {
                dates.push_back(make_shared<DateTime>(stoi(parts.at(0)),
                                                      stoi(parts.at(1)),
                                                      stoi(parts.at(2)),
                                                      stoi(parts.at(3)),
                                                      stoi(parts.at(4)),
                                                      stoi(parts.at(5))));
            }
        }

        // Catching invalid arguments, i.e. non-numeric strings given to stoi
        catch (invalid_argument const& ex)
        {
            cout << "invalid_argument: " << ex.what() << endl;
        }

        // Catching illegal date and time strings
        catch(DateException const& ex)
        {
            cout << "DateException: " << ex.what() << endl;
        }
    }

    // Printing legal dates and times
    for(unsigned int i = 0; i < dates.size(); ++i)
    {
        cout << "Date #" << i + 1 << ": " << dates.at(i)->toString() << endl;
    }

    return 0;
}
