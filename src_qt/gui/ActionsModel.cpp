#include <QString>
#include "ActionsModel.h"
#include "../Brain.h"
#include <QColor>
#include <QBrush>

namespace CnotiMind
{

	ActionsModel::ActionsModel(const Brain* brain, QObject *parent) :
	   QAbstractTableModel( parent ),
	   _brain( brain )
   {

   }

   int ActionsModel::rowCount(const QModelIndex &parent) const
   {
	   Q_UNUSED(parent);

	   return _actions.size();
   }


   int ActionsModel::columnCount(const QModelIndex &parent) const
   {
	   Q_UNUSED(parent);

	   return 2;
   }

	QVariant ActionsModel::data(const QModelIndex &index, int role) const
	{
		if( !index.isValid() )
		{
			return QVariant();
		}

		QPair<QString, QString> p = _actions.value( _actions.size() - index.row() - 1 );

		switch(role)
		{
			case Qt::DisplayRole:
				if( index.column() == 0 )
				{
					return p.first;
				}
				else  // Column 1
				{
					return p.second;
				}
//			case Qt::BackgroundRole:
//				if( _colors.contains( p.first ) )
//				{
//					return QBrush( _colors[p.first] );
//				}
//				else
//				{
//					QColor color( qrand() % 255, qrand() % 255, qrand() % 255 );
//					_colors.insert( p.first, color );
//					return QBrush( color );
//				}
//				break;
		}
		return QVariant();
   }

   QVariant ActionsModel::headerData(int section, Qt::Orientation orientation, int role) const
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
			   return "Action";
		   }
		   else
		   {
			   return "Value";
		   }
	   }
	   else // Vertical
	   {
		   return _actions.size() - section;
	   }
   }

   /*

   */
   void ActionsModel::update( const QString& key, const QString& value )
   {
	   layoutAboutToBeChanged();

	   _actions.append( qMakePair( key, value ) );

	   layoutChanged();

   }

   bool ActionsModel::insertRow(int row, const QModelIndex &parent)
   {
	   Q_UNUSED( parent )

	   beginInsertRows( parent, row, row );
	   endInsertRows();

	   return true;
   }

}
