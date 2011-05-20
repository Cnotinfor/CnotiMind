#ifndef ACTIONSMODEL_H
#define ACTIONSMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QPair>
#include <QHash>
#include <QColor>

namespace CnotiMind
{
	class Brain;

	class ActionsModel : public QAbstractTableModel
	{
		Q_OBJECT
	public:
		explicit ActionsModel( const Brain* brain, QObject *parent = 0 );

		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		QVariant data(const QModelIndex &index, int role) const;

		QVariant headerData(int section, Qt::Orientation orientation, int role) const;

		void update( const QString& key, const QString& value );
		bool insertRow(int row, const QModelIndex &parent);

	private:
		const Brain* _brain;
		QList< QPair<QString, QString> > _actions;
		QHash<QString, QColor> _colors;

	};

}
#endif // ACTIONSMODEL_H
