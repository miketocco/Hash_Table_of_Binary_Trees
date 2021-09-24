#include <iostream>
#include "HashTable.h"
#include <math.h>

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize) : tableSize(initTableSize)
{
	dataTable = new BSTree<DataType, KeyType>[tableSize];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	// copy constructor
	*this = other;
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if (*this != other)
	{
		tableSize = other.tableSize;
		dataTable = new BSTree<DataType, KeyType>[tableSize];
		for (int i = 0; i < tableSize; i++) {

			dataTable[i] = other.dataTable[i];

		}
	}
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::copyTable(const HashTable& source)
{
	tableSize = source.tableSize;
	dataTable = new BSTree<DataType, KeyType>[tableSize];
	for (int i = 0; i < tableSize; i++) {

		dataTable[i] = source.dataTable[i];

	}
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	clear();
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	unsigned int loc = DataType::hash(newDataItem.getKey()) % tableSize;

	dataTable[loc].insert(newDataItem);
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	if (!isEmpty())
	{
		unsigned int loc = DataType::hash(deleteKey) % tableSize;
		return dataTable[loc].remove(deleteKey);		
	}
	return false;
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	if (!isEmpty())
	{
		unsigned int loc = DataType::hash(searchKey) % tableSize;
		return dataTable[loc].retrieve(searchKey, returnItem);
	}
	return false;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	for (int i = 0; i < tableSize; i++) {
		dataTable[i].clear();
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for (int i = 0; i < tableSize; i++) {
		if (! dataTable[i].isEmpty() )
			return 0;
	}
	
	return 1;
}


template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
	if (isEmpty())
		return 0;

	double totalKeys = 0; // N
	double sumOfKeys = 0;
	double mean = 0; // u
	double numerator = 0; // summation of (xSubI - u)^2
	double standDev = 0;

	for (int i = 0; i < tableSize; i++)
	{
		totalKeys += dataTable[i].getCount();
		sumOfKeys += dataTable[i].sumKeys();
	}

	mean = sumOfKeys / totalKeys;

	for (int i = 0; i < tableSize; i++)
	{
		numerator += dataTable[i].getNumerator(mean);
	}

	standDev = sqrt(numerator / totalKeys);

	return standDev;

}


template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {

	if (!isEmpty()) {
		for (int i = 0; i < tableSize; i++) {

			cout << "Cell " << i + 1 << ": " << endl;

			dataTable[i].showStructure();

			cout << endl << endl << endl;
		}
	}
	else
		cout << "Empty table" << endl;
}
