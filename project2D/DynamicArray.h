/*=============================================================================
 |   Assignment:  Dynamic Array (Code Design and Data Structures)
 |     Due Date:  1st of May
 |       Author:  Lachlan Wernert
 |      Teacher:  Richard Stern
 |
 |  Description:  A Dynamic Array template that can store different data types.
 |                Searching using O(1) for index searches, and the rest are O(n).
 |
 | Deficiencies:
 *===========================================================================*/
#pragma once
#include <memory.h>
#include <assert.h>
#include <functional>

template <typename T>
class DynamicArray
{
public:
	DynamicArray(int nInitialSize = 1)
	{
		// Simple check to determine whether the initial size of the array is less then 1, if it is then just set it to one.
		int nSize = nInitialSize;
		if (nSize < 1)
			nSize = 1;
		// Creating a new array with the initial size.
		m_pData = new T[nSize];
		// Setting the current total size.
		m_nTotalSize = nSize;
		// Setting the used count to 0.
		m_nUsedCount = 0;
		// Setting the should be deleted bool to true.
		m_bShouldDelete = true;
	}

	~DynamicArray()
	{
		// Deallocating the data in the array.
		if (m_bShouldDelete)
			delete[] m_pData;
		else
			m_pData = nullptr;
	}

	void SetShouldDelete(bool bDelete)
	{
		m_bShouldDelete = bDelete;
	}

	// Function to set the total size of the array.
	void SetTotalSize(int newTotalSize)
	{
		m_nTotalSize = newTotalSize;
	}

	void PushFront(T data)
	{
		// Iterating through the array backwards.
		for (int i = m_nUsedCount; i > 0; --i)
		{
			// Swapping the data with the data to it's left.
			m_pData[i] = m_pData[i - 1];
		}
		// Setting the first slot in the array to the data given.
		m_pData[0] = data;
		// Adding one to the used count.
		++m_nUsedCount;
	}

	void PushBack(T data)
	{
		// Checking if the count matches or is greater then the total size.
		if (m_nUsedCount >= m_nTotalSize)
			// Resize the array if so.
			Resize();

		// Adding the data to the very end of the array.
		m_pData[m_nUsedCount] = data;
		// Adding one to the used count.
		++m_nUsedCount;
	}

	void Insert(int index, T data)
	{
		// Checking if the slot chosen is possible.
		if (index <= m_nUsedCount)
			// Iterating through the array backwards, until it hits the selected slot.
			for (int i = m_nUsedCount; i > index; --i)
			{
				// Swapping the data with the data to it's left.
				m_pData[i] = m_pData[i - 1];
			}
		// Setting the selected slot to the inputted data.
		m_pData[index] = data;
		// Adding one to the used count.
		++m_nUsedCount;
	}

	void Erase(int index)
	{
		// Checking if the index chosen is possible.
		if (index <= m_nUsedCount)
			//Iterating through the array starting at the selected index.
			for (int i = index; i < m_nUsedCount; ++i)
			{
				// Swapping the data from the right index into the left.
				m_pData[i] = m_pData[i + 1];
			}
		// Subtracting one from the used count.
		--m_nUsedCount;
	}

