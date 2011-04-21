#if !defined(_ROOTNODE_H)
#define _ROOTNODE_H

#include <QtCore/QString>
#include <QtCore/QList>

#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class RootNode : public RuleNode
	{
		Q_OBJECT

	public:
		RootNode( Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		bool isRoot() const;

		QString info( int depth = 0 ) const;
	};

}
#endif  //_ROOTNODE_H
