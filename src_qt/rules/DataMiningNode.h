#ifndef DATAMININGNODE_H
#define DATAMININGNODE_H

#include <QtCore/QVariant>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class DataMiningNode : public RuleNode
	{
		Q_OBJECT

	public:
		DataMiningNode(const QString& key, const QString& value, DataMiningOperation dataMiningOperation,
					   MemoryType memory, const QString& variable, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;


	protected:
		bool isTrue();

		QString _event;
		QString _value;
		const DataMiningOperation _operation;
		const MemoryType _memory;
		const QString _variable;
		qreal _valueNumeric;
		bool _isValueNumeric;
		QVariant _result;
	};

}

#endif // DATAMININGNODE_H
