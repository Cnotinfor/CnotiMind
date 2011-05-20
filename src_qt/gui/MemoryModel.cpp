#include "MemoryModel.h"
#include "../Brain.h"

namespace CnotiMind
{

	MemoryModel::MemoryModel( MemoryType memory, const Brain* brain, QObject *parent) :
		QAbstractTableModel( parent ),
		_brain( brain ),
		_memory( memory == CnotiMind::LongTermMemory ? &brain->_longTermMemory : &brain->_workingMemory )
	{

	}

	int MemoryModel::rowCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return _memory->size();
	}


	int MemoryModel::columnCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return 2;
	}

	QVariant MemoryModel::data(const QModelIndex &index, int role) const
	{
		if( !index.isValid() )
		{
			return QVariant();
		}

		switch(role)
		{
			case Qt::DisplayRole:

				MemoryEvent me = _memory->at( _memory->size() - index.row() - 1 );

				if( index.column() == 0 )
				{
					return me.event();
				}
				else  // Column 1
				{
					return me.value();
				}
				break;
		}
		return QVariant();
	}

	QVariant MemoryModel::headerData(int section, Qt::Orientation orientation, int role) const
	{
		//  role == Qt::SizeHintRole - to change the size
		if( role != Qt::DisplayRole  )
		{
			return QVariant();
		}

		if( orientation == Qt::Horizontal )
		{
			if( section == 0 )
			{
				return "Event";
			}
			else
			{
				return "Value";
			}
		}
		else // Vertical
		{
			return _memory->size() - section;
		}
	}

	void MemoryModel::update()
	{
		emit layoutChanged();
	}

}
