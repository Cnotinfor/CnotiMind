#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QAbstractTableModel>
#include "../CnotiMind.h"
#include "../MemoryEvent.h"

namespace CnotiMind
{
	class Brain;

	class MemoryModel : public QAbstractTableModel
	{
		Q_OBJECT
	public:
		MemoryModel( MemoryType memory, const Brain* brain, QObject *parent = 0 );

		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		void update();

	private:
		const Brain* _brain;
		const QList<MemoryEvent>* _memory;
	};

}
#endif // MEMORYMODEL_H
