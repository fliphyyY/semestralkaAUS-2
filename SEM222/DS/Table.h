#pragma once
#include "heap_monitor.h"
#include "Structure.h"
#include "StructureItem.h"
#include "Iterator.h"

namespace DS
{
	template <typename K, typename T>
	class Table :
		public Structure,
		public Iterable<TableItem<K, T>*>
	{
	public:
		~Table() override;

		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& other) override;
		virtual Table<K, T>& operator=(const Table<K, T>& other);

		virtual size_t size() const = 0;
		virtual T& operator[](const K& key) = 0;
		virtual const T& operator[](const K& key) const = 0;

		virtual void insert(const K& key, const T& value) = 0;
		virtual T remove(const K& key) = 0;
		virtual bool tryFind(const K& key, T*& value) const = 0;
		virtual void clear() = 0;

		virtual Iterator<TableItem<K, T>*> begin() const = 0;
		virtual Iterator<TableItem<K, T>*> end() const = 0;
	protected:
		Table(const CompareFunction<K> compare);
		Table(const Table<K, T>& other);

		CompareFunction<K> compare_;
	};

	template<typename K, typename T>
	Table<K, T>::~Table()
	{
		compare_ = nullptr;
	}

	template<typename K, typename T>
	Structure & Table<K, T>::operator=(const Structure & other)
	{
		*this = dynamic_cast<const Table<K, T>&>(other);
		return *this;
	}

	template<typename K, typename T>
	Table<K, T>& Table<K, T>::operator=(const Table<K, T>& other)
	{
		if (this != &other)
		{
			compare_ = other.compare_;
		}
		return *this;
	}

	template<typename K, typename T>
	Table<K, T>::Table(const CompareFunction<K> compare) :
		compare_(compare)
	{
	}

	template<typename K, typename T>
	Table<K, T>::Table(const Table<K, T>& other) :
		compare_(other.compare_)
	{
	}
}