	void Remove(T data)
	{
		//Iterating through the array.
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			// Checking if the inputted data compares equally to the data in the index.
			if (data == m_pData[i])
			{
				// Using the erase function to erase the data.
				Erase(i);
			}
		}
	}

	void Clear()
	{
		// Setting the used count to 0, marking all the slots as avalible.
		m_nUsedCount = 0;
	}

	T PopBack()
	{
		// Defining a new data type to the data at the end of the array.
		T data = m_pData[m_nUsedCount - 1];
		// Subtracting one from the used count.
		--m_nUsedCount;
		// Returning the data.
		return data;
	}

	T PopFront()
	{
		// Defining a data type to the data in index 0.
		T data = m_pData[0];
		// Iterating through the array, starting from 0.
		for (int i = 0; i < m_nUsedCount; ++i)
		{
			// Swapping the data from the right index into the left.
			m_pData[i] = m_pData[i + 1];
		}
		// Subtracting one from the used count.
		--m_nUsedCount;
		// Returning the data.
		return data;
	}

	T First()
	{
		// Defining a data type to the data in index 0.
		T data = m_pData[0];
		return data;
	}

	T Middle()
	{
		// Defining a data type to the data in the middle of the array, by halving the usedCount as an index.
		T data = m_pData[m_nUsedCount / 2];
		return data;
	}

	T Last()
	{
		// Defining a data type to the data at the end of the array, by getting the used count and subtracting one and using it as an index.
		T data = m_pData[m_nUsedCount - 1];
		// Returing the data.
		return data;
	}

	int GetSize()
	{
		// Getter for the amount of items in the array.
		return m_nUsedCount;
	}

	T& operator[](int index)
	{
		// Setting the subscript operator to use the class as an array.
		return m_pData[index];
	}

	bool IsEmpty()
	{
		// A boolean to determine whether the array is empty.
		return m_nUsedCount <= 0;
	}

	T ReturnDataFromIndex(int index)
	{
		// Using a binary search to get the data from the specified index.
		int L = 0;            // left side
		int R = m_nUsedCount; // right side
		int M = 0;			  // middle
		// Checks the middle of the list for the specified index, and loops through until the middle has been reached.
		while (L <= R && M != index)
		{
			// Setting the middle.
			M = (L + R) / 2;
			// If the middle is less then the index, discard the left side.
			if (M < index)
			{
				L = M + 1;
			}
			// If the middle is greather then the index, discard the right side.
			else if (M > index)
			{
				R = M - 1;
			}
		}
		// Return the data from the final middle destination.
		return m_pData[M];
	}

	// Adds a copy of each index from one dynamic array to another.
	void AddAll(DynamicArray<T> arr)
	{
		for (int i = 0; i < arr.GetSize(); ++i)
		{
			PushBack(arr[i]);
		}
	}

	/* Make sure to include functional!
	   Start should always = 0, and end should always be GetSize() - 1.
	   Syntax for the Lambda function:
							  - Data to compare / Pivot data / Side we comparing (true = left, false = right).
			auto compareLeft = [] (T* &toCompare, T* &pivot, bool left)
			{
				if left
					if(toCompare < pivot)
				else
					if(toCompare > pivot)
			}
		And the same for compare right.
	*/
	void QuickSort(int start, int end, std::function<bool(T&, T&, bool)> compare)
	{
		// Left = Starting Point.
		int nLeft = start;
		// Right = Ending Point.
		int nRight = end;
		// Pivot being the middle of the array.
		T pivot = m_pData[(start + end) / 2];

		/* Partition */
		// Rearranging the elements so that the elements less then the pivot go to the left,
		// and the elements greater then the pivot go to the right. Anything equal to the pivot
		// will stay in its current position.
		while (nLeft <= nRight)
		{
			// Checking each element to determine if it his less then the pivot, moving forward one position after every check.
			// Then doing the same for each element to the right of the pivot, but moving backwards one position after every check.

			while (compare(m_pData[nLeft], pivot, true))
				++nLeft;
			while (compare(m_pData[nRight], pivot, false))
				--nRight;

			if (nLeft <= nRight)
			{
				// If the value on the left is less then or equal to the one on the right, then swap it.
				Swap(nLeft, nRight);
				// Shrinking the checking size.
				++nLeft;
				--nRight;
			}
		};

		/* Recursion */
		// Looping back through the array to sort both the left side with the right side.
		if (start < nRight)
			QuickSort(start, nRight, compare);
		if (nLeft < end)
			QuickSort(nLeft, end, compare);
	}

	// Swapping position 1 with position 2.
	void Swap(int pos1, int pos2)
	{
		T temp = m_pData[pos1];
		m_pData[pos1] = m_pData[pos2];
		m_pData[pos2] = temp;
	}

	// Returns the array of data. 
	T* GetArray()
	{
		return m_pData;
	}

private:
	void Resize()
	{
		// Defining a new a new pointer array to be double the size of the previous array.
		T* pBiggerArray = new T[m_nTotalSize * 2];

		// Coping the data from the previous array into the bigger array.
		memcpy_s(pBiggerArray, sizeof(T) * m_nTotalSize * 2, m_pData, sizeof(T) * m_nTotalSize);

		// Deleting the data in the previous array.
		delete[] m_pData;

		// Setting the value of the previous array to the new bigger array.
		m_pData = pBiggerArray;

		// Doubling the size of the array.
		m_nTotalSize *= 2;
	}

	// Declaring a pointer data type to use as an array.
	T* m_pData;
	// Declaring 2 integars to hold the total size of the array, and how many slots we have in use.
	int m_nTotalSize;
	int m_nUsedCount;
	bool m_bShouldDelete;
};