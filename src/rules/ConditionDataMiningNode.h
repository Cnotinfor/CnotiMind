#if !defined(_CONDITIONDATAMININGNODE_H)
#define _CONDITIONDATAMININGNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionDataMiningNode : public ConditionNode
	{
		Q_OBJECT

	public:

		ConditionDataMiningNode(const QString& key, const QString& value, ConditionOperator op, DataMiningOperation _dataMiningOperator, Brain* brain, QObject* parent);
		ConditionDataMiningNode(const QString& key, const QString& value, ConditionOperator op, DataMiningOperation _dataMiningOperator, const QString& variable, Brain* brain, QObject* parent);

		void exec();
		RuleNodeTypes type() const;
		const QString& variable() const;

	protected:
		int _dataMiningOperator;
		QString _variable;
		bool isTrue() const;
	};

}

#endif  //_CONDITIONDATAMININGNODE_H
