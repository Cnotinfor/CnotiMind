#if !defined(_CONDITIONEMOTIONNODE_H)
#define _CONDITIONEMOTIONNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"
#include "../Emotion.h"

namespace CnotiMind
{
	class Brain;

	class ConditionEmotionNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionEmotionNode( const QString& emotion, const QString& value, ConditionOperator op, Brain* brain, QObject* parent );

	protected:
		bool isTrue() const;
		bool testEmotion( const Emotion& e ) const;

		int _valueInt;
	};

}
#endif  //_CONDITIONEMOTIONNODE_H
