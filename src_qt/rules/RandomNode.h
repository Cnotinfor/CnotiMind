#ifndef RANDOMNODE_H
#define RANDOMNODE_H

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class RandomNode : public RuleNode
	{
		Q_OBJECT
	public:
		RandomNode(Brain* brain, QObject *parent = 0);


		virtual void exec() = 0;
		virtual void exec( QHash<QString, QString>& variables ) = 0;

		virtual QString info( int depth = 0 ) const = 0;

	};

}

#endif // RANDOMNODE_H
