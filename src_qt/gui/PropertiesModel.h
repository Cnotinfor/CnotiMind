#ifndef PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include <QAbstractTableModel>

namespace CnotiMind
{
	class Brain;

	class PropertiesModel : public QAbstractTableModel
	{
		Q_OBJECT
	public:
		PropertiesModel( const Brain* brain, QObject *parent = 0);

		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		void update();

	signals:

	public slots:

	private:
		const Brain* _brain;

	};

}
#endif // PROPERTIESMODEL_H
