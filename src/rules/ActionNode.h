#if !defined(_ACTIONNODE_H)
#define _ACTIONNODE_H

#include <QtCore/QString>
#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class ActionNode : public RuleNode
	{
		Q_OBJECT

	public:
		ActionNode( const QString& key, const QString& value, Brain* brain, QObject* parent );

		void exec();
		RuleNodeTypes type() const;
	};

}

#endif  //_ACTIONNODE_H
