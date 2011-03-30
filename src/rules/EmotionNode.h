#if !defined(_EMOTIONNODE_H)
#define _EMOTIONNODE_H

#include <QtCore/QString>

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class EmotionNode : public RuleNode
	{
		Q_OBJECT

	public:
		EmotionNode(const QString& key, const QString& value, Brain* brain, QObject* parent);
		EmotionNode(const QString& key, const QString& value, int max, int min, Brain* brain, QObject* parent);

		void exec();
		RuleNodeTypes type() const;

	protected:
		int _min;
		int _max;
		int _valueInt;
	};

}
#endif  //_EMOTIONNODE_H
