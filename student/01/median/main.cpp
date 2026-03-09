#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;


// Splits the given string into several parts using the given delimiter.
// Returns a vector containing the split parts.
vector<string> split(const string& str, const char delimiter)
{
    vector<string> parts;
    string remaining = str;

    while (remaining.find(delimiter) != string::npos)
    {
        string word = remaining.substr(0, remaining.find(delimiter));
        remaining = remaining.substr(remaining.find(delimiter) + 1);

        if (not word.empty())
        {
            parts.push_back(word);
        }
    }

    if (not remaining.empty())
    {
        parts.push_back(remaining);
    }

    return parts;
}


// Converts input string numbers into double values and calculates median.
// Throws invalid_argument if input is empty or contains invalid numbers.
double median(const string& input)
{
    // Split input string into words
    vector<string> words = split(input, ' ');

    // Check if no numbers were given
    if (words.empty())
    {
        throw invalid_argument("No input");
    }

    // Convert words into double numbers
    vector<double> numbers;

    for (const string& word : words)
    {
        try
        {
            double number = stod(word);
            numbers.push_back(number);
        }
        catch (...)
        {
            throw invalid_argument("Not a double");
        }
    }

    // Sort numbers to prepare for median calculation
    sort(numbers.begin(), numbers.end());

    int count = numbers.size();

    // If count is odd, return middle element
    if (count % 2 == 1)
    {
        return numbers.at(count / 2);
    }
    // If count is even, return mean of two middle elements
    else
    {
        double left_middle = numbers.at(count / 2 - 1);
        double right_middle = numbers.at(count / 2);

        return (left_middle + right_middle) / 2.0;
    }
}


#ifndef MEDIAN_TEST
int main()
{
    cout << "Enter numbers: ";

    string input_line;
    getline(cin, input_line);

    try
    {
        double result = median(input_line);
        cout << "Median: " << result << endl;
    }
    catch (const invalid_argument& error)
    {
        cout << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#endif
