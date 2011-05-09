#ifndef PROPERTYNODE_H
#define PROPERTYNODE_H

#include <QObject>

#include "RuleNode.h"

namespace CnotiMind
{

	class PropertyNode : public RuleNode
	{
		Q_OBJECT

	public:
		PropertyNode( const QString& key, const QString& value, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

	protected:
		QString _key;
		QString _value;
	};

}

#endif // PROPERTYNODE_H
