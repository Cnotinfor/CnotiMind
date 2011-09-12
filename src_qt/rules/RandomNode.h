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


		virtual void exec();
		virtual void exec( QHash<QString, QString>& variables );

		virtual QString info( int depth = 0 ) const;

		static RandomNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );
	};

}

#endif // RANDOMNODE_H
