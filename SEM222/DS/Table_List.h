#pragma once
#include "heap_monitor.h"
#include "Table.h"
#include "List.h"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace DS
{// trieda ktora si pamata
	template <typename K, typename T>
	class Table_List :
		public Table<K, T>
	{
	public:
		~Table_List() override;

		virtual Structure* clone() const = 0;
		Structure& operator=(const Structure& other) override;
		Table<K, T>& operator=(const Table<K, T>& other) override;
		virtual Table_List<K, T>& operator=(const Table_List<K, T>& other);

		size_t size() const override;
		T& operator[](const K& key) override;
		const T& operator[](const K& key) const override;

		void insert(const K& key, const T& value) override;
		T remove(const K& key) override;
		bool tryFind(const K& key, T*& value) const override;
		void clear() override;

		Iterator<TableItem<K, T>*> begin() const override;
		Iterator<TableItem<K, T>*> end() const override;
	protected:
		Table_List(List<TableItem<K, T>*>* list, const CompareFunction<K> compare);

		virtual int indexOfKey(const K& key) const;
		List<TableItem<K, T>*> * list_;

		//atributy
	};

	template<typename K, typename T>
	Table_List<K, T>::~Table_List()
	{
		clear();
		delete list_;
	}

	template<typename K, typename T>
	Structure & Table_List<K, T>::operator=(const Structure & other)
	{
		*this = dynamic_cast<const Table_List<K, T>&>(other);
		return *this;
	}

	template<typename K, typename T>
	Table<K, T>& Table_List<K, T>::operator=(const Table<K, T>& other)
	{
		*this = dynamic_cast<const Table_List<K, T>&>(other);
		return *this;
	}

	template<typename K, typename T>
	Table_List<K, T>& Table_List<K, T>::operator=(const Table_List<K, T>& other)
	{


		if (this != &other) {
			clear();
			list_ = other.list_;
			for (TableItem<K, T>* pom : *other.list_) {
				list_->add(new TableItem<K, T>(*pom));
			}

		}
		return *this;
	}

	template<typename K, typename T>
	size_t Table_List<K, T>::size() const
	{
		return list_->size();
	}

	template<typename K, typename T>
	T & Table_List<K, T>::operator[](const K & key)
	{

		int index = indexOfKey(key);
		if (index < list_->size()) {
			if ((*list_)[index]->getKey() == key)
				return (*list_)[index]->getData();
		}

		TableItem<K, T> * pom = new TableItem<K, T>(key, {});
		insert(key, pom->getData());

		return pom->getData();



	}

	template<typename K, typename T>
	const T & Table_List<K, T>::operator[](const K & key) const
	{
		int index = indexOfKey(key);
		if (index < list_->size()) {
			if ((*list_)[index]->getKey() == key)
				return (*list_)[index]->getData();
		}
		throw std::out_of_range("Takyto prvok sa v tabulke nenachadza");

	}

	template<typename K, typename T>
	void Table_List<K, T>::insert(const K & key, const T & value) {
		

		int index = indexOfKey(key);
		if (index < list_->size()) {

			if ((*list_)[index]->getKey() == key) {

				throw std::invalid_argument("Takyto zaznam uz v tabulke existuje");
			}
			else {
				list_->insert(new TableItem<K, T>(key, value), index);
			}
		}
		else {

			list_->add(new TableItem<K, T>(key, value));
		}

	}

	template<typename K, typename T>
	T Table_List<K, T>::remove(const K & key)
	{
		int index = indexOfKey(key);
		if (index > list_->size() - 1) {
			throw std::invalid_argument("Takyto prvok sa v tabulke nenachadza");
		}
		else {
			if ((*list_)[index]->getKey() == key) {
				T pom = (*list_)[index]->getData();
				list_->removeAt(index);

				return pom;
			}
			else {
				throw std::invalid_argument("Takyto prvok sa v tabulke nenachadza");
			}

		}

	}

	template<typename K, typename T>
	bool Table_List<K, T>::tryFind(const K & key, T* & value) const
	{
		int index = indexOfKey(key);
		if (index < list_->size()) {
			if ((*list_)[index]->getKey() == key) {
				value = &(*list_)[index]->getData();
				return true;
			}
			else {
				throw std::invalid_argument("Takyto prvok sa v tabulke nenachadza");
				return false;
			}
		}
		else {
			throw std::invalid_argument("Takyto prvok sa v tabulke nenachadza");
			return false;
		}
	}

	template<typename K, typename T>
	void Table_List<K, T>::clear()
	{
		for (TableItem<K, T> * pom : *list_) {
			delete pom;
		}
		list_->clear();
	}

	template<typename K, typename T>
	Iterator<TableItem<K, T>*> Table_List<K, T>::begin() const
	{
		return list_->begin();
	}

	template<typename K, typename T>
	Iterator<TableItem<K, T>*> Table_List<K, T>::end() const
	{
		return list_->end();
	}

	template<typename K, typename T>
	Table_List<K, T>::Table_List(List<TableItem<K, T>*>* list, const CompareFunction<K> compare) :Table<K, T>(compare), list_(list)
	{

	}

	template<typename K, typename T>
	int Table_List<K, T>::indexOfKey(const K & key) const
	{
		int index = 0;
		for (TableItem<K, T> * pom : *list_) {

			if (pom->getKey() == key)
				return index;
			index++;
		}
		return index;
	}
}