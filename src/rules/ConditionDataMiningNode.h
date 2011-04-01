#if !defined(_CONDITIONDATAMININGNODE_H)
#define _CONDITIONDATAMININGNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"
#include "../Brain.h"

namespace CnotiMind
{


	class ConditionDataMiningNode : public ConditionNode
	{
		Q_OBJECT

	public:

		ConditionDataMiningNode(const QString& key, const QString& value, ConditionOperator op, DataMiningOperation _dataMiningOperator, Brain::MemoryType memory, Brain* brain, QObject* parent);
		ConditionDataMiningNode(const QString& key, const QString& value, ConditionOperator op, DataMiningOperation _dataMiningOperator, Brain::MemoryType memory, const QString& variable, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		const QString& variable() const;


	protected:
		int _dataMiningOperator;
		QString _variable;
		QString _result;
		Brain::MemoryType _memory;
		bool isTrue() const;
	};

}

#endif  //_CONDITIONDATAMININGNODE_H
