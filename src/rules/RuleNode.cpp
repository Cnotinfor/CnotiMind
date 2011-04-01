#include <QtCore/QString>
#include <QtCore/QListIterator>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RuleNode::RuleNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		Node( key, value ),
		QObject( parent ),
		_brain( brain )
	{
	}


	bool RuleNode::isRoot() const
	{
		return false;
	}

	/**
		Executes all children nodes exec
	*/
	void RuleNode::execChildren()
	{
		QListIterator<QObject*> it( children() );

		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );

			node->exec();
		}
	}

	/**
		Executes all children nodes exec.
		It uses the variables
	*/
	void RuleNode::execChildren( QHash<QString, QString>& variables )
	{
		QListIterator<QObject*> it( children() );

		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );

			node->exec( variables );
		}
	}

	/*
		Check if there is a variable in the value parameter.

		If it is a variable try to get the value from the variables.

		Variables start with the character $.
	*/
	const QString& RuleNode::variableToValue( const QString& value, QHash<QString, QString>& variables )
	{
		if(value.at(0) == '$')
		{
			QString variableName = value.mid(1); // Get the variable name, removes $

			QHash<QString,QString>::const_iterator it = variables.find( variableName);
			if( it != variables.end()  )
			{
				return it.value();
			}
		}

		return value;
	}
}
