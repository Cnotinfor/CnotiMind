#if !defined(_ROOTNODE_H)
#define _ROOTNODE_H

#include <QtCore/QString>

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class RootNode : public RuleNode
	{
		Q_OBJECT

	public:
		RootNode(const QString& key, const QString& value, Brain* brain, QObject* parent);
		void exec();
		RuleNodeTypes type() const;
		bool isRoot() const;
	};

}
#endif  //_ROOTNODE_H
