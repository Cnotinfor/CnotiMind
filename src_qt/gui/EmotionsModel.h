#ifndef EMOTIONSMODEL_H
#define EMOTIONSMODEL_H

#include <QAbstractTableModel>

namespace CnotiMind
{
	class Brain;

	class EmotionsModel : public QAbstractTableModel
	{
		Q_OBJECT

	public:
		EmotionsModel( const Brain* brain, QObject *parent = 0 );

		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		void update();

	private:
		const Brain* _brain;
	};

}
#endif // EMOTIONSMODEL_H
