#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int SIZE_OF_CORRUPTS = 4;

void printVector(const vector<int>& vect);
bool locsContains(const array<int,SIZE_OF_CORRUPTS> locs, const int& index);
vector<int> memorySwap(const vector<int>& vect);
vector<int> corruptSwap(const vector<int>& vect, const array<int,SIZE_OF_CORRUPTS> locs);
vector<int> optimizedSwap(const vector<int>& vect, const array<int, SIZE_OF_CORRUPTS> locs);

int main()
{
	vector<int> unsortedVector = { 1, 6, 3, 7, 1, 7, 3, 9, 3 };
	vector<int> corruptVector = { 1, 5, 0, 2, 5, 2, 0, 5, 2, 7, 2, 0, 0 };
	array<int,SIZE_OF_CORRUPTS> corruptLocs = { 2, 6, 11, 12 };

	printVector(unsortedVector);
	printVector(memorySwap(unsortedVector));

	printVector(corruptVector);
	printVector(corruptSwap(corruptVector, corruptLocs));
	printVector(optimizedSwap(corruptVector, corruptLocs));

	return 0;
}

// Print passed vector
void printVector(const vector<int>& vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		cout << vect[i];
	}
	cout << endl;
}

bool locsContains(const array<int,SIZE_OF_CORRUPTS> locs, const int& index)
{
	for (int loc : locs)
	{
		if (loc == index)
			return true;
	}
	
	return false;
}

// Swap list without memory constraints
vector<int> memorySwap(const vector<int>& vect)
{
	vector<int> returnVect;

	for (int i = vect.size()-1; i > -1; i--)
	{
		returnVect.push_back(vect[i]);
	}

	return returnVect;
}

// Swap integer list without touching zero(corrrupt) values
vector<int> corruptSwap(const vector<int>& vect, const array<int,SIZE_OF_CORRUPTS> locs)
{
	vector<int> flippedVect;
	vector<int> returnVect (vect);

	for (int i = vect.size() - 1; i > -1; i--)
	{
		if (locsContains(locs, i))
			continue;
		flippedVect.push_back(vect[i]);
	}

	int skipped = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		if (locsContains(locs, i))
		{
			++skipped;
			continue;
		}
		returnVect[i] = flippedVect[i-skipped];
	}

	return returnVect;
}

// Swap list using less memory
vector<int> optimizedSwap(const vector<int>& vect, const array<int, SIZE_OF_CORRUPTS> locs)
{
	vector<int> returnVect(vect);

	for (int frontOffset = 0, backOffset = returnVect.size()-1; backOffset >= frontOffset;)
	{
		if (locsContains(locs, frontOffset))
		{
			++frontOffset;
			continue;
		}
		else if (locsContains(locs, backOffset))
		{
			--backOffset;
			continue;
		}

		int temp = vect[frontOffset];
		returnVect[frontOffset] = returnVect[backOffset];
		returnVect[backOffset] = temp;

		++frontOffset;
		--backOffset;
	}

	return returnVect;
}