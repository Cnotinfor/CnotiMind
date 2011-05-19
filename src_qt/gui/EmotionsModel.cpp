#include "EmotionsModel.h"
#include "../Brain.h"
#include "../Emotion.h"

namespace CnotiMind
{

	EmotionsModel::EmotionsModel( const Brain* brain, QObject *parent) :
		QAbstractTableModel( parent ),
		_brain( brain )
	{

	}

	int EmotionsModel::rowCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return _brain->_emotions.size();
	}


	int EmotionsModel::columnCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);

		return 2;
	}

	QVariant EmotionsModel::data(const QModelIndex &index, int role) const
	{
		if( !index.isValid() )
		{
			return QVariant();
		}

		switch(role)
		{
			case Qt::DisplayRole:

				// Iterates hash values, n rows
				QListIterator<Emotion> i(_brain->_emotions);
				int r = index.row();
				Emotion e;
				while( r >= 0 )
				{
					e = i.next();
					r--;
				}

				if( index.column() == 0 )
				{
					return e.key();
				}
				else  // Column 1
				{
					return e.value();
				}
				break;
		}
		return QVariant();
	}

	QVariant EmotionsModel::headerData(int section, Qt::Orientation orientation, int role) const
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

	void EmotionsModel::update()
	{
		emit layoutChanged();
	}

}
