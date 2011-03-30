#if !defined(_CONDITIONNODE_H)
#define _CONDITIONNODE_H

#include <QtCore/QString>

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionNode : public RuleNode
	{
		Q_OBJECT

	public:

		enum ConditionOperator
		{
			Equal,
			Different,
			Smaller,
			Bigger,
			EqualOrBigger,
			EqualOrSmaller
		};
		Q_ENUMS( ConditionOperator )

		enum DataMiningOperation
		{
			Max,
			Min,
			Sum,
			Count,
			Mean,
			Exists,
			Last,
			First,
			Duration
		};
		Q_ENUMS( DataMiningOperation )

		ConditionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		virtual void exec() = 0;
		RuleNodeTypes type() const;


	protected:
		ConditionOperator _operator;
		virtual bool isTrue() = 0;
	};

}

#endif  //_CONDITIONNODE_H
