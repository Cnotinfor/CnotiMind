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

	protected:
		bool isTrue();

	};

}
#endif // CONDITIONPROPERTYNODE_H
