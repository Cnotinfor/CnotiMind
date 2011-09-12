#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "RootNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RootNode::RootNode( Brain* brain, QObject* parent ):
		RuleNode( brain, parent)
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

	/*
		Reimplementation. This is the only node that it is root
	*/
	bool RootNode::isRoot() const
	{
		return true;
	}

	/*
		Debug information
	*/
	QString RootNode::info( int depth) const
	{
		return "Root" + RuleNode::info( depth );
	}

	RootNode *RootNode::fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject *parent)
	{
		Q_UNUSED(atts);

		if( qName.compare( "Rules", Qt::CaseInsensitive ) == 0 )
		{
			return new RootNode(brain, parent);
		}
		return NULL;
	}
}
