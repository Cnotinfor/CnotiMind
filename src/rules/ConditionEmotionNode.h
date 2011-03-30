#if !defined(_CONDITIONEMOTIONNODE_H)
#define _CONDITIONEMOTIONNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionEmotionNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionEmotionNode( const QString& emotion, const QString& value, ConditionOperator op, Brain* brain, QObject* parent );
		void exec();
		RuleNodeTypes type() const;

	protected:
		bool isTrue() const;
	};

}
#endif  //_CONDITIONEMOTIONNODE_H
