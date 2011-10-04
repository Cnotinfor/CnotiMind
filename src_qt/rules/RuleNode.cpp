#include <QtCore/QString>
#include <QtCore/QListIterator>
#include <QRegExp>
#include <QDebug>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RuleNode::RuleNode( Brain* brain, QObject* parent ):
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



		// calls exec for each children;
		while(it.hasNext())
		{
			QObject* obj = it.next();

			RuleNode* node = qobject_cast<RuleNode*>( obj );

			info += node->info( depth + 1 );
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
		Check if in the value string there are variable or property tags

		If it is a variable tag try to get the value from the variables lists.

		Variables tags are betweeen square brackets [].
		Property tags are between curl brackets {}.

		If the variable/property tag is not found, it is replaced by an empty string.
	*/
	void RuleNode::tagsToValue( QString& value, const QHash<QString, QString>& variables )
	{
		static QString empty;

		// VARIABLES
		QRegExp regex_variables_tags( "(\\[[a-zA-Z0-9_\\- \\.]+\\])", Qt::CaseInsensitive );
		// Search for variable value is between square brackets
		int pos = 0;
		while( (pos = regex_variables_tags.indexIn( value, pos ) ) != -1 )
		{
			QString var = regex_variables_tags.cap( 1 );
			//pos += regex.matchedLength();

			// Search for the variable in the variables list
			QHash<QString,QString>::const_iterator it = variables.find( var );
			if( it != variables.end()  )
			{
				// found it, replace by the variable tag, by the variable value
				value.replace( var, it.value(), Qt::CaseInsensitive );
				pos += it.value().length();
			}
			else
			{
				// not found replace by an empty string
				value.replace( var, empty, Qt::CaseInsensitive );
			}
		}

		// PROPERTIES
		QRegExp regex_properties_tags( "\\{([a-zA-Z0-9_\\- \\.]+)\\}", Qt::CaseInsensitive );
		// Search for variable value is between curl brackets
		pos = 0;
		while( (pos = regex_properties_tags.indexIn( value, pos ) ) != -1 )
		{
			QString var = regex_properties_tags.cap( 1 );

			// Search for the variable in the variables list
			QHash<QString,QString>::const_iterator it = _brain->_properties.find( var );
			if( it != _brain->_properties.end()  )
			{
				// found it, replace by the property tag, by the property value
				value.replace( "{" + var + "}", it.value(), Qt::CaseInsensitive );
				pos += it.value().length();
			}
			else
			{
				// not found replace by an empty string
				value.replace( var, empty, Qt::CaseInsensitive );
			}
		}

	}


	QString RuleNode::space(int depth) const
	{
		QString space = "\n";
		for( int i=0; i < depth; i++ )
		{
			space += "\t";
		}

		return space;
	}
}
