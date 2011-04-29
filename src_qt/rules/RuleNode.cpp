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

	/*
		Writes the information about the node and child nodes

		Depth parameter is to be used internally to beatify the output
	*/
	QString RuleNode::info( int depth ) const
	{
		QString info;
		QListIterator<QObject*> it( children() );

		QString s = space( depth );

		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );


			info += s + node->info( depth + 1 );
		}

		return info;
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
		Check if there is a variable in the value parameter name.

		If it is a variable try to get the value from the variables.

		Variables are betweeen square brackets [].

		If the variable is not found, it return an empty QString
	*/
	const QString& RuleNode::variableToValue( const QString& value, QHash<QString, QString>& variables )
	{
		static QString empty;
		// A variable is between square brackets
		if(value.at(0) == '[' && value.at( value.size() - 1 ) == ']')
		{
			QHash<QString,QString>::const_iterator it = variables.find( value );
			if( it != variables.end()  )
			{
				return it.value();
			}
			return empty;
		}

		return value;
	}


	QString RuleNode::space(int depth) const
	{
		QString space = "\n";
		for( int i=0; i <= depth; i++ )
		{
			space += "\t";
		}

		return space;
	}
}
