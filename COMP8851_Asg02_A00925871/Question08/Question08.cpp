/*========================================================================================
	Question 08
	
	Demonstrates the different running times of an O(N^2) vs O(NlogN) solution to 
	determining whether an array of ints contains any pair of ints that add up to a given 
	int K.
    
    Copyright 2018 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://github.com/erick-fda
        https://bitbucket.org/erick-fda
	
========================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <algorithm>
#include <chrono>
#include <vector>

/*========================================================================================
	Constants
========================================================================================*/
const std::string HORIZONTAL_RULE = "-------------------------------------";
const int n = 200000;
const int k = 100;
const int impossibleK = -1;
int values1[n];
int values2[n];
std::vector<int> sortedValues2;

/*========================================================================================
	Functions
========================================================================================*/
/**
	Get answer in O(N^2) time.
*/
bool SlowSolution()
{
	/* For each item... */
	for (int i = 0; i < n; ++i)
	{
		/* ...check against every other item. */
		for (int j = 0; j < n; ++j)
		{
			/* Skip if this is the same item. */
			if (j == i)
			{
				continue;
			}

			/* If the values add up, return true. */
			if (values1[i] + values1[j] == impossibleK)
			{
				return true;
			}
		}
	}

	/* Return false if we didn't find any match. */
	return false;
}

/**
	Binary search through values2.
	Look for value val, ignoring index i (the index we are comparing against).
*/
bool BinarySearch(int val, int left, int right, int indexToIgnore)
{
	/* Only keep searching as long as we have some range left. */
	if (right >= left)
	{
		int middle = left + ((right - left) / 2);

		/* Match found. */
		if (val == values2[middle])
		{
			/* Make sure we're not matching against the same index. */
			if (middle != indexToIgnore)
			{
				return true;
			}
			/* Check just below for a match. */
			else if (left < middle &&
				values2[middle - 1] == val)
			{
				return true;
			}
			/* Check just above for a match. */
			else if (right > middle &&
				values2[middle + 1] == val)
			{
				return true;
			}
			/* If we get here, it means the only thing 
				we match with is ourselves. */
			else
			{
				return false;
			}
		}
		/* Search lower. */
		else if (val < values2[middle])
		{
			return BinarySearch(val, left, middle - 1, indexToIgnore);
		}
		/* Search higher. */
		else if (val > values2[middle])
		{
			return BinarySearch(val, middle + 1, right, indexToIgnore);
		}
	}

	return false;
}

/**
	Get answer in O(NlogN) time.
*/
bool FastSolution()
{
	/* Sort in O(NlogN) */
	std::sort(values2, values2 + n);

	/* For each item... */
	for (int i = 0; i < n; ++i)
	{
		/* ...if there is a match using binary search, return true. */
		if (BinarySearch(impossibleK - values2[i], 0, n-1, i))
		{
			return true;
		}
	}

	/* Return false if we didn't find a match. */
	return false;
}

/*========================================================================================
	Main Function
========================================================================================*/
int main()
{
	std::cout << HORIZONTAL_RULE << "\n\tQuestion 08\n" << HORIZONTAL_RULE << "\n\n";

	/* Generate n random values between 0 and k-1 for each of the two arrays. */
	std::srand(time(nullptr));
	for (int i = 0; i < n; ++i)
	{
		values1[i] = rand() % k;
		values2[i] = rand() % k;
	}

	/* Time the slow solution. */
	std::cout << "Starting O(N^2) solution...\n";
	auto slowStart = std::chrono::high_resolution_clock::now();
	bool foundWithSlow = SlowSolution();
	auto slowEnd = std::chrono::high_resolution_clock::now();

	if (foundWithSlow)
	{
		std::cout << "Found a match with the O(N^2) solution.\n";
	}
	else
	{
		std::cout << "Did not find a match with the O(N^2) solution.\n";
	}

	std::cout << "O(N^2) solution took " << 
		std::chrono::duration_cast<std::chrono::milliseconds>(slowEnd - slowStart).count() << " ms.\n\n";

	/* Time the fast solution. */
	std::cout << "Starting O(NlogN) solution...\n";
	auto fastStart = std::chrono::high_resolution_clock::now();
	bool foundWithFast = FastSolution();
	auto fastEnd = std::chrono::high_resolution_clock::now();

	if (foundWithFast)
	{
		std::cout << "Found a match with the O(NlogN) solution.\n";
	}
	else
	{
		std::cout << "Did not find a match with the O(NlogN) solution.\n";
	}

	std::cout << "O(NlogN) solution took " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(fastEnd - fastStart).count() << " ms.\n\n";

	std::cout << "Press any key to quit...\n";
	std::cin.ignore();
	return 0;
}
