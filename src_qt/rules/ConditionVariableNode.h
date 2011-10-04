#ifndef CONDITIONVARIABLENODE_H
#define CONDITIONVARIABLENODE_H

#include "ConditionNode.h"

namespace CnotiMind
{

	class ConditionVariableNode : public ConditionNode
	{
		Q_OBJECT
	public:

		ConditionVariableNode(const QString& variable, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;

		static ConditionVariableNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:

		QString _variable;
		QString _value;
		qreal _valueNumeric;
		bool _isValueNumeric;

		bool isTrue();
		bool isTrue( QHash<QString,QString>& variables );

	};

}
#endif // CONDITIONVARIABLENODE_H
