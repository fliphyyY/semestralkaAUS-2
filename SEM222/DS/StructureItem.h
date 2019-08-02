#pragma once
#include "heap_monitor.h"
namespace DS
{
#pragma region DataItem
	template<typename T>
	class DataItem
	{
	public:
		DataItem(const T& data);
		DataItem(const DataItem<T>& other);
		virtual ~DataItem();
		T& getData();
		const T& getData() const;
		void setData(const T& data);
	private:
		T data_;
	};

	template<typename T>
	DataItem<T>::DataItem(const T& data) :
		data_(data)
	{
	}

	template<typename T>
	DataItem<T>::DataItem(const DataItem<T>& other) :
		DataItem(other.data_)
	{
	}

	template<typename T>
	DataItem<T>::~DataItem()
	{
	}

	template<typename T>
	T& DataItem<T>::getData()
	{
		return data_;
	}

	template<typename T>
	const T & DataItem<T>::getData() const
	{
		return data_;
	}

	template<typename T>
	void DataItem<T>::setData(const T & data)
	{
		data_ = data;
	}
#pragma endregion DataItem


#pragma region LinkedItem
	template<typename T>
	class LinkedItem :
		public DataItem<T>
	{
	public:
		LinkedItem(const T& data);
		~LinkedItem() override;
		LinkedItem<T>* getNext() const;
		void setNext(LinkedItem<T>* next);
	private:
		LinkedItem<T>* next_;
	};

	template<typename T>
	LinkedItem<T>::LinkedItem(const T& data) :
		DataItem<T>(data),
		next_(nullptr)
	{
	}

	template<typename T>
	LinkedItem<T>::~LinkedItem()
	{
		next_ = nullptr;
	}

	template<typename T>
	typename LinkedItem<T>* LinkedItem<T>::getNext() const
	{
		return next_;
	}

	template<typename T>
	void LinkedItem<T>::setNext(LinkedItem<T>* next)
	{
		next_ = next;
	}
#pragma endregion LinkedItem


#pragma region PriorityItem
	template<typename T>
	class PriorityItem :
		public DataItem<T>
	{
	public:
		PriorityItem(const int priority, const T& data);
		PriorityItem(const PriorityItem<T>& other);
		~PriorityItem() override;
		const int getPriority() const;
	private:
		int priority_;
	};

	template<typename T>
	PriorityItem<T>::PriorityItem(const int priority, const T& data) :
		DataItem<T>(data),
		priority_(priority)
	{
	}

	template<typename T>
	PriorityItem<T>::PriorityItem(const PriorityItem<T>& other) :
		DataItem<T>(other),
		priority_(other.priority_)
	{
	}

	template<typename T>
	PriorityItem<T>::~PriorityItem()
	{
	}

	template<typename T>
	const int PriorityItem<T>::getPriority() const
	{
		return priority_;
	}
#pragma endregion PriorityItem


#pragma region TableItem
	template<typename K, typename T>
	class TableItem :
		public DataItem<T>
	{
	public:
		TableItem(const K& key, const T& data);
		TableItem(const TableItem<K, T>& other);
		~TableItem() override;
		const K& getKey() const;
	private:
		K key_;
	};

	template<typename K, typename T>
	TableItem<K, T>::TableItem(const K& key, const T& data) :
		DataItem<T>(data),
		key_(key)
	{
	}

	template<typename K, typename T>
	TableItem<K, T>::TableItem(const TableItem<K, T>& other) :
		DataItem<T>(other),
		key_(other.key_)
	{
	}

	template<typename K, typename T>
	TableItem<K, T>::~TableItem()
	{
	}

	template<typename K, typename T>
	const K& TableItem<K, T>::getKey() const
	{
		return key_;
	}
#pragma endregion TableItem


#pragma region BTNode
	template<typename T>
	class BTNode :
		public DataItem<T>
	{
	public:
		BTNode(const T& data);
		BTNode(const BTNode<T>& other);
		~BTNode() override;
		virtual BTNode<T>* clone() const;

		BTNode<T>* getParent() const;
		void resetParent();
		BTNode<T>* getLSon() const;
		void setLSon(BTNode<T>* lSon);
		BTNode<T>* getRSon() const;
		void setRSon(BTNode<T>* rSon);
		bool isLSon(const BTNode<T>* node) const;
		bool isRSon(const BTNode<T>* node) const;
	private:
		BTNode<T>* parent_;
		BTNode<T>* lSon_;
		BTNode<T>* rSon_;
	};

	template<typename T>
	BTNode<T>::BTNode(const T& data) :
		DataItem<T>(data),
		parent_(nullptr),
		lSon_(nullptr),
		rSon_(nullptr)
	{
	}

	template<typename T>
	BTNode<T>::BTNode(const BTNode<T>& other) :
		DataItem<T>(other),
		parent_(other.parent_),
		lSon_(other.lSon_),
		rSon_(other.rSon_)
	{
	}

	template<typename T>
	BTNode<T>::~BTNode()
	{
		parent_ = nullptr;
		lSon_ = nullptr;
		rSon_ = nullptr;
	}

	template<typename T>
	BTNode<T>* BTNode<T>::clone() const
	{
		return new BTNode<T>(*this);
	}

	template<typename T>
	BTNode<T>* BTNode<T>::getParent() const
	{
		return parent_;
	}

	template<typename T>
	void BTNode<T>::resetParent()
	{
		parent_ = nullptr;
	}

	template<typename T>
	BTNode<T>* BTNode<T>::getLSon() const
	{
		return lSon_;
	}

	template<typename T>
	void BTNode<T>::setLSon(BTNode<T>* lSon)
	{
		lSon_ = lSon;
		if (lSon_ != nullptr)
		{
			lSon_->parent_ = this;
		}
	}

	template<typename T>
	BTNode<T>* BTNode<T>::getRSon() const
	{
		return rSon_;
	}

	template<typename T>
	void BTNode<T>::setRSon(BTNode<T>* rSon)
	{
		rSon_ = rSon;
		if (rSon_ != nullptr)
		{
			rSon_->parent_ = this;
		}
	}
	template<typename T>
	bool BTNode<T>::isLSon(const BTNode<T>* node) const
	{
		return node != nullptr ? (this == node->getLSon() ? true : false) : false;
	}
	template<typename T>
	bool BTNode<T>::isRSon(const BTNode<T>* node) const
	{
		return node != nullptr ? (this == node->getRSon() ? true : false) : false;
	}
#pragma endregion BTNode


#pragma region TreapNode
	template<typename K, typename T>
	class TreapNode :
		public BTNode<TableItem<K, T>*>
	{
	public:
		TreapNode(TableItem<K, T>* data, const int priority);
		TreapNode(const TreapNode<K, T>& other);
		~TreapNode() override;

		virtual BTNode<TableItem<K, T>*>* clone() const;
		int getPriority() const;
	private:
		int priority_;
	};

	template<typename K, typename T>
	TreapNode<K, T>::TreapNode(TableItem<K, T>* data, const int priority) :
		BTNode<TableItem<K, T>*>(data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	TreapNode<K, T>::TreapNode(const TreapNode<K, T>& other) :
		BTNode<TableItem<K, T>*>(other),
		priority_(other.priority_)
	{
	}

	template<typename K, typename T>
	TreapNode<K, T>::~TreapNode()
	{
	}

	template<typename K, typename T>
	BTNode<TableItem<K, T>*>* TreapNode<K, T>::clone() const
	{
		return new TreapNode<K, T>(*this);
	}

	template<typename K, typename T>
	int TreapNode<K, T>::getPriority() const
	{
		return priority_;
	}
#pragma endregion TreapNode
}
