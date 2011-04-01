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
			ConditionOperatorEqual,
			ConditionOperatorDifferent,
			ConditionOperatorSmaller,
			ConditionOperatorBigger,
			ConditionOperatorBiggerOrEqual,
			ConditionOperatorSmallerOrEqual,
			ConditionOperatorUndefined
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
			Duration,
			Time,
			Undefined
		};
		Q_ENUMS( DataMiningOperation )

		ConditionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );


		static ConditionOperator translateConditionOperator( const QString &text );
		static DataMiningOperation translateDataMiningOperator( const QString &text );

	protected:
		ConditionOperator _operator;
		virtual bool isTrue() const = 0;

	};

}

#endif  //_CONDITIONNODE_H
