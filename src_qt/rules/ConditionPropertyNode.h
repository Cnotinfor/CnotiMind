#ifndef CONDITIONPROPERTYNODE_H
#define CONDITIONPROPERTYNODE_H

#include "ConditionNode.h"

namespace CnotiMind
{

	class ConditionPropertyNode : public ConditionNode
	{
		Q_OBJECT
	public:
		explicit ConditionPropertyNode(const QString& property, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		QString info( int depth = 0 ) const;

		static ConditionPropertyNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		bool isTrue();

		QString _property;
		QString _value;
		qreal _valueNumeric;
		bool _isValueNumeric;
	};

}
#endif // CONDITIONPROPERTYNODE_H
