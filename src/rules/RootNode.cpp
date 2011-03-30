#include <QtCore/QString>

#include "RootNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RootNode::RootNode(const QString& key, const QString& value, Brain* brain, QObject* parent):
		RuleNode(key, value, brain, parent)
	{

	}

	void RootNode::exec()
	{
		const QObjectList& objs = children();

		// calls exec for each children;

		//qobject_cast<>
	}

	RuleNode::RuleNodeTypes RootNode::type() const
	{
		return Root;
	}

	bool RootNode::isRoot() const
	{
		return true;
	}


}
