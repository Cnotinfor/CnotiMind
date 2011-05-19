#include "PerceptionsModel.h"
#include "../Brain.h"
#include "../Perception.h"

namespace CnotiMind
{

	PerceptionsModel::PerceptionsModel( QObject *parent) :
		QAbstractTableModel( parent )
	{

	}

	int PerceptionsModel::rowCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return _perceptions.size();
	}


	int PerceptionsModel::columnCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return 2;
	}

	QVariant PerceptionsModel::data(const QModelIndex &index, int role) const
	{
		if( !index.isValid() )
		{
			return QVariant();
		}

		switch(role)
		{
			case Qt::DisplayRole:

				// Iterates hash values, n rows
				QListIterator<Perception> i( _perceptions );
				int r = index.row();
				Perception p;
				while( r >= 0 )
				{
					p = i.next();
					r--;
				}

				if( index.column() == 0 )
				{
					return p.name();
				}
				else  // Column 1
				{
					return p.value();
				}
				break;
		}
		return QVariant();
	}

	QVariant PerceptionsModel::headerData(int section, Qt::Orientation orientation, int role) const
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
			return section;
		}
	}

	void PerceptionsModel::update( const Perception& p )
	{
		_perceptions.append( p );
		insertRow( _perceptions.size() - 1, QModelIndex() );
	}

	bool PerceptionsModel::insertRow(int row, const QModelIndex &parent)
	{
		Q_UNUSED( parent );

		beginInsertRows( parent, row, row );
		endInsertRows();

		return true;
	}

}
