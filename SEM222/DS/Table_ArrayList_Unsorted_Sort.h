#pragma once
#include "Table_ArrayList_Unsorted.h"
#include "heap_monitor.h"
namespace DS {//to iste ako unsorted ale viem tu pouzit nejaky sort 
	template<typename K, typename T>
	using SortCompareFunction = int(*)(TableItem<K, T> &a, TableItem<K, T> &b);

	template <typename K, typename T>
	class Table_ArrayList_Unsorted_Sort :
		public Table_ArrayList_Unsorted<K, T> {
	public:
		Table_ArrayList_Unsorted_Sort(const CompareFunction<K> compare);
		Table_ArrayList_Unsorted_Sort(const Table_ArrayList_Unsorted_Sort &other);
		void sort(SortCompareFunction<K, T> compare);
	private:
		void quick(int left, int right, SortCompareFunction<K, T> compare);

	};

	template<typename K, typename T>
	Table_ArrayList_Unsorted_Sort<K, T>::Table_ArrayList_Unsorted_Sort(const CompareFunction<K> compare) :
		Table_ArrayList_Unsorted(compare)
	{
	}

	template<typename K, typename T>
	inline Table_ArrayList_Unsorted_Sort<K, T>::Table_ArrayList_Unsorted_Sort(const Table_ArrayList_Unsorted_Sort & other)
	{
		*this = *other;
	}

	template<typename K, typename T>
	inline void Table_ArrayList_Unsorted_Sort<K, T>::sort(SortCompareFunction<K, T> compare)
	{
		quick(0, list_->size() - 1, compare);
	}

	template<typename K, typename T>
	void Table_ArrayList_Unsorted_Sort<K, T>::quick(int left, int right, SortCompareFunction<K, T> compare)
	{


		int i = left;
		int j = right;

		int pivot = ((left + right) / 2);
		TableItem<K, T> pom = (*(*list_)[pivot]);


		while (i <= j) {
			while ((compare((*(*list_)[i]), pom) < 0))
				i++;
			while ((compare((*(*list_)[j]), pom) > 0))
				j--;
			if (i <= j) {

				DSRoutines::swap<TableItem<K, T>*>((*list_)[i], (*list_)[j]);

				i++;
				j--;

			}
		}

		if (left < j)
			quick(left, j, compare);

		if (i< right)
			quick(i, right, compare);
	}


}


