#if !defined(_CONDITIONEVENTNODE_H)
#define _CONDITIONEVENTNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionEventNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionEventNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		RuleNodeTypes type() const;

	protected:
		bool isTrue();
	};

}
#endif  //_CONDITIONEVENTNODE_H
