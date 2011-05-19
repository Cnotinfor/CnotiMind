#ifndef PERCEPTIONSMODEL_H
#define PERCEPTIONSMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "../Perception.h"

namespace CnotiMind
{
	class Brain;

	class PerceptionsModel : public QAbstractTableModel
	{
		Q_OBJECT
	public:
		explicit PerceptionsModel( QObject *parent = 0 );

		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		void update( const Perception& p );
		bool insertRow(int row, const QModelIndex &parent);

	private:
		QList<Perception> _perceptions;
	};

}

#endif // PERCEPTIONSMODEL_H
