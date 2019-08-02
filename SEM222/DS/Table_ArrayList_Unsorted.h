#pragma once
#include "heap_monitor.h"
#include "Table_List.h"
#include "ArrayList.h"
namespace DS
{// ako vlozim do neutriedenej tak tam to tak je
	template <typename K, typename T>
	class Table_ArrayList_Unsorted :
		public Table_List<K, T>
	{
	public:
		Table_ArrayList_Unsorted(const CompareFunction<K> compare);
		Table_ArrayList_Unsorted(const Table_ArrayList_Unsorted<K, T>& other);

		Structure* clone() const override;
		virtual Table_ArrayList_Unsorted<K, T>& operator=(const Table_ArrayList_Unsorted<K, T>& other);

		T remove(const K& key) override;
	};

	template<typename K, typename T>
	Table_ArrayList_Unsorted<K, T>::Table_ArrayList_Unsorted(const CompareFunction<K> compare) : Table_List<K, T>(new ArrayList<TableItem<K, T>*>, compare)
	{

	}

	template<typename K, typename T>
	Table_ArrayList_Unsorted<K, T>::Table_ArrayList_Unsorted(const Table_ArrayList_Unsorted<K, T>& other) : Table_List<K, T>(other)
	{

	}

	template<typename K, typename T>
	Structure * Table_ArrayList_Unsorted<K, T>::clone() const
	{
		return new  Table_ArrayList_Unsorted <K, T>(*this);
	}

	template<typename K, typename T>
	Table_ArrayList_Unsorted<K, T>& Table_ArrayList_Unsorted<K, T>::operator=(const Table_ArrayList_Unsorted<K, T>& other)
	{
		*this = other;
		return *this;
	}

	template<typename K, typename T>
	T Table_ArrayList_Unsorted<K, T>::remove(const K & key)
	{

		int index = indexOfKey(key);
		if (index == -1)
			throw std::out_of_range("Prvok s takymto klucom v tabulke nie je");
		else {
			T pom = (*list_)[index]->getData();
			if (index != list_->size()) {

				DSRoutines::swap((*list_)[list_->size() - 1], (*list_)[index]);


			}
			list_->removeAt(list_->size() - 1);
			

			return pom;
		}
	}
}

