#include <iostream>
#include <vector>

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

// Converts the words, found from the input string, to double values and
// counts the mean of these values.
double mean(const string& input)  // Don't change the function definition!
{
    // Split the input string into separate number strings
    vector<string> numbers = split(input, ' ');

    double sum = 0.0;   // Sum of all numbers
    int count = 0;      // Number of valid numbers

    // Go through all tokens returned by split
    for(const string& num : numbers)
    {
            try
        {
            // Try converting string to double
            double value = stod(num);

        // Add value to total sum
        sum += value;

        // Increase number count
        ++count;
        }
        catch(const invalid_argument&)
        {
            // Throws invalid_argument exception with customized message if conversion fails
            throw invalid_argument("invalid_argument: stod");
        }

    }

    // Throws domain_error if no numbers are given
    if(count == 0)
    {
        throw domain_error("domain_error: No numbers");
    }

    // Return the average value
    return sum / count;
}


// Don't remove! Needed for tests.
#ifndef MEAN_TEST
// Don't remove! Needed for tests.
// Main function
int main()
{
    // Prompt user for input
    cout << "Enter numbers: ";

    // Read the whole line containing numbers
    string input_line;
    getline(cin, input_line);

    try
    {
        // Call mean function to calculate the average
        double result = mean(input_line);

        // Print the calculated mean
        cout << "Mean: " << result << endl;
    }
    catch(const invalid_argument& error)
    {
        // Error occurs if stod fails to convert a string to double
        cout << error.what() << endl;
    }
    catch(const domain_error& error)
    {
        // Error occurs if no numbers were given
        cout << error.what() << endl;
    }

    return EXIT_SUCCESS;
}
// Don't remove! Needed for tests.
#endif // MEAN_TEST
// Don't remove! Needed for tests.
