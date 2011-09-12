#if !defined(_CONDITIONNODE_H)
#define _CONDITIONNODE_H

#include <QtCore/QString>
#include <QtCore/QHash>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class ConditionNode : public RuleNode
	{
		Q_OBJECT

	public:

		ConditionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;



	protected:
		QString _key;
		QString _value;
		ConditionOperator _operator;
		virtual bool isTrue() = 0;

		qreal _valueNumeric;
		bool _isValueNumeric;

	};

}

#endif  //_CONDITIONNODE_H
