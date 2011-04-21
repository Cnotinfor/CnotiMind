#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "RootNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RootNode::RootNode( Brain* brain, QObject* parent ):
		RuleNode("Root", "", brain, parent)
	{
	}

	void RootNode::exec()
	{
		execChildren();
	}

	/*
		This method should not be called

		Unless in the future, variable are passed already to the root node.
	*/
	void RootNode::exec( QHash<QString, QString>& variables )
	{
		execChildren( variables );
	}

	bool RootNode::isRoot() const
	{
		return true;
	}

	QString RootNode::info( int depth) const
	{
		return "Root" + RuleNode::info( depth );
	}
}
