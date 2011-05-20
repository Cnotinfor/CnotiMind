#include "PropertiesModel.h"
#include "../Brain.h"


namespace CnotiMind
{

	PropertiesModel::PropertiesModel( const Brain* brain, QObject *parent) :
		QAbstractTableModel( parent ),
		_brain( brain )
	{

	}

	int PropertiesModel::rowCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return _brain->_properties.size();
	}


	int PropertiesModel::columnCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return 2;
	}

	QVariant PropertiesModel::data(const QModelIndex &index, int role) const
	{
		if( !index.isValid() )
		{
			return QVariant();
		}

		switch(role)
		{
			case Qt::DisplayRole:

				// Iterates hash values, n rows
				QHashIterator<QString, QString> i(_brain->_properties);
				int r = index.row();
				while( r >= 0 )
				{
					i.next();
					r--;
				}

				if( index.column() == 0 )
				{
					return i.key();
				}
				else  // Column 1
				{
					return i.value();
				}
				break;
		}
		return QVariant();
	}

	QVariant PropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
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
				return "Name";
			}
			else
			{
				return "Value";
			}
		}
		else // Vertical
		{
			return section + 1;
		}
	}

	void PropertiesModel::update()
	{
		emit layoutChanged();
	}

}
